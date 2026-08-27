
let ledsEnabled = true;

function updateValue(param, value) {
    const xhr = new XMLHttpRequest();
    xhr.open('POST', `/?param=${param}&value=${value}`, true);
    xhr.send();

    const displayElement = document.getElementById(param + 'Value');
    if (displayElement) {
        displayElement.textContent = value;
    }
}

function updateSpeedValue(sliderValue) {
    const xhr = new XMLHttpRequest();
    xhr.open("GET", `/settings?param=speed&value=${invertedValue}`, true);
    xhr.send();

    const displayElement = document.getElementById('speedValue');
    if (displayElement) {
        displayElement.textContent = invertedValue;
    }
}

function toggleLEDs() {
    const button = document.getElementById('ledControlButton');
    ledsEnabled = !ledsEnabled;

    if (ledsEnabled) {
        button.textContent = 'LEDs ausschalten';
        button.classList.remove('on');
    } else {
        button.textContent = 'LEDs einschalten';
        button.classList.add('on');
    }

    fetch(`/toggle-leds?enabled=${ledsEnabled ? 1 : 0}`)
        .then(response => response.text())
        .then(result => {
            console.log('LED-Steuerung: ' + result);
        })
        .catch(error => {
            console.error('Fehler bei LED-Steuerung:', error);
        });
}

document.addEventListener('DOMContentLoaded', function () {
    fetchLogs().then(text => document.getElementById('logs').innerText = text);

    fetch('/values')
        .then(response => response.json())
        .then(data => {
            const setValue = (name) => {
                document.getElementById(name).value = data[name];
                const value = document.getElementById(`${name}Value`);
                if (value) {
                    value.textContent = data[name];
                }
            }

            setValue('mode');
            setValue('speed');
            setValue('brightness');
            setValue('sensitivity');
            setValue('frequency');

            if (data.primaryColor !== undefined) {
                const primaryBoxes = document.querySelectorAll('.control-group:nth-child(2) .color-box');
                const primaryIndex = Math.floor(data.primaryColor / 16);
                if (primaryBoxes[primaryIndex]) {
                    primaryBoxes[primaryIndex].classList.add('selected');
                }
            }
            if (data.secondaryColor !== undefined) {
                const secondaryBoxes = document.querySelectorAll('.control-group:nth-child(3) .color-box');
                const secondaryIndex = Math.floor(data.secondaryColor / 16);
                if (secondaryBoxes[secondaryIndex]) {
                    secondaryBoxes[secondaryIndex].classList.add('selected');
                }
            }

            if (data.ledsEnabled !== undefined) {
                ledsEnabled = data.ledsEnabled;
                const button = document.getElementById('ledControlButton');
                if (!ledsEnabled) {
                    button.textContent = 'LEDs einschalten';
                    button.classList.add('on');
                }
            }
        });
});

function updateBatteryInfo() {
    console.log('🔍 updateBatteryInfo() gestartet');
    fetch('/battery-status')
        .then(response => {
            console.log('🔍 Response erhalten:', response.status, response.statusText);
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.json();
        })
        .then(data => {
            console.log('🔍 Batterie-Daten erhalten:', data);
            // Spannungen
            document.getElementById('batteryVoltage').textContent = data.vbat.toFixed(2) + 'V';
            document.getElementById('batterySystemVoltage').textContent = data.vsys.toFixed(2) + 'V';
            document.getElementById('batteryBusVoltage').textContent = data.vbus.toFixed(2) + 'V';

            // Prozentsatz
            document.getElementById('batteryPercentage').textContent = data.percentage + '%';

            // Batteriestand-Balken aktualisieren
            const batteryLevel = document.getElementById('batteryLevel');
            batteryLevel.style.width = data.percentage + '%';

            // Farbe je nach Ladezustand
            batteryLevel.className = 'battery-level';
            if (data.percentage < 20) {
                batteryLevel.classList.add('critical');
            } else if (data.percentage < 50) {
                batteryLevel.classList.add('low');
            }

            // Ladezustand
            const chargingIcon = document.getElementById('chargingIcon');
            if (data.isCharging) {
                chargingIcon.style.display = 'inline';
                chargingIcon.innerHTML = '&#x26A1;'; // HTML-kodiertes Blitzsymbol
                document.getElementById('batteryStatus').textContent = 'Wird geladen';
            } else {
                chargingIcon.style.display = 'none';
                document.getElementById('batteryStatus').textContent = 'Entladen';
            }

            document.getElementById('batteryCurrent').textContent = data.ichg.toFixed(0) + ' mA';
            document.getElementById('batteryPower').textContent = data.power.toFixed(3) + ' W';
            document.getElementById('batteryChargeStatus').textContent = data.chargeStatus;
        })
        .catch(error => {
            console.error('❌ Fehler beim Abrufen der Akku-Daten:', error);
            document.getElementById('batteryVoltage').textContent = 'Fehler';
            document.getElementById('batteryPercentage').textContent = '?%';
        });
}

function setChargeCurrent(mA) {
    fetch(`/set-charge-current?current=${mA}`);
}

function fetchLogs() {
    return fetch('/logs')
        .then(response => response.text())
        .catch(console.error);
}

function rebootESP() {
    if (confirm('ESP32 wirklich neu starten? Die Verbindung wird kurz unterbrochen.')) {
        fetch('/reboot')
            .then(response => response.text())
            .then(result => {
                alert('ESP32 wird neu gestartet. Bitte warten Sie 10-15 Sekunden und laden Sie die Seite neu.');
            })
            .catch(error => {
                console.error('Fehler beim Neustart:', error);
                alert('Neustart wurde gesendet. Bitte warten Sie 10-15 Sekunden und laden Sie die Seite neu.');
            });
    }
}