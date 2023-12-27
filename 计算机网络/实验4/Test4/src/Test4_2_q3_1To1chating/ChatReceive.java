package Test4_2_q3_1To1chating;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ChatReceive implements Runnable {
    private DatagramSocket server; // 接收端
    private int port; // 接收端使用端口
    private String from; // 发送方标记
    public ChatReceive(int port, String from) {
        this.from = from;
        try {
            server = new DatagramSocket(port);
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) {
            try {
                // 准备容器封装成DatagramPacket 包裹
                byte[] container = new byte[1024 * 60];
                DatagramPacket packet = new DatagramPacket(container, container.length);
                // 阻塞式接收包裹
                server.receive(packet);
                // 输出接收时间
                SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                System.out.println("接收 " + format.format(new Date()));
                // 分析数据
                byte[] datas = packet.getData();
                String msg = new String(datas, 0, packet.getLength());
                System.out.println(from + ":" + msg);
                if(msg.equals("bye")) {
                    break;
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        // 释放资源
        server.close();
    }
}


