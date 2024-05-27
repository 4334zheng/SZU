import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws Exception{
        Scanner scanner = new Scanner(System.in);
        String factoryName;
        while (true){
            System.out.println("请输入你要创建的协议连接工厂名（输入exit退出）");
            //接收输入的协议名，使用反射机制创建工厂
            factoryName = scanner.next();
            if(factoryName.equals("exit"))
                break;
            Class<?> factoryClass = Class.forName(factoryName);
            NetworkConnectFactory factory = (NetworkConnectFactory) factoryClass.newInstance();
            //使用工厂创建具体网络连接对象
            Connection connection = factory.createConnection();
        }
    }
}
