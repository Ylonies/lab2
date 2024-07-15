
#ifndef LAB2_MUTABLELISTSEQUENCE_H
#define LAB2_MUTABLELISTSEQUENCE_H

#include <iostream>
#include "../LinkedList.h"
#include "Sequence.h"
#include "../DynamicArray.h"


template <typename T>
class MutableListSequence : public Sequence<T> {
private:
    void checkIndex(int index) const{
        if (index < 0)
            throw std::out_of_range("Index must be positive");
        if (index >= getLength())
            throw std::out_of_range("Index out of length");
    }
protected:
    LinkedList<T> *List;

public:
    //constructors
    MutableListSequence() : List(new LinkedList<T>()) {};
    MutableListSequence(T *items, int size) : List(new LinkedList<T>(items, size)) {}

    explicit MutableListSequence(const LinkedList<int> *list) : List(new LinkedList<T>()) {
        int x = list->getLength();
        for (int i = 0; i < list->getLength(); i++) {
            List->append(list->get(i));
        }
    };

    T getFirst() const override {
        return List->getFirst();
    };

    T getLast() const override {
        return List->getLast();
    };

    T get(int index) const override {
        return List->get(index);
    };

    T& operator[](int index) override{
        return List->operator[](index);
    }

    MutableListSequence<T> *getSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        auto *subList = List->getSubList(startIndex, endIndex);
        auto *subSequence = new MutableListSequence{};
        for (int i=0; i< endIndex-startIndex+1; i++){
            subSequence->append(subList->get(i));
        }
        return subSequence;
    }//TODO check is it correct

    size_t getLength() const override {
        return List->getLength();
    };

    Sequence<T>* append(T item) override {
        List->append(item);
        return this;
    };
    Sequence<T>* prepend(T item) override {
        List->prepend(item);
        return this;
    };
    Sequence<T>* insertAT(T item, int index) override {
        checkIndex(index);
        List->insertAt(item, index);
        return this;
    };

    Sequence<T>* concat(Sequence<T> *seq) override{
        List = List->concat(seq->getList());
        return this;
    }

    Sequence<T> *map(T (*function)(T)) const override{
        Sequence<T> *resSeq = new MutableListSequence<T>{};
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
        auto *resSeq = new MutableListSequence<T>;
        for (int i = 0; i < getLength(); i++){
            T item = get(i);
            if (function(item)){
                resSeq->append(item);
            }
        }
        return resSeq;
    }

    MutableListSequence<LinkedList<int>> * split(bool (*function)(T)) const {
        auto *resSeq = new MutableListSequence<LinkedList<T>>;
        auto *curSeq = new LinkedList<T>;
        for (int i = 0; i < getLength(); i++){
            T item = get(i);
            if (function(item)){
                resSeq->append(*curSeq);
                curSeq = new LinkedList<T>;
            }
            else{
                curSeq->append(item);
            }
        }
        resSeq->append(*curSeq);
        return resSeq;
    }


    DynamicArray<T>* getArray() override {
        auto * array = new DynamicArray<T>{};
        for (int i=0; i<getLength(); i++){
            array->add(get(i));
        }
        return array;
    }

    LinkedList<T>* getList() override{
        return List;
    }

    void print() override{
        std::cout << "ListSequence: [";
        for (int i = 0; i< getLength(); i++){
            std::cout << get(i)<< " ";
        }
        std::cout << "]" << endl;
    };

};



#endif //LAB2_MUTABLELISTSEQUENCE_H
