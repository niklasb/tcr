#define MAX 1024
 
#define TERMINALS 7
#define NONTERMINALS 14
 
// #define A 1, #define MOD 2, #define BA 4, usw fuer alle Nichtterminale
// SENTENCE ist die Axiom
 
int nonterminal_map[NONTERMINALS][NONTERMINALS], words, symbol[MAX][MAX];

// am Anfang in symbol[i][i] die Maske des Nichtterminals des i-ten Wortes eintragen
bool cyk() {
    int i, j, k, m, n;
    for (i = 1; i < words; ++i)
        for (j = 0; j + i < words; ++j) {
            symbol[j][j + i] = 0;
            for (k = 0; k < i; ++k)
                for (m = 0; m < NONTERMINALS; ++m)
                    for (n = 0; n < NONTERMINALS; ++n)
                        if ((symbol[j][j + k] & (1 << m))
                            && (symbol[j + k + 1][j + i] & (1 << n)))
                            symbol[j][j + i] |= nonterminal_map[m][n];
        }
    return words > 0 && (symbol[0][words - 1] & SENTENCE);
}
