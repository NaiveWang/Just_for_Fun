package text_check;

import java.sql.*;

public class chunk_gen {
	private static int length=6;
	
	private static Connection c;
	private static Statement qstmt,stmt;
	private static ResultSet q;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			c = DriverManager.getConnection("jdbc:sqlite:base");
			stmt = c.createStatement();
			qstmt = c.createStatement();
			q = qstmt.executeQuery("select id,content from content where pid="+args[0]);
			while(q.next()) {
				
				String content = q.getString("content");
				int cid = q.getInt("id");
				
				System.out.println(content);
				
				for(int i=0;i <= content.length()-length;i++) {
					String chunk = content.substring(i, i+length);
					//System.out.println(chunk);
					
					int checksum=0;
					int pos=0;
					for(char c : chunk.toCharArray()) {
						pos++;
						//checksum
						checksum+= pos*pos*c;
					}
					stmt.executeUpdate("insert into chunks(cid,pos,content,checksum) values("+
					cid+","+i+",'"+chunk+"',"+checksum+")");	
				}
			}
		}catch(Exception e) {
			System.out.println("my bad");
			System.exit(0);
		}
	}
}
