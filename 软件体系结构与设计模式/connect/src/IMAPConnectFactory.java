public class IMAPConnectFactory implements NetworkConnectFactory {
    public Connection createConnection(){
        System.out.println("创建IMAP连接");
        return new IMAPConnection();
    }
}
