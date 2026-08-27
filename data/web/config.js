class AnimationConfig extends Config {
    deserialize(buffer) {
        this.delay = buffer.read() | buffer.read() << 8;
        this.micFrequency = buffer.read() | buffer.read() << 8;
        this.brightness = buffer.read();
        this.mode = buffer.read();
        this.noiseLevel = buffer.read();
        this.primaryHue = buffer.read();
        this.secondaryHue = buffer.read();
    }

    serialize(buffer) {
        buffer.write(this.delay);
        buffer.write(this.delay >> 8);
        buffer.write(this.micFrequency);
        buffer.write(this.micFrequency >> 8);
        buffer.write(this.brightness);
        buffer.write(this.mode);
        buffer.write(this.noiseLevel);
        buffer.write(this.primaryHue);
        buffer.write(this.secondaryHue);
    }
}