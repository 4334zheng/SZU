public class Client{
    public static void main(String[] args){
        ComputerBuilder cb = (ComputerBuilder) XMLUtil.getBean();
        ComputerAssembleDirector director = new ComputerAssembleDirector();
        director.setCb(cb);
        Computer computer = director.assemble();
        System.out.println("计算机组成");
        System.out.println(computer.getCpu());
        System.out.println(computer.getRam());
        System.out.println(computer.getDisk());
        System.out.println(computer.getHost());
        try{
            System.out.println(computer.getMonitor());
        }catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
}
