public class AdapterOpe1 extends Encrypt implements DBOperation{
    private final DBUtil dbUtil; // 适配者DBUtil对象
    public AdapterOpe1(){
        this.dbUtil = new DBUtil();
    }
    public void save(User user){
        User encryptUser = new User();
        // 调用Encrypt中的加密方法，对token和mail进行加密
        encryptUser.setToken(super.encryption(user.getToken()));
        encryptUser.setMail(super.encryption(user.getMail()));
        // 转发调用适配者类DBUtil的save方法
        dbUtil.save(encryptUser);
    }
}
