// MaxFlow Dinic algorithm with scaling.
// O(N * M * log(MC)), where MC is maximum edge capacity.
// Based on problem http://informatics.mccme.ru/mod/statements/view3.php?chapterid=2784#1
// For not using long long, make all "ll"s int and change infs.
struct Edge {
    int a, b;
    ll f, c;
    Edge (int a, int b, ll f, ll c) : a(a), b(b), f(f), c(c) {};
};
const int INF_BFS=1e9;
const int MAXN = 550;
const ll INF_CAP = (ll)1e16;
int d[MAXN], source=MAXN-2, sink=MAXN-1;
int pt[MAXN]; // very important performance trick
vector <Edge> e;
vector <ll> g[MAXN];
ll lim;

void add_edge(int a, int b, ll ab_cap, ll ba_cap=0) {
    //keep edges in vector: e[ind] - direct edge, e[ind ^ 1] - back edge
    g[a].emplace_back(e.size());
    e.emplace_back(Edge(a, b, 0, ab_cap));

    g[b].emplace_back(e.size());
    e.emplace_back(Edge(b, a, 0, ba_cap));
}

bool bfs() {
    fill(d, d+MAXN, INF_BFS); // be cautious about using this.
    d[source] = 0;
    queue <int> q;
    q.push(source);
    while (!q.empty() && d[sink] == INF_BFS) {
        int cur = q.front(); q.pop();
        for (size_t i = 0; i < g[cur].size(); i++) {
            int id = g[cur][i];
            int to = e[id].b;
            //printf("cur = %d id = %d a = %d b = %d f = %d c = %d\n", cur, id, e[id].a, e[id].b, e[id].f, e[id].c);
            if (d[to] == INF_BFS && e[id].c - e[id].f >= lim) {
                d[to] = d[cur] + 1;
                q.push(to);
            }
        }
    }
    while (!q.empty())
        q.pop();
    return d[sink] != INF_BFS;
}

bool dfs(int v, ll flow) {
    if (flow == 0)
        return false;
    if (v == sink) {
        //cerr << v << endl;
        return true;
    }
    for (; pt[v] < g[v].size(); pt[v]++) {
        int id = g[v][pt[v]];
        int to = e[id].b;
        //printf("v = %d id = %d a = %d b = %d f = %d c = %d\n", v, id, e[id].a, e[id].b, e[id].f, e[id].c);
        if (d[to] == d[v] + 1 && e[id].c - e[id].f >= flow) {
            bool pushed = dfs(to, flow);
            if (pushed) {
                e[id].f += flow;
                e[id ^ 1].f -= flow;
                return true;
            }
        }
    }
    return false;
}

ll dinic() {
    ll flow=0;
    for (lim = (1LL << 62); lim >= 1;) {
        if (!bfs()) {
            lim >>= 1;
            continue;
        }
        fill(pt, pt + MAXN, 0); // be cautious about this one.
        while (dfs(source, lim)) {
            flow = flow + lim;
        }
        //cerr << flow << endl;
    }
    return flow;
}