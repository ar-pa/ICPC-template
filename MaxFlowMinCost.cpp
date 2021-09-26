// Running Complexity is about O(SPFA() * Max_flow) but better. Can be O(N^3M) using dijkstra.
const int maxn=3000;
const int maxm=30*maxn;
const int INF=1e5;
int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], ecnt, source=maxn-2, sink=maxn-1;
int q[maxm]; // Be cautious about this size of the SPFA queue.
void init() {memset(head, -1, sizeof head); ecnt = 0;} // Call me.
void add_edge(int v, int u, int cst, int vu, int uv=0) {
    prv[ecnt] = head[v], to[ecnt] = u, cap[ecnt] = vu, cost[ecnt] = cst, head[v] = ecnt++;
    prv[ecnt] = head[u], to[ecnt] = v, cap[ecnt] = uv, cost[ecnt] = -cst, head[u] = ecnt++;
}
int d[maxn], par[maxn];
int spfa() {
    memset(d, 31, sizeof d);
    d[source] = 0;
    int h = 0, t = 0;
    q[t++] = source, par[source] = -1;
    while (h < t) {
        int v = q[h++];
        for (int e = head[v]; ~e; e = prv[e])
            if (cap[e] && d[to[e]] > d[v] + cost[e])
                d[to[e]] = d[v] + cost[e], q[t++] = to[e], par[to[e]] = e;
    }
    if(d[sink] < 1e9) {
        int flow=INF;
        for (int e = par[sink]; ~e; e = par[to[e ^ 1]])
            flow=min(flow, cap[e]);
        return flow;
    } return 0;
}
int mincost() {
    int ans = 0, flow=0;
    for (int tmp; (tmp=spfa()); flow+=tmp)
        for (int e = par[sink]; ~e; e = par[to[e ^ 1]])
            cap[e] -= tmp, cap[e ^ 1] += tmp, ans += cost[e] * tmp;
    return flow*INF-ans;
}