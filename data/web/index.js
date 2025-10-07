
const colors = [
    { hue: 0,   value: 0,   title: "Rot" },
    { hue: 30,  value: 21,  title: "Orange" },
    { hue: 60,  value: 43,  title: "Gelb" },
    { hue: 90,  value: 64,  title: "Gelbgr&uuml;n" },
    { hue: 120, value: 85,  title: "Gr&uuml;n" },
    { hue: 150, value: 107, title: "Gr&uuml;ncyan" },
    { hue: 180, value: 128, title: "Cyan" },
    { hue: 210, value: 149, title: "Blau" },
    { hue: 240, value: 171, title: "Blauviolett" },
    { hue: 270, value: 192, title: "Violett" },
    { hue: 300, value: 213, title: "Magenta" },
    { hue: 330, value: 235, title: "Rosa" },
    { hue: 15,  value: 11,  title: "Rotorange" },
    { hue: 45,  value: 32,  title: "Goldgelb" },
    { hue: 75,  value: 53,  title: "Hellgr&uuml;n" },
    { hue: 195, value: 139, title: "Himmelblau" },
];

const buildColors = (name) => {
    document.getElementById(name).append(
        ...colors.map(({hue, value, title}) => {
            const label = document.createElement('label');
            label.classList.add('color-box');
            label.style.backgroundColor = `hsl(${hue}, 100%, 50%)`;
            label.title = title;

            const input = document.createElement('input');
            input.type = "radio";
            input.name = name;
            input.value = value;

            label.appendChild(input);
            return label;
        }),
    );
}

buildColors('primary');
buildColors('secondary');

let ledsEnabled = true;
let currentLogType = 'esp';

let espLogs = [];
let bqLogs = [];

const maxLogLines = 100;
const maxAnimationSpeed = 50; // in ms

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
    const invertedValue = maxAnimationSpeed - parseInt(sliderValue);

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
    fetch(`/set-charge-current?current=${mA}`)
        .then(response => response.text())
        .then(result => {
            console.log('Ladestrom ge&auml;ndert: ' + result);
            addLogEntry('esp', 'Ladestrom auf ' + mA + ' mA gesetzt');
        })
        .catch(error => {
            console.error('Fehler bei Ladestrom-Einstellung:', error);
        });
}

function switchTab(logType) {
    document.getElementById('esp-logs').style.display = logType === 'esp' ? 'block' : 'none';
    document.getElementById('bq-logs').style.display = logType === 'bq' ? 'block' : 'none';

    const buttons = document.querySelectorAll('.tab-button');
    buttons.forEach(btn => {
        btn.classList.remove('active');
    });

    const activeButton = Array.from(buttons).find(btn =>
        btn.textContent.toLowerCase().includes(logType));
    if (activeButton) {
        activeButton.classList.add('active');
    }

    currentLogType = logType;
}

function clearLogs() {
    if (currentLogType === 'esp') {
        espLogs = [];
        document.getElementById('esp-logs').innerHTML = '';
    } else {
        bqLogs = [];
        document.getElementById('bq-logs').innerHTML = '';
    }

    // Auch auf dem Server l&ouml;schen
    fetch('/clear-logs?type=' + currentLogType)
        .then(response => response.text())
        .then(result => {
            console.log('Logs gel&ouml;scht: ' + result);
        });
}

function addLogEntry(type, message) {
    const timestamp = new Date().toLocaleTimeString();
    const logEntry = `[${timestamp}] ${message}`;

    if (type === 'esp') {
        espLogs.push(logEntry);
        if (espLogs.length > maxLogLines) {
            espLogs.shift();
        }
        updateLogDisplay('esp-logs', espLogs);
    } else {
        bqLogs.push(logEntry);
        if (bqLogs.length > maxLogLines) {
            bqLogs.shift();
        }
        updateLogDisplay('bq-logs', bqLogs);
    }
}

function updateLogDisplay(containerId, logs) {
    const container = document.getElementById(containerId);
    const wasScrolledToBottom = container.scrollHeight - container.scrollTop === container.clientHeight;

    container.innerHTML = logs.join('<br>');

    // Check if user did scroll, so we do not jump around
    if (wasScrolledToBottom) {
        container.scrollTop = container.scrollHeight;
    }
}

function fetchLogs() {
    console.log('🔍 fetchLogs() gestartet');
    fetch('/get-logs')
        .then(response => {
            console.log('🔍 Logs Response:', response.status, response.statusText);
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.json();
        })
        .then(data => {
            console.log('🔍 Log-Daten erhalten:', data);
            if (data.esp && data.esp.length > 0) {
                espLogs = data.esp;
                updateLogDisplay('esp-logs', espLogs);
            }

            if (data.bq && data.bq.length > 0) {
                bqLogs = data.bq;
                updateLogDisplay('bq-logs', bqLogs);
            }
        })
        .catch(error => {
            console.error('❌ Fehler beim Abrufen der Logs:', error);
        });
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