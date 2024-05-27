public class Songs {
    private String songs;
    public Songs(String songs){
        this.songs = songs;
    }
    public void copy(){
        System.out.println(songs + "已完成备份");
    }
}
