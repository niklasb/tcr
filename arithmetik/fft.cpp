typedef complex<double> cplx;
// input should have size 2^k
vector<cplx> fft(const vector<cplx>& a, bool inv=0) {
    int len=1, n=a.size();
    vector<cplx> A(n);
    while((1<<len)<n) len++;
    for(int i=0; i<n; i++) {
        int j=0;
        for(int k=0; k<len; k++)
            if(i & (1<<k))
                j |= (1<<(len-1-k));
        A[j] = a[i]; }
    for(int s=2; s<=n; s<<=1) {
        double ang = 2 * pi / s * (inv ? -1 : 1);
        cplx ws(cos(ang), sin(ang));
        for(int j=0; j<n; j+=s) {
            cplx w=1;
            for(int k=0; k<s/2; k++) {
                cplx u = A[j+k], t = A[j+s/2+k];
                A[j+k] = u + w*t;
                A[j+s/2+k] = u - w*t;
                if(inv) A[j+k] /= 2, A[j+s/2+k] /= 2;
                w *= ws; } } }
    return A;
}
vector<cplx> a = {1,2,3,4}, b = {2,3,0,1}; // polynomials
a = fft(a); b = fft(b);
for (int i = a.size()-1; i >= 0; --i) a[i] *= b[i]; // convult spectrum
a = fft(a,1); // ifft, a = a * b
