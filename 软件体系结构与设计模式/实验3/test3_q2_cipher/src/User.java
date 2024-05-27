public class User {
//    定义属性值命令token和邮箱mail
    private String token;
    private String mail;
//    属性的set方法和get方法
    public void setToken(String token){
        this.token = token;
    }
    public String getToken(){
        return token;
    }
    public void setMail(String mail){
        this.mail = mail;
    }
    public String getMail(){
        return mail;
    }
//    定义toString方法增加输出结果可读性
    public String toString(){
        return "User{token=" + token + ",mail=" + mail + "}";
    }
}
