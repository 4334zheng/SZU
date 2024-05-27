public class Circle implements shape{
    public Circle(){
        System.out.println("圆形创建成功");
    }
    @Override
    public void draw() {
        System.out.println("绘制圆形");
    }

    @Override
    public void erase() {
        System.out.println("擦除圆形");
    }
}
