public class HTTPConnectFactory implements NetworkConnectFactory {
    public Connection createConnection(){
        System.out.println("创建HTTP连接");
        return new HTTPConnection();
    }
}
