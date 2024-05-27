public class ComputerAssembleDirector {
    ComputerBuilder cb;
    public void setCb(ComputerBuilder cb){
        this.cb = cb;
    }
    public Computer assemble(){
        cb.buildCpu();
        cb.buildRam();
        cb.buildDisk();
        cb.buildHost();
        cb.buildMonitor();
        return cb.getComputer();
    }
}
