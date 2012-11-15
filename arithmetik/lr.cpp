const int MAX = 42;
void lr(double a[MAX][MAX], int n) {
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < i; ++k) a[i][i] -= a[i][k] * a[k][i];
		for (int j = i + 1; j < n; ++j) {
			for (int k = 0; k < i; ++k) a[j][i] -= a[j][k] * a[k][i];
			a[j][i] /= a[i][i];
			for (int k = 0; k < i; ++k) a[i][j] -= a[i][k] * a[k][j];
		}
	}
}
double det(double a[MAX][MAX], int n) {
	lr(a, n);
	double d = 1;
	for (int i = 0; i < n; ++i) d *= a[i][i];
	return d;
}
void solve(double a[MAX][MAX], double *b, int n) {
	for (int i = 1; i < n; ++i)
		for (int j = 0; j < i; ++j) b[i] -= a[i][j] * b[j];
	for (int i = n - 1; i >= 0; --i) {
		for (int j = i + 1; j < n; ++j) b[i] -= a[i][j] * b[j];
		b[i] /= a[i][i];
	}
}