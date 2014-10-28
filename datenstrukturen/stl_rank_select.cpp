#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std; using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Tree;
int main() {
    Tree X;
    for (int i = 1; i <= 16; i <<= 1) X.insert(i); // { 1, 2, 4, 8, 16 };
    cout << *X.find_by_order(3) << endl; // => 8
    cout << X.order_of_key(10) << endl; // => 4 = successor of 10 = min i such that X[i] >= 10
}
