//
// Created by HOME on 24.06.2024.
//
#ifndef LAB2_IMMUTABLEARRAYSEQUENCE_H
#define LAB2_IMMUTABLEARRAYSEQUENCE_H

#include <iostream>
#include "MutableArraySequence.h"

template<typename T>
class ImmutableArraySequence : public MutableArraySequence<T>{
private:
    using MutableArraySequence<T>::Array;

    MutableArraySequence<T>* Instance() {
        auto* cloneSequence = new MutableArraySequence<T>{Array};
        return cloneSequence;
    };
public:

    //constructors
    using MutableArraySequence<T>::MutableArraySequence;

//    public methods of sequence
    Sequence<T>* append(T item) override
    {
        return Instance()->MutableArraySequence<T>::append(item);
    }

    Sequence<T>* prepend(T item) override
    {
        return Instance()->MutableArraySequence<T>::prepend(item);
    }

    Sequence<T>* insertAT(T item, int index) override {
        return Instance()->MutableArraySequence<T>::insertAT(item, index);
    };

    Sequence<T>* concat(Sequence<T> *seq) override {
        return Instance()->MutableArraySequence<T>::concat(seq);
    };

};

#endif //LAB2_IMMUTABLEARRAYSEQUENCE_H
