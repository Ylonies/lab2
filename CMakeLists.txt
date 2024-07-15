cmake_minimum_required(VERSION 3.26)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2 main.cpp
        DynamicArray.h
        LinkedList.h
        Sequence/Sequence.h
        Sequence/MutableArraySequence.h
        Sequence/MutableListSequence.h
        Sequence/ImmutableArraySequence.h
        Sequence/ImmutableListSequence.h
        UI/Menu.h
        Elements/Integer.h
        Elements/Complex.h
        UI/MenuFunctions.h
        Sequence/NamedSequence.h
)
