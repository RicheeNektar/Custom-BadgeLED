class Util {
    static onLoad() {
        for (let link of document.querySelectorAll('#navbarNav a')) {
            if (window.location.pathname.replace(/(.)\/$/, '$1') === link.pathname) {
                link.classList.add('active');
                link.ariaCurrent = 'page';
                break;
            }
        }
    }

    static waitForElementById(id) {
        return new Promise((resolve) => {
            const interval = setInterval(() => {
                const element = document.getElementById(id);
                if (element) {
                    clearInterval(interval);
                    resolve(element);
                }
            }, 100);
        });
    }

    static fillConfigInputs(config) {
        for (let input of document.getElementsByTagName('input')) {
            const key = input.getAttribute('data-config-key');
            if (key) {
                switch (input.type) {
                    case 'checkbox':
                        input.checked = 1 === config[key];
                        break;
                    default:
                        input.value = config[key];
                        break;
                }
                input.dispatchEvent(new Event('input'));
            }
        }

        for (let input of document.getElementsByTagName('select')) {
            const key = input.getAttribute('data-config-key');
            if (key) {
                input.querySelector(`option[value='${config[key]}']`).selected = true;
            }
        }
    }
}

document.addEventListener('DOMContentLoaded', Util.onLoad);
