import java.util.ArrayList;
import java.util.Iterator; 
import java.util.List;
import org.jdom2.Document; 
import org.jdom2.Element;
import org.jdom2.input.SAXBuilder;
import stu.*;

/**
 * 从MySudentInfo.xml读取学生信息
 * @author wch
 */
public class MyXMLReader {
    String xmlpath;

    /**
     * @description 构造函数
     * @param xmlpath: xml文件所在路径
     */
    MyXMLReader(String xmlpath){
        this.xmlpath = xmlpath;
    }

    /**
     * 读取xml文件中所有学生信息
     * @author wch
     * @return students: Student类List集合,存储了所有学生信息
     */
    public List<Student> readAll(){
        //定义student类list集合
        List<Student> students = new ArrayList<>();
        SAXBuilder builder=new SAXBuilder();
        try {
            Document doc = builder.build(xmlpath);      
            Element root = doc.getRootElement();
            List<Element> studentlist = root.getChildren("student");
            //设置循环读取xml文件中的所有学生信息
            for (Iterator<Element> iter = studentlist.iterator(); iter.hasNext();) {
                Element stu = (Element) iter.next();
                Student obj = new Student(stu.getChildText("number"), stu.getChildText("name"), stu.getChildText("gender"), stu.getChildText("major"));
                //将读取的信息添加到student类list集合中
                students.add(obj);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return students;
    }

    /**
     * 读取xml文件中序号为n的学生信息
     * @author wch
     * @param n: 需要查找学生序号(n>0)
     * @return student: 当序号存在时，返回一个Student对象; 当该序号不存在时,返回null
     */
    public Student readStudent(int n){
        //定义student类对象obj
        Student obj = new Student();
        SAXBuilder builder=new SAXBuilder();
        try {
            Document doc = builder.build(xmlpath);      
            Element root = doc.getRootElement();
            int nodenum = root.getContentSize();
            //判断指定读取序号是否存在
            if ((nodenum - 1)/2 < n || n < 1)
                return null;
            int i = 0;
            List<Element> studentlist = root.getChildren("student");
            Iterator<Element> iter = studentlist.iterator();
            //查找序号n
            while (iter.hasNext() && i != n - 1){
                iter.next();
                i++;
            }
            Element stu = iter.next();
            obj = new Student(stu.getChildText("number"), stu.getChildText("name"), stu.getChildText("gender"), stu.getChildText("major"));
        }catch (Exception e) {
            e.printStackTrace();
        }
        return obj;
    }
}
