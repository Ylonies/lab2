//
// Created by HOME on 25.06.2024.
//

#ifndef LAB2_IMMUTABLELISTSEQUENCE_H
#define LAB2_IMMUTABLELISTSEQUENCE_H

#include <iostream>
#include "MutableListSequence.h"

template<typename T>
class ImmutableListSequence : public MutableListSequence<T>{
private:
    using MutableListSequence<T>::List;

    MutableListSequence<T>* Instance() {
        auto* cloneSequence = new MutableListSequence<T>{List};
        return cloneSequence;
    };
public:

    //constructors
    using MutableListSequence<T>::MutableListSequence;

//    public methods of sequence
    Sequence<T>* append(T item) override
    {
        return Instance()->MutableListSequence<T>::append(item);
    }

    Sequence<T>* prepend(T item) override
    {
        return Instance()->MutableListSequence<T>::prepend(item);
    }

    Sequence<T>* insertAT(T item, int index) override {
        return Instance()->MutableListSequence<T>::insertAT(item, index);
    };

    Sequence<T>* concat(Sequence<T> *seq) override {
        return Instance()->MutableListSequence<T>::concat(seq);
    };

};


#endif //LAB2_IMMUTABLELISTSEQUENCE_H

