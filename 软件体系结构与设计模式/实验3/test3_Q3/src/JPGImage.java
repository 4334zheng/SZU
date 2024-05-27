public class JPGImage extends Image{
    public JPGImage(Filter filter){
        super(filter);
    }
    public void operation(){
        filter.addFilter();
    }
}
