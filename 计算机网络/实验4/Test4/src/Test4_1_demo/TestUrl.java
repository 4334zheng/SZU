//使用URL类下载深圳大学首页http://www.szu.edu.cn，并统计下载得到网页文件的大小
package Test4_1_demo;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.text.DecimalFormat;

public class TestUrl {
    public static void main(String[] args) throws Exception{
        URL url = new URL("https://www.baidu.com");
        InputStream in = url.openStream();//生成输入流
        FileOutputStream fout = new FileOutputStream(new File("test.html"));
        int a = 0;
        while(a>-1){
            a = in.read();//读入
            fout.write(a);//写出
        }
        // 统计文件的大小
        File file = new File("test.html");
        System.out.println("文件大小为:" + new DecimalFormat("#.00").format(file.length() / 1024.00)
                + "k");
    }
}
