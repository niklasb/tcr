struct edge {int to; ...}

// Rueckgabe: jeder vector hat die Knoten in einer SCC
vector<vector<int> > scc(const vector<vector<edge> >& graph, const vector<vector<edge> >& rgraph)
{// rgraph ist der Graph mit Kanten in umgekehrten Richtung
	vector<bool> visited(graph.size(), false);
	vector<bool> done(graph.size(), false);
	vector<bool> in_order(graph.size(), false);
	vector<int> order;
	
	std::stack<int> s;
	for (int start = 0; start < (int)graph.size(); start++)
	{
		if (visited[start]) continue;
		
		s.push(start);
		while (!s.empty())
		{
			int c;
			do {c = s.top(); s.pop();} while (!s.empty() && (visited[c] && !done[c]));
			if (visited[c] && !done[c]) break;
			else visited[c] = true;
			
			if (done[c] && !in_order[c])
			{
				order.push_back(c);
				in_order[c] = true;
			}
			else if (!done[c])
			{
				s.push(c);
				
				for (size_t i = 0; i < graph[c].size(); i++)
					if (!visited[graph[c][i].to])
						s.push(graph[c][i].to);
						
				done[c] = true;
			}
		}
	}
	
	vector<vector<int> > answer;
	
	for (size_t i = 0; i < visited.size(); i++) visited[i] = false;
	for (int si = (int)order.size()-1; si >= 0; si--)
	{
		const int& start = order[si];
		
		if (visited[start]) continue;
		
		answer.push_back(vector<int>());
		std::stack<int> s;
		s.push(start); visited[start] = true; answer.back().push_back(start);
		
		while (!s.empty())
		{
			int c = s.top(); s.pop();
			
			for (size_t i = 0; i < rgraph[c].size(); i++)
				if (!visited[rgraph[c][i].to])
				{
					visited[rgraph[c][i].to] = true;
					s.push(rgraph[c][i].to);
					answer.back().push_back(rgraph[c][i].to);
				}
		}
	}
	
	return answer;
}
