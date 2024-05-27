<!--MySQL驱动版本为8.0.26,版本低于8.0的com.mysql.cj.jdbc.Driver 更换为 com.mysql.jdbc.Driver-->
<!--url端口号需检查是否一致,端口号后的数据库名改成自己的-->
<!--username和password改成自己的-->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="net.sf.json.JSONObject" %>
<%@ page import="java.sql.*"%>
<%@ page import="stu.*"%>

<html>
    <head>
        <title>通过JSP打开数据表</title>
    </head>
    <body>
        <%  
            try {
                //注册驱动
                Class.forName("com.mysql.cj.jdbc.Driver");
                String url = "jdbc:mysql://localhost:3306/finalpro?useSSL=false&serverTimezone=UTC&useUnicode=true&characterEncoding=utf-8"; //数据库名
                String username = "root";
                String password = "022511";
                //获取数据库对象
                Connection conn = DriverManager.getConnection(url, username, password);

                //定义sql
                String sql = "SELECT *FROM TstudentInfo;";  //查询语句
                Statement stmt = conn.createStatement();
                //执行sql
                ResultSet rs = stmt.executeQuery(sql);

                //在遍历结果集的同时将数据创建到json对象中
                while(rs.next())
                {
                    Student stu = new Student(rs.getString("number"),rs.getString("name"),rs.getString("gender"),rs.getString("major"));
                    JSONObject obj = JSONObject.fromObject(stu);
                    String str = obj.toString();
                    out.print(str + "</br>");
                }
                
            }catch (Exception e) {
                out.print("数据库连接异常！");
            }  
        %>   
    </body>
</html>