package text_check;

import java.sql.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import text_check.merge_algo;
import text_check.result_set;

public class text_cmp_util {
	private static Connection c;
	private static Statement qstmt;//,stmt;
	private static ResultSet q;
	public static List<result_set<Integer,Integer,Integer,Integer,String>> cmp_core(int id, int _id) {
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
			
			int idx_stale=-1,_idx_stale=-1;
			int idx=0,_idx=0,pos=0,_pos=0;
			//System.out.println(q.getFetchSize());
			String chunk="", chunk_stale="";
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
	public static List<result_set<Integer,Integer,Integer,Integer,Integer>> cmp_core_len(int id, int _id) {
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
			
			int idx_stale=-1,_idx_stale=-1;
			int idx=0,_idx=0,pos=0,_pos=0;
			//System.out.println(q.getFetchSize());
			String chunk="", chunk_stale="";
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
					
					r.add(result_set.create(idx_stale, pos, _idx_stale, _pos, chunk_stale.length()));
					System.out.println(">"+idx_stale+" "+pos+" "+_idx_stale+" "+_pos+" "+chunk_stale);
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
				a.debug();
				ii_s.debug();
				
				ii_s = ii;
				while(idx == idx_s) {
					
					if(i.hasNext()) {
						ii=i.next();
						
						idx=ii.cid();
						pos = ii_s.pos();
						len = ii_s.match();
						a.add_val(pos, pos + len);
						a.debug();
						ii_s.debug();
						
						ii_s = ii;
					}else {
						
						pos = ii_s.pos();
						len = ii_s.match();
						a.add_val(pos, pos + len);
						a.debug();
						ii_s.debug();
						
						break;
					}
				}
				idx_s = idx;
				ii_s=ii;
				count+=a.check_out();
				a.debug();
				a.purge();
				
			}
		}
		
		return count;
	}

}
