<%-- 
    Document   : company_delete_page2
    Created on : Nov 16, 2023, 8:20:14 PM
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
        <jsp:useBean id="c" class="companymanagement.company" scope="session"/>
        <form action ="company.html">          
            <%  
                String v_companyid = request.getParameter("companytodelete");
                c.companyid = Integer.valueOf(v_companyid);
                    
                int status = c.delete_company();
                if (status == 1) {
            %>
                <h1>Company deletion successfully</h1>
            <% } else { %>
                <h1>Company deletion failed</h1>
            <% } %>
            <input type="submit" value="Return">
        </form>
    </body>
</html>
