typedef double D;
D f(D x) {return exp(-x * x);} //O(2^maxitr) function evaluations
D Romberg(D a, D b, D(*f)(D), D eps, int maxitr = 25) {
	D T[maxitr][maxitr];
	for (int i = 0; i < maxitr; ++i) {
		D h = (b - a) / (1 << i), x = a + h, pow = 4;
		T[i][0] = (f(a) + f(b)) / 2;
		for (int j = (1 << i) - 1; j >= 1; x += h, --j) T[i][0] += f(x);
		T[i][0] *= h;
		for (int j = 1; j <= i; pow *= 4, ++j)
			T[i][j] = T[i][j - 1] + (T[i][j - 1] - T[i - 1][j - 1]) / (pow - 1);
		if (i > 0 && abs(T[i][i] - T[i - 1][i - 1]) <= eps) return T[i][i];
	}
	return T[maxitr - 1][maxitr - 1]; 
}
