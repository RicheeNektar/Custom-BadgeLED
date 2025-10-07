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
                console.log(r);
                return r;
            })
            .then(async r => ({status: r.status, content: await r.text()}))
            .then(({status, content}) => {
                switch (status) {
                    case 204:
                        alert('Update erfolgreich');
                        break;
                    case 403:
                    case 400:
                        switch (content) {
                            case 'Invalid firmware file':
                                alert('Veraltete Firmware Datei');
                                break;
                            case 'Invalid version':
                                alert('Ungültige Firmware Datei');
                                break;
                            case 'Missing firmware':
                                alert('Bitte wähle erst eine Datei aus.');
                                break;
                            default:
                                alert('Unbekannter Fehler: ' + content);
                                break;
                        }
                        break;
                    default:
                        alert('Unbekannter Status: ' + status);
                        break;
                }
            }).catch(e => {
                console.error(e);
                alert('Update erfolgreich');
            })
        ;
    }
}

ota = new Ota();

document.addEventListener('DOMContentLoaded', ota.onLoad);
