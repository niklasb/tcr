class R {
	BigInteger n, d;
	R(BigInteger n_, BigInteger d_) {
		n = n_; d = d_;
		BigInteger g = n.gcd(d);
		n.divide(g); d.divide(g);
	}
	R add(R x) {
		return new R(n.multiply(x.d).add(d.multiply(x.n)), d.multiply(x.d));
	}
	R negate() { return new R(n.negate(), d); }
	R subtract(R x) { return add(x.negate()); }
	R multiply(R y) {
		return new R(n.multiply(x.n), d.multiply(x.d));
	}
	R invert() { return new R(d, n); }
	R divide(R y) { return multiply(y.invert()); }
	boolean zero() { return d.equals(BigInteger.ZERO); }
}

int maxm = 13, maxn = 4;
R[][] M = new R[maxm][maxn]; // the LGS matrix
R[] B = new R[maxm];         // the right side

void gauss(int m, int n) { // reduces M to Gaussian normal form
	int row = 0;
	for (int col = 0; col < n; ++col) { // eliminate downwards
		int pivot=row;
		while(pivot<m&&M[pivot][col].zero())pivot++;
		if (M[pivot][col].zero()) continue;
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
		// for double, normalize pivot row here (divide it by pivot value)
		for (int j = row+1; j < m; ++j) {
			if (M[j][col].zero()) continue;
			R a = M[row][col], b = M[j][col];
			for(int k=0; k<n; ++k)
				M[j][k] = M[j][k].multiply(a).subtract(M[row][k].multiply(b));
			B[j] = B[j].multiply(a).subtract(B[row].multiply(b));
		}
		row++;
	}
	for (int col = 0; col < n; ++col) { // eliminate upwards
		for (row = m-1; row >= 0; --row) {
			if (M[row][col].zero()) continue;
			boolean valid=true;
			for (int j = 0; j < col; ++j)
				if (!M[row][j].zero()) { valid=false; break; }
			if (!valid) continue;
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
