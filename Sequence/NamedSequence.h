//
// Created by HOME on 25.06.2024.
//

#ifndef LAB2_NAMEDSEQUENCE_H
#define LAB2_NAMEDSEQUENCE_H


#include <string>
#include <utility>
#include "Sequence.h"
#include "../DynamicArray.h"

using namespace std;

template<typename T>
class NamedSequence{
public:
    Sequence<T>* sequence;
    std::string name;
    explicit NamedSequence(Sequence<T>* sequence, std::string name): sequence(sequence), name(std::move(name)){};
    explicit NamedSequence():sequence(nullptr), name("-") {}

};

template<typename T>
class Collection: public DynamicArray<NamedSequence<T>> {
public:
  using  DynamicArray<NamedSequence<T>>::DynamicArray;
  using  DynamicArray<NamedSequence<T>>::currentSize;
  using  DynamicArray<NamedSequence<T>>::data;

  Sequence<T>* findByName( std::string name){
        for (int i =0; i<currentSize; i++){
            if (data[i].name == name){
                return data[i].sequence;
            }
        }
        return nullptr;
    }
};

#endif //LAB2_NAMEDSEQUENCE_H
