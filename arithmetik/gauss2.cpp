struct R {
	ll n, d; // or use BigInteger in Java
	R(ll n_=0, ll d_=1) {
		n = n_; d = d_;
		ll g = __gcd(n,d);
		n/=g;
		d /= g;
		if (d < 0){
			n=-n;
			d=-d;
		}
	}
	R add(R x) {
		return R(n * x.d + d*x.n, d * x.d);
	}
	R negate() { return R(-n, d); }
	R subtract(R x) { return add(x.negate()); }
	R multiply(R x) {
		return R(n * x.n, d * x.d);
	}
	R invert() { return R(d, n); }
	R divide(R y) { return multiply(y.invert()); }
	bool zero() { return !n; }
};

void normalize_row(int i, int cols) {
	ll g = 0;
	for (int j = 0; j < cols; ++j)
		g = __gcd(g, M[i][j].n);
	if (g == 0)return;
	for (int j = 0; j < cols; ++j)
		M[i][j].n /= g;
}

void gauss(int m, int n) { // m=rows, n=cols, reduces M to Gaussian normal form
	int row = 0;
	for (int col = 0; col < n; ++col) { // eliminate downwards
		int pivot=row;
		while(pivot<m&&M[pivot][col].zero())pivot++;
		if (pivot == m || M[pivot][col].zero()) continue;
		if (row!=pivot) {
			for (int j = 0; j < n; ++j) {
				R tmp = M[row][j];
				M[row][j] = M[pivot][j];
				M[pivot][j] = tmp;
			}
			R tmp = B[row];
			B[row] = B[pivot];
			B[pivot] = tmp;
		}
		normalize_row(row, n); // to avoid overflows. also use in case of double
		for (int j = row+1; j < m; ++j) {
			if (M[j][col].zero()) continue;
			R a = M[row][col], b = M[j][col];
			for(int k=0; k<n; ++k)
				M[j][k] = M[j][k].multiply(a).subtract(M[row][k].multiply(b));
			B[j] = B[j].multiply(a).subtract(B[row].multiply(b));
		}
		row++;
	}
	for (int row = m-1; row >= 0; --row) { // eliminate upwards
		normalize_row(row, n);
		for (int col = 0; col < n; ++col) {
			if (M[row][col].zero()) continue;
			for (int i = 0; i < row; ++i) {
				R a = M[row][col], b = M[i][col];
				for (int k =0; k<n; ++k)
					M[i][k] = M[i][k].multiply(a).subtract(M[row][k].multiply(b));
				B[i] = B[i].multiply(a).subtract(B[row].multiply(b));
			}
			break;
		}
	}
}

int getrank() {
	int rank = 0;
	for (int i = 0; i < m; ++i) {
		bool valid = 0;
		for (int j=0;j<n;++j)
			if (!M[i][j].zero())
				valid=1;
		rank += valid?1:0;
	}
	return rank;
}
