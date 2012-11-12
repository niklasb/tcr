#include <algorithm>
 
int eingabe[SIZE];
int seq[SIZE];
 
int lis() {
    int m = 0;
    for(int i = 0; i < p; ++i) {
        int j = lower_bound(seq, seq + m, eingabe[i]) - seq;
        if(j == m) seq[m++] = eingabe[i]; else seq[j] = eingabe[i];
    }
    return m;
}
