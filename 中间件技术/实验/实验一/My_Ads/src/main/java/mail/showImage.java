package mail;
import java.io.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet(name = "showImage", value = "/showImage")

public class showImage extends HttpServlet{
    public void doGet(HttpServletRequest request,HttpServletResponse response)
        throws IOException,ServletException{
            try {
                String id=request.getParameter("id");
                Class.forName("com.mysql.cj.jdbc.Driver");
                String sConnStr="jdbc:mysql://localhost:3306/testbase?serverTimezone=UTC&useSSL=false" +
                        "&allowPublicKeyRetrieval=true&rewriteBatchedStatements=true";
                String user="root";
                String password="022511";
                Connection conn=DriverManager.getConnection(sConnStr,user,password);
                String sql="select type,file from banner where id="+id;
                Statement stmt=conn.createStatement();

                ResultSet rs=stmt.executeQuery(sql);
                InputStream in=null;
                if(rs.next())
                    in=rs.getBinaryStream("file");
                response.setContentType(rs.getString("type"));
                //response.setContentType("text/html;charset=gb2312");

                ServletOutputStream sout=response.getOutputStream();
                byte b[]=new byte[1024];

                while(in.read(b)!=-1){
                    sout.write(b);
                }
                sout.flush();
                sout.close();
                rs.close();
                stmt.close();
                conn.close();
            }catch (Exception e){
                e.printStackTrace();
            }
    }

    public void doPost(HttpServletRequest request,HttpServletResponse response)
        throws IOException,ServletException{
            doGet(request,response);
    }
}
