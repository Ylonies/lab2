#include <iostream>
#include "SequenceTests.h"
#include "UI/Menu.h"
#include "UI/MenuFunctions.h"


void sequence_UI(){
    int input0, input1, input3;
    std::string name;
    auto * arrayCollection = new Collection<int>;
    auto * listCollection = new Collection<int>;

//    Collection<Complex> arrayCollection{};
//    Collection<Complex> listCollection{};

    while(true) {
        printMenu();
        cin >> input0;
        if (input0 == 0) {
            break;
        }
        switch (input0) {
            case 1:{
                DynamicArraysMenu();
                cin >> input1;
                if (input1 == 0) {
                    break;
                }
                switch (input1) {
                    case 1: {
                        newArray(arrayCollection);
                        break;
                    }
                    case 2:{
                        auto* arraySeq = findSeq(arrayCollection, "array");
                        if (arraySeq == nullptr){
                            wprintf(L"There is no array with this name.\n");
                            break;
                        }
                        input3 = 1;
                        while (input3){
                            input3 = case2(arrayCollection, arraySeq, "array");
                        }
                        break;
                    }
                    default:
                    {
                        wprintf(L"Unknown command.\n");
                        break;
                    }
                }
                break;
            }
            case 2:{
                LinkedListsMenu();
                cin >> input1;
                if (input1 == 0) {
                    break;
                }
                switch (input1) {
                    case 1: {
                        newList(listCollection);
                        break;
                    }
                    case 2:{
                        auto* listSeq = findSeq(listCollection, "list");
                        if (listSeq == nullptr){
                            wprintf(L"There is no list with this name.\n");
                            break;
                        }
                        input3 = 1;
                        while (input3){
                            input3 = case2(arrayCollection, listSeq, "list");
                        }
                        break;
                    }
                    default:
                    {
                        wprintf(L"Unknown command.\n");
                        break;
                    }
                }
                break;
            }

            default:
            {
                wprintf(L"Unknown command.\n");
                break;
            }
        }
    }
}

int main(){

//    test();
//    sequence_UI();
}



