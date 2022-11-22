#include <assert.h>
#include <string.h>
#include <math.h>
#include "parser.hpp"


int getE();         ///< E::=T{[+-]T}*
int getT();         ///< T::=D{[*/]D}*
int getD();         ///< D::=U{'^'U}*
int getU();         ///< U::=['sin''cos''ln']P|P
int getP();         ///< P::='('E')'|N
int getN();         ///< N::=['0'-'9']


const char *s = nullptr;


int getG(const char *str) {
    s = str;
    
    int value = getE();

    assert(*s == '\0' && "No \0 at the end of expression!");

    return value;
}


int getE() {
    int value = getT();

    while(*s == '+' || *s == '-') {
        char op = *s; 

        s++;
        int tmp = getT();

        if (op == '+') value += tmp;
        else value -= tmp;
    }

    return value;
}


int getT() {
    int value = getD();

    while(*s == '*' || *s == '/') {
        char op = *s; 

        s++;
        int tmp = getD();

        if (op == '*') value *= tmp;
        else value /= tmp;
    }

    return value;
}


int getD() {
    int value = getU();

    while(*s == '^') {
        s++;
        int tmp = getU(), base = value;

        for(value = 1; tmp > 0; tmp--) value *= base;
    }

    return value;
}


int getU() {
    int value = 0;

    if (strncmp(s, "sin", 3) == 0) {
        s+=3;
        value = (int) sin(getP());
    }
    else if (strncmp(s, "cos", 3) == 0) {
        s+=3;
        value = (int) cos(getP());
    }
    else if (strncmp(s, "ln", 2) == 0) {
        s+=2;
        value = (int) log(getP());
    }
    else value = getP();
    
    return value;
}


int getP() {
    int value = 0;

    if (*s == '(') {
        s++;
        value = getE();

        assert(*s == ')' && "No closing bracket!");

        s++;
    }
    else value = getN();
    
    return value;
}


int getN() {
    int value = 0;
    const char *old_s = s;

    while ('0' <= *s && *s <= '9') {
        value = value * 10 + *s - '0';
        s++;
    }

    assert(s != old_s && "No number found!");

    return value;
}
