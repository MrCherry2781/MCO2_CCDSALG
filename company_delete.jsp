<%-- 
    Document   : company_delete.jsp
    Created on : Nov 16, 2023, 1:02:14 AM
    Author     : ccslearner
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.util.*, companymanagement.*" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Delete company processing</title>
    </head>
    <body>
        <form action="company_delete_page2.jsp">
            <jsp:useBean id="c" class="companymanagement.company" scope="session"/>
            Company: <select id = "companytodelete" name = "companytodelete"><br>
                <%
                    c.companycurrent();
                    for(int i= 0;i<c.companyidlist.size();i++){
                %>
                    <option value="<%=c.companyidlist.get(i)%>"><%=c.companynamelist.get(i)%></option>
                <% } %>
                     </select><br>
            <input type="submit" value="Submit">
        </form>
    </body>
</html>
