#pragma once
#include <list>
#include <functional>
#include <iostream>
#include <memory>

namespace curs
{

    const size_t size_table[] =
        {
            5ul, 53ul, 97ul, 193ul, 389ul,
            769ul, 1543ul, 3079ul, 6151ul, 12289ul,
            24593ul, 49157ul, 98317ul, 196613ul, 393241ul,
            786433ul, 1572869ul, 3145739ul, 6291469ul, 12582917ul,
            25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul,
            805306457ul, 1610612741ul, 3221225473ul, 4294967291ul};
    const size_t max_size_table_index = 23;


    template <typename key_type, typename value_type>
    class Pair
    {
    public:
        Pair(key_type, value_type);
        // ~Pair<key_type, value_type>(){};
        void Print();

    private:
        key_type key;
        value_type value;
    };

    template <typename key_type, typename value_type>
    class HashMap
    {
        friend class Pair<key_type, value_type>;

    public:
        HashMap<key_type, value_type>();
        ~HashMap<key_type, value_type>(){};
        void Put(key_type, value_type);
        void Remove(key_type &, value_type &);
        bool Contains(key_type &);
        value_type &Get(value_type &);
        size_t correct_index(key_type);

    private:
        size_t total_buckets;
        size_t occpied_buckets;
        const double max_load_factor = 0.75;
        size_t size_table_index;
        std::unique_ptr<std::list<Pair<key_type, value_type>>[]> buckets;
        void Resize();
    };

} // namespace curs

#include "hashmap.tpp"