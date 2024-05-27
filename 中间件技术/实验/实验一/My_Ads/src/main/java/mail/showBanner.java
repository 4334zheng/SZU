package mail;
import java.io.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet(name = "showBanner", value = "/showBanner")
//@WebServlet("/showBanner")

public class showBanner extends HttpServlet{
    public void doGet(HttpServletRequest request,HttpServletResponse response)
        throws IOException,ServletException{
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                String sConnStr="jdbc:mysql://localhost:3306/testbase?serverTimezone=UTC&useSSL=false" +
                        "&allowPublicKeyRetrieval=true&rewriteBatchedStatements=true";
                String user="root";
                String password="022511";
                Connection conn=DriverManager.getConnection(sConnStr,user,password);
                String sql="select id,link from banner where link!='' and " +
                        "type!='' and file!=''";

                //Statement stmt=conn.createStatement();
                Statement stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
                ResultSet rs=stmt.executeQuery(sql);
                rs.last();
                Random r=new Random();
                int selectedbanner=Math.abs((r.nextInt())%(rs.getRow()));
                int i=0;
                int id=0;
                String link="";

                rs.absolute(1);
                while(true){
                    if(selectedbanner==i++){
                        id=rs.getInt("id");
                        link=rs.getString("link");
                        break;
                    }
                    rs.next();
                }

                rs.close();
                stmt.close();
                conn.close();

                response.setContentType("text/html;charset=gb2312");
                PrintWriter out=response.getWriter();
                out.print("<a href='"+link+"'><img border=0 src=" +
                        "'showImage?id="+id+"'></a>");
            }catch (Exception e){
                e.printStackTrace();
            }
    }

    public void doPost(HttpServletRequest request,HttpServletResponse response)
        throws IOException,ServletException{
            doGet(request,response);
    }
}
