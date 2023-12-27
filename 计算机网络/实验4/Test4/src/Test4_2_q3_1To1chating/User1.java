package Test4_2_q3_1To1chating;

import java.net.SocketException;

public class User1 {
    public static void main(String[] args) throws SocketException{
        new Thread(new ChatSend(9999, "localhost", 8888)).start();
        new Thread(new ChatReceive(7777, "User2")).start();
    }
}
