public class POP3ConnectFactory implements NetworkConnectFactory {
    public Connection createConnection(){
        System.out.println("创建POP3连接");
        return new POP3Connection();
    }
}
