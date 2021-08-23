typedef long long ll;
const ll INFL = (1 << 60);
using Weight = ll;
const Weight InfWeight = INFL;

Weight hungarianMin(const vector <vector<Weight>> &A) {
	if (A.empty()) return 0;
	int h = A.size(), n = A[0].size();
	if (h > n) return InfWeight;
	vector <Weight> fx(h), fy(n);
	vector<int> x(h, -1), y(n, -1);
	vector<int> t(n), s(h + 1);
	for (int i = 0; i < h;) {
		fill(t.begin(), t.end(), -1);
		s[0] = i;
		int q = 0;
		for (int p = 0; p <= q; ++p) {
			for (int k = s[p], j = 0; j < n; ++j) {
				if (fx[k] + fy[j] == A[k][j] && t[j] < 0) {
					s[++q] = y[j];
					t[j] = k;
					if (s[q] < 0) {
						for (p = j; p >= 0; j = p) {
							y[j] = k = t[j];
							p = x[k];
							x[k] = j;
						}
						++i;
						goto continue_;
					}
				}
			}
		}
		if (0) {
		continue_:;
		} else {
			Weight d = InfWeight;
			for (int j = 0; j < n; j++)
				if (t[j] < 0) {
					for (int k = 0; k <= q; ++k)
						if (A[s[k]][j] != InfWeight)
							d = min(d, A[s[k]][j] - fx[s[k]] - fy[j]);
				}
			if (d == InfWeight)
				return InfWeight;
			for (int j = 0; j < n; ++j) {
				if (t[j] >= 0)
					fy[j] -= d;
			}
			for (int k = 0; k <= q; ++k)
				fx[s[k]] += d;
		}
	}
	Weight res = 0;
	for (int i = 0; i < h; ++i)
		res += A[i][x[i]];
	return res;
}
