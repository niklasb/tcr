#include <cstring>

const int N = 200, MAXWEIGHT = 1001, MAXCUT = N*N*MAXWEIGHT;
int g[N][N]; // ungerichteter graph als adjazensmatrix
int v[N];	// besucht-status
int c[N];	// kosten, um aus bisher besuchter menge zu knoten zu kommen
int n;	   // knotenanzahl

int mincut() {
  memset(v, 0, sizeof(v));
  int bestcut = MAXCUT;
  for(int iter = 1; iter < n; ++iter) {
	memset(c, 0, sizeof(c));
	int t = 0, s = 0, w = MAXCUT;
	for(int nvis = iter; nvis < n; ++nvis) {
	  v[t] = iter;
	  int cmax = 0, next = -1;
	  for( int i = 0; i < n; ++i ) // c[i] updaten und groesstes merken
		if(v[i] < iter ) {
		  if(g[t][i]) c[i] += g[t][i];
		  if( c[i] && c[i] > cmax )	cmax = c[i], next = i;
		}
	  
	  if( next == -1 ) { // graph unzusammenhaengend
		w = 0; break;
	  }
	  s = t; t = next; w = cmax;
	}
	if( w < bestcut ) {
	  bestcut = w; // trennt s und t
	}
	for( int i = 0; i < n; ++i ) // knotenkontraktion s,t -> t
	  if( i != t && g[s][i]) {
		g[t][i] += g[s][i], g[i][t] += g[s][i];
	  }
	v[s] = N; // knoten "s" nie mehr besuchen
  }
  return bestcut;
}
