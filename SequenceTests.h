//
// Created by HOME on 19.05.2024.
//

#include <iostream>
#include <string>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence/MutableArraySequence.h"
#include "Sequence/ImmutableArraySequence.h"
#include "Sequence/ImmutableListSequence.h"
#include "Sequence/MutableListSequence.h"
#include "Sequence/NamedSequence.h"
#include "Elements/Integer.h"

int LinkedListTest() {
    int list[2];
    list[0] = 1;
    list[1] = 2;
    LinkedList<int> linkedList{};
    LinkedList<int> linkedList1{list, 2};
    LinkedList<int> linkedList2{linkedList1};

    linkedList2.print();
    cout << "First element:" << linkedList2.getFirst()<< endl;
    cout << "Last element:"<< linkedList2.getLast()<< endl;
    cout << "Length:" << linkedList2.getLength()<< endl;
    cout << linkedList2.get(0)<< endl;

    linkedList2.append(3);
    linkedList2.prepend(3);
    linkedList2.insertAt(10, 2);
    linkedList2.print();

    LinkedList<int>* subList = linkedList2.getSubList(1, 2);
    subList->print();

    LinkedList<int>* concatList = linkedList2.concat(&linkedList1);
    concatList->print();

    return 0;
}

int MutableListSequenceTest(){
    int mas[3];
    mas[0] = 1;
    mas[1] = 2;
    mas[2] = 3;

    LinkedList<int> list{mas, 1};
    //constructors
    MutableListSequence<int> listSeq{};
    MutableListSequence<int> listSeq2{mas, 3};
    MutableListSequence<int> listSeq3{&list};
    listSeq.print();
    listSeq2.print();
    listSeq3.print();

    MutableListSequence<int> * subSeq = listSeq2.getSubsequence(1, 2);
    subSeq->print();

    listSeq2.concat(&listSeq3)->print();

    MutableArraySequence<int> array2{ mas, 1};
    listSeq2.concat(&array2)->print(); //concat can join all sequence

    return 0;
};

int MutableArraySequenceTest(){
    int  mas[3];
    mas[0] = 1;
    mas[1] = 2;
    mas[2] = 3;
    // constructors
    DynamicArray<int> array2{ mas, 3};
    MutableArraySequence<int> arraySeq{mas, 3};

    arraySeq.prepend(0);
    arraySeq.append(5);
    arraySeq.insertAT(4, 4);

    std::cout << "First element:" << arraySeq.getFirst() << std::endl;
    std::cout << "Last element:" <<  arraySeq.getLast() << std::endl;
    std::cout << "Length:" <<  arraySeq.getLength() << std::endl;
    arraySeq.print();

    MutableArraySequence<int>* subArray = arraySeq.getSubsequence(0, 2);
    subArray->print();

    arraySeq.concat(subArray);
    arraySeq.print();

    MutableListSequence<int> list{mas, 2};
    arraySeq.concat(&list)->print();
    return 0;
}

int ImmutableArraySequenceTest(){
    int  mas[3];
    mas[0] = 1;
    mas[1] = 2;
    mas[2] = 3;
    // constructors
    DynamicArray<int> array2{ mas, 3};
    ImmutableArraySequence<int> arraySeq{mas, 3};

    arraySeq.append(4)->print();
    arraySeq.prepend(0)->print();
    arraySeq.insertAT(-2, 2)->print();
    arraySeq.concat(&arraySeq)->print();
    arraySeq.print();
    return 0;
}

int ImmutableListSequenceTest(){
    int  mas[4];
    mas[0] = 1;
    mas[1] = 2;
    mas[2] = 3;
    mas[3] = 4;

    LinkedList<int> list{mas, 3};
    ImmutableListSequence<int> listSeq{mas, 4};
    listSeq.append(4)->print();
    listSeq.prepend(0)->print();
    listSeq.insertAT(-2, 2)->print();
    listSeq.concat(&listSeq);
//    listSeq.split(f)->print();
    std::cout << listSeq[0] << std::endl;
    listSeq.print();

//    Collection<int> collection{};
//    collection.addSequence(&listSeq, "first");
    DynamicArray<NamedSequence<int>> collection{};
    NamedSequence seq{&listSeq, "first"};
    collection.add(seq);
    std::cout<<collection[0].name;
    collection[0].sequence->append(2);

    Collection<int> collection2{};
    collection2.add(seq);
    collection2.findByName("first")->print();
    listSeq.map(IntMapLen)->print();
    return 0;

}


int test() {
    MutableListSequenceTest();
    ImmutableArraySequenceTest();
    ImmutableListSequenceTest();
    LinkedListTest();
    return 0;
}