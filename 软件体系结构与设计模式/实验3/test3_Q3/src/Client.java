public class Client {
    public static void main(String[] args){
        // 创建一个BMP格式的图像并使用Blur滤镜
        Filter filter = new Blur();
        Image image = new BMPImage(filter);
        image.operation();
    }
}
