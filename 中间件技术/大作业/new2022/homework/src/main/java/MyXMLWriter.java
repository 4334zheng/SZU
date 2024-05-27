import java.io.*;
import org.jdom2.Document; 
import org.jdom2.Element;
import org.jdom2.JDOMException; 
import org.jdom2.input.SAXBuilder;
import org.jdom2.output.Format; 
import org.jdom2.output.XMLOutputter;

/**
 * 向MySudentInfo.xml添加写入学生信息
 * @author wch
 */
public class MyXMLWriter {

    String xmlpath;

    /**
     * @description 构造函数
     * @param xmlpath: xml文件所在路径
     */
    MyXMLWriter(String xmlpath){
        this.xmlpath = xmlpath;
    }

    /**
     * @description 添加单个学生的信息
     * @author wch
     * @param number: 学号
     * @param name: 姓名
     * @param gender: 性别
     * @param major: 主修专业
     */
    public void write(String number,String name,String gender,String major){
        SAXBuilder builder=new SAXBuilder();
        try {
            Document doc = builder.build(xmlpath);      
            Element root = doc.getRootElement();
            int nodenum = (root.getContentSize() + 1) / 2;
            Element student = new Element("student").setAttribute("no",Integer.toString(nodenum));
            
            student.addContent(new Element("number").setText(number));
            student.addContent(new Element("name").setText(name));
            student.addContent(new Element("gender").setText(gender));
            student.addContent(new Element("major").setText(major));
            root.addContent(student);

            XMLOutputter outputter=new XMLOutputter();
            outputter.setFormat(Format.getPrettyFormat());      
            outputter.output(doc,new FileOutputStream(xmlpath));
        } catch (JDOMException e) {
            e.printStackTrace();     
        } catch (IOException e) {          
            e.printStackTrace();
        }
    }

    /**
     * @description 添加文件中所有学生的信息
                    文件内容 "学号 姓名 性别 主修专业"
     * @author wch
     * @param docpath: txt文件路径
     * @throws IOException
     */
    public void writeFromFile(String docpath) throws IOException{
        BufferedReader fr = new BufferedReader(new InputStreamReader(new FileInputStream(new File(docpath)),"utf-8"));
        String str;
        String strs[];
        try {
            while ((str = fr.readLine()) != null){
                strs = str.split("\\s+",4);
                write(strs[0], strs[1], strs[2], strs[3]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        //写入项目组所有成员信息
        MyXMLWriter writer = new MyXMLWriter("src//MyStudentInfo.xml");
        writer.write("2020151084", "韦承昊", "男", "软件工程");
        writer.write("2020151015", "谭文权", "男", "软件工程");
        writer.write("2020151070", "伍政韬", "男", "软件工程");
        writer.write("2020151073", "王卓耀", "男", "软件工程");
        writer.write("2020151022", "郑彦薇", "女", "软件工程");
    }
}
