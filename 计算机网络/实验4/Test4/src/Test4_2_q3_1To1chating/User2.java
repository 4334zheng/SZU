package Test4_2_q3_1To1chating;

import java.net.SocketException;

public class User2 {
    public static void main(String[] args) throws SocketException{
        new Thread(new ChatReceive(8888, "User1")).start();
        new Thread(new ChatSend(6666, "localhost", 7777)).start();
    }
}
