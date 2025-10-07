class DisplayConfig extends Config {
    deserialize(buffer) {
        this.nameColorRed = buffer.read() === 1;
        this.invertColors = buffer.read() === 1;

        this.name = buffer.readText();
        this.telegram = buffer.readText();

        this.description = buffer.readText() + "\n"
            + buffer.readText() + "\n"
            + buffer.readText();
    }

    serialize(buffer) {
        buffer.write(this.nameColorRed);
        buffer.write(this.invertColors);

        buffer.writeText(this.name);
        buffer.writeText(this.telegram);

        this.description.split("\n").forEach(buffer.writeText);
    }
}