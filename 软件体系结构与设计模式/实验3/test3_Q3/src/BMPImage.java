public class BMPImage extends Image{
    // 调用父类的构造方法，将传入的filter对象传递给父类
    public BMPImage(Filter filter){
        super(filter);
    }

    @Override
    public void operation() {
        filter.addFilter();
    }
}
