//
// Created by HOME on 25.06.2024.
//

#ifndef LAB2_COMPLEX_H
#define LAB2_COMPLEX_H

#include <stdexcept>
#include <iostream>
#include <memory>

using namespace std;

typedef struct {
    int real;
    int imag;
} Complex;


std::ostream& operator << (std::ostream &os, Complex elem)
{
    std::string message{ std::to_string(elem.real)};
    message.append("+");
    message.append(std::to_string(elem.imag));
    message.append("i");
    return os << message;
}; //TODO cin>> operator

void complexMapOpposite(const Complex * elem, Complex* res) {
    res->real = elem->real;
    res->imag = (elem->imag)*(-1);
}

void complexMapReverse(const Complex * elem, Complex* res) {
    res->real = elem->imag;
    res->imag = elem->real;
}

int complexCheckPosReal(const Complex * elem) {
    return elem->real > 0;
}

int complexCheckImagNotNull(const Complex * elem) {
    return elem->imag != 0;
}

void complexSum(const Complex* elem1, const Complex* elem2, Complex* res) {
    res->real = elem1->real + elem2->real;
    res->imag = elem1->imag + elem2->imag;
}

#endif //LAB2_COMPLEX_H
