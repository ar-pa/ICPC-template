#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
const int N = int(2e5)+1;
const int M = int(2e5)+1;
const int LOGN = 20;
VI g[N],tree[N],st;//graph in edge-list form. N should be 2*N
int U[M],V[M],low[N],ord[N],sz[N],depth[N],col[N],C,T,compNo[N],extra[N],level[N],DP[LOGN][N];
bool isArtic[N];
int arr[N],dep[N],vis[N];
int adj(int u,int e){
    return u^V[e]^U[e];
}
//everything from [1,n+C] whose extra[i]=0 is part of Block-Tree 
//1-Based Graph Input.Everything from [1,C] is type B and [C,n+C] is type C.
void dfs(int i){
    low[i]=ord[i]=T++;
    for(int j=0;j<SZ(g[i]);j++){
	int ei=g[i][j],to = adj(i,ei);
	if(ord[to]==-1){
	    depth[to]=depth[i]+1;
	    st.PB(ei);dfs(to);
	    low[i] = min(low[i],low[to]);
	    if(ord[i]==0||low[to]>=ord[i]){
		if(ord[i]!=0||j>=1)
		    isArtic[i] = true;
		++C;
		while(!st.empty()){
		    int fi=st.back();st.pop_back();
		    col[fi]=C;
		    if(fi==ei)break;
		}
	    }
	}else if(depth[to]<depth[i]-1){
	    low[i] = min(low[i],ord[to]);
	    st.PB(ei);
	}
    }
}
void run(int n){
    SET(low,-1);SET(depth,-1);
    SET(ord,-1);SET(col,-1);
    SET(isArtic,0);st.clear();C=0;
    for(int i=1;i<=n;++i)
	if(ord[i]==-1){
	    T = 0;dfs(i);
	}
}
void buildTree(int n){
    run(n);SET(compNo,-1);
    VI tmpv;SET(extra,-1);
    tmpv.clear();SET(sz,0);
    for(int i=1;i<=n;i++){
	tmpv.clear();
	for(auto e:g[i])
	    tmpv.PB(col[e]);
	sort(ALL(tmpv));
	tmpv.erase(unique(ALL(tmpv)), tmpv.end());
	//handle isolated vertics
	if(tmpv.empty()){
	    compNo[i]=C+i;extra[C+i]=0;
	    sz[C+i]=1;continue;
	}if(SZ(tmpv)==1){//completely in 1 comp.
	    compNo[i]=tmpv[0];
	    extra[tmpv[0]]=0;
	    sz[tmpv[0]]++;
	}else{ //it's an articulation vertex.
	    compNo[i]=C+i;
	    extra[C+i]=0;sz[C+i]++;
	    for(auto j:tmpv){
		extra[j]=0;sz[j]++;
		tree[C+i].push_back(j);
		tree[j].push_back(C+i);
	    }
	}
    }
}
int currComp;
void dfs2(int u,int p){
    level[u]=level[p]+1;DP[0][u]=p;
    arr[u]=++T;vis[u]=currComp;
    for(auto w:tree[u])
	if(w!=p)
	    dfs2(w,u);
    dep[u]=T++;
}
int lca(int a,int b){
    if(level[a]>level[b])swap(a,b);
    int d = level[b]-level[a];
    for(int i=0;i<LOGN;i++)
	if((1<<i)&d)
	    b = DP[i][b];
    if(a==b)return a;
    for(int i=LOGN-1;i>=0;i--)
	if(DP[i][a]!=DP[i][b])
	    a=DP[i][a],b=DP[i][b];
    return DP[0][a];
}
bool anc(int p,int u){
    return (arr[u]>=arr[p] && dep[u]<=dep[p]);
}
int main()
{
    int n,m,q;
    si(n);si(m);si(q);
    for(int i=0;i<m;i++){
	scanf("%d %d",U+i,V+i);
	g[U[i]].PB(i);
	g[V[i]].PB(i);
    }
    buildTree(n);T=0;
    for(int i=1;i<=C+n;i++)
	if(!vis[i] && !extra[i])
	    currComp++,dfs2(i,i);
    for(int i=1;i<LOGN;i++)
	for(int j=1;j<=C+n;j++)
	    if(!extra[j])
		DP[i][j]=DP[i-1][DP[i-1][j]];
    while(q--){
	int u,v,w;
	si(u);si(v);si(w);
	if(u==v){
	    puts(u==w?"Party":"Break-Up");
	    continue;
	}
	u=compNo[u];v=compNo[v];w=compNo[w];
	if(!(vis[u]==vis[w] && vis[w]==vis[v])){
	    puts("Break-Up");
	    continue;
	}
	int LCA = lca(u,v);
	if(level[u]>level[v])swap(u,v);
	if(sz[w]==1 && w!=LCA && w!=DP[0][LCA] && sz[DP[0][w]]>2) w = DP[0][w];
	if(sz[u]==1 && u!=LCA && sz[DP[0][w]]>2) u = DP[0][u];
	if(sz[v]==1 && v!=LCA && sz[DP[0][v]]>2) v = DP[0][v];
	bool ok=false;
	ok|=anc(w,u);
	ok|=anc(w,v);
	ok&=anc(LCA,w);
	ok|=(sz[LCA]>2 && w==DP[0][LCA]);
	puts(ok?"Party":"Break-Up");
    }
    return 0;
}
