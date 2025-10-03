class Config {
    constructor(uint8array) {
        this.serialize.bind(this);
        this.deserialize.bind(this);
        this.toBase64.bind(this);

        this.deserialize(new Buffer(uint8array));
    }

    toBase64() {
        const buffer = new Buffer();
        this.serialize(buffer);
        return buffer.toBase64();
    }

    serialize(buffer) {}

    deserialize(buffer) {}
}
