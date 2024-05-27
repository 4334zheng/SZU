public class Messages {
    private String messages;
    public Messages(String messages){
        this.messages = messages;
    }
    public void copy(){
        System.out.println(messages + "已完成备份");
    }
}
