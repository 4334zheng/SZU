package Test4_2_q2;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

public class FileClient {
    private static final String SERVERIP = "127.0.0.1";
    private static final int SERVERPORT = 12345;
    private static final int CLIENTPORT = 54321;

    public static void main(String[] args) {

        byte[] buf = new byte[100];

        Socket s = new Socket();
        try {
            s.connect(new InetSocketAddress(SERVERIP, SERVERPORT), CLIENTPORT);
            System.out.println("与服务器连接成功");
            InputStream is = s.getInputStream();
            int len = is.read(buf);
            String fileName = new String(buf, 0, len);
            System.out.println("接收到的文件为：" + fileName);
            System.out.println("保存为：" + "1" + fileName);
            //创建输出流，修改文件名
            FileOutputStream fos = new FileOutputStream("1" + fileName);
            int data;
            while (-1 != (data = is.read())) {
                fos.write(data);
            }

            is.close();
            s.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
