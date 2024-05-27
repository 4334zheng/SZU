public class Test {
    public static void main(String[] args){
        User user = new User();
        user.setToken("1234");
        user.setMail("666666@qq.com");
//        DBUtil dbUtil = new DBUtil();
//        dbUtil.save(user);

//        重写
//        DBOperation dbOperation = new AdapterOpe();
        DBOperation dbOperation = new AdapterOpe1();
        dbOperation.save(user);
    }
}
