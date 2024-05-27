<%@ page language="java" contentType="text/html; charset=utf-8"
         pageEncoding="utf-8" import="java.lang.String"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>receive form data</title>
</head>
<body>

<%=request.getParameter("user")%>
<%=request.getParameter("password")%>
</body>
</html>
