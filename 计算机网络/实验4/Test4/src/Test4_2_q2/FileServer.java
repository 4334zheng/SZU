package Test4_2_q2;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class FileServer implements Runnable{

    private static final int MONITORPORT  = 12345;
    private Socket s ;

    public FileServer(Socket s) {
        super();
        this.s = s;
    }

    public static void server()
    {
        try {
            ServerSocket ss = new ServerSocket(MONITORPORT);
            int i=0;
            while(true)
            {
                i++;
                Socket s = ss.accept(); //与客户端进行连接并存放到s中
                System.out.println("服务器的线程"+i+"启动,与客户端1连接成功");

                new Thread(new FileServer(s)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        FileServer.server();
    }

    @Override
    public void run() {
        byte[] buf = new byte[100];
        OutputStream os=null;
        FileInputStream fins=null;
        try {
            os = s.getOutputStream();

            String fileName = "test.txt";

            System.out.println("要传输的文件为: "+fileName);

            os.write(fileName.getBytes());
            System.out.println("开始传输文件");
            fins = new FileInputStream(fileName);
            int data;
            while(-1!=(data = fins.read()))
            {
                os.write(data);
            }
            System.out.println("文件传输结束");
        } catch (IOException e) {
            e.printStackTrace();
        }finally
        {
            try {
                if(fins!=null) fins.close();
                if(os!=null)	os.close();
                this.s.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}