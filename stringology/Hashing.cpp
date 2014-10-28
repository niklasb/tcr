int q = 311;
struct Hasher { // use two of those, with different mod (e.g. 1e9+7 and 1e9+9)
  string s;
  int mod;
  vector<int> power, pref;
  Hasher(const string& s, int mod) : s(s), mod(mod) {
    power.pb(1);
    rep(i,1,s.size()) power.pb((ll)power.back() * q % mod);
    pref.pb(0);
    rep(i,0,s.size()) pref.pb(((ll)pref.back() * q % mod + s[i]) % mod);
  }
  int hash(int l, int r) {
    return (pref[r+1] - (ll)power[r-l+1] * pref[l] % mod + mod) % mod;
  }
};
