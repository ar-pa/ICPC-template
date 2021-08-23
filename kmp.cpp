const int maxn = 5e6 + 17;
string s, p;
int f[maxn];
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> s >> p;
	int k = 0;
	for(int i = 1; i < p.size(); i++){
		while(k && p[k] != p[i])  k = f[k];
		if(p[k] == p[i])  k++;
		f[i + 1] = k;
	}
	k = 0;
	for(int i = 0; i < s.size(); i++){
		while(k && p[k] != s[i])  k = f[k];
		if(p[k] == s[i])  k++;
		if(k == p.size()){
			cerr << "A match occurred on " << i << '\n';
			k = f[k];
		}
	}
	return 0;
}
