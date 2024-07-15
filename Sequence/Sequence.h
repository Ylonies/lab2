//
// Created by HOME on 19.05.2024.
//

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H




template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;

    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual size_t getLength() const = 0;
    virtual T get(int index) const = 0;
    virtual Sequence<T> *getSubsequence(int startIndex, int endIndex) const = 0;
//    virtual void append(T item) = 0;
    virtual T& operator[](int index) = 0;
    virtual Sequence<T>* prepend(T item) = 0;
    virtual Sequence<T>* insertAT(T item, int index) = 0;
    virtual Sequence<T>* append(T item)=0;
    virtual Sequence <T>* concat(Sequence <T> *list) = 0;

    virtual Sequence<T>* map(T (*function)(T)) const = 0;
    virtual T reduce(T (*function)(T, T)) const = 0;
    virtual Sequence<T> *where(bool (*function)(T)) const = 0;

    virtual LinkedList<T>* getList() = 0 ;
    virtual DynamicArray<T>* getArray() = 0;
    virtual void print() = 0;


};


#endif //LAB2_SEQUENCE_H
