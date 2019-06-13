package text_check;

import java.sql.*;


import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.StringTokenizer;

public class split_post {

	private static String buf, delimeter=",.．?!、:;；。，\n：;；？！ 		";
	private static Connection c;
	private static Statement stmt;
	private static ResultSet q;
	public static void main(String[] args) {
		c = null;
		try {
			buf = new String(Files.readAllBytes(Paths.get(args[0])));
			//System.out.println(buf);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		StringTokenizer st = new StringTokenizer(buf,delimeter);
		
		
		try {
			
			c = DriverManager.getConnection("jdbc:sqlite:base");
			stmt = c.createStatement();
			
			stmt.execute("insert into post(blah)values('raw test')");
			q = stmt.executeQuery("select seq from sqlite_sequence where name=\"post\"");
			int id = q.getInt("seq");
			
			System.out.println(id);
			
			while(st.hasMoreTokens()) {
				String content = st.nextToken();
				stmt.execute("insert into content(pid,content)values("+id+",'"+content+"')");
				//System.out.println(content);
				
			}
				
			
			
		}catch(Exception e) {
			System.out.println("my bad");
			System.exit(0);
		}
		
	}

}
