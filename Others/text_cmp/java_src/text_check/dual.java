package text_check;

public class dual<A, B> {
	public A l;
	public B r;
	public dual(A l, B r) {
		this.l = l;
		this.r = r;
	}
	public void debug() {
		System.out.println(">"+this.l+" "+this.r);
	}
}
