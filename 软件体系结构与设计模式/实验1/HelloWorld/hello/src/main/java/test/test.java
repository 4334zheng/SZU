package test;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class test {
    //解析beans.xml文件，生成管理相应的Bean对象
    ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
    //getBean:参数即为Spring配置文件中bean的id
    Hello hello = (Hello) context.getBean("hello");
    hello.show();
}
