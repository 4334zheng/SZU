import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;
import org.jdom.output.XMLOutputter;

import javax.swing.text.html.HTMLDocument;

public class JDomParse {
    public JDomParse(){
        //确定xml文件位置
        String xmlpath= "C:\\Users\\4334\\IdeaProjects\\Test_2\\src\\books.xml";
        //使用的解析器，这里表示默认的解析器
        SAXBuilder builder=new SAXBuilder(false);
        try {
            //得到document，以后的操作都是document操作的
            Document doc=builder.build(xmlpath);
            //得到根元素
            Element books=doc.getRootElement();
            //取根元素下所有名字为”book“的元素
            List booklist=books.getChildren("book");
            for (Iterator iter = booklist.iterator(); iter.hasNext();) {
                Element book = (Element) iter.next();
                //获得id属性
                String bookid=book.getAttributeValue("BookID");
                System.out.println("BookID:"+bookid);
                //获得元素
                String name=book.getChildText("name");
                System.out.println("name:"+name);
                String price=book.getChildText("price");
                System.out.println("price:"+price);
                //分割线
                System.out.println("---------------------");
            }

            //修改书名为”Lincon“的图书价格为30.5
            for(Iterator iter = booklist.iterator();iter.hasNext();)
            {
                Element book = (Element) iter.next();
                if(book.getChildText("name").equals("Lincon"))//遍历所有图书，找到书名为Lincon的图书
                {
                    Element price=book.getChild("price");//获得该书的price
                    price.setText("30.5");//将该书的price更改为30.5
                }
            }
            //输出修改后的图书信息
            System.out.println("修改后的图书信息输出：\n");
            for (Iterator iter = booklist.iterator(); iter.hasNext();) {
                Element book = (Element) iter.next();
                //获得id属性
                String bookid=book.getAttributeValue("BookID");
                System.out.println("BookID:"+bookid);
                //获得元素
                String name=book.getChildText("name");
                System.out.println("name:"+name);
                String price=book.getChildText("price");
                System.out.println("price:"+price);
                //分割线
                System.out.println("---------------------");
            }

            //增加一本图书信息
            Element newBook=new Element("book");//新建一个图书节点
            newBook.setAttribute("BookID","5");//新建newBook的属性，即图书id为5
            Element newName=new Element("name");//增加图书元素name
            newName.setText("中间件技术");
            newBook.addContent(newName);//将元素添加进newBook节点
            Element newPrice=new Element("price");//增加图书元素price
            newPrice.setText("39.0");
            newBook.addContent(newPrice);
            books.addContent(newBook);//将新增加的图书接入books.xml中
            //新增图书后的图书信息输出
            System.out.println("增加一本图书后的图书信息输出：\n");
            for (Iterator iter = booklist.iterator(); iter.hasNext();) {
                Element book = (Element) iter.next();
                //获得id属性
                String bookid=book.getAttributeValue("BookID");
                System.out.println("BookID:"+bookid);
                //获得元素
                String name=book.getChildText("name");
                System.out.println("name:"+name);
                String price=book.getChildText("price");
                System.out.println("price:"+price);
                //分割线
                System.out.println("---------------------");
            }

            //JDOM转换为xml
            XMLOutputter outputter=new XMLOutputter();
            outputter.output(doc,new FileOutputStream(xmlpath));
        } catch (JDOMException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        new JDomParse();
    }
}