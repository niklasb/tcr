#include <iostream>
#include <cstring>
 
#define LEN 128
#define DPI 9
#define MOD 1000000000
 
typedef int bignum[LEN];
 
/* alpha = integ; */
void set_int(bignum alpha, int integ) {
    alpha[0] = 2;
    alpha[1] = integ;
}
 
/* alpha = atoi(str); */
void set_str(bignum alpha, char *str) {
    char *ptr = str + strlen(str);
    int power10, digits = DPI;
 
    alpha[0] = 1;
    while (ptr-- != str) {
        if (digits == DPI) {
            alpha[alpha[0]++] = 0;
            power10 = 1;
            digits = 0;
        }
 
        alpha[alpha[0] - 1] += (*ptr - '0') * power10;
        power10 *= 10;
        ++digits;
    }
 
    while (alpha[0] > 2 && alpha[alpha[0] - 1] == 0) --alpha[0];
}
 
/* alpha = beta; */
void set_big(bignum alpha, const bignum beta) {
    int i;
 
    for (i = 0; i < beta[0]; ++i) {
        alpha[i] = beta[i];
    }
}
 
/* alpha += integ; */
void add_int(bignum alpha, int integ) {
    int i = 1;
 
    while (integ > 0) {
        if (i < alpha[0]) integ += alpha[i];
        alpha[i++] = integ % MOD;
        integ /= MOD;
    }
 
    if (i > alpha[0]) alpha[0] = i;
}
 
/* alpha += beta; */
void add_big(bignum alpha, const bignum beta) {
    int carry = 0, i = 1, j = 1;
 
    while (carry > 0 || j < beta[0]) {
        if (i < alpha[0]) carry += alpha[i];
        if (j < beta[0]) carry += beta[j++];
        alpha[i++] = carry % MOD;
        carry /= MOD;
    }
 
    if (i > alpha[0]) alpha[0] = i;
}
 
/* alpha -= integ; */
void sub_int(bignum alpha, int integ) {
    int i = 1;
 
    integ = -integ;
    while (integ < 0) {
        integ += alpha[i];
        if (integ < 0) integ += 2 * MOD;
        alpha[i++] = integ % MOD;
        integ /= -MOD;
    }
 
    while (alpha[0] > 2 && alpha[alpha[0] - 1] == 0) --alpha[0];
}
 
/* alpha -= beta; */
void sub_big(bignum alpha, const bignum beta) {
    int carry = 0, i = 1, j = 1;
 
    while (carry < 0 || j < beta[0]) {
        carry += alpha[i];
        if (j < beta[0]) carry -= beta[j++];
        if (carry < 0) carry += 2 * MOD;
        alpha[i++] = carry % MOD;
        carry /= -MOD;
    }
 
    while (alpha[0] > 2 && alpha[alpha[0] - 1] == 0) --alpha[0];
}
 
/* alpha *= integ; */
void mul_int(bignum alpha, long long integ) {
    long long carry = 0;
    int i = 1;
 
    while (carry > 0 || i < alpha[0]) {
        if (i < alpha[0]) carry += alpha[i] * integ;
        alpha[i++] = carry % MOD;
        carry /= MOD;
    }
 
    if (i > alpha[0]) alpha[0] = i;
}
 
/* alpha += beta * gamma; */
void mul_add(bignum alpha, const bignum beta, const bignum gamma) {
    long long integ, carry;
    int i, j, k = 1;
 
    while (k < gamma[0]) {
        integ = gamma[k];
        carry = 0;
        i = k++;
        j = 1;
 
        while (carry > 0 || j < beta[0]) {
            if (i < alpha[0]) carry += alpha[i];
            if (j < beta[0]) carry += beta[j++] * integ;
            alpha[i++] = carry % MOD;
            carry /= MOD;
        }
 
        if (i > alpha[0]) alpha[0] = i;
    }
 
    while (alpha[0] > 2 && alpha[alpha[0] - 1] == 0) --alpha[0];
}
 
/* alpha *= beta; */
void mul_big(bignum alpha, const bignum beta) {
    bignum gamma;
 
    set_int(gamma, 0);
    mul_add(gamma, alpha, beta);
    set_big(alpha, gamma);
}
 
/* alpha /= integ; return alpha % integ; */
int div_int(bignum alpha, int integ) {
    long long carry = 0;
    int i = alpha[0];
 
    while (i > 1) {
        carry *= MOD;
        carry += alpha[--i];
        alpha[i] = carry / integ;
        carry %= integ;
    }
 
    while (alpha[0] > 2 && alpha[alpha[0] - 1] == 0) --alpha[0];
 
    return carry;
}
 
/* alpha = pow(alpha, integ); */
void pow_int(bignum alpha, int integ) {
    bignum square[2], answer[2];
    int square_idx = 0, answer_idx = 0;
 
    set_int(answer[answer_idx], 1);
    set_big(square[square_idx], alpha);
 
    while (integ > 0) {
        if ((integ & 1)) {
            set_int(answer[answer_idx ^ 1], 0);
            mul_add(answer[answer_idx ^ 1], answer[answer_idx], square[square_idx]);
            answer_idx ^= 1;
        }
        integ >>= 1;
 
        set_int(square[square_idx ^ 1], 0);
        mul_add(square[square_idx ^ 1], square[square_idx], square[square_idx]);
        square_idx ^= 1;
    }
 
    set_big(alpha, answer[answer_idx]);
}
 
/* cout << alpha; */
void print_big(bignum alpha) {
    int i = alpha[0] - 1;
 
    cout << alpha[i];
    cout.fill('0');
    while (i-- > 1) {
        cout.width(DPI);
        cout << alpha[i];
    }
    cout.fill();
}
