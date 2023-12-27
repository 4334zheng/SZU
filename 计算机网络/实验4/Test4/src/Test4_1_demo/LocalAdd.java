//使用InetAddress类的方法获取本地机的名称和IP地址
package Test4_1_demo;

import java.net.InetAddress;

public class LocalAdd {
    public static void main(String[] args) throws Exception{
        //获取本机地址信息
        InetAddress local = InetAddress.getLocalHost();
        //获取本地ip地址
        String LocalAddress = local.getHostAddress();
        //获取本地主机名
        String LocalName = local.getHostName();
        //输出信息
        System.out.println("本地主机IP:"+LocalAddress);
        System.out.println("本地主机名:"+LocalName);
    }
}
