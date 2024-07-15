#include <stdexcept>
#include <iostream>
#include <memory>
using namespace std;

#ifndef LINK_LIST_SEQUENCE_H
#define LINK_LIST_SEQUENCE_H


template<typename T>
struct ListElem {
    T data;
    ListElem<T>* next;
    explicit ListElem(T item) : data(item), next(nullptr) {}
};


template<typename T>
class LinkedList {
protected:
    ListElem<T>* first = nullptr;
    ListElem<T>* last = nullptr;
    size_t size=0;

    struct Iterator{
        using pointer = T *;
        using reference = T &;
    private:
        ListElem<T> *current_ptr;
    public:
        Iterator(ListElem<T> *ptr) : current_ptr(ptr) {}

        reference operator*() const {
            return current_ptr->data;
        }
        pointer operator->() {
            return current_ptr->data;
        }

        Iterator &operator++() {
            current_ptr = current_ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &itr1, const Iterator &itr2) {
            return itr1.current_ptr == itr2.current_ptr;
        };
    };

    Iterator begin() {
        return Iterator(first);
    }
    Iterator end() {
        return Iterator(nullptr);
    }

private:
    ListElem<T> * getElem(size_t index) const {
        ListElem<T> *current = first;
        for (size_t i =0; i< index; i++){
            current = current -> next;
        }
        return current;
    }

    void checkIndex(int index) const {
        if (index < 0)
            throw std::out_of_range("Index must be positive");
        if (index >= getLength())
            throw std::out_of_range("Index out of length");
    }

public:
    //contructors
    LinkedList() {};

    LinkedList(T* items, int size){
        for (int i = 0; i < size; i++) {
            //TODO try-catch here
            append(items[i]);
        }
    };

    LinkedList(const LinkedList <T> & list){
        for (ListElem<T> *current = list.first; current != nullptr; current= current->next) {
            append(current->data);
        }
    };


    void append(T item){
        auto *newElem = new ListElem<T>(item);
        if (first==nullptr) {
            first = newElem;
            last = newElem;
        }
        else {
            last->next = newElem;
            last  = newElem;
        }
        size ++;
    }

    T getFirst(){
        checkIndex(1);
        return first->data;
    };
    T getLast(){
        checkIndex(1);
        return last-> data;
    }

    T get(size_t index) const{
        checkIndex(index);
        ListElem<T> *current = getElem(index);
        return current->data;
    }

    T& operator[](int index) {
        checkIndex(index);
        ListElem<T> *current = getElem(index);
        return current->data;
    }

    LinkedList<T>* getSubList(size_t startIndex, size_t endIndex){
        checkIndex(startIndex);
        checkIndex(endIndex);
        auto *subList = new LinkedList<T>();
        ListElem<T>* current = getElem(startIndex);
        for (size_t i = startIndex; i <= endIndex; i++) {
            subList->append(current->data);
            current = current->next;
        }
        return subList;
    }

    size_t getLength() const {
       return size;
    };

    void prepend(T item){
        auto *newElem = new ListElem<T>(item);
        newElem -> next = first;
        first = newElem;
        size++;
    };

    void insertAt(T item, int index){
        checkIndex(index);
        auto *newElem = new ListElem<T>(item);
        newElem -> next = getElem(index);
        getElem(index-1) -> next = newElem;
        size++;
    };

    LinkedList<T>* concat(LinkedList<T> *list){
        auto *newList = new LinkedList<T>(*this);
        ListElem<T> *current = list->first;
        for (size_t i = 0; i< list->size; i++){
            newList->append(current->data);
            current = current-> next;
        };
        return newList;
    }; //OK


    void print() {
        ListElem<T>* current = first;
        while (current) {
            cout << current->data<< " ";
            current = current->next;
        }
        cout<< "\n";
    };


};

std::ostream& operator << (std::ostream &os, LinkedList<int> list)
{
    std::string message{ "["};
    for (int i =0; i<list.getLength(); i++){
        message.append( std::to_string(list.get(i)));
    } //TODO for others types
    message.append("]");
    return os << message;
};



#endif
