import java.sql.*;
import java.util.List;
import stu.*;

/**
 * 使用MyXMLReader类从MySudentInfo.xml中读出所有学生数据信息,写入数据库TstudentInfo中
 * @author wch
 */
public class XMLtoDB {
    String xmlpath;

    /**
     * @description 构造函数
     * @param xmlpath: xml文件所在路径
     */
    XMLtoDB(String xmlpath){
        this.xmlpath = xmlpath;
    }

    /**
     * @description 使用MyXMLReader类读取xml生成Student类对象,并将Student对象写入数据表TstudentInfo中,
                    数据表不需要提前建好
     * @description 数据库类型为MySQL,版本与java驱动均为8.0.26
     * @param database_name: 数据库名
     * @param username: 用户名
     * @param password: 密码
     */
    public void toDB(String database_name, String username, String password){
        try {
            Class.forName("com.mysql.jdbc.Driver");
            String sConnStr = "jdbc:mysql://localhost/:3306/" + database_name + "?user=" + username + "&password=" + password + "&useUnicode=true&characterEncoding=utf-8";
            Connection conn = DriverManager.getConnection(sConnStr);

            String sql = "create table if not exists TstudentInfo(number varchar(20), name varchar(20), gender varchar(20), major varchar(30))";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.execute();

            sql = "insert into TstudentInfo (number,name,gender,major) values(?,?,?,?)";
            pstmt = conn.prepareStatement(sql);
            MyXMLReader reader = new MyXMLReader(xmlpath);
            List<Student> students = reader.readAll();
            for (Student stu : students){
                pstmt.setString(1, stu.getNumber());
                pstmt.setString(2, stu.getName());
                pstmt.setString(3, stu.getGender());
                pstmt.setString(4, stu.getMajor());
                pstmt.execute();
            }
            pstmt.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        XMLtoDB obj = new XMLtoDB("src//MyStudentInfo.xml");
        obj.toDB("test", "root", "wch71243875");
    }
}
