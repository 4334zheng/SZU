public class Contacts {
    private String contacts;
    public Contacts(String contacts){
        this.contacts = contacts;
    }
    public void copy(){
        System.out.println(contacts + "已完成备份");
    }
}
