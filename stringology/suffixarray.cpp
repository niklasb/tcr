/* Runtime: Linear
 * LCP: 	Longest Common Prefix.
 * S: 		integer array indicates a string. If the input is characters,
 * 			convert them into integers first.
 * SA[i]: 	i-th suffix of s in alphabet order.
 * Rank[i]: rank of suffix starting at position i in alphabet order */
#include <cstdio>
#include <cmath>
#define maxn 200010
#define maxl 19     // 1 << (maxl - 1) should be >= maxn
#define EPS 1e-12
int  n, s[maxn], SA[maxn], rank[maxn], h[maxn], height[20][maxn];
inline int max(int a1,int a2) {return a1>a2?a1:a2;}
inline int min(int a1,int a2) {return a1<a2?a1:a2;}
inline bool leq(int a1, int a2, int b1, int b2)
	{return(a1 < b1 || (a1 == b1 && a2 <= b2)); }
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3)
	{return(a1 < b1 || (a1 == b1 && leq(a2,a3, b2,b3))); }
static void radixPass(int* a, int* b, int* r, int n, int K) {
	int i,sum;
	int* c = new int[K + 1];
	for ( i = 0; i <= K; i++) c[i] = 0;
	for ( i = 0; i < n; i++) c[r[a[i]]]++;
	for ( i = 0, sum = 0; i <= K; i++) {int t = c[i]; c[i] = sum; sum += t; }
	for ( i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
	delete [] c;
}
void suffixArray(int* s, int* SA, int n, int K) {
	int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
	int* s12 = new int[n02 + 3]; s12[n02]= s12[n02+1]= s12[n02+2]=0;
	int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
	int* s0 = new int[n0];
	int* SA0 = new int[n0];
	int i,j,p,t,k;
	for ( i=0, j=0; i < n+(n0-n1); i++) if (i%3 != 0) s12[j++] = i;
	radixPass(s12 , SA12, s+2, n02, K);
	radixPass(SA12, s12 , s+1, n02, K);
	radixPass(s12 , SA12, s , n02, K);
	int name = 0, c0 = -1, c1 = -1, c2 = -1;
	for ( i = 0; i < n02; i++) {
		if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2)
			{name++; c0 = s[SA12[i]]; c1 = s[SA12[i]+1]; c2 = s[SA12[i]+2]; }
		if (SA12[i] % 3 == 1) { s12[SA12[i]/3] = name; }
			else {s12[SA12[i]/3 + n0] = name; }
	}
	if (name < n02) {
		suffixArray(s12, SA12, n02, name);
		for (  i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
	} else
		for (  i = 0; i < n02; i++) SA12[s12[i] - 1] = i;
	for (  i=0, j=0; i < n02; i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
	radixPass(s0, SA0, s, n0, K);
	for (  p=0, t=n0-n1, k=0; k < n; k++) {
		#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
		i = GetI();
		j = SA0[p];
		if (SA12[t] < n0 ? leq(s[i], s12[SA12[t] + n0], s[j], s12[j/3]):
				leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
		{
			SA[k] = i; t++;
			if (t == n02)
				for (k++; p < n0; p++, k++) SA[k] = SA0[p];
		} else {
			SA[k] = j; p++;
			if (p == n0)
				for (k++; t < n02; t++, k++) SA[k] = GetI();
		}
	}
	delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
}
void Height_RMQ() { // calculate the height array and prepare for RMQ
	 int i,j,last=0;
	 for (i=0;i<n;++i) rank[SA[i]]=i;
	 for (i=0;i<n;++i)
		 if (rank[i]==0)
		 	 {h[i]=0; last=0;}
		 else {
			j=SA[rank[i]-1];
			while (s[i+last]==s[j+last]) last++;
			h[i]=last--;
			if (last<0) last=0;
		 }
	 for (i=0;i<n;++i) height[0][i]=h[SA[i]];
	 for (i=1;(1<<i)<n;++i)
		 for (j=0;j<=n-(1<<i);++j)
			 height[i][j]=min(height[i-1][j],height[i-1][j+(1<<(i-1))]);
}
int LCP(int a,int b) { // return the LCP of two suffixes starting at a & b
	if (a==b) return n - a;
	a = rank[a], b = rank[b];
	if (a>b) a^=b, b^=a, a^=b;
	a++;
	int delta=(int)(log(b-a+1)/log(2)+EPS);
	return min(height[delta][a],height[delta][b-(1<<delta)+1]);
}
int main() {
	scanf("%d",&n);
	for (int i=0;i<n;++i) { scanf("%d",&s[i]); s[i]++; } // let s[i] != 0
	s[n]=s[n+1]=s[n+2]=0;	// add 3 special value after the sequence
	if (n>1) suffixArray(s,SA,n,256); else SA[0]=0; 	// get SA array
	Height_RMQ();
	printf("%d\n",LCP(0,1)); // Example
	return 0;
}
