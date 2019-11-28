package text_check;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import text_check.dual;

public class merge_algo {
	private final LinkedList<dual<Integer, Integer>> lst;
	private dual<Integer, Integer> xen, yum;
	
	private void removeList(final List<dual<Integer, Integer>> l) {
		Iterator<dual<Integer, Integer>> x = l.iterator();
		while(x.hasNext()) {
			this.lst.remove(x.next());
		}
	}
	public merge_algo() {
		lst = new LinkedList<dual<Integer, Integer>>();
		
		xen = null;
		yum = null;
	}
	public void purge() {
		removeList(lst);
	}
	public void add_val(int l, int r) {
		//compare and modify
		List<dual<Integer, Integer>> rm = new ArrayList<dual<Integer, Integer>>();
		if(lst.peek() != null) {//passed
			xen = lst.peekLast();
			if(xen.r < l) {
				lst.addLast(new dual<Integer, Integer>(l, r));
				return;
			}
			xen = lst.peekFirst();
			if(xen.l > r) {
				lst.addFirst(new dual<Integer, Integer>(l, r));
				return;
			}//passed
			Iterator<dual<Integer, Integer>> i=lst.iterator();
			while(i.hasNext()) {
				xen = i.next();
				//xen.debug();
				if(l <= xen.l)
					if(r <= xen.l) {
						//add new
						lst.add(lst.indexOf(xen), new dual<Integer, Integer>(l, r));
						return;
					}
					else if(r <= xen.r) {
						xen.l = l;
						return;
					}else {
						xen.l = l;
						break;//break point found
					}
						
			}//passed
			//
			//xen.debug();
			//this.debug();
			if(i.hasNext()) {
				//delete
				while(i.hasNext()) {
					yum = i.next();
					if(yum.l > r) {
						xen.r = r;
						this.removeList(rm);
						return;
						
					}else if(yum.r <= r) {
						//delete node
						//yum.debug();
						rm.add(yum);
						//lst.remove(lst.indexOf(yum));
						if(i.hasNext())
							continue;
						else {
							xen.r = r;
							this.removeList(rm);
							return;
						}
					}else {
						//merge two
						xen.r = yum.r;
						//yum.debug();
						rm.add(yum);
						//lst.remove(lst.indexOf(yum));
						this.removeList(rm);
						return;
					}
				}
			}else {
				if(xen.r < r)
					xen.r = r;
				return;
			}
			
		}else//passed
			lst.add(new dual<Integer, Integer>(l, r));
	}
	public int check_out() {
		int rtn=0;
		Iterator<dual<Integer, Integer>> i=lst.iterator();
		while(i.hasNext()) {
			xen = i.next();
			rtn += xen.r - xen.l;
			//xen.r=xen.l=0;
		}
		return rtn;
	}
	public void debug() {
		Iterator<dual<Integer, Integer>> i=lst.iterator();
		System.out.println("- - - - - - -");
		while(i.hasNext()) {
			xen = i.next();
			System.out.println(xen.l+" "+xen.r);
		}
		
	}
}
