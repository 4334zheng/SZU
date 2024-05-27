package mail;
import java.io.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet(name = "AddBanner", value = "/AddBanner")

public class AddBanner extends HttpServlet{
    public void doGet(HttpServletRequest request,HttpServletResponse response)
        throws IOException,ServletException{
            response.setContentType("text/html;charset=gb2312");
            PrintWriter out=response.getWriter();
            try{
                ParseRequest pf=new ParseRequest();
                Vector v=pf.getFormData(request);

                FormData fd;
                String link="";
                String contentType="";
                byte[] image=null;

                Enumeration e=v.elements();
                while (e.hasMoreElements()){
                    fd=(FormData) e.nextElement();
                    if(fd.name.equals("link")){
                        link=fd.value;
                        continue;
                    }else if(fd.name.equals("image")){
                        contentType=fd.contentType;
                        image=fd.file;
                    }
                }
                System.out.println(link);
                System.out.println(image);
                System.out.println(contentType);

                if(!link.equals("")&&!contentType.equals("")&&image!=null){
                    Class.forName("com.mysql.cj.jdbc.Driver");
                    String sConnStr="jdbc:mysql://localhost:3306/testbase?serverTimezone=UTC&useSSL=false" +
                            "&allowPublicKeyRetrieval=true&rewriteBatchedStatements=true";
                    String user="root";
                    String password="022511";
                    Connection conn=DriverManager.getConnection(sConnStr,user,password);
                    String sql="insert into banner (link,type,file) values(?,?,?)";
                    PreparedStatement pstmt=conn.prepareStatement(sql);
                    pstmt.setString(1,link);
                    pstmt.setString(2,contentType);
                    pstmt.setBytes(3,image);
                    pstmt.execute();
                    pstmt.close();
                    conn.close();
                    out.println("广告条信息添加成功！");
                }else {
                    out.println("广告条数据添加失败！");
                }
            }catch (NullPointerException npe){}
            catch (Exception e){
                System.err.println(e);
                e.printStackTrace();
            }

            out.println("<html>");
            out.println("<body>");
            out.println("<head>");
            out.println("</head>");
            out.println("<body bgcolor=\"white\">");
            out.println("<h3>广告条信息添加</h3>");
            out.println("<form action=\"");
            out.println("AddBanner\" ");
            out.println("method=POST  enctype='multipart/form-data'>");
            out.println("连接");
            out.println("<input type=text size=20 name=link>");
            out.println("<br>");
            out.println("图片");
            out.println("<input type=file size=20 name=image>");
            out.println("<br>");
            out.println("<input type=submit value='提交'>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
    }

    public void doPost(HttpServletRequest request,HttpServletResponse response)
        throws IOException,ServletException{
            doGet(request,response);
    }
}
