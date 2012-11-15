int KMP(const string &s, const string &t) {
	static int next[10010]; int times = 0;
	next[0]=-1;
	for (int i = 1, tp = -1, lt = t.size(); i<lt; ++i) {
		while (tp!=-1 && t[i]!=t[tp+1]) tp = next[tp];
		if (t[i]==t[tp+1]) tp++;
		next[i] = tp;
	}
	for (int i = 0, tp = -1, lt = t.size(), ls = s.size(); i<ls; ++i) {
		while (tp!=-1 && s[i]!=t[tp+1]) tp = next[tp];
		if (s[i]==t[tp+1]) tp++;
		if (tp == lt-1) {times++; tp = next[tp];}
	}
	return times;
}

