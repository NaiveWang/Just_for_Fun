package text_check;

import text_check.text_cmp_util;
public class post_cmp_wrapper {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int src = Integer.parseInt(args[0]);
		int dst = Integer.parseInt(args[1]);
		
		int cnt = text_cmp_util.cmp_core_count(text_cmp_util.cmp_core_len(src, dst));
		int cntt = text_cmp_util.post_word_count(src);
		System.out.println(cnt+" "+cntt);
		
	}

}
