/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package companymanagement;

import java.sql.*;
import java.util.*;

/**
 *
 * @author ccslearner
 */
public class company {
    
    // Fields
    public int      companyid;
    public String   company_name;
    public int      building_no;
    public String   street;
    public String   city;
    public String   province;
    public String   country;
    public double   company_budget;
    
    // Lists
    public ArrayList<Integer>   companyidlist       = new ArrayList<>();
    public ArrayList<String>    companynamelist     = new ArrayList<>();
    public ArrayList<Integer>   building_nolist     = new ArrayList<>();
    public ArrayList<String>    streetlist          = new ArrayList<>();
    public ArrayList<String>    citylist            = new ArrayList<>();
    public ArrayList<String>    provincelist        = new ArrayList<>();
    public ArrayList<String>    countrylist         = new ArrayList<>();
    public ArrayList<Double>    companybudgetlist   = new ArrayList<>();
    
    // Constructor
    public company() {}
    
    public int companycurrent(){
        try{
            Connection conn;
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/requestmanagementdb?user=root&password=12345678");
            System.out.println("Connection Successful");

            PreparedStatement pstmt = conn.prepareStatement("SELECT companyid, company_name FROM company");
            ResultSet rst =pstmt.executeQuery();
            companyidlist.clear();
            companynamelist.clear();
            while(rst.next()){
                companyid = rst.getInt("companyid");
                company_name = rst.getString("company_name");
                companyidlist.add(companyid);
                companynamelist.add(company_name);
            }
            
                pstmt.close();
                conn.close();
                System.out.println("Successful");
                return 1;
            } catch (Exception e){
                System.out.println(e.getMessage());
                return 0;
            }
    }
    
    public int search_company() {
        return 0;
    }
    
    public int view_company() {
        try{
            Connection conn;
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/requestmanagementdb?user=root&password=12345678");
            System.out.println("Connection Successful");

            PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM company");
            ResultSet rst = pstmt.executeQuery();
            
            while(rst.next()){
                companyid       = rst.getInt("companyid");
                company_name    = rst.getString("company_name");
                building_no     = rst.getInt("building_no");
                street          = rst.getString("street");
                city            = rst.getString("city");
                province        = rst.getString("province");
                country         = rst.getString("country");
                company_budget  = rst.getDouble("company_budget");
                companyidlist.add(companyid);
                companynamelist.add(company_name);
                building_nolist.add(building_no);
                streetlist.add(street);
                citylist.add(city);
                provincelist.add(province);
                countrylist.add(country);
                companybudgetlist.add(company_budget);
            }
            
            pstmt.close();
            conn.close();
            System.out.println("Successful");
            return 1;
        } catch(Exception e) {
            System.out.println(e.getMessage());
            return 0;
        }
    }    
    
    public int register_company(){
        try{
            Connection conn;
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/requestmanagementdb?user=root&password=12345678");
            System.out.println("Connection Successful");

            PreparedStatement pstmt = conn.prepareStatement("SELECT MAX(companyid) + 1 AS newID FROM company");
            ResultSet rst = pstmt.executeQuery();
            
            while(rst.next()){
                companyid       = rst.getInt("newID");
            }
                pstmt = conn.prepareStatement("INSERT INTO company (companyid, company_name, building_no, street, city, province, country, company_budget) VALUE (?,?,?,?,?,?,?,?)");
                pstmt.setInt(1,companyid);
                pstmt.setString(2, company_name);
                pstmt.setInt(3, building_no);
                pstmt.setString(4, street);
                pstmt.setString(5, city);
                pstmt.setString(6, province);
                pstmt.setString(7, country);
                pstmt.setDouble(8, company_budget);
                
                pstmt.executeUpdate();

                pstmt.close();
                conn.close();
                System.out.println("Successful");
            
                return 1;
            } catch (Exception e){
                System.out.println(e.getMessage());
                return 0;
            }
    }
    
    public int delete_company() {
        try{
            Connection conn;
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/requestmanagementdb?user=root&password=12345678");
            System.out.println("Connection Successful");

            PreparedStatement pstmt = conn.prepareStatement("DELETE FROM company WHERE companyid =" + companyid);
            pstmt.executeUpdate();

            pstmt.close();
            conn.close();
            System.out.println("Successful");
            
                return 1;
            } catch (Exception e){
                System.out.println(e.getMessage());
                return 0;
            }
    }
    
    public static void main (String args[]){
        
        company c = new company();
        c.company_name= "ANOTHER";
        c.register_company();
    }
    
    public int getCompanyNameList() {
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/requestmanagementdb?user=root&password=12345678");
            System.out.println("Connection Successful");

            PreparedStatement pstmt = conn.prepareStatement("SELECT company_name FROM company");
            ResultSet rst =pstmt.executeQuery();
            companynamelist.clear();
            while(rst.next()){
                company_name = rst.getString("company_name");
                companynamelist.add(company_name);
            }
                pstmt.close();
                conn.close();
                System.out.println("Successful");
                return 1;
            } catch (Exception e){
                System.out.println(e.getMessage());
                return 0;
            }
    }
    
    
}
