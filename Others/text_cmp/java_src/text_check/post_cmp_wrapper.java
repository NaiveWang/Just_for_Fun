package text_check;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import text_check.text_cmp_util;
public class post_cmp_wrapper {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int code = Integer.parseInt(args[0]);
		int cnt;
		switch(code) {
		case 0://gen blocks
			text_cmp_util.gen_block();
			//no argumants
			break;
		case 1://gen chunks
			//get chunk size
			text_cmp_util.gen_chunk_all(Integer.parseInt(args[1]));
			break;
		case 2://cmp post-post
			//two post id
			List<result_set<Integer, Integer, Integer, Integer, Integer>> l= text_cmp_util.cmp_core_len(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
			Iterator<result_set<Integer, Integer, Integer, Integer, Integer>> i = l.iterator();
			while(i.hasNext()) {
				i.next().debug();
			}
			break;
		case 3://cmp post-List<post id>
			//post id, post num, post list
			List<Integer> l0 = new ArrayList<Integer>();
			cnt = Integer.parseInt(args[2]) + 3;
			
			for(int _cnt=3; _cnt < cnt; _cnt++) {
				l0.add(Integer.parseInt(args[_cnt]));
			}
			text_cmp_util.cmp_core_count_batch(Integer.parseInt(args[1]), l0);
			
			break;
		case 4://instance-post
			//instance string, post id, Blen
			text_cmp_util.temp_cmp(args[1], Integer.parseInt(args[3]), Integer.parseInt(args[2]));
			break;
		case 5://instance-List<post id>
			//instance string, post num, post id list
			List<Integer> l1 = new ArrayList<Integer>();
			cnt = Integer.parseInt(args[3]) + 4;
			for(int _cnt=4; _cnt < cnt; _cnt++) {
				l1.add(Integer.parseInt(args[_cnt]));
			}
			text_cmp_util.temp_cmp_batch(args[1], l1, Integer.parseInt(args[2]));
			break;
		default:
			System.out.println("Error Operate Code "+code);
				
		}
	}

}
