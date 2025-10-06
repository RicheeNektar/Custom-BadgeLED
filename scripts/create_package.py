import os
import re

FILES_DIR = 'data/web/'
FIRMWARE_PATH = '.pio/build/esp32-s3-devkitc-1/firmware.bin'

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

def get_version():
    f_globals = open('include/Globals.h')
    for line in f_globals:
        match = re.search('iVERSION 0x([0-9a-fA-F]+)', line, re.IGNORECASE)
        if match:
            return int(match.group(1), 16)

    raise BaseException("Version not found")

def get_firmware_len():
    return os.path.getsize(FIRMWARE_PATH)

def put_header(fd):
    os.write(fd, get_version().to_bytes(4))
    os.write(fd, get_firmware_len().to_bytes(4))

def copy(fd, path):
    src_fd = os.open(path, os.O_RDONLY)
    while True:
        chunk = os.read(src_fd, 1024)
        if not chunk:
            break
        os.write(fd, chunk)
    os.close(src_fd)

def put_files(fd, files):
    os.write(fd, len(files).to_bytes(4))
    for f in files:
        path, file = f['path'], f['file']
        os.write(fd, len(path).to_bytes(4))
        os.write(fd, os.path.getsize(file.path).to_bytes(4))
        os.write(fd, bytes(path, 'ascii'))
        copy(fd, FILES_DIR + path)
    pass

def put_firmware(fd):
    copy(fd, FIRMWARE_PATH)

def package():
    files = get_files()

    fd = os.open('led-badge.firm', os.O_WRONLY | os.O_CREAT)
    put_header(fd)
    put_files(fd, files)
    put_firmware(fd)
    os.close(fd)

    pass

if __name__ == "__main__":
    package()