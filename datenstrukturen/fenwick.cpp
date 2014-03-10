const int n = 100;

// get v[idx] (1 <= idx <= n)
int read_idx(int tree[], int idx) {
  int sum = 0;
  for (; idx <= n; idx += idx & -idx) sum += tree[idx];
  return sum;
}
// update v[1..idx] += val
void update_prefix(int tree[], int idx, int val) {
  if (idx < 1) return;
  for (; idx > 0; idx -= idx & -idx) tree[idx] += val;
}
