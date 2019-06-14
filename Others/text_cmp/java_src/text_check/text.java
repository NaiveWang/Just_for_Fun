package text_check;
import text_check.text_cmp_util;


import java.util.Arrays;

import text_check.merge_algo;
public class text {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		int cnt;
		
		cnt = text_cmp_util.cmp_core_count(text_cmp_util.cmp_core_len(6, 1));
		System.out.println(cnt);
		cnt = text_cmp_util.cmp_core_count(text_cmp_util.cmp_core_len(6, 2));
		System.out.println(cnt);
		
		cnt = text_cmp_util.post_word_count(9);
		System.out.println(cnt);*/
		//text_cmp_util.temp_cmp("人脸识别失败之后,国务院大堂总经理导致双输局面", 1, 3);
		text_cmp_util.temp_cmp_batch("人脸识别失败之后,国务院大堂总经理导致双输局面", Arrays.asList(1, 1, 1, 1, 1), 3);
		/*
		merge_algo i = new merge_algo();
		
		i.add_val(0, 1);
		i.add_val(10, 11);
		i.add_val(5, 6);
		i.debug();
		//i.add_val(1, 6);
		
		
		System.out.println(i.check_out());
		i.purge();
		i.debug();*/
	}

}
