#include <cstdlib>
 
// erst ptr setzen, dann Aufruf von parse()
char* ptr;
 
double atom();
double prod();
double parse();

double atom() {	// Anpassen wenn unaerer - zulaessig
    double res;
    if (*ptr == '(') {
        ++ptr;
        res = parse();
        ++ptr;
    } else res = strtod(ptr, &ptr);
    return res;
}
 
double prod() {
    double res = atom();
    while (*ptr == '*' || *ptr == '/')
        res = *ptr++ == '*' ? res * atom() : res / atom();
    return res;
}
 
double parse() {
    double res = prod();
    while (*ptr == '+' || *ptr == '-')
        res = *ptr++ == '+' ? res + prod() : res - prod();
    return res;
}
