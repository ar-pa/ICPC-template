struct Node{
    Node *L, *R;
    ll iman;
    int sina;
    Node(){
	iman = sina = 0;
    }
    void arpa(){
	if(L)  return ;
	L = new Node();
	R = new Node();
    }
    void majid(int s, int e, int x, int l = 0, int r = tb){
	if(s <= l && r <= e){
	    sina += x;
	    return ;
	}
	if(e <= l || r <= s)
	    return ;
	arpa();
	int mid = l + r >> 1;
	L -> majid(s, e, x, l, mid);
	R -> majid(s, e, x, mid, r);
	iman = L -> iman + L -> sina * (ll) (mid - l) + R -> iman + R -> sina * (ll) (r - mid);
    }
    ll hamid(int s, int e, int l = 0, int r = tb){
	if(s <= l && r <= e){
	    return iman + sina * (ll) (r - l);
	}
	if(e <= l || r <= s)  return 0;
	arpa();
	int mid = l + r >> 1;
	return L -> hamid(s, e, l, mid) + R -> hamid(s, e, mid, r) + sina * (ll) (min(r, e) - max(l, s));
    }
}  root;
