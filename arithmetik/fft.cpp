typedef double D; // or long double?
typedef complex<D> cplx; // use own implementation for 2x speedup
const D pi = acos(-1); // or -1.L for long double

// input should have size 2^k
vector<cplx> fft(const vector<cplx>& a, bool inv=0) {
    int logn=1, n=a.size();
    vector<cplx> A(n);
    while((1<<logn)<n) logn++;
    rep(i,0,n) {
        int j=0; // precompute j = rev(i) if FFT is used more than once
        rep(k,0,logn) j = (j<<1) | ((i>>k)&1);
        A[j] = a[i]; }
    for(int s=2; s<=n; s<<=1) {
        D ang = 2 * pi / s * (inv ? -1 : 1);
        cplx ws(cos(ang), sin(ang));
        for(int j=0; j<n; j+=s) {
            cplx w=1;
            rep(k,0,s/2) {
                cplx u = A[j+k], t = A[j+s/2+k];
                A[j+k] = u + w*t;
                A[j+s/2+k] = u - w*t;
                if(inv) A[j+k] /= 2, A[j+s/2+k] /= 2;
                w *= ws; } } }
    return A;
}
vector<cplx> a = {0,0,0,0,1,2,3,4}, b = {0,0,0,0,2,3,0,1}; // polynomials
a = fft(a); b = fft(b);
rep(i,0,a.size()) a[i] *= b[i]; // convult spectrum
a = fft(a,1); // ifft, a = a * b
