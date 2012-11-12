#include <iostream>
#include <vector>

// liefert die groesste Summe von Elementen aus v, die kleiner oder gleich limit ist
int subset_sum(const vector<int>& v, int limit) {
    vector<bool> poss(limit + 1, false);
    int m = 0;

    poss[0] = true;
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        for (int j = m; j >= 0; --j)
            if (poss[j] && j + *it <= limit) {
                poss[j + *it] = true;
                m = max(m, j + *it);
            }

    return m;
}
