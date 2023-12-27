//服务器端
package Test4_2_q1;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class Server {
    public static void main(String[] args) {
        try {
            ServerSocket server = new ServerSocket(6789);
            System.out.println("服务器启动完毕");
            Socket socket=server.accept();//等待连入请求，并创建客户连接
            System.out.println("创建客户连接");
            BufferedReader reader;
            //创建与套接字连接的输入流，接收信息使用BufferedReader读取
            reader=new BufferedReader(new InputStreamReader(socket.getInputStream()));

            while (true) {
                String str = reader.readLine();
                DataOutputStream ToClient=new DataOutputStream(socket.getOutputStream());
                //如果接收到“exit”，打印"bye"，退出
                if (str.equals("Exit")) {
                    ToClient.writeBytes("Bye\n");
                    System.out.println("Bye");
                    break;
                }
                //如果收到"Time"，将服务器端当前时间返回给客户端
                if(str.equals("Time")) {
                    Calendar calendar=Calendar.getInstance();
                    //设置日期格式
                    SimpleDateFormat dateformat= new SimpleDateFormat("yyyy-MM-dd  :hh:mm:ss ");
                    System.out.println("服务器当前的时间为:"+dateformat.format(calendar.getTime()));
                    String str1="Current Client Time is:"+dateformat.format(calendar.getTime());
                    ToClient.writeBytes(str1+"\n");
                }
            }
            reader.close();
            socket.close();
            server.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}