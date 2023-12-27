//使用InetAddress类的方法获取网站www.csdn.net的IP地址，如果存在多个IP地址，要求全部返回
package Test4_1_demo;

import java.io.IOException;
import java.net.InetAddress;

public class CSDNAdd {
    public static void main(String[] args) throws IOException{
        String csdnhost = "www.csdn.net";
        //获取指定域名地址信息
        InetAddress ip1 = InetAddress.getByName(csdnhost);
        //获取网站ip地址
//        String csdn_add = ip1.getHostAddress();
//        System.out.println("网站www.csdn.net的IP地址:" + csdn_add);

        //返回所有ip地址
        System.out.println("网站www.csdn.net的所有IP地址为:");
        InetAddress[] ip2 = InetAddress.getAllByName(csdnhost);
        for(int i=0;i<ip2.length;i++){
            System.out.println(i+1+":"+ip2[i].getHostAddress());
        }
    }
}
