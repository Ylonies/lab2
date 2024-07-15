//
// Created by HOME on 25.06.2024.
//

#ifndef LAB2_MENU_H
#define LAB2_MENU_H

void printMenu(){
    wprintf(L"Choose:\n");
    wprintf(L"0. STOP\n");
    wprintf(L"1. Dynamic Arrays\n");
    wprintf(L"2. Linked Lists\n");
}

void DynamicArraysMenu(){
    wprintf(L"Choose:\n");
    wprintf(L"0. STOP\n");
    wprintf(L"1. New array\n");
    wprintf(L"2. Show existing array\n");
}

void LinkedListsMenu(){
    wprintf(L"Choose:\n");
    wprintf(L"0. STOP\n");
    wprintf(L"1. New list\n");
    wprintf(L"2. Show existing list\n");
}

void ArrayMenu(){
    wprintf(L"Choose:\n");
    wprintf(L"0. Exit\n");
    wprintf(L"1. Show array\n");
    wprintf(L"2. Add element to the end\n");
    wprintf(L"3. Add element to the beginning\n");
    wprintf(L"4. Insert element in array\n");
    wprintf(L"5. Get a subsequence\n");
    wprintf(L"6. Concatenate this array with other\n");
    wprintf(L"7. Map array\n");
    wprintf(L"8. Reduce array\n");
    wprintf(L"9. Filter array\n");
}

void MapMenu(){
    wprintf(L"1. Make positive\n");
    wprintf(L"2. Change to length\n");
}

void ReduceMenu(){
    wprintf(L"1. Summarise all\n");
    wprintf(L"2. Multiply all \n");
}

void FilterMenu(){
    wprintf(L"1. Only positive\n");
    wprintf(L"2. Only even\n");
}


void ListMenu(){
    wprintf(L"Choose:\n");
    wprintf(L"0. Exit\n");
    wprintf(L"1. Show list\n");
    wprintf(L"2. Add element to the end\n");
    wprintf(L"3. Add element to the beginning\n");
    wprintf(L"4. Insert element in list\n");
    wprintf(L"5. Get a subsequence\n");
    wprintf(L"6. Concatenate this list with other\n");
}


#endif //LAB2_MENU_H
