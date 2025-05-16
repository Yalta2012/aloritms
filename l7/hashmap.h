#pragma once
#include <list>
#include <functional>

template<typename T> class HashMap{
    int bucket;

    HashMap();
    HashMap(int bucket);
    ~HashMap();
};


#include "hashmap.tpp"