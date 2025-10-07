class Buffer {
    constructor(data = []) {
        this.read.bind(this);
        this.readText.bind(this);
        this.write.bind(this);
        this.writeText.bind(this);
        this.toBase64.bind(this);

        this.data = data;
        this.position = 0;
    }

    read(length = 1) {
        if (length === 1) {
            return this.data[this.position++];
        }
        return this.data.slice(this.position, this.position += Math.min(length, this.data.length - this.position));
    }

    readText() {
        const length = this.read(1);
        return new TextDecoder().decode(this.read(length));
    }

    write(data) {
        if (typeof data === 'number') {
            this.data[this.position++] = data;

        } else if (typeof data === 'boolean') {
            this.data[this.position++] = data ? 1 : 0;

        } else if (typeof data[Symbol.iterator] === 'function') {
            this.data.push(...data);
            this.position += data.length;

        } else if (data === undefined || data === null) {
            this.data[this.position++] = 0;

        } else {
            throw new Error('Invalid data type: ' + typeof data);
        }
    }

    writeText(text) {
        const encoder = new TextEncoder();
        if (text.length > 0) {
            this.write(text.length);
            this.write(encoder.encode(text));
        } else {
            this.write(0);
        }
    }

    toBase64() {
        return new Uint8Array(this.data).toBase64();
    }
}