#define ALPHA 'A'
struct trie {
    struct trie *down[26];
    bool end_of_word;
} node[100000]; // ggf. Anzahl anpassen
int nodes = 0; // so macht man alle Tries ungueltig
struct trie *root = NULL; // so loescht man einen einzelnen Trie
// Aufruf mit add(&root, str); gibt true zurueck, wenn Wort noch nicht vorhanden war
bool add(struct trie **root_ptr, char *word) {
    struct trie *p;
    do {
        p = *root_ptr;
        if (p == NULL) {
            p = node + nodes++;
            for (int i = 0; i < 26; ++i) p->down[i] = NULL;
            p->end_of_word = false;
            *root_ptr = p;
        }
        root_ptr = p->down + (*word - ALPHA);
    } while (*word++);
    return p->end_of_word ? false : (p->end_of_word = true);
}
// Aufruf mit check(root, str); gibt true zurueck, wenn Wort vorhanden
bool check(struct trie *root, char *word) {
    while (*word) {
        if (root == NULL) return false;
        root = root->down[*word++ - ALPHA];
    }
    return root != NULL && root->end_of_word;
}
