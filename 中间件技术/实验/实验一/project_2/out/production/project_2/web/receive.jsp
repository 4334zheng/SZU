<%@ page contentType="text/html; charset=UTF-8"%>
<html>
<head>
    <title>display</title>
</head>
<body>
<%
    String user = request.getParameter("user");
    String password = request.getParameter("password");
    out.println(user);
    out.println(password);
%>
</body>
</html>