#define REP(i, n) for(int i = 0; i < (n); i++)
typedef int llint;
namespace FFT {
	const int MAX = 1 << 17;

	typedef llint value;
	typedef complex<double> comp;

	int N;
	comp omega[MAX];
	comp a1[MAX], a2[MAX];
	comp z1[MAX], z2[MAX];

	void fft(comp *a, comp *z, int m = N) {
		if (m == 1) {
			z[0] = a[0];
		} else {
			int s = N/m;
			m /= 2;

			fft(a, z, m);
			fft(a+s, z+m, m);

			REP(i, m) {
				comp c = omega[s*i] * z[m+i];
				z[m+i] = z[i] - c;
				z[i] += c;
			}
		}
	}

	void mult(value *a, value *b, value *c, int len) {
		N = 2*len;
		while (N & (N-1)) ++N;
		assert(N <= MAX);

		REP(i, N) a1[i] = 0;
		REP(i, N) a2[i] = 0;
		REP(i, len) a1[i] = a[i];
		REP(i, len) a2[i] = b[i];

		REP(i, N) omega[i] = polar(1.0, 2*M_PI/N*i);
		fft(a1, z1, N);
		fft(a2, z2, N);

		REP(i, N) omega[i] = comp(1, 0) / omega[i];
		REP(i, N) a1[i] = z1[i] * z2[i] / comp(N, 0);
		fft(a1, z1, N);

		REP(i, 2*len) c[i] = round(z1[i].real());
	}

	void mult_mod(int *a, int *b, int *c, int len, int mod) {
		static llint a0[MAX], a1[MAX];
		static llint b0[MAX], b1[MAX];
		static llint c0[MAX], c1[MAX], c2[MAX];

		REP(i, len) a0[i] = a[i] & 0xFFFF;
		REP(i, len) a1[i] = a[i] >> 16;

		REP(i, len) b0[i] = b[i] & 0xFFFF;
		REP(i, len) b1[i] = b[i] >> 16;

		FFT::mult(a0, b0, c0, len);
		FFT::mult(a1, b1, c2, len);

		REP(i, len) a0[i] += a1[i];
		REP(i, len) b0[i] += b1[i];
		FFT::mult(a0, b0, c1, len);
		REP(i, 2*len) c1[i] -= c0[i] + c2[i];

		REP(i, 2*len) c1[i] %= mod;
		REP(i, 2*len) c2[i] %= mod;
		REP(i, 2*len) c[i] = (c0[i] + ((long long) c1[i] << 16) + ((long long) c2[i] << 32)) % mod;
	}
}
#undef REP

