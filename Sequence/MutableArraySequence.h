#ifndef LAB2_MUTABLEARRAYSEQUENCE_H
#define LAB2_MUTABLEARRAYSEQUENCE_H

#include <iostream>
#include "Sequence.h"
#include "../DynamicArray.h"
#include "../LinkedList.h"

using namespace std;

template<typename T>
class MutableArraySequence: public Sequence<T> {
private:

protected:
    DynamicArray<T> *Array;

    void checkIndex(int index) const {
        if (index < 0)
            throw std::out_of_range("Index must be positive");
        if (index >= getLength())
            throw std::out_of_range("Index out of length");
    }

public:
    //constructors
    MutableArraySequence(): Array(new DynamicArray<T>()) {}
    MutableArraySequence(T *items, int size) : Array(new DynamicArray<T>(items, size)) {}
    explicit MutableArraySequence(DynamicArray <T> *array): Array(new DynamicArray<T>(array)) {}
//    /*virtual T& operator[](size_t index) = 0;*/ //TODO

    T getFirst() const override{
        return Array->get(0);
    };

    T getLast() const override{
        return Array->get(Array->size() - 1);
    };

    size_t getLength() const override {
        return Array->size();
    }

    T get(int index) const override{
        return Array->get(index);
    }

    T& operator[](int index) override {
        return Array->operator[](index);
    }

    MutableArraySequence<T> *getSubsequence(int startIndex, int endIndex) const override{
        checkIndex(startIndex);
        checkIndex(endIndex);
        auto *subSequence = new MutableArraySequence<T>();
        for (int index = startIndex; index <= endIndex; index++) {
            subSequence->append(Array->get(index));
        }
        return subSequence;
    };

    Sequence<T>* append(T item) override{
        Array->add(item);
        return this;
    }

    Sequence<T>* prepend(T item) override {
        size_t arraySize = Array->size();
        if (arraySize == 0) {
            append(item);
            return this;
        }
        Array->resize(arraySize+1);
        Array->add(Array->get(arraySize-1));
        for (int i=arraySize-1; i>0; i--){
            Array->set(Array->get(i-1), i);
        }
        Array->set(item, 0);
        return this;
    };

    Sequence<T>* insertAT(T item, int index) override {
        checkIndex(index);
        size_t arraySize = Array->size();
        Array->resize(arraySize+1);
        Array->add(Array->get(arraySize-1));
        for (int i=index+1; i<arraySize; i++){
            Array->set(Array->get(i-1), i);
        }
        Array->set(item, index);
        return this;
    };

    Sequence<T>* concat(Sequence<T> *seq) override{
        DynamicArray<T>* array = seq->getArray();
        for (int i = 0; i< array->size(); i++){
            append(array->get(i));
        }
        return this;
    };

    Sequence<T> *map(T (*function)(T)) const override{
        Sequence<T> *resSeq = new MutableArraySequence<T>{};
        for (int i = 0; i < getLength(); i++){
            resSeq->append(function(get(i)));
        }
        return resSeq;
    }

    T reduce(T (*function)(T, T)) const override{
        T result = getFirst();
        for (int i = 1; i < getLength(); i++){
            result = function(result, get(i));
        }
        return result;
    }

    Sequence<T> *where(bool (*function)(T)) const override {
        auto *resSeq = new MutableArraySequence<T>;
        for (int i = 0; i < getLength(); i++){
            T item = get(i);
            if (function(item)){
                resSeq->append(item);
            }
        }
        return resSeq;
    }


    DynamicArray<T>* getArray() override{
        return Array;
    }
    LinkedList<T>* getList() {
        auto * list = new LinkedList<T>{};
        for (int i=0; i<getLength(); i++){
            list->append(get(i));
        }
        return list;
    }

    void print() override{
        std::cout << "ArraySequence: [";
        for (int i = 0; i< getLength(); i++){
            std::cout << get(i)<< " ";
        }
        std::cout << "]" << endl;
    };

};

#endif //LAB2_MUTABLEARRAYSEQUENCE_H
