#include "Firmware.h"
#include "LEDS.h"
#include "web/DataWrapper.h"
#include "web/routes/OTA.h"

#include <LittleFS.h>
#include <Update.h>

void Firmware::removeIfExists(const char* path)
{
    if (LittleFS.exists(path))
    {
        LittleFS.remove(path);
    }
}

void Firmware::cleanup(File* file)
{
    if (file)
    {
        file->close();
    }

    removeIfExists(TEMP_FIRMWARE_PATH);
    removeIfExists(WEB_PATH);
}

void Firmware::update()
{
    File firmwareFile = LittleFS.open(TEMP_FIRMWARE_PATH, FILE_READ);

    if (!firmwareFile) {
        cleanup(&firmwareFile);
        UPDATE_STATUS = UPDATE_STATUS_ERROR;
        UPDATE_RESULT = UPDATE_RESULT_MISSING_FIRMWARE;
        return;
    }

    log_i("Starting firmware update...");
    DataWrapper wrapper(&firmwareFile);
    const uint32_t version = wrapper.readUInt32();

    if (
        // The first byte should be 0
        (version & 0xFF000000) != 0
    ) {
        cleanup(&firmwareFile);
        UPDATE_STATUS = UPDATE_STATUS_ERROR;
        UPDATE_RESULT = UPDATE_RESULT_INVALID_VERSION;
        return;
    }

    if (
        version < iVERSION
    ) {
        cleanup(&firmwareFile);
        UPDATE_STATUS = UPDATE_STATUS_ERROR;
        UPDATE_RESULT = UPDATE_RESULT_OUTDATED_VERSION;
        return;
    }

    UPDATE_STATUS = UPDATE_STATUS_IN_PROGRESS;
    LEDS::status(STATUS_LED_ID_MAIN, STATUS_YELLOW);

    const uint32_t firmwareLength = wrapper.readUInt32();
    const uint32_t filesCount = wrapper.readUInt32();

    char buffer[128];

    for (uint32_t i = 0; i < filesCount; i++) {
        const uint32_t filepathLength = wrapper.readUInt32();

        if (filepathLength > 0x7F)
        {
            log_e("%d - %d", i, filepathLength);
            cleanup(&firmwareFile);
            UPDATE_STATUS = UPDATE_STATUS_ERROR;
            UPDATE_RESULT = UPDATE_RESULT_FILE_PATH_TOO_LONG;
            return;
        }

        const uint32_t fileSize = wrapper.readUInt32();

        char filePath[filepathLength + 1];
        wrapper.readBytes(filePath, filepathLength);
        filePath[filepathLength] = '\0';

        log_d("%s - %d", filePath, fileSize);

        File file = LittleFS.open(WEB_PATH + String(filePath), FILE_WRITE, true);

        for (uint32_t pos = 0; pos < fileSize; pos += 128)
        {
            const size_t remaining = fileSize - pos;
            const size_t len = std::min(static_cast<uint32_t>(128), remaining);
            file.write(
                reinterpret_cast<const uint8_t*>(buffer),
                wrapper.readBytes(buffer, len)
            );
        }

        file.flush();
        file.close();
    }

    LittleFS.remove(WEB_PATH);
    LittleFS.rename(WEB_PATH_NEW, WEB_PATH);

    log_i("Web done");

    Update.begin(firmwareLength);
    Update.writeStream(wrapper);
    Update.end();

    cleanup(&firmwareFile);
    UPDATE_STATUS = UPDATE_STATUS_SUCCESS;
    UPDATE_RESULT = UPDATE_RESULT_SUCCESS;
}

uint8_t UPDATE_STATUS = UPDATE_STATUS_IDLE;
uint8_t UPDATE_RESULT = UPDATE_RESULT_NONE;
