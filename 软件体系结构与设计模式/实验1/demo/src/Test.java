import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args){
        //读取配置文件，加载里面的配置
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("spring-config.xml");
        //通过getBean得到对象，其中HelloWorld就是在application.xml中配置的bean中的id
        HelloWorld helloWorld = (HelloWorld) applicationContext.getBean("HelloWorld");
    }
}
