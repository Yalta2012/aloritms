#include "hashmap.h"
using namespace curs;

template <typename key_type, typename value_type>
void Pair<key_type, value_type>::Print()
{
    std::cout << "Pair: " << key << " " << value << std::endl;
}
template <typename key_type, typename value_type>
Pair<key_type, value_type>::Pair(key_type k, value_type v)
{
    key = k;
    value = v;
    // std::cout << "Pair: " << key << " " << value << std::endl;
}

// Pair<key_type, value_type>(key_type _key, value_type _value) : key(_key), value(_value){};

template <typename key_type, typename value_type>
HashMap<key_type, value_type>::HashMap()
{
    size_table_index = 0;
    size_t total_buckets;
    size_t occpied_buckets;
    const double max_load_factor = 0.75;
    buckets = std::make_unique<std::list<Pair<key_type, value_type>>[]>(size_table[size_table_index]);
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::Put(key_type key, value_type val)
{
    buckets[correct_index(key)].push_back(Pair(key, val));
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::correct_index(key_type key)
{
    auto hash = std::hash<key_type>();
    return hash(key) % size_table[size_table_index];
}