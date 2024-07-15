//
// Created by HOME on 25.06.2024.
//

#ifndef LAB2_MENUFUNCTIONS_H
#define LAB2_MENUFUNCTIONS_H

#include <iostream>
#include <string>
#include "../DynamicArray.h"
#include "../Sequence/NamedSequence.h"
#include "../Sequence/ImmutableArraySequence.h"
#include "../Elements/Integer.h"

using namespace std;

template <typename T>
int  case2(Collection<T>* collection, Sequence<T>* sequence, string seqType){
    int input3;
    if (seqType == "array"){
        ArrayMenu();
    }
    if (seqType == "list"){
        ListMenu();
    }
    cin>> input3;
    if (input3 == 0){
        return 0;
    }
    switch (input3) {
        case 1:
        {
            showSequence(sequence);
            return 1;
        }
        case 2:{
            appendSequence(sequence);
            showSequence(sequence);
            return 1;
        }
        case 3:{
            prependSequence(sequence);
            showSequence(sequence);
            return 1;
        }
        case 4:{
            insertATSequence(sequence);
            showSequence(sequence);
            return 1;
        }
        case 5:{
            Sequence<T>* subSeq = getSubsequence(sequence);
            showSequence(subSeq);
            return 1;
        }
        case 6:{
            Sequence<T>* concatSeq = concat(collection, sequence, "array");
            showSequence(concatSeq);
            return 1;
        }
        case 7:{
            MapMenu();
            Sequence<T>* seq = mapSequence(sequence);
            showSequence(seq);
            return 1;
        }
        case 8:{
            ReduceMenu();
            T seq = reduceSequence(sequence);
            cout << "Result: " << seq << endl;
            return 1;
        }
        case 9:{
            FilterMenu();
            Sequence<T>* seq = filterSequence(sequence);
            showSequence(seq);
            return 1;
        }
        default:
        {
            wprintf(L"Unknown command.\n");
            return 1;
        }
    }
};

//template <typename T>
//int listCase(Collection<T>* listCollection, Sequence<T>* listSeq){
//    int input3;
//    ListMenu();
//    cin>> input3;
//    if (input3 == 0){
//        return 0;
//    }
//    switch (input3) {
//        case 1:
//        {
//            showSequence(listSeq);
//            return 1;
//        }
//        case 2:{
//            appendSequence(listSeq);
//            showSequence(listSeq);
//            return 1;
//        }
//        case 3:{
//            prependSequence(listSeq);
//            showSequence(listSeq);
//            return 1;
//        }
//        case 4:{
//            insertATSequence(listSeq);
//            showSequence(listSeq);
//            return 1;
//        }
//        case 5:{
//            Sequence<T>* subSeq = getSubsequence(listSeq);
//            showSequence(subSeq);
//            return 1;
//        }
//        case 6:{
//            Sequence<T>* concatSeq = concat(listCollection, listSeq, "array");
//            showSequence(concatSeq);
//            return 1;
//        }
//        case 7:{
//            MapMenu();
//            Sequence<T>* seq = mapSequence(listSeq);
//            showSequence(seq);
//            return 1;
//        }
//        case 8:{
//            ReduceMenu();
//            T seq = reduceSequence(listSeq);
//            cout << "Result: " << seq << endl;
//            return 1;
//        }
//        case 9:{
//            FilterMenu();
//            Sequence<T>* seq = filterSequence(listSeq);
//            showSequence(seq);
//            return 1;
//        }
//        default:
//        {
//            wprintf(L"Unknown command.\n");
//            return 1;
//        }
//    }
//}

template <typename T>
void newArray(Collection<T> *arrayCollection){
    string name;
    wprintf(L"Write name for new array.\n");
    cin >> name;
    auto *array = new MutableArraySequence<int>{};//TODO immutable too?
    arrayCollection->add(NamedSequence<T>{array, name});
}

template <typename T>
void newList(Collection<T> *listCollection){
    string name;
    wprintf(L"Write name for new list.\n");
    cin >> name;
    auto *array = new MutableListSequence<int>{};//TODO immutable too?
    listCollection->add(NamedSequence<T>{array, name});
}


template <typename T>
Sequence<T>* findSeq(Collection<T> *collection, string seqType){
    string name;
    cout << "All " << seqType << "s:" << endl;
    for (int i=0; i < collection->size(); i++){
        cout << (*collection)[i].name << " ";
    }
    cout<< endl;
    cout << "Write name of " << seqType << endl;

    cin >> name;
    return collection->findByName(name);
};

template <typename T>
void showSequence(Sequence<T>* seq){
    seq->print();
};

template <typename T>
void appendSequence(Sequence<T>* seq){
    wprintf(L"Write an element:\n");
    T elem;
    cin>> elem;
    seq->append(elem);
};

template <typename T>
void prependSequence(Sequence<T>* seq){
    wprintf(L"Write an element:\n");
    T elem;
    cin>> elem;
    seq->prepend(elem);
};

template <typename T>
void insertATSequence(Sequence<T>* seq){
    wprintf(L"Write an element:\n");
    T elem;
    cin>> elem;
    wprintf(L"Write a position:\n");
    int index;
    cin>> index;
    seq->insertAT(elem, index);
};

template <typename T>
Sequence<T>* getSubsequence(Sequence<T>* seq){
    int startIndex, endIndex;
    wprintf(L"Write start index:\n");
    cin>> startIndex;
    wprintf(L"Write end index:\n");
    cin>> endIndex;
    return seq->getSubsequence(startIndex, endIndex);
};

template <typename T>
Sequence<T>* concat(Collection<T> *collection, Sequence<T>* seq, string seqType){
    string name;
    cout << "Write name of " << seqType << endl;
    cin>> name;
    auto* seq2 = collection->findByName(name);
    return seq->concat(seq2);
};

template <typename T>
Sequence<T>* mapSequence(Sequence<T>* seq){
    int input;
    Sequence<T>* newSeq;
    cin>> input;
    switch (input) {
        case 1:{
            if (std::is_same<T, int>::value){
                newSeq = seq->map(IntMapAbs);
            }
            //TODO complex
            break;
        }
        case 2:{
            if (std::is_same<T, int>::value){
                newSeq =  seq->map(IntMapLen);
            }
            break;
        }
    }
    return newSeq;
}

template <typename T>
T reduceSequence(Sequence<T>* seq){
    int input;
    T newSeq;
    cin>> input;
    switch (input) {
        case 1:{
            if (std::is_same<T, int>::value){
                newSeq = seq->reduce(IntSum);
            }
            //TODO complex
            break;
        }
        case 2:{
            if (std::is_same<T, int>::value){
                newSeq =  seq->reduce(IntMult);
            }
            break;
        }
    }
    return newSeq;
}

template <typename T>
Sequence<T>* filterSequence(Sequence<T>* seq){
    int input;
    Sequence<T>* newSeq;
    cin>> input;
    switch (input) {
        case 1:{
            if (std::is_same<T, int>::value){
                newSeq = seq->where(IntCheckPos);
            }
            //TODO complex
            break;
        }
        case 2:{
            if (std::is_same<T, int>::value){
                newSeq =  seq->where(IntCheckEven);
            }
            break;
        }
    }
    return newSeq;
}



#endif //LAB2_MENUFUNCTIONS_H
