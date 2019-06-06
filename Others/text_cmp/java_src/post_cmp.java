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
			int idx=0,_idx=0,pos=0,_pos=0;
			
			String chunk="", dup="";
			if(q.next()) {
				chunk = q.getString(5);
				idx_stale = q.getInt(1);
				_idx_stale = q.getInt(2);
				pos = q.getInt(3);
				_pos = q.getInt(4);
			}else {
				System.out.println("Nothing matched");
				System.exit(0);
			}
			if(q.next()) {
				dup = q.getString(5);
				idx = q.getInt(1);
				_idx = q.getInt(2);
				pos = q.getInt(3);
				_pos = q.getInt(4);
				
				int state = S_START;
				boolean flag=true;
				
				while(flag) {
					switch(state) {
					case S_START:
						
						if(idx == idx_stale && _idx == _idx_stale) {
							state = S_INNERLOOP;
							break;
						}else {
							idx_stale = idx;
							_idx_stale = _idx;
							//chunk=dup;
							state = S_OUTPUT;
						}

						break;
					case S_INNERLOOP:
						//dup = q.getString(5);
						chunk+=dup.substring(dup.length()-1);
						//System.out.println(chunk);
						state = S_START;
						if(idx != idx_stale || _idx != _idx_stale)
							state = S_OUTPUT;
						if(q.next()) {
							idx = q.getInt(1);
							_idx = q.getInt(2);
							pos = q.getInt(3);
							_pos = q.getInt(4);
							dup = q.getString(5);
						}else {
							state=S_QUIT;
							break;
						}
						break;
					case S_OUTPUT:
						System.out.println(idx+" "+pos+" "+_idx+" "+_pos+" "+chunk);
						state = S_START;
						chunk=dup;
						if(q.next()) {
							idx = q.getInt(1);
							_idx = q.getInt(2);
							pos = q.getInt(3);
							_pos = q.getInt(4);
							dup = q.getString(5);
						}else {
							state=S_QUIT;
							break;
						}
						break;
					case S_QUIT:
						System.out.println(idx+" "+pos+" "+_idx+" "+_pos+" "+chunk);
						flag=false;
					}
				}
				
				
			}else {
				
				System.out.println(idx+" "+pos+" "+_idx+" "+_pos+" "+chunk);
			}

			
			
			
		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		
	}

}
