import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String shapeName = "";
        while (true){
            System.out.println("请输入你要创建的图形名称（输入exit退出）");
            // 接收输入图形名称
            shapeName = scanner.next();
            // 如果为“exit”程序退出
            if (shapeName.equals("exit"))
                break;
            try {
                // 使用简单工厂创建shape对象
                shape s = shapeFactory.createShape(shapeName);
                // 调用方法
                s.draw();
                s.erase();
            } catch (UnsupportedShapeException e) {
                System.out.println(e.toString());
            }
        }
    }
}
