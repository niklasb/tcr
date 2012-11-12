#include <stack>

int precval( char c ) {
    if( c == '+' || c == '-' ) return 1;
    else return 2;
}

bool precIsSmaller( char op1, char op2 ) {
    return precval( op1 ) < precval( op2 );
}

void parse( char *infix, char *postfix ) {
    stack<char> s;
    char c;

    while( *infix != 0 ) {
        switch( *infix ) {
            case '(':
                s.push( '(' );
                break;
            case ')':
                while( !s.empty() ) {
                    c = s.top();
                    s.pop();
                    if( c == '(') break;
                    *postfix++ = c;
                }
                break;
            case '+': case '-': case '*': case '/':
                while( !s.empty() ) {
                    c = s.top();
                    if( c == '(' ) break;
                    else if( !precIsSmaller( c, *infix ) ) {
                        s.pop();
                        *postfix++ = c;
                    } else break;
                }
                s.push( *infix );
                break;
            default:
                *postfix++ = *infix;
                break;
        }
        ++infix;
    }

    while( !s.empty() ) {
        *postfix++ = s.top();
        s.pop();
    }

    *postfix = 0;
}

