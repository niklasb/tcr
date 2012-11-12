list< int > cyc;
void euler( list< int >::iterator i, int u ) {
  for( int v = 0; v < n; v++ ) if( graph[u][v] ) {
    graph[u][v] = graph[v][u] = false;
    euler( cyc.insert( i, u ), v );
  }
}
 
int main() {
  // read graph into graph[][] and set n to the number of vertices
  euler( cyc.begin(), 0 );
  // cyc contains an euler cycle starting at 0
} 
