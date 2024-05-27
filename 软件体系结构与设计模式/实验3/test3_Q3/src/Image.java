public abstract class Image {
    protected Filter filter;
    // 构造函数，传入filter对象初始化Image对象的filter属性
    public Image(Filter filter){
        super();
        this.filter = filter;
    }
    // 抽象方法，不同格式定义自己的滤镜使用方法
    public abstract void operation();
}
