// hier mit int, aber es reicht, wenn operator< definiert ist
void lift(vector<int>& v, int i) {
    for (int j; i > 0; i = j) {
        j = (i - 1) / 2;
        if (!(v[j] < v[i])) break;
        swap(v[i], v[j]);
    }
}
void sink(vector<int>& v, int i) {
    for (int j; (j = 2 * i + 1) < int(v.size()); i = j) {
        if (j + 1 < int(v.size()) && v[j] < v[j + 1]) ++j;
        if (!(v[i] < v[j])) break;
        swap(v[i], v[j]);
    }
}
