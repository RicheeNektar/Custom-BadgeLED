class Ota {
    async onLoad() {
        ota.form = await Util.waitForElementById('ota-form');
        ota.form.addEventListener('submit', ota.onSubmit);

        ota.firmware = await Util.waitForElementById('firmware');
        ota.firmware.addEventListener('change', ota.onChange);

        ota.firmware.feedback = await Util.waitForElementById('firmware-feedback');

        const vResponse = await fetch('/api/version').catch(() => null);
        const vElement = await Util.waitForElementById('current_version');
        if (vResponse?.status === 200) {
            vElement.innerHTML = await vResponse.text();
        } else {
            vElement.innerHTML = `N/A`;
        }

        ota.selectedVersion = await Util.waitForElementById('selected_version');

        ota.isReady = true;
    }

    async onChange(e) {
        ota.firmware.classList.remove('is-valid', 'is-invalid');
        ota.firmware.feedback.classList.add('d-none');
        ota.firmware.invalid = true;

        const file = ota.firmware.files[0] ?? null;
        if (file) {
            const expected = 'richee/custom-badgeled';

            const actual = await file.slice(0, expected.length).text();
            console.log(actual);
            console.log(expected);

            if (expected !== actual) {
                ota.selectedVersion.textContent = '';
                ota.firmware.feedback.textContent = 'Invalid firmware';
                ota.firmware.feedback.classList.remove('d-none');
                ota.firmware.classList.add('is-invalid');
                return;
            }

            // +1 because first byte is unused
            const vBuffer = await file.slice(expected.length + 1, expected.length + 4).text();
            ota.selectedVersion.textContent = `v${vBuffer.charCodeAt(0)}.${vBuffer.charCodeAt(1)}.${vBuffer.charCodeAt(2)}`;
            ota.firmware.classList.add('is-valid');
            ota.firmware.invalid = false;
        } else {
            ota.selectedVersion.textContent = '';
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
