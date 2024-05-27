public class Triangle implements shape{
    public Triangle(){
        System.out.println("三角形创建成功");
    }
    public void draw(){
        System.out.println("绘制三角形");
    }

    @Override
    public void erase() {
        System.out.println("擦除三角形");
    }
}
