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
    public void toJSON(String xmlpath, String jsonpath){
        MyXMLReader reader = new MyXMLReader(xmlpath);
        List<Student> students = reader.readAll();
        JSONArray objs = JSONArray.fromObject(students);
        
        try {
            File jsonfile = new File(jsonpath);
            if (!jsonfile.exists())
                jsonfile.createNewFile();
            FileWriter fw = new FileWriter(jsonfile,Charset.forName("UTF8"));
            BufferedWriter bw = new BufferedWriter(fw);
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
