import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;

public class XMLUtil {
    //从xml配置文件中提取具体类类名，并返回一个实例对象
    public static Object getBean(){
        try{
            DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = dFactory.newDocumentBuilder();
            Document doc;
            //从项目根目录开始读取
            doc = builder.parse(new File("src//config.xml"));
            //获取包含类名的文本节点
            NodeList nl = doc.getElementsByTagName("className");
            Node classNode = nl.item(0).getFirstChild();
            String cName = classNode.getNodeValue();
            //通过类名生成实例对象并返回
            Class c = Class.forName(cName);
            Object obj = c.newInstance();
            return obj;

        }catch(Exception e){
            e.printStackTrace();
            return null;
        }
    }
}
