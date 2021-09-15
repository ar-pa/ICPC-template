int mat[N][2];
bool mark[N];

bool dfs(int v){
    if(mark[v])  return 0;
    mark[v] = 1;
    for(auto u : adj[v][0])
	if(mat[u][1] == -1 || dfs(mat[u][1]))
	    return mat[v][0] = u, mat[u][1] = v, 1;
    return 0;
}
void dfs(int v, int part){
    seen[v][part] = 1;
    for(auto u : adj[v][part])
	if(!seen[u][!part]){
	    bad[u] = 1;
	    seen[u][!part] = 1;
	    dfs(mat[u][!part], part);
	}
}
void maximum_matching() { // can be used to find max independent set
    memset(mat, -1, sizeof mat);
    bool br = 0;
    int ans = n;
    while(br ^= 1) {
		memset(mark, 0, sizeof mark);
		for(int i = 0; i < n; i++)
		    if(mat[i][0] == -1 && dfs(i))
				ans--, br = 0;
    }
    for(int i = 0; i < n; i++)
		for(int j = 0; j < 2; j++)
	    	if(seen[i][j] == 0 && mat[i][j] == -1)
				dfs(i, j);

    cout << ans << '\n';
    for(int i = 0; i < n; i++)
	if(bad[i] == 0 && seen[i][0] == 1)
	    cout << i + 1 << ' ';
    cout << '\n';
}
