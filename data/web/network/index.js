class Network {
    async onLoad() {
        network.apName = await Util.waitForElementById('apName');
        network.apPassword = await Util.waitForElementById('apPassword');
        
        const r = await fetch('/api/config/network');
        network.config = new NetworkConfig(await r.bytes());

        network.apName.value = network.config.ssid;
        network.apPassword.value = network.config.password;
        
        network.isReady = true;
    }

    save(e) {
        e.preventDefault();

        if (!(
            network.isReady
            && network.apName.reportValidity()
            && network.apPassword.reportValidity()
        )) {
            return;
        }

        network.config.enabled = true;
        network.config.ssid = network.apName.value.trim();
        network.config.password = network.apPassword.value.trim();

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
