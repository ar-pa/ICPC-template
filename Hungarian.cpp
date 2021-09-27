const ll INFL = (1LL << 50);
const int N=110; // N is max(up, down)
ll u[N], v[N], p[N], way[N], minv[N];
bool used[N];
pair<vector<ll> , ll> HungarianMin(vector<vector<ll >> &matrix) {
	ll n = matrix.size(); // matrix must be square.
	if (n == 0) return {vector<ll> (), 0};
	for(ll i = 1; i <= n; i++) {
		for(ll i = 0; i <= n; i++) minv[i] = INFL;
		memset(way, 0, (n+1) * sizeof(ll ));
		for(ll j = 0; j <= n; j++) used[j] = false;
		p[0] = i;
		ll k0 = 0;
		do {
			used[k0] = true;
			ll i0 = p[k0], k1;
			ll delta = INFL;
			for(ll j = 1; j <= n; j++)
				if(!used[j]) {
					ll cur = matrix[i0-1][j-1] - u[i0] - v[j];
					if(cur < minv[j])
						minv[j] = cur, way[j] = k0;
					if(minv[j] < delta) 
						delta = minv[j], k1 = j;
				}
			for(ll j = 0; j <= n; j++)
					if(used[j])
							u[p[j]] += delta, v[j] -= delta;
					else
							minv[j] -= delta;
			k0 = k1;
		} while (p[k0] != 0);
		do {
			ll k1 = way[k0];
			p[k0] = p[k1];
			k0 = k1;
		} while (k0 != 0);
	}
	vector<ll> ans(n, -1);
	for(ll j = 1; j <= n; j++) {
		if(p[j] == 0) continue;
		ans[p[j] - 1] = j-1;
	}
	return {ans, -v[0]};
}