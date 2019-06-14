package text_check;

import java.sql.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

import text_check.merge_algo;
import text_check.result_set;
import text_check.db_conf;
public class text_cmp_util {
	private static String delimeter = ",.．?!、:;；。，\n：;；？！ 		";
	private static Connection c;
	private static Statement qstmt;//, stmt;
	private static ResultSet q;
	private static Connection initConnection() {
		try {
			c = DriverManager.getConnection("jdbc:sqlite:"+db_conf.db);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return c;
	}
	private static List<result_set<Integer,Integer,Integer,Integer,String>> core(ResultSet rst) {
		// TODO Auto-generated method stub
		//System.out.println(args[0]+args[1]);
		/*	@Author Elvin Wang@https://github.com/NaiveWang
		 * 
		 * this algorithm is strongly relay on the database sequence. 
		 * the advantage we took here is save more computing time, 
		 * the O(n^2) would be reduced to O(n) and since the database uses BTree(O(log2n)), 
		 * the whole algorithm would be optimized from O(log2n*n^2) to O(log2(n+1)*n). 
		 * 
		 * 
		 * bug : if one block has two identical blocks, the merged string would be repeated. 
		 * bug fix : retrieve the position value to skip repeated string (not implemented).
		 */
		List<result_set<Integer,Integer,Integer,Integer,String>> r = new ArrayList<result_set<Integer, Integer, Integer, Integer, String>>();
		try {
			
			
			int idx_stale=-1,_idx_stale=-1;
			int idx=0,_idx=0,pos=0,_pos=0;
			String chunk="", chunk_stale="";
			if(rst.next()) {
				chunk_stale = rst.getString(5);
				idx_stale = rst.getInt(1);
				_idx_stale = rst.getInt(2);
				pos = rst.getInt(3);
				_pos = rst.getInt(4);
				
				while(rst.next()) {
					chunk = rst.getString(5);
					idx = rst.getInt(1);
					_idx = rst.getInt(2);
					while(idx==idx_stale && _idx==_idx_stale) {
						//loop for merging
						chunk_stale += chunk.substring(chunk.length()-1);
						chunk=chunk_stale;
						//System.out.println(chunk);
						if(rst.next()) {
							chunk = rst.getString(5);
							idx = rst.getInt(1);
							_idx = rst.getInt(2);
						}else
							break;
					}
					
					r.add(result_set.create(idx_stale, pos, _idx_stale, _pos, chunk_stale));
					//System.out.println(idx_stale+" "+pos+" "+_idx_stale+" "+_pos+" "+chunk_stale);
					chunk_stale=chunk;
					idx_stale=idx;
					_idx_stale=_idx;
					try {
						pos = q.getInt(3);
						_pos = q.getInt(4);
					}catch(Exception e) {
						//
						
						return r;
					}
				}
			}
			
		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		return r;
	}
	private static List<result_set<Integer,Integer,Integer,Integer,Integer>> core_len(ResultSet rst) {
		// TODO Auto-generated method stub
		//System.out.println(args[0]+args[1]);
		/*	@Author Elvin Wang@https://github.com/NaiveWang
		 * 
		 * This method returns a length instead.
		 * 
		 * bug : if one block has two identical blocks, the merged string would be repeated. 
		 * bug fix : retrieve the position value to skip repeated string (not implemented).
		 */
		List<result_set<Integer,Integer,Integer,Integer,Integer>> r = new ArrayList<result_set<Integer, Integer, Integer, Integer, Integer>>();
		try {
			
			
			int idx_stale=-1,_idx_stale=-1;
			int idx=0,_idx=0,pos=0,_pos=0;
			String chunk="", chunk_stale="";
			if(rst.next()) {
				chunk_stale = rst.getString(5);
				idx_stale = rst.getInt(1);
				_idx_stale = rst.getInt(2);
				pos = rst.getInt(3);
				_pos = rst.getInt(4);
				
				while(rst.next()) {
					chunk = rst.getString(5);
					idx = rst.getInt(1);
					_idx = rst.getInt(2);
					while(idx==idx_stale && _idx==_idx_stale) {
						//loop for merging
						chunk_stale += chunk.substring(chunk.length()-1);
						chunk=chunk_stale;
						//System.out.println(chunk);
						if(rst.next()) {
							chunk = rst.getString(5);
							idx = rst.getInt(1);
							_idx = rst.getInt(2);
						}else
							break;
					}
					
					r.add(result_set.create(idx_stale, pos, _idx_stale, _pos, chunk_stale.length()));
					//System.out.println(idx_stale+" "+pos+" "+_idx_stale+" "+_pos+" "+chunk_stale);
					chunk_stale=chunk;
					idx_stale=idx;
					_idx_stale=_idx;
					try {
						pos = q.getInt(3);
						_pos = q.getInt(4);
					}catch(Exception e) {
						//
						
						return r;
					}
				}
			}
			
		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		return r;
	}
	public static List<result_set<Integer,Integer,Integer,Integer,String>> cmp_core(int id, int _id) {

		try {
			c = DriverManager.getConnection("jdbc:sqlite:base");
			qstmt = c.createStatement();
			
			
			q = qstmt.executeQuery("select chunks.cid,target.cid,chunks.pos,target.pos,"
					+ "chunks.content from chunks, content,"
					+ "(select chunks.* from chunks, content where chunks.cid = content.id and content.pid="
					+ id
					+ ") as target where chunks.cid = content.id and content.pid="
					+ _id
					+ " and target.checksum=chunks.checksum and target.content=chunks.content"
					+ " order by chunks.cid,target.cid,chunks.pos asc;");
			
			//System.out.println("asdasdasd");
		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		return core(q);
		
	}
	public static List<result_set<Integer,Integer,Integer,Integer,Integer>> cmp_core_len(int id, int _id) {
		try {
			c = DriverManager.getConnection("jdbc:sqlite:"+db_conf.db);
			qstmt = c.createStatement();
			q = qstmt.executeQuery("select chunks.cid,target.cid,chunks.pos,target.pos,"
					+ "chunks.content from chunks, content,"
					+ "(select chunks.* from chunks, content where chunks.cid = content.id and content.pid="
					+ id
					+ ") as target where chunks.cid = content.id and content.pid="
					+ _id
					+ " and target.checksum=chunks.checksum and target.content=chunks.content"
					+ " order by chunks.cid,target.cid,chunks.pos asc;");
			
			//System.out.println("asdasdasd");
		}catch(Exception e) {
			System.out.println(e);
			System.exit(0);
		}
		return core_len(q);
		
	}
	public static int cmp_core_count(List<result_set<Integer,Integer,Integer,Integer,Integer>> l){
		int count=0;
		/*
		 * @Author Elvin Wang@https://github.com/NaiveWang
		 * 
		 * this method would count all of the overlapped matches 
		 * and count'em to be a return integer, which is assumed to
		 * be the overlapped size of the whole text.
		 * 
		 * of course, this would be like the overlap size of the alpha one, 
		 * which is the source one. 
		 * 
		 * Then the algorithm is based on an assumption that the alpha block
		 * sequence of the passed list is sorted and at the decreasing order.
		 * without this scenario, error will occur.
		 */
		//the set[0,2,4] are needed. 
		int idx, idx_s, pos, len;
		boolean tag;
		Iterator<result_set<Integer, Integer, Integer, Integer, Integer>> i = l.iterator();
		result_set<Integer, Integer, Integer, Integer, Integer> ii,ii_s;
		merge_algo a = new merge_algo();
		if(i.hasNext()) {
			ii_s=i.next();
			idx_s=ii_s.cid();
			//ii_s.debug();
			
			while(i.hasNext()) {
				ii=i.next();
				idx=ii.cid();
				
				pos = ii_s.pos();
				len = ii_s.match();
				a.add_val(pos, pos + len);
				//a.debug();
				//ii_s.debug();
				
				ii_s = ii;
				tag=true;
				while(idx == idx_s) {
					tag=false;
					if(i.hasNext()) {
						ii=i.next();
						
						idx=ii.cid();
						pos = ii_s.pos();
						len = ii_s.match();
						a.add_val(pos, pos + len);
						//a.debug();
						//ii_s.debug();
						
						ii_s = ii;
					}else {
						
						pos = ii_s.pos();
						len = ii_s.match();
						a.add_val(pos, pos + len);
						//a.debug();
						//ii_s.debug();
						
						break;
					}
				}
				if(tag) {
					idx_s = idx;
					ii_s=ii;
					count+=a.check_out();
					//System.out.println("- - - - - - - -");
					//a.debug();
					a.purge();
				}
				
			}
			pos = ii_s.pos();
			len = ii_s.match();
			a.add_val(pos, pos + len);
			//ii_s.debug();
			//System.out.println("- - - - - - - -");
			count+=a.check_out();
		}
		
		return count;
	}
	public static int post_word_count(int id) {
		int rtn = 0;
		try {
			c = DriverManager.getConnection("jdbc:sqlite:base");
			qstmt = c.createStatement();
			q = qstmt.executeQuery("select content from content where pid = "+id);
			while(q.next()) {
				rtn += q.getString(1).length();
			}
			
			
		}catch(Exception e) {
			System.out.println(e);
			System.exit(-1);
		}
			
		return rtn;
	}
	public static void block_gen(Connection c, int pid) {
		try {
			PreparedStatement ps=c.prepareStatement("insert into content(pid,content)values(?, ?)");
			
			qstmt = c.createStatement();
			q=qstmt.executeQuery("select blah from post where id = "+pid);
			StringTokenizer st = new StringTokenizer(q.getString(1), delimeter);
			while(st.hasMoreTokens()) {
				String content = st.nextToken();
				ps.setInt(1, pid);
				ps.setString(2, content);
				ps.addBatch();
			}
			ps.executeBatch();
			ps.clearParameters();
		}catch(Exception e) {
			System.out.println(e);
			System.exit(-1);
		}
	}
	private static void block_gen_temp(Connection c, String post) {
		/*
		 * We assumed that the temporary table is called '_blocks'
		 */
		try {
			PreparedStatement ps=c.prepareStatement("insert into "+db_conf.blocks_temp+"(content)values(?)");
			
			StringTokenizer st = new StringTokenizer(post, delimeter);
			while(st.hasMoreTokens()) {
				String content = st.nextToken();
				ps.setString(1, content);
				ps.addBatch();
			}
			ps.executeBatch();
			ps.clearParameters();
		}catch(Exception e) {
			System.out.println(e);
			System.exit(-1);
		}
	}
	public static void chunk_gen(Connection c, String chunk_table, String block_table, int lenB) {
		try {
			//stmt = c.createStatement();
			qstmt = c.createStatement();
			
			PreparedStatement psc=c.prepareStatement("insert into "+chunk_table+"(cid, pos, content, checksum) values(?, ?, ?, ?)");
			q = qstmt.executeQuery("select id,content from "+block_table);
			while(q.next()) {
				String content = q.getString("content");
				int cid = q.getInt("id");
				for(int i=0;i <= content.length()-lenB;i++) {
					String chunk = content.substring(i, i+lenB);
					//System.out.println(chunk);
					
					int checksum=0;
					int pos=0;
					for(char chr : chunk.toCharArray()) {
						pos++;
						//checksum
						checksum+= pos*pos*chr;
					}
					psc.setInt(1, cid);
					psc.setInt(2, i);
					psc.setString(3, chunk);
					psc.setInt(4, checksum);
					psc.addBatch();
				}
				psc.executeBatch();
				psc.clearParameters();
			}
			
		}catch(Exception e) {
			System.out.println(e);
			System.exit(-1);
		}
	}
	private static Connection temp_core_init(Connection c, String post, int lenB) {
		/*
		 * This method would create a temporary table to extract the raw text in to a virtual table
		 * to achieve the performance perks. 
		 * Note : in the case of a multi-user server, this temp table name
		 * should be set as a random value to avoid conflicts. 
		 * This method would out put a list of the raw and a word counter. 
		 */
		
		try {
			qstmt = c.createStatement();
			qstmt.execute("CREATE temp TABLE \""+db_conf.blocks_temp+"\" (\n" + 
					"	\"id\"	INTEGER PRIMARY KEY AUTOINCREMENT,\n" + 
					"	\"content\"	TEXT" + 
					")");
			block_gen_temp(c, post);
			qstmt.execute("CREATE temp TABLE \""+db_conf.chunks_temp+"\" (\n" + 
					"	\"id\"	INTEGER PRIMARY KEY AUTOINCREMENT,\n" + 
					"	\"cid\"	INTEGER,\n" + 
					"	\"pos\"	INTEGER,\n" + 
					"	\"content\"	TEXT,\n" + 
					"	\"checksum\"	INTEGER\n" + 
					")");
			chunk_gen(c, db_conf.chunks_temp, db_conf.blocks_temp, lenB);
			q = qstmt.executeQuery("select _chunks.content from _chunks");
			int cnt=0;
			while(q.next()) {
				System.out.println(q.getString(1));
				cnt+=q.getString(1).length();
			}
			System.out.println(cnt+"\n");
		}catch(Exception e) {
			System.out.println(e);
			System.exit(-1);
		}
		return c;
	}
	private static Connection temp_core_cmp(Connection c, int id) {
		/*
		 * Hi there ! You need to initialize the connection which contains the
		 * in-memory volatile table first. 
		 * To serve the wrapper, the output was appointed to the IO buffer, which can be called by
		 * the subprocess call. 
		 * the output stream would be the matched penta tuple and the overlaped counter(x,0,0,0,0)
		 */
		try {
			q = qstmt.executeQuery("select "+db_conf.chunks_temp+".cid,target.cid,"+db_conf.chunks_temp+".pos,target.pos,"
					+db_conf.chunks_temp+".content from "+db_conf.chunks_temp+", "+db_conf.blocks_temp+","
					+ "(select chunks.* from chunks, content where chunks.cid = content.id and content.pid="
					+ id
					+ ") as target where "+db_conf.chunks_temp+".cid = _blocks.id"
					+ " and target.checksum="+db_conf.chunks_temp+".checksum and target.content="+db_conf.chunks_temp+".content"
					+ " order by "+db_conf.chunks_temp+".cid,target.cid,"+db_conf.chunks_temp+".pos asc;");
			List<result_set<Integer,Integer,Integer,Integer,Integer>> lst = core_len(q);
			Iterator<result_set<Integer, Integer, Integer, Integer, Integer>> i = lst.iterator();
			while(i.hasNext()) 
				i.next().debug();

			System.out.println(cmp_core_count(lst)+"\n");
		}catch(Exception e) {
			System.out.println(e);
			System.exit(-1);
		}
		return c;
	}
	public static void temp_cmp(String post, int id, int lenB) {
		c=temp_core_init(initConnection(), post, lenB);
		temp_core_cmp(c, id);
	}
	public static void temp_cmp_batch(String post, List<Integer> idL, int lenB) {
		c=temp_core_init(initConnection(), post, lenB);
		Iterator<Integer> i = idL.iterator();
		while(i.hasNext())
			temp_core_cmp(c, i.next());
	}
	

}
