import os
from re import search
from pathlib import Path
from zlib import crc32
from functools import partial

FIRMWARE_PATH = ".pio/build/esp32-s3-devkitc-1/firmware.bin"
FILES_DIR = "data/web/"
WEB_TMP_PATH = "web.tmp"
PACKAGE_NAME = "led-badge.firm"

PATHS = list(Path(FILES_DIR).rglob("*.*"))
WEB_CRC32 = 0

def open_write(path):
    return open(path, "wb")

def open_read(path):
    return open(path, "rb")

def copy(from_fd, to_fd):
    for chunk in iter(partial(from_fd.read, 1024), b""):
        to_fd.write(chunk)

def copy_path(to_fd, path):
    with open_read(path) as from_td:
        copy(from_td, to_fd)

def merge_web_files():
    global WEB_CRC32

    if WEB_CRC32 != 0:
        return

    with open_write(WEB_TMP_PATH) as fd:
        for path in PATHS:
            relative_path = path.relative_to(FILES_DIR)
            if relative_path.match(WEB_TMP_PATH):
                continue
            fd.write(len(str(relative_path)).to_bytes(4))
            fd.write(os.path.getsize(path).to_bytes(4))
            fd.write(bytes(str(relative_path), 'utf8'))
            copy_path(fd, path)

    with open_read(WEB_TMP_PATH) as fd:
        for chunk in iter(partial(fd.read, 65536), b""):
            WEB_CRC32 = crc32(chunk, WEB_CRC32)

def get_version():
    with open("include/Globals.h") as f_globals:
        for line in f_globals:
            if match := search("iVERSION 0x([0-9a-f]+)", line):
                return int(match.group(1), 16)
    raise BaseException("Version not found")

def put_header(fd):
    fd.write(bytes("richee/custom-badgeled", "ascii"))
    fd.write(get_version().to_bytes(4))
    fd.write(WEB_CRC32.to_bytes(4))
    fd.write(os.path.getsize(FIRMWARE_PATH).to_bytes(4))
    fd.write(os.path.getsize(WEB_TMP_PATH).to_bytes(4))
    fd.write(len(PATHS).to_bytes(4))

def put_web(fd):
    copy_path(fd, WEB_TMP_PATH)

def put_firmware(fd):
    copy_path(fd, FIRMWARE_PATH)

def write_package():
    with open_write(PACKAGE_NAME) as fd:
        put_header(fd)
        put_web(fd)
        put_firmware(fd)

def clean_up():
    if os.path.exists(WEB_TMP_PATH):
        os.unlink(WEB_TMP_PATH)

if __name__ == "__main__":
    merge_web_files()
    write_package()
    clean_up()
