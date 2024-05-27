public class Facade {
    private Contacts contacts;
    private Messages messages;
    private Photos photos;
    private Songs songs;
    public Facade(){
        this.contacts = new Contacts("通讯录");
        this.messages = new Messages("短信");
        this.photos = new Photos("照片");
        this.songs = new Songs("音乐");
    }
    // 调用子系统的备份方法
    public void backup(){
        contacts.copy();
        messages.copy();
        photos.copy();
        songs.copy();
    }
}
