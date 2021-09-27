struct Sat {
	int n = maxn, col[maxn] = {}, cnt, ver[maxn] = {}, versz, cer[maxn];
	vector<int> g[maxn], rg[maxn];
	bool mrk[maxn] = {};
	void addE(int x, int y) {
		g[x].push_back(y);
		rg[y].push_back(x);
	}
	void addOr(int x, int y) {
		addE(x ^ 1, y);
		addE(y ^ 1, x);
	}
	void dfsadd(int v){
		mrk[v]=1; for(auto &u:g[v])if(!mrk[u])dfsadd(u);
		ver[versz++]=v;
	}
	void dfsset(int v){
		col[v]=cnt;
		for(auto &u:rg[v])
			if(col[u]==-1)
				dfsset(u);
	}
	bool ok() {
		memset(mrk, 0, n);
		memset(col, -1, n * sizeof col[0]);
		for(int v = 0; v < n; v++)
			if(!mrk[v])
				dfsadd(v);
			while(versz)if(col[ver[--versz]]==-1) dfsset(ver[versz]), cnt++;
		for(int v = 0; v < n; v += 2)
			if(col[v]==col[v^1])
				return 0;
			else
				cer[v] = col[v^1] < col[v];
		return 1;
	}
}  sat;
