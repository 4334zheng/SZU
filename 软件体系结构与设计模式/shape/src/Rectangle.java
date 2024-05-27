public class Rectangle implements shape{
    public Rectangle(){
        System.out.println("矩形创建成功");
    }
    @Override
    public void draw() {
        System.out.println("绘制矩形");
    }

    @Override
    public void erase() {
        System.out.println("擦除矩形");
    }
}
