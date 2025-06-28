#pragma once
#include <list>
#include <iostream>
#include <vector>
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

    enum class pair_type
    {
        REGULAR,
        BUCKET_BEGIN,
        LIST_END
    };

    template <typename key_t, typename value_t>
    class hash_map;

    /////////////////////////

    template <typename key_t, typename value_t>
    class pair
    {
        friend class hash_map<key_t, value_t>;

    public:
        pair(const key_t &key, const value_t &value, pair_type type) : _key(key), _value(value), type(type) {}
        key_t key() { return _key; }
        value_t value() { return _value; }
        pair &operator=(const pair &p)
        {
            _key = p._key;
            _value = p._value;
            type = p.type;
            return *this;
        }

    private:
        key_t _key;
        value_t _value;
        pair_type type;
    };

    /////////////////////////

    template <typename key_t, typename value_t>
    class hash_map
    {
    private:
        const double max_load_factor = 0.75;
        size_t size_table_index;
        std::list<pair<key_t, value_t>> element_list;
        std::vector<decltype(element_list.begin())> iterators;
        void resize();
        size_t _size = 0;

    public:
        struct iterator
        {
            friend class hash_map<key_t, value_t>;

        private:
            std::list<pair<key_t, value_t>>::iterator iter;

            void skip()
            {
                while ((*iter).type == pair_type::BUCKET_BEGIN)
                {
                    iter++;
                }
            }

        public:
            iterator(std::list<pair<key_t, value_t>>::iterator iter) : iter(iter) {}
            iterator &operator++()
            {
                ++iter;
                skip();
                return *this;
            }
            pair<key_t, value_t> *operator->()
            {
                return &(*iter);
            }

            pair<key_t, value_t> &operator*() const
            {
                return *iter;
            }
            bool operator==(const iterator &other)
            {
                return iter == other.iter;
            }
            bool operator!=(const iterator &other)
            {
                return iter != other.iter;
            }
        };

        hash_map();
        void put(const key_t &, const value_t &);
        void remove(const key_t &);
        bool contains(const key_t &);
        bool empty();
        value_t &get(const key_t &);
        value_t &operator[](const key_t &);

        size_t total_buckets();
        size_t size();
        void clear();
        iterator begin();
        iterator end();
        void print();
        static size_t hash(const key_t &, size_t);
        hash_map<key_t, value_t> &operator=(const hash_map<key_t, value_t> &);
    };

} // namespace curs

#include "hashmap.tpp"