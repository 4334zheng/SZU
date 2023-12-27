//客户机端
package Test4_2_q1;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Objects;
import java.util.Scanner;

public class Client {
    static String hostname = new String("localhost");
    public static void main(String[] args) {
        try {
            //client端创建一个socket，与服务器连接
            Socket ClientSocket = new Socket(hostname, 6789);

            //创建与socket连接的输出流，定义为out
            DataOutputStream out = new DataOutputStream(ClientSocket.getOutputStream());
            BufferedReader reader;
            reader=new BufferedReader(new InputStreamReader(ClientSocket.getInputStream()));

            String sentence;
            String modifiedSentence;
            while(true){ //可以多次输入Time，直到输入Exit才结束
                BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
                sentence = inFromUser.readLine();
                out.writeBytes(sentence+'\n');
                modifiedSentence = reader.readLine();
                System.out.println("From Server:" + modifiedSentence);
                if(sentence.equals("Exit")){
                    break;
                }
            }
            ClientSocket.close();
            out.close();
            reader.close();
        } catch (UnknownHostException e) {
            System.out.println("UnknownHost");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}