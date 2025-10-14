#ifndef FIRMWARE_H
#define FIRMWARE_H

#include <FS.h>

#define TEMP_FIRMWARE_PATH "/firmware.tmp"
#define WEB_PATH_NEW "/web.new/"
#define WEB_PATH "/web/"

#define UPDATE_RESULT_SUCCESS            0x00
#define UPDATE_RESULT_MISSING_FIRMWARE   0x01
#define UPDATE_RESULT_INVALID_VERSION    0x02
#define UPDATE_RESULT_OUTDATED_VERSION   0x03
#define UPDATE_RESULT_FILE_PATH_TOO_LONG 0x04
#define UPDATE_RESULT_NONE               0xFF

#define UPDATE_STATUS_IDLE        0x0
#define UPDATE_STATUS_UPLOADING   0x1
#define UPDATE_STATUS_IN_PROGRESS 0x2
#define UPDATE_STATUS_ERROR       0x3
#define UPDATE_STATUS_SUCCESS     0x4

class  Firmware {
    static void removeIfExists(const char* path);

public:
    static void cleanup(File* file);

    static void update();
};

extern uint8_t UPDATE_STATUS;
extern uint8_t UPDATE_RESULT;

#endif //FIRMWARE_H
