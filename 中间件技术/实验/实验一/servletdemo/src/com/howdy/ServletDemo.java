package com.howdy;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "ServletDemo")
public class ServletDemo extends HttpServlet{
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=utf-8");
        PrintWriter out =response.getWriter();
        String uname=request.getParameter("username");
        String password=request.getParameter("password");
        out.println("<html>");
        out.println("<body>");
        out.println("<h3>Servlet打印:</h3>");
        out.println("<h3>您的姓名是:"+uname+" </h3>");
        out.println("<h3>您的密码是:"+password+" </h3>");
        out.println("</body>");
        out.println("</html>");
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}
