// Dinic: O(V^2*E).
// Runs in O(E * sqrt(V)) for finding matching in bipartite graph (for more specification go to parsa's talabarg). 
const int maxn = 2e3 + 17, maxm = 5e4 + 17, inf = 1e9;
int ptr[maxn], head[maxn], prv[maxm], to[maxm], cap[maxm], d[maxn], q[maxn], dis[maxn], so = maxn - 1, sink = maxn - 2, ecnt;
void init(){
	memset(head, -1, sizeof head);
	ecnt = 0;
}
void add(int v, int u, int vu, int uv = 0){
	to[ecnt] = u, prv[ecnt] = head[v], cap[ecnt] = vu, head[v] = ecnt++;
	to[ecnt] = v, prv[ecnt] = head[u], cap[ecnt] = uv, head[u] = ecnt++;
}
bool bfs(){
	memset(dis, 63, sizeof dis);
	dis[so] = 0;
	int h = 0, t = 0;
	q[t++] = so;
	while(h < t){
		int v = q[h++];
		for(int e = head[v]; e >= 0; e = prv[e])
			if(cap[e] && dis[ to[e] ] > dis[v] + 1){
				dis[ to[e] ] = dis[v] + 1, q[t++] = to[e];
				if(to[e] == sink)
					return 1;
			}
	}
	return 0;
}
int dfs(int v, int f = inf){
	if(v == sink || f == 0)
		return f;
	int ret = 0;
	for(int &e = ptr[v]; e >= 0; e = prv[e])
		if(dis[v] == dis[ to[e] ] - 1){
			int x = dfs(to[e], min(f, cap[e]));
			f -= x, ret += x;
			cap[e] -= x, cap[e ^ 1] += x;
			if(!f)
				break;
		}
	return ret;
}
int mf(){
	int ans = 0;
	while(bfs()){
		memcpy(ptr, head, sizeof ptr);
		ans += dfs(so);
	}
	return ans;
}
