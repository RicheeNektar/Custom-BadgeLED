class Display {
    async onLoad() {
        display.name = await Util.waitForElementById('name');
        display.telegram = await Util.waitForElementById('telegram');
        display.description = await Util.waitForElementById('description');

        display.invertColors = await Util.waitForElementById('invertColors');
        display.nameColorRed = await Util.waitForElementById('nameColorRed');

        const r = await fetch('/api/config/display');
        display.config = new DisplayConfig(await r.bytes());

        display.name.value = display.config.name;
        display.telegram.value = display.config.telegram;
        display.description.value = display.config.description;

        display.invertColors.checked = display.config.invertColors;
        display.nameColorRed.checked = display.config.nameColorRed;

        display.isReady = true;
    }

    save(e) {
        e.preventDefault();

        if (!(
            display.isReady
            && display.name.reportValidity()
            && display.telegram.reportValidity()
            && display.description.reportValidity()
        )) {
            return;
        }

        display.config.name = display.name.value.trim();
        display.config.telegram = display.telegram.value.trim();
        display.config.description = display.description.value.trim();

        display.config.invertColors = display.invertColors.checked;
        display.config.nameColorRed = display.nameColorRed.checked;
    }
}

display = new Display();

document.addEventListener('DOMContentLoaded', display.onLoad);
