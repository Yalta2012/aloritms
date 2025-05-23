#pragma once
#include <list>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <vector>
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

    enum class PairType
    {
        REGULAR,
        BUCKET_BEGIN,
        LIST_END
    };


    template <typename key_t, typename value_t>
    class HashMap;
    /////////////////////////
    template <typename key_t, typename value_t>
    class Pair
    {
        friend class HashMap<key_t, value_t>;

    public:
        Pair(const key_t &, const value_t &, PairType);

    private:
        key_t key;
        value_t value;
        const PairType type;
    };
    /////////////////////////

    template <typename key_t, typename value_t>
    class HashMap
    {

    private:
        const double max_load_factor = 0.75;
        size_t size_table_index;
        size_t element_couner;
        std::list<Pair<key_t, value_t>> element_list;
        std::vector<decltype(element_list.begin())> iterators;
        struct Iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Pair<key_t, value_t>;
            using pointer = Pair<key_t, value_t> *;
            using reference = Pair<key_t, value_t> &;
            pointer m_ptr;

        public:
            Iterator(pointer ptr) : m_ptr(ptr) {};
            Iterator &operator++();
            Iterator operator++(int);
            pointer operator->();
            reference operator*() const;
            bool operator==(const Iterator &);
            bool operator!=(const Iterator &);
        };

    public:
        HashMap();
        void Put(const key_t &, const value_t &);
        void Remove(const key_t &);
        bool Contains(const key_t &);
        value_t &Get(const key_t &);
        value_t &operator[](const key_t &);
        size_t TotalBuckets();
        size_t Size();
        void Resize(char direction);
        void Clear();
        Iterator begin();
        Iterator end();
        void Print();
        static size_t hash(const key_t &, size_t);
        // size_t correct_index(const key_t &);
        // size_t correct_index(const key_t &, size_t);
    };

} // namespace curs

#include "hashmap.tpp"