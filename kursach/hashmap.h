#pragma once
#include <list>
#include <functional>

namespace curs
{
    
    template<typename Key, typename Val> class Pair{
        Key key;
        Val value;
    };
    
    template<typename Key, typename Val> class HashMap{
        private:
            size_t m;
            size_t n;
            size_t coefficietn;
            std::list<Pair> * buckets [];

            void Put(&Key, &Val);
            void Remove(&Key, &Val);
            &Key Get(&Val);

    };
    
} // namespace curs

#include "hashmap.tpp"