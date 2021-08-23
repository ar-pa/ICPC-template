void minus(int a[], int b[]){
	for(int i = 0; i < maxn; i++)
		a[i] = (a[i] - b[i] + mod) % mod;
}
void fwht(int *data, int dim) {
    for (int len = 1; 2 * len <= dim; len <<= 1) {
        for (int i = 0; i < dim; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int a = data[i + j];
                int b = data[i + j + len];
                
                data[i + j] = (a + b) % mod;
                data[i + j + len] = (mod + a - b) % mod;
            }   
        }
    }
}
ll poww(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod; 
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}
 
void raise(int data[]){
	fwht(data, maxn);
	for (int i = 0; i < maxn; i++)
		data[i] = poww(data[i], 2);
	fwht(data, maxn);
	int inv = poww(maxn, mod - 2);
	for (int i = 0; i < maxn; i++)
		data[i] = ((ll) data[i] * inv) % mod;
}
int all[maxn];
void fftxor(int a[], int b[], int c[maxn]){
	for(int i = 0; i < maxn; i++)
		all[i] = (a[i] + b[i]) % mod;
	raise(all);
	raise(a);
	raise(b);
	minus(all, a);
	minus(all, b);
	int r2 = poww(2, mod - 2);
	for(int i = 0; i < maxn; i++)
		all[i] = (ll) all[i] * r2 % mod;
	memcpy(c, all, maxn * 4);
}
