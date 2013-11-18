const int maxn = 100100;
const ll hmod = 1e18+3, hp = 311;
ll hpow[maxn];

ll MultiplyMod(ll a, ll b, ll mod) { //computes a * b % mod
  ull r = 0;
  while (b) {
    if (b & 1) r = (r + a) % mod;
    b >>= 1, a = ((ull)a << 1) % mod;
  }
  return r;
}
void initpow() { // call once
  hpow[0] = 1;
  rep(i,1,maxn) hpow[i] = MultiplyMod(hpow[i-1],hp,hmod);
}
void initstr(string& s, ll pref[]) { // call to initialize prefix hash array for s
  pref[0] = 0;
  rep(i,0,s.size())
    pref[i+1] = (MultiplyMod(pref[i],hp,hmod) + s[i])%hmod;
}
ll gethash(int l, int r, ll pref[]) { // hash s[l..r]
  return (pref[r+1] - MultiplyMod(hpow[r-l+1],pref[l],hmod) + hmod)%hmod;
}
