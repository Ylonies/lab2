#include <stdexcept>
#include <iostream>

#ifndef DIN_ARRAY_SEQUENCE_H
#define DIN_ARRAY_SEQUENCE_H


template<typename T>
class DynamicArray {
protected:
//public:
    T* data;
    size_t capacity;
    size_t currentSize;

private:

    void checkIndex(int index) const {
        if (index < 0)
            throw std::out_of_range("Index must be positive");
        if (index >= currentSize)
            throw std::out_of_range("Index out of length");
    }

public:
    //constructors
    DynamicArray() : data(new T[1]), capacity(1), currentSize(0) {}

    DynamicArray(size_t size) : data(new T[size]), capacity(size), currentSize(0) {}

    DynamicArray(T* items, int count): DynamicArray(count) {
        for (int i = 0; i < count; i++) {
            add(items[i]);
        }
    };

    DynamicArray(const DynamicArray<T>* dynamicArray) : DynamicArray(dynamicArray->data, dynamicArray->currentSize) {};


    //deconstructor
    ~DynamicArray() {
        delete[] data;
    };


    T get(int index) {
        checkIndex(index);
        return data[index];
    }

    T& operator[](int index) {
        checkIndex(index);
        return data[index];
    };

    size_t size() {
        return currentSize;
    }

    void set(T item, int index) {
        checkIndex(index);
        data[index] = item;
    }

    void resize(size_t newSize) {
        capacity = newSize;
        T* newData = new T[capacity];
        currentSize = (currentSize < capacity) ? currentSize : capacity;
        for (size_t i = 0; i < currentSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    void add(const T& item) {
        if (currentSize >= capacity) {
            resize(capacity*2);
        }
        data[currentSize++] = item;
    }


    void remove(size_t index) {
        checkIndex(index);
        for (size_t i = index + 1; i < currentSize; i++) {
            data[i - 1] = data[i];
        }
        resize(currentSize - 1);
    }

//    void print() {
//        for (int i = 0; i < currentSize; i++) {
//            std::cout << data[i]<< " ";
//        }
//        std::cout << "\n";
//    }
};

#endif
