//
// Created by HOME on 25.06.2024.
//

#ifndef LAB2_INTEGER_H
#define LAB2_INTEGER_H

#include <cmath>

int IntMapAbs(int el) {
    return abs(el);
}

int IntMapLen(int el) {
    el = abs(el);
    int i = 0;
    while (el > 0) {
        el = el / 10;
        i++;
    }
    return i;
}

bool IntCheckPos(int el) {
    return el > 0;
}

bool IntCheckEven(int el) {
    return el % 2 == 0;
}

int IntSum(int el1, int el2) {
    return el1+el2;
}

int IntMult(int el1, int el2) {
    return el1*el2;
}


#endif //LAB2_INTEGER_H
