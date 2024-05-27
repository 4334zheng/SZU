package jni;

public class Main {
    public static void main(String[] args){
        System.load("C:\\Users\\4334\\Desktop\\自用\\深大\\中间件技术\\实验\\实验四\\JniDemo\\src\\native\\Win32Project4.dll");
        Demo demo = new Demo();
        demo.sayHello(2, 3);
    }
}
