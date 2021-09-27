int nxt[maxn][z], q[maxn], f[maxn], sz = 1;
int insert(string &s){
  int v = 0;
  for(auto c : s){
    if(!nxt[v][c - 'a'])
      nxt[v][c - 'a'] = sz++;
    v = nxt[v][c - 'a'];
  }
  return v;
}
void aho_corasick(){
  int head = 0, tail = 0;
  for(int i = 0; i < z; i++)
    if(nxt[0][i])
      q[tail++] = nxt[0][i];
  while(head < tail){
    int v = q[head++];
    for(int i = 0; i < z; i++)
      if(nxt[v][i]){
        f[ nxt[v][i] ] = nxt[ f[v] ][i];
        q[tail++] = nxt[v][i];
      }
      else
        nxt[v][i] = nxt[ f[v] ][i];
  }
}
