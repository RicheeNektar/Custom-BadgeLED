class Index {
    async onLoad() {
        index.logsWarning = await Util.waitForElementById('logs-warning');
        index.logsBody = await Util.waitForElementById('logs-body');

        const r = await fetch('/api/config/animation');
        index.config = new AnimationConfig(await r.bytes());

        Util.fillConfigInputs(index.config);

        await index.updateLogs();
        setInterval(index.updateLogs, 5000);
    }

    async updateLogs() {
        const response = await fetch('/api/logs');

        const logs = (await response.text())
            .replace('\r', '')
            .split("\n")
        ;

        if (logs.find(log => log.charAt(2) === '1')) {
            index.logsWarning.classList.remove('d-none');
        }

        index.logsBody.replaceChildren(
            ...logs.map(
                log => {
                    const p = document.createElement('p');
                    p.textContent = log.substring(3);
                    if ('1' === log.charAt(2)) {
                        p.classList.add('text-danger');
                    }
                    return p;
                }
            ),
        );
    }
}

index = new Index();

document.addEventListener('DOMContentLoaded', index.onLoad);
