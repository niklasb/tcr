struct trie {
    struct trie *next, *down;
    char letter;
} node[1000000]; /* ggf. Anzahl anpassen */
int nodes = 0; /* so macht man alle Tries ungueltig */
struct trie *root = NULL; /* so loescht man einen einzelnen Trie */
/* Aufruf mit add(&root, str); gibt true zurueck, wenn Wort noch nicht vorhanden war */
int add(struct trie **root_pp, char *word) {
    struct trie *p, **prev_pp;
    int n = nodes;
    do {
        for (prev_pp = root_pp; (p = *prev_pp) != NULL && p->letter < *word;
                prev_pp = &(p->next)) {}
        if (p == NULL || p->letter != *word) {
            p = node + nodes++;
            p->next = *prev_pp;
            p->down = NULL;
            p->letter = *word;
            *prev_pp = p;
        }
        root_pp = &p->down;
    } while (*word++);
    return n < nodes;
}
/* Aufruf mit check(root, str); gibt true zurueck, wenn Wort vorhanden */
int check(struct trie *root, char *word) {
    do {
        while (root != NULL && root->letter < *word) root = root->next;
        if (root == NULL || root->letter != *word) return 0;
        root = root->down;
    } while (*word++);
    return 1;
}
