package text_check;

import java.sql.*;

public class chunk_gen_base {
	private static int length=6;
	
	private static Connection c;
	private static Statement qstmt,stmt;
	private static ResultSet q;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			length = Integer.parseInt(args[0]);
			c = DriverManager.getConnection("jdbc:sqlite:base");
			stmt = c.createStatement();
			qstmt = c.createStatement();
			PreparedStatement psc=c.prepareStatement("insert into chunks(cid, pos, content, checksum) values(?, ?, ?, ?)");
			
			q = qstmt.executeQuery("select id,content from content where is_chunk_ready=0");
			while(q.next()) {
				
				String content = q.getString("content");
				int cid = q.getInt("id");
				
				//System.out.println(content);
				
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
					psc.setInt(1, cid);
					psc.setInt(2, i);
					psc.setString(3, chunk);
					psc.setInt(4, checksum);
					psc.addBatch();
					//stmt.executeUpdate("insert into chunks(cid,pos,content,checksum) values("+
					//cid+","+i+",'"+chunk+"',"+checksum+")");	
				}
				psc.executeBatch();
				psc.clearParameters();
				stmt.executeUpdate("update content set is_chunk_ready=1 where id="+cid);
			}
		}catch(Exception e) {
			System.out.println("my bad");
			System.exit(0);
		}
	}
}