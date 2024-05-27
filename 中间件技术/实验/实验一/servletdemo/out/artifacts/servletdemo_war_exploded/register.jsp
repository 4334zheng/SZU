<%--
  Created by IntelliJ IDEA.
  User: 4334
  Date: 2022/9/21
  Time: 10:55
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Servlet表单提交</title>
</head>
<body>
//创建表单
<form action="ServletDemo" method="post">
    Servlet输入信息：
    <table>
        <tr>
            <td>姓名：</td>
            <td><input type="text" name="username" id="username"/></td>
        </tr>
        <tr>
            <td>密码：</td>
            <td><input type="password" name="password" id="password"></td>
        </tr>
    </table>
    <input type="submit" value="提交">
    <input type="reset" value="重新填写">
</form>
</body>
</html>
