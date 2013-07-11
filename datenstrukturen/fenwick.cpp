const int n = 100;
static int tree[n+1];
// get v[idx] (1 <= idx <= n)
int read(int idx){
  int sum = 0;
  for (; idx > 0; idx -= idx&-idx) sum += tree[idx];
  return sum;
}
// update v[1..idx] += val
void update(int idx, int val){
  int sum = 0;
  for (; idx <= n; idx += idx&-idx) tree[idx] += val;
}
