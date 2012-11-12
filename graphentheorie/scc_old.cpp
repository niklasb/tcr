vvi gr;
vi nr, low;
stack<int> S;
vvi sccs;
vector<bool> inst;
int idx = 0;

void visit (int i) {
	nr[i] = low[i] = idx++;
	S.push (i);
	in_stack[i] = true;
	for (vi::iterator it = gr[i].begin (); it != gr[i].end (); ++it) {
		if (nr[*it] < 0) {
			visit (*it);
			low[i] = min (low[i], low[*it]);
		} else if (in_stack[*it]) {
			low[i] = min (low[i], low[*it]);
		}
	}
	if (nr[i] == low[i]) {
		int n;
		vi comp;
		do {
			n = S.top (); S.pop ();
			in_stack[n] = false;
			comp.push_back (n);
		} while (n != i);
		sccs.push_back (comp);
	}
}

void scc () {
	nr.resize (gr.size (), -1);
	low.resize (gr.size ());
	inst.resize (gr.size (), false);
	for (int i = 0; i < gr.size (); ++i) {
		if (nr[i] < 0) {
			visit (i);
		}
	}
}
