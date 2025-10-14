class Ota {
    async onLoad() {
        ota.form = await Util.waitForElementById('ota-form');
        ota.form.addEventListener('submit', ota.onSubmit);

        ota.firmware = await Util.waitForElementById('firmware');

        ota.isReady = true;
    }

    onSubmit(e) {
        console.log(e);
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
                                            alert("Update erfolgreich. Badge startet in kürze neu...");
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
