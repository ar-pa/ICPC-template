stack<int> stak;
inline void add_edge(int v, int u){
    g[v].push_back(u), g[u].push_back(v);
}
int get_cut(int v = 0, int p = -1){
    if(mark[v])  return h[v];
    hi[v] = h[v] = ~p ? h[p] + 1 : 0, mark[v] = 1;
    stak.push(v);
    for(auto u : adj[v])
	smin(hi[v], get_cut(u, v));
    if(hi[v] + 1 == h[v]){
	while(stak.top() != v)
	    add_edge(stak.top(), v + n), stak.pop();
	add_edge(v, v + n), stak.pop();
	add_edge(p, v + n);
    }
    return hi[v];
}
