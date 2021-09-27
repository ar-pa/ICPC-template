bool mark[maxn], in_comp[maxn];
vector<int> g[maxn], rg[maxn];
void dfs(int v, vector<int> *g, vector<int> &vec){
    mark[v] = 1;
    for(auto u : g[v])
	if(!mark[u])
	    dfs(u, g, vec);
    vec.push_back(v);
}
bool mark[maxn], in_comp[maxn];
int main(){
    vector<int> all;
    for(int i = 0; i < n; i++)
	if(!mark[i])
	    dfs(i, g, all);
    memset(mark, 0, sizeof mark);
    reverse(all.begin(), all.end());
    for(auto v : all){
	if(mark[v])  continue;
	vector<int> comp;
	dfs(v, rg, comp);
	for(auto u : comp)  in_comp[u] = 1;
	for(auto u : comp)  in_comp[u] = 0;
    }
}
