public class Server extends ComputerBuilder{
    public void buildCpu(){
        computer.setCpu("Server's Cpu");
    }
    public void buildRam(){
        computer.setRam("Server's 内存");
    }
    public void buildDisk(){
        computer.setDisk("Server's 硬盘");
    }
    public void buildHost(){
        computer.setHost("Server's 主机");
    }
    public void buildMonitor(){
        //服务器没有主机，所以为空方法
    }
}
