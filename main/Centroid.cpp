#include <bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> ppi;
const int maxn = 2e5 + 17, lg = 18;

int n = 1, q, par[maxn][lg], cpar[maxn], h[maxn], sz[maxn];
set<ppi> s[maxn];
vector<int> g[maxn], ch[maxn];
struct Q{
  int t, v, d;
}  qu[maxn];
void prep(int v = 0){
  sz[v] = 1;
  for(auto u : g[v]){
    prep(u);
    sz[v] += sz[u];
  }
}
int get_cent(int root = 0){
  int v = root, size = sz[root];
  bool done = 0;
  while(done ^= 1)
    for(auto &u : g[v])
      if(sz[u] > (size >> 1)){
        v = u, done = 0;
        break;
      }
  int mysz = sz[v];
  for(int u = v; ; u = par[u][0]){
    sz[u] -= mysz;
    if(u == root)  break;
  }
  for(auto &u : g[v])
    if(sz[u]){
      int x = get_cent(u);
      //cerr << v << ' ' << x << '\n';
      cpar[x] = v;
      ch[v].pb(x);
    }
  if(v != root){
    int x = get_cent(root);
    //cerr << v << ' ' << x << '\n';
    cpar[x] = v;
    ch[v].pb(x);
  }
  return v;
}
int dis(int v, int u){
    if(h[u] < h[v])  swap(v, u);
    int ans = h[v] + h[u];
    for(int i = 0; i < lg; i++)
  if((h[u] - h[v]) >> i & 1)
      u = par[u][i];
    for(int i = lg - 1; i >= 0; i--)
  if(par[v][i] != par[u][i])
      v = par[v][i], u = par[u][i];
    return v == u ? ans - 2 * h[v] : ans - 2 * (h[v] - 1);
}
void add(int v){
  for(int u = v; u != -1; u = cpar[u]){
    if(v == 6)
      ;//cerr << u << '\n';
    int d = dis(u, v);
    auto it = s[u].lower_bound({{d + 1, -1}, -1});
    if(it != s[u].begin() && prev(it) -> X.Y >= h[v])
      continue;
    it = s[u].insert({{d, h[v]}, v}).X;
    it++;
    while(it != s[u].end() && it -> X.Y <= h[v])
      s[u].erase(prev(++it));
  }
}
int get(int v, int d){
  int ans = -1, cer = -1;
  for(int u = v; u != -1; u = cpar[u]){
    int di = dis(u, v);
    //cerr << u << '\n';
    auto it = s[u].lower_bound({{d - di + 1, -1}, -1});
    if(it != s[u].begin()){
      it--;
      if(it -> X.Y > ans)
        ans = it -> X.Y, cer = it -> Y;
    }
  }
  return cer;
}



/////////////////////////////////////////////////////////////////////////////////////////////


#include <bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> ppi;
typedef long long ll;
const int maxn = 5e5 + 17, lg = 19;
const ll inf = 1e18;
int n, q, par[maxn][lg], cpar[maxn], h[maxn], sz[maxn], che[maxn];
ll sw[maxn][lg], ns[maxn], sd[maxn][lg];
vector<int> ch[maxn];
vector<pii> g[maxn];
bool mark[maxn];
void prep(int v = 0, int p = 0){
  sz[v] = 1;
  par[v][0] = p;
  for(auto e : g[v])
    if(e.X != p){
      h[e.X] = h[v] + 1;
      sw[e.X][0] = e.Y;
      prep(e.X, v);
      sz[v] += sz[e.X];
    }
}
void setD(int v, int lvl, int p = -1, ll cd = 0){
  if(mark[v])
    return ;
  sd[v][lvl] = cd;
  for(auto e : g[v])
    if(e.X != p)
      setD(e.X, lvl, v, cd + e.Y);
}
int get_cent(int root = 0, int h = 0){
  int v = root, size = sz[root];
  bool done = 0;
  while(done ^= 1)
    for(auto &e : g[v])
      if(e.X != par[v][0] && sz[e.X] > (size >> 1)){
        v = e.X, done = 0;
        break;
      }
  che[v] = h;
  setD(v, h);
  mark[v] = 1;
  int mysz = sz[v];
  for(int u = v; ; u = par[u][0]){
    sz[u] -= mysz;
    if(u == root)  break;
  }
  for(auto &e : g[v])
    if(e.X != par[v][0] && sz[e.X]){
      int x = get_cent(e.X, h + 1);
      //cerr << v << ' ' << x << '\n';
      cpar[x] = v;
      ch[v].pb(x);
    }
  if(v != root){
    int x = get_cent(root, h + 1);
    //cerr << v << ' ' << x << '\n';
    cpar[x] = v;
    ch[v].pb(x);
  }
  return v;
}
ll dis(int v, int u){
  if(h[u] < h[v])  swap(v, u);
  ll ans = 0;
  for(int i = 0; i < lg; i++)
    if(h[u] - h[v] >> i & 1){
      ans += sw[u][i];
      //cerr << "$ " << u << ' ' << i << ' ' << sw[u][i] << '\n';
      u = par[u][i];
    }
  //cerr << ans << '\n';
  if(v == u)
    return ans;
  for(int i = lg - 1; i >= 0; i--)
    if(par[v][i] != par[u][i]){
      ans += sw[v][i], ans += sw[u][i];
      v = par[v][i], u = par[u][i];
    }
  ans += sw[v][0] + sw[u][0];
  return ans;
}
void add(int v){
  for(int u = v; u != -1; u = cpar[u])
    ns[u] = min(ns[u], sd[v][che[u]]);
}
void clear(int v){
  for(int u = v; u != -1; u = cpar[u])
    ns[u] = inf;
}
ll get(int v){
  ll ans = inf;
  for(int u = v; u != -1; u = cpar[u]){
    ans = min(ans, sd[v][che[u]] + ns[u]);
    //cerr << dis(u, v) << ' ' << ns[u] << '\n';
  }
  return ans;
}