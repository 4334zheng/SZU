public class Computer {
    private String cpu;
    private String ram;//内存
    private String disk;//硬盘
    private String host;//主机
    private String monitor;//显示器

    public String getMonitor() {
        //如果为空，则抛出异常，交给调用者处理
        if (monitor == null) {
            throw new RuntimeException("服务器没有显示器");
        }
        return monitor;
    }

    public void setMonitor(String monitor) {
        this.monitor = monitor;
    }

    public String getCpu() {
        return cpu;
    }

    public void setCpu(String cpu) {
        this.cpu = cpu;
    }

    public String getRam() {
        return ram;
    }

    public void setRam(String ram) {
        this.ram = ram;
    }

    public String getDisk() {
        return disk;
    }

    public void setDisk(String disk) {
        this.disk = disk;
    }

    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }
}
