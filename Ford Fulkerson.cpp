// Ford Fulkerson: Runs in O(E * maxflow)
int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], ecnt;
const int maxn = 2e3 + 17, maxm = maxn * maxn + 17, inf = 1e9 + 17;
void init() {
	memset(head, -1, sizeof head);
    ecnt = 0;
}
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