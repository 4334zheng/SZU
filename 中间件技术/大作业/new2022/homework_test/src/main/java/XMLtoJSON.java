//导包
import java.io.File;
import java.io.FileWriter;
import java.nio.charset.Charset;
import java.io.BufferedWriter;
import java.util.List;
import net.sf.json.JSONArray;
import stu.*;

/**
 * 从MySudentInfo.xml读取学生信息,并转为json文件存储
 * @author wch
 */

public class XMLtoJSON {
    /**
     * @description 使用MyXMLReader类读取xml生成Student类对象,并将Student对象转为json对象写入json文件
     * @param xmlpath: xml文件所在路径
     * @param jsonpath: json文件所在路径
     * @author wch
     */
    //定义toJSON方法，读取指定xml路径下的数据转换为json字符串并存放在指定路径的json文件中
    public void toJSON(String xmlpath, String jsonpath){
        MyXMLReader reader = new MyXMLReader(xmlpath);
        List<Student> students = reader.readAll();
        JSONArray objs = JSONArray.fromObject(students);
        
        try {
            File jsonfile = new File(jsonpath);
            //json路径下检查文件是否存在，不存在则生成一个新文件
            if (!jsonfile.exists())
                jsonfile.createNewFile();
            FileWriter fw = new FileWriter(jsonfile,Charset.forName("UTF8"));
            BufferedWriter bw = new BufferedWriter(fw);
            //使用内置的toString()函数将类对象各属性值转换为json字符串
            bw.write(objs.toString());
            bw.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        XMLtoJSON xmLtoJSON = new XMLtoJSON();
        xmLtoJSON.toJSON("src//MyStudentInfo.xml","src//MyStudentInfo.json");
    }
}
