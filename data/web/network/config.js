class NetworkConfig extends Config {
    deserialize(buffer) {
        this.enabled = buffer.read() === 1;
        this.ssid = buffer.readText();
        this.password = buffer.readText();
    }

    serialize(buffer) {
        buffer.write(this.enabled);
        buffer.writeText(this.ssid);
        buffer.writeText(this.password);
    }
}