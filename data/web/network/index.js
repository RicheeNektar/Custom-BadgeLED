class Network {
    async onLoad() {
        network.ssid = await Util.waitForElementById('ssid');
        network.password = await Util.waitForElementById('password');

        network.form = await Util.waitForElementById('network-form');
        network.form.addEventListener('submit', network.save);
        
        const r = await fetch('/api/config/network');
        network.config = new NetworkConfig(await r.bytes());

        network.ssid.value = network.config.ssid;
        network.password.value = network.config.password;

        Util.loadingModal.hide();
    }

    save(e) {
        e.preventDefault();

        if (!(
            network.ssid.reportValidity()
            && network.password.reportValidity()
        )) {
            return;
        }

        network.config.enabled = true;
        network.config.ssid = network.ssid.value.trim();
        network.config.password = network.password.value.trim();

        fetch('/api/config/network', {
            method: 'POST',
            body: network.config.toBase64(),
            headers: {
                'Content-Type': 'application/octet-stream',
            },
        }).then(() => location.reload());
    }
}

network = new Network();

document.addEventListener('DOMContentLoaded', network.onLoad);
