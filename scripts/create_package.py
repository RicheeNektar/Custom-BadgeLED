import os
import re
import zlib

PADDING = False

FILES_DIR = 'data/web/'
FIRMWARE_PATH = '.pio/build/esp32-s3-devkitc-1/firmware.bin'

def open_write(path):
    if os.name == "nt":
        return os.open(path, os.O_CREAT | os.O_WRONLY | os.O_BINARY)
    else:
        return os.open(path, os.O_CREAT | os.O_WRONLY)

def open_read(path):
    if os.name == "nt":
        return os.open(path, os.O_CREAT | os.O_RDONLY | os.O_BINARY)
    else:
        return os.open(path, os.O_CREAT | os.O_RDONLY)

def get_version():
    f_globals = open('include/Globals.h')
    for line in f_globals:
        match = re.search('iVERSION 0x([0-9a-fA-F]+)', line, re.IGNORECASE)
        if match:
            return int(match.group(1), 16)

    raise BaseException("Version not found")

def calc_web_crc32():
    fd = open_read('web.tmp')

    checksum = 0
    while chunk := os.read(fd, 65536):
        checksum = zlib.crc32(chunk, checksum)
    os.close(fd)

    return checksum

def put_header(fd, files, crc32):
    os.write(fd, get_version().to_bytes(4))
    os.write(fd, crc32.to_bytes(4))
    os.write(fd, os.path.getsize(FIRMWARE_PATH).to_bytes(4))
    os.write(fd, os.path.getsize('web.tmp').to_bytes(4))
    os.write(fd, len(files).to_bytes(4))

    if PADDING:
        os.write(fd, b'\x00\x00\x00\x00') # padding

def get_files(src = ''):
    files = []

    for file in os.scandir(FILES_DIR + src):
        if file.is_dir():
            files.extend(get_files(src + file.name + '/'))
        elif file.is_file():
            files.append({
                'path': src + file.name,
                'file': file,
            })

    return files

def copy(fd, path):
    src_fd = open_read(path)

    while True:
        chunk = os.read(src_fd, 1024)
        if not chunk:
            break
        os.write(fd, chunk)

    os.close(src_fd)

def merge_files(files):
    fd = open_write('web.tmp')

    for f in files:
        path, file = f['path'], f['file']
        os.write(fd, len(path).to_bytes(4))
        os.write(fd, os.path.getsize(file.path).to_bytes(4))
        os.write(fd, bytes(path, 'utf8'))
        copy(fd, FILES_DIR + path)

        if PADDING:
            padding = (len(path) + os.path.getsize(file.path)) % 16
            os.write(fd, b'\x00' * padding)

    os.close(fd)

def put_firmware(fd):
    copy(fd, FIRMWARE_PATH)

def package():
    files = get_files()

    if os.path.exists('led-badge.firm'):
        os.unlink('led-badge.firm')

    if os.path.exists('data/web.crc32'):
        os.unlink('data/web.crc32')

    merge_files(files)
    crc32 = calc_web_crc32()

    crc_fd = open_write('data/web.crc32')
    os.write(crc_fd, crc32.to_bytes(4))
    os.close(crc_fd)

    fd = open_write('led-badge.firm')
    put_header(fd, files, crc32)
    copy(fd, 'web.tmp')
    put_firmware(fd)
    os.close(fd)

    if os.path.exists('web.tmp'):
        os.unlink('web.tmp')

if __name__ == "__main__":
    package()