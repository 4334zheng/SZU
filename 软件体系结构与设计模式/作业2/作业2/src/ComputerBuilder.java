public abstract class ComputerBuilder {
    protected Computer computer = new Computer();
    public abstract void buildCpu();
    public abstract void buildRam();
    public abstract void buildDisk();
    public abstract void buildHost();
    public abstract void buildMonitor();

    public Computer getComputer() {
        return computer;
    }
}
