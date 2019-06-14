package text_check;

import java.util.Iterator;
import java.util.List;

import text_check.text_cmp_util;
public class post_cmp_wrapper {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int code = Integer.parseInt(args[0]);
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
			break;
		case 4://instance-post
			//instance string, post id, Blen
			text_cmp_util.temp_cmp(args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
			break;
		case 5://instance-List<post id>
			//instance string, post num, post id list
			break;
		default:
			System.out.println("Error Operate Code "+code);
				
		}
	}

}
