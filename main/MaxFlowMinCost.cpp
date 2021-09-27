// Running Complexity is about O(SPFA() * Max_flow) but better. Can be O(N^3M) using dijkstra.
const int maxn = 1e2 + 17, maxm = 1e4 + 17, so = maxn - 1, sink = maxn - 2;
int head[maxn], to[maxm], prv[maxm], cap[maxm], cost[maxm], q[maxm * maxn], ecnt;
void init(){
    memset(head, -1, sizeof head);
    ecnt = 0;
}
void add(int v, int u, int cst = 0, int vu = 1, int uv = 0){
    prv[ecnt] = head[v], to[ecnt] = u, cap[ecnt] = vu, cost[ecnt] = cst, head[v] = ecnt++;
    prv[ecnt] = head[u], to[ecnt] = v, cap[ecnt] = uv, cost[ecnt] = -cst, head[u] = ecnt++;
}
int d[maxn], par[maxn];
bool mark[maxn];
bool spfa(){
    memset(d, 63, sizeof d);
    d[so] = 0;
    int h = 0, t = 0;
    q[t++] = so, par[so] = -1;
    while(h < t){
        int v = q[h++];
        mark[v] = 0;
        for(int e = head[v]; ~e; e = prv[e])
            if(cap[e] && d[to[e]] > d[v] + cost[e]){
                d[to[e]] = d[v] + cost[e];
                if(!mark[to[e]]){
                    mark[to[e]] = 1;
                    q[t++] = to[e];
                }
                par[to[e]] = e;
            }
    }
    return d[sink] < 1e9;
}
int mincost(){
    int ans = 0;
    while(spfa())
        for(int e = par[sink]; ~e; e = par[to[e ^ 1]])
            cap[e]--, cap[e ^ 1]++, ans += cost[e];
    return ans;
}