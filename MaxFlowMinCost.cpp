// Ford Fulkerson: Runs in O(E * maxflow)

//be careful about   memset(h,-1,sizeof h);
int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], ecnt;
const int maxn = 2e3 + 17, maxm = maxn * maxn + 17, inf = 1e9 + 17;
void add(int v, int u, int vu, int uv = 0) {
	to[ecnt] = u, prv[ecnt] = head[v], cap[ecnt] = vu, head[v] = ecnt++;
	to[ecnt] = v, prv[ecnt] = head[u], cap[ecnt] = uv, head[u] = ecnt++;
}
int dfs(int v, int flow = inf) {
	if (v == sink || flow == 0) return f;
	if (mark[v]) return 0;
	mark[v] = 1;
	for (int e = head[v]; e != -1; e = prv[e])
		if (cap[e]) {
			int x = dfs(to[e], min(flow, cap[e]));
			if (x)
				return cap[e] -= x, cap[e ^ 1] += x, x;
		}
	return 0;
}
int maxflow() {
	int ans = 0;
	for (int tmp; (tmp = dfs(so)); ans += tmp)
		memset(mark, 0, sizeof mark);
	return ans;
}

// 
// min cost
int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], ecnt;
void add(int v, int u, int cst, int vu, int uv = 0) {
	prv[ecnt] = head[v], to[ecnt] = u, cap[ecnt] = vu, cost[ecnt] = cst, head[v] = ecnt++;
	prv[ecnt] = head[u], to[ecnt] = v, cap[ecnt] = uv, cost[ecnt] = -cst, head[u] = ecnt++;
}
int d[maxn], par[maxn];
bool mark[maxn];
bool spfa() {
	memset(d, 63, sizeof d);
	d[so] = 0;
	int h = 0, t = 0;
	q[t++] = so, par[so] = -1;
	while (h < t) {
		int v = q[h++];
		mark[v] = 0;
		for (int e = head[v]; ~e; e = prv[e])
			if (!mark[to[e]] && cap[e] && d[to[e]] > d[v] + cost[e])
				mark[to[e]] = 1, d[to[e]] = d[v] + cost[e], q[t++] = to[e], par[to[e]] = e;
	}
	return d[sink] < 1e9;
}
int mincost() {
	int ans = 0;
	while (spfa())
		for (int e = par[sink]; ~e; e = par[to[e ^ 1]])
			cap[e]--, cap[e ^ 1]++, ans += cost[e];
	return ans;
}