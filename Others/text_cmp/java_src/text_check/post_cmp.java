package text_check;

import java.sql.*;

public class post_cmp {
	
	private static Connection c;
	private static Statement qstmt;//,stmt;
	private static ResultSet q;
	private static final int S_START=3;
	private static final int S_INNERLOOP=1;
	private static final int S_OUTPUT=2;
	private static final int S_QUIT=0;
	
	//private String query = "select *";
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//System.out.println(args[0]+args[1]);
		
		try {
			c = DriverManager.getConnection("jdbc:sqlite:base");
			qstmt = c.createStatement();
			
			
			q = qstmt.executeQuery("select chunks.cid,target.cid,chunks.pos,target.pos,"
					+ "chunks.content from chunks, content,"
					+ "(select chunks.* from chunks, content where chunks.cid = content.id and content.pid="
					+ args[0]
					+ ") as target where chunks.cid = content.id and content.pid="
					+ args[1]
					+ " and target.checksum=chunks.checksum and target.content=chunks.content"
					+ " order by chunks.cid,target.cid,chunks.pos asc;");
			
			//System.out.println("asdasdasd");
			
			int idx_stale=-1,_idx_stale=-1;
			int tag=0;
			int idx=0,_idx=0,pos=0,_pos=0;
			
			String chunk="", chunk_stale="", dup="";
			if(q.next()) {
				chunk_stale = q.getString(5);
				idx_stale = q.getInt(1);
				_idx_stale = q.getInt(2);
				pos = q.getInt(3);
				_pos = q.getInt(4);
				
				while(q.next()) {
					chunk = q.getString(5);
					idx = q.getInt(1);
					_idx = q.getInt(2);
					//pos = q.getInt(3);
					//_pos = q.getInt(4);
					while(idx==idx_stale && _idx==_idx_stale) {
						//loop for merging
						chunk_stale += chunk.substring(chunk.length()-1);
						chunk=chunk_stale;
						//System.out.println(chunk);
						if(q.next()) {
							chunk = q.getString(5);
							idx = q.getInt(1);
							_idx = q.getInt(2);
							//pos = q.getInt(3);
							//_pos = q.getInt(4);
						}else
							break;
					}
					
					System.out.println(idx_stale+" "+pos+" "+_idx_stale+" "+_pos+" "+chunk_stale);
					chunk_stale=chunk;
					idx_stale=idx;
					_idx_stale=_idx;
					try {
						pos = q.getInt(3);
						_pos = q.getInt(4);
					}catch(Exception e) {
						//
					}
				}
			}

		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		
	}

}
