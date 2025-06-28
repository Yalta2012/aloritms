#include "hashmap.h"
using namespace curs;

template <typename key_t, typename value_t>
size_t
hash_map<key_t, value_t>::total_buckets()
{
    return size_table[size_table_index];
}

template <typename key_t, typename value_t>
hash_map<key_t, value_t>::hash_map() : size_table_index(0)
{
    element_list = std::list<pair<key_t, value_t>>();
    iterators = std::vector<decltype(element_list.begin())>(total_buckets() + 1);

    for (size_t i = 0; i < total_buckets(); i++)
    {
        element_list.push_back(pair(key_t(), value_t(), pair_type::BUCKET_BEGIN));
        iterators[i] = std::prev(element_list.end());
    }
    element_list.push_back(pair(key_t(), value_t(), pair_type::LIST_END));
}

template <typename key_t, typename value_t>
size_t
hash_map<key_t, value_t>::hash(const key_t &key, size_t __size)
{
    auto hash = std::hash<key_t>();
    return hash(key) % __size;
}

template <typename key_t, typename value_t>
void hash_map<key_t, value_t>::print()
{
    size_t c = 0;
    for (auto i : element_list)
    {
        std::cout << c << ") ";
        switch (i.type)
        {
        case pair_type::LIST_END:
            std::cout << "$END OF LIST";
            break;
        case pair_type::BUCKET_BEGIN:
            std::cout << "$BEGINING OF BUCKET";
            break;
        case pair_type::REGULAR:
            std::cout << i._key << " " << i._value;
            break;
        default:
            std::cout << "$UNKNOWN";
            break;
        }
        std::cout << std::endl;
        if (i.type == pair_type::LIST_END)
            break;
        c++;
    }
}

template <typename key_t, typename value_t>
bool hash_map<key_t, value_t>::contains(const key_t &key)
{
    auto i = iterators[hash(key, total_buckets())];
    for (i++; i->type == pair_type::REGULAR; i++)
        if (i->_key == key)
            return true;
    return false;
}

template <typename key_t, typename value_t>
void hash_map<key_t, value_t>::put(const key_t &key, const value_t &val)
{
    auto i = iterators[hash(key, total_buckets())];

    for (i++; i->type == pair_type::REGULAR; i++)
        if (i->_key == key)
        {
            i->_value = val;
            return;
        }
    element_list.insert(i, pair(key, val, pair_type::REGULAR));
    _size++;
    if (static_cast<double>(size()) / total_buckets() >= max_load_factor)
    {
        resize();
    }
}

template <typename key_t, typename value_t>
void hash_map<key_t, value_t>::remove(const key_t &key)
{
    auto i = iterators[hash(key, total_buckets())];
    for (i++; i->type == pair_type::REGULAR; i++)
        if (i->_key == key)
        {
            element_list.erase(i);

            _size--;
            return;
        }
}

template <typename key_t, typename value_t>
value_t &hash_map<key_t, value_t>::get(const key_t &key)
{
    auto i = iterators[hash(key, total_buckets())];
    for (i++; i->type == pair_type::REGULAR; i++)
        if (i->_key == key)
        {
            return (*i)._value;
        }
    element_list.insert(i, pair(key, value_t(), pair_type::REGULAR));
    return (*(--i))._value;
}

template <typename key_t, typename value_t>
value_t &hash_map<key_t, value_t>::operator[](const key_t &key)
{
    return get(key);
}

template <typename key_t, typename value_t>
size_t hash_map<key_t, value_t>::size()
{
    return _size;
}

template <typename key_t, typename value_t>
bool hash_map<key_t, value_t>::empty()
{
    return size() == 0;
}

template <typename key_t, typename value_t>
void hash_map<key_t, value_t>::clear()
{
    size_table_index=0;
    element_list = std::list<pair<key_t, value_t>>();
    iterators = std::vector<decltype(element_list.begin())>(total_buckets() + 1);
    
    size_t i;
    for (i = 0; i < total_buckets(); i++)
    {
        element_list.push_back(pair(key_t(), value_t(), pair_type::BUCKET_BEGIN));
    }
    element_list.push_back(pair(key_t(), value_t(), pair_type::LIST_END));
    i = 0;
    for (auto iter = element_list.begin(); iter != element_list.end(); i++, iter++)
    {
        iterators[i] = iter;
    }
    _size=0;
}

template <typename key_t, typename value_t>
hash_map<key_t, value_t> &hash_map<key_t, value_t>::operator=(const hash_map<key_t, value_t> &map)
{
    element_list = std::list<pair<key_t, value_t>>();
    size_table_index = map.size_table_index;
    iterators = std::vector<decltype(element_list.begin())>(map.iterators.size());
    _size = map._size;
    size_t i = 0;

    for (auto iter = map.element_list.begin(); iter != map.element_list.end(); iter++)
    {
        element_list.push_back(*iter);
        if (element_list.back().type == pair_type::BUCKET_BEGIN)
        {
            iterators[i++] = std::prev(element_list.end());
        }
    }

    return *this;
}

template <typename key_t, typename value_t>
hash_map<key_t, value_t>::iterator hash_map<key_t, value_t>::begin()
{
    auto res = iterator(element_list.begin());
    res.skip();
    return res;
}

template <typename key_t, typename value_t>
hash_map<key_t, value_t>::iterator hash_map<key_t, value_t>::end()
{
    return iterator(std::prev(element_list.end()));
}

template <typename key_t, typename value_t>
void hash_map<key_t, value_t>::resize()
{
    if (size_table_index < max_size_table_index)
    {
        size_table_index++;
    }
    else
        return;

    auto buf_element_list = element_list;
    element_list.clear();
    iterators = std::vector<decltype(element_list.begin())>(total_buckets() + 1);

    for (size_t i = 0; i < total_buckets(); i++)
    {
        element_list.push_back(pair(key_t(), value_t(), pair_type::BUCKET_BEGIN));
        iterators[i] = std::prev(element_list.end());
    }
    element_list.push_back(pair(key_t(), value_t(), pair_type::LIST_END));

    for (auto &j : buf_element_list)
    {
        if (j.type == pair_type::REGULAR)
        {

            auto iter = iterators[hash(j._key, total_buckets())];
            for (iter++; iter->type == pair_type::REGULAR; iter++)
            {
                ;
            }
            element_list.insert(iter, pair(j._key, j._value, pair_type::REGULAR));
        }
    }
}

////////////////////////////////////////////////////
