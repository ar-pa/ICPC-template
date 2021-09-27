// The error in approximating an integral by Simpson's formula is: −1/90* ((b−a)/2)^5 * f(4)(ξ)
// f(4) is the forth derivative of f.
// ξ is some number between a and b.

const int N = 1000 * 1000; // number of steps (already multiplied by 2)
double simpson_integration(double a, double b){ // Find integration in [a, b] range.
    double h = (b - a) / N;
    double s = f(a) + f(b); // a = x_0 and b = x_2n
    for (int i = 1; i <= N - 1; ++i) { // Refer to final Simpson's formula
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
    }
    s *= h / 3;
    return s;
}