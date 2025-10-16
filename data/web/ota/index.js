class Ota {
    async onLoad() {
        ota.form = await Util.waitForElementById('ota-form');
        ota.form.addEventListener('submit', ota.onSubmit);

        ota.firmware = await Util.waitForElementById('firmware');
        ota.firmware.addEventListener('change', ota.onChange);

        const vResponse = await fetch('/version');
        const vElement = await Util.waitForElementById('current_version');
        if (vResponse.status === 200) {
            vElement.innerHTML = await vResponse.text();
        } else {
            vElement.innerHTML = `N/A`;
        }

        ota.selectedVersion = await Util.waitForElementById('selected_version');

        ota.isReady = true;
    }

    async onChange(e) {
        if (ota.firmware.files[0]) {
            const vBuffer = await ota.firmware.files[0].slice(1, 4).text();
            ota.selectedVersion.innerHTML = `v${vBuffer.charCodeAt(0)}.${vBuffer.charCodeAt(1)}.${vBuffer.charCodeAt(2)}`;
        } else {
            ota.selectedVersion.innerHTML = ``;
        }
    }

    onSubmit(e) {
        e.preventDefault();

        if (!(
            ota.isReady
            || ota.firmware.reportValidity()
        )) {
            return;
        }

        const data = new FormData();
        data.append('firmware', ota.firmware.files[0]);

        fetch('/ota/update', {
            method: 'POST',
            body: data,
        })
            .then(r => {
                if (
                       r.status === 201 // Started
                    || r.status === 400 // Already running
                ) {
                    ota.checkInterval = setInterval(
                        () => {
                            fetch('/ota/update')
                                .then(async r => {
                                    switch (r.status) {
                                        case 204:
                                            // wait
                                            return;
                                        case 200:
                                            alert("Update erfolgreich. Badge startet in kurze neu...");
                                            clearInterval(ota.checkInterval);
                                            return;
                                        case 400:
                                            alert(await r.text());
                                            clearInterval(ota.checkInterval);
                                            return;
                                        default:
                                            alert("Unbekannter status code: " + r.status);
                                            clearInterval(ota.checkInterval);
                                            return;
                                    }
                                })
                            ;
                        },
                        1000
                    );
                } else {
                    alert("Fehler beim starten des Updates: " + r.status);
                }
            })
        ;
    }
}

ota = new Ota();

document.addEventListener('DOMContentLoaded', ota.onLoad);
