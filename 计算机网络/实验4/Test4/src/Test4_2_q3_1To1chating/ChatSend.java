package Test4_2_q3_1To1chating;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 消息发送端线程
 */
public class ChatSend implements Runnable {
    private DatagramSocket client;// 发送端
    BufferedReader br; // 输入流
    private String toIp;// 发送目标ip
    private int toPort;// 发送目标端口 和接收端使用端口一致
    public ChatSend(int port, String toIp, int toPort) {
        this.toIp = toIp;
        this.toPort = toPort;
        try {
            client = new DatagramSocket(port);
            br = new BufferedReader(new InputStreamReader(System.in));
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }
    @Override
    public void run() {
        while (true) {
            try {
                // 准备数据 一定转成字节数组
                String data = br.readLine();
                byte[] datas = data.getBytes();
                // 封装成DatagramPacket 包裹，需要指定地址
                DatagramPacket packet = new DatagramPacket(datas, 0, datas.length,
                        new InetSocketAddress(this.toIp, this.toPort));
                // 输出发送时间
                SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                System.out.println("发送 " + format.format(new Date()));
                // 发送包裹
                client.send(packet);
                if(data.equals("bye")) {
                    break;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        // 释放资源
        client.close();
    }
}

