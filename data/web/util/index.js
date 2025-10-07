class Util {
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
}