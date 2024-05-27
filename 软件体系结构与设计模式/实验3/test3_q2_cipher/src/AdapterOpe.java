// AdapterOpe实现DBOperation接口
public class AdapterOpe implements DBOperation{
    // 维持一个对适配器对象的引用
    private final Encrypt encrypt;
    private final DBUtil dbUtil;

    public AdapterOpe(){
        encrypt = new Encrypt();
        dbUtil = new DBUtil();
    }

    public void save(User user){
        // 创建一个User对象，对测试类中设置的token和mail进行加密，获得加密后的token和mail
        User encryptUser = new User();
        encryptUser.setToken(encrypt.encryption(user.getToken()));
        encryptUser.setMail(encrypt.encryption(user.getMail()));
        // 在save方法中将User对象加密后传递给适配者类DBUtil的save方法，实现对DBUtil类的适配
        dbUtil.save(encryptUser);
    }
}
