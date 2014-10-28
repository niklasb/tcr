#include <bits/stdc++.h>
#include <cassert>
#include <sys/resource.h>
using namespace std;
using ll=long long;
using ld=long double;
using pii=pair<int,int>;
using vi=vector<int>;
#define rep(i,s,e) for (int i=(s);i<(e);++i)
#define all(x) begin(x),end(x)
#define clr(x,y) memset(x,y,sizeof x)
#define contains(x,y) (x).find(y)!=end(x)
#define mk make_pair
#define fst first
#define snd second
#define pb push_back
const int dx[]={0,0,1,-1,1,-1,1,-1}, dy[]={-1,1,0,0,1,-1,-1,1};
void run();
int main() {
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(16);
  rlim_t stacksz = 64*1024*1024;
  rlimit rl{stacksz,stacksz};
  setrlimit(RLIMIT_STACK, &rl); // should return 0
  run();
}
void run() { }
