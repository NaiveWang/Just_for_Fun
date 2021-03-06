package text_check;

import java.sql.*;


import java.util.StringTokenizer;

public class split_post_base {

	private static String buf, delimeter=",.．?!、:;；。，\n：;；？！ 		";
	private static Connection c;
	private static Statement qstmt, stmt;
	private static ResultSet q;
	public static void main(String[] args) {
		c = null;

		try {
			
			c = DriverManager.getConnection("jdbc:sqlite:base");
			//System.out.println(c);
			PreparedStatement ps=c.prepareStatement("insert into content(pid,content)values(?, ?)");
			stmt = c.createStatement();
			qstmt = c.createStatement();
			q = qstmt.executeQuery("select id, blah from post where is_split=0");
			
			while(q.next()) {
				
				int id=q.getInt(1);
				buf = q.getString(2);
				//System.out.println(id);
				StringTokenizer st = new StringTokenizer(buf,delimeter);
				
				while(st.hasMoreTokens()) {
					String content = st.nextToken();
					ps.setInt(1, id);
					ps.setString(2, content);
					ps.addBatch();
					
					
					//stmt.execute("insert into content(pid,content)values("+id+",'"+content+"')");
					//System.out.println(content);		
				}
				ps.executeBatch();
				ps.clearParameters();
				stmt.executeUpdate("update post set is_split=1 where id="+id);
			}

		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		
	}

}