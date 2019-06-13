package text_check;

public class result_set<C, P, _C, _P, S> {
	private final C cid;
	private final _C _cid;
	private final P pos;
	private final _P _pos;
	private final S match;
	public result_set(C cid, P pos, _C _cid, _P _pos, S match) {
		this.cid = cid;
		this._cid = _cid;
		this.pos = pos;
		this._pos = _pos;
		this.match = match;
	}
	public static <C, P, _C, _P, S>result_set<C, P, _C, _P, S> create(C cid, P pos, _C _cid, _P _pos, S match) {
		return new result_set<C, P, _C, _P, S>(cid, pos, _cid, _pos, match);
	}
	public C cid() {return cid;}
	public _C _cid() {return _cid;}
	public P pos() {return pos;}
	public _P _pos() {return _pos;}
	public S match() {return match;}
	public void debug() {
		System.out.println(this.cid+" "+this.pos+" "+this._cid+" "+this._pos+" "+this.match);
	}
}
