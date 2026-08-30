class Display {
    async onLoad() {
        display.name = await Util.waitForElementById('name');
        display.telegram = await Util.waitForElementById('telegram');
        display.description = await Util.waitForElementById('description');
        display.invertColors = await Util.waitForElementById('invert-colors');
        display.redName = await Util.waitForElementById('red-name');
        display.formConfig = await Util.waitForElementById('form-config');

        display.formConfig.addEventListener('submit', display.save);

        const r = await fetch('/api/config/display');
        display.config = new DisplayConfig(await r.bytes());

        display.name.value = display.config.name;
        display.telegram.value = display.config.telegram;
        display.description.value = display.config.description;
        display.invertColors.checked = display.config.invertColors;
        display.redName.checked = display.config.redName;

        Util.loadingModal.hide();
    }

    save(e) {
        e.preventDefault();

        display.config.name = display.name.value.trim();
        display.config.telegram = display.telegram.value.trim();
        display.config.description = display.description.value.trim();
        display.config.invertColors = display.invertColors.checked;
        display.config.redName = display.redName.checked;
    }
}

display = new Display();

document.addEventListener('DOMContentLoaded', display.onLoad);
