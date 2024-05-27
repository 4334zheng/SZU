public class Photos {
    private String photos;
    public Photos(String photos){
        this.photos = photos;
    }
    public void copy(){
        System.out.println(photos + "已完成备份");
    }
}
