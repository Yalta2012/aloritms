#include "hashmap.h"
using namespace curs;

// Pair

template <typename key_t, typename value_t>
void Pair<key_t, value_t>::Print()
{
    std::cout << "Pair: " << key << " " << value << std::endl;
}

template <typename key_t, typename value_t>
Pair<key_t, value_t>::Pair(key_t k, value_t v) : key(k), value(v) {}

// HashMap

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::HashMap():size_table_index(0), occpied_buckets(0),begin_iterator(nullptr)
{
    buckets = std::vector<std::list<Pair<key_t, value_t>>>(size_table[size_table_index]);
    begin_iterator.m_ptr = nullptr;
}

template <typename key_t, typename value_t>
size_t HashMap<key_t, value_t>::correct_index(const key_t &key)
{
    auto hash = std::hash<key_t>();
    return hash(key) % size_table[size_table_index];
}

template <typename key_t, typename value_t>
bool HashMap<key_t, value_t>::Contains(const key_t &key)
{
    for (auto &i : buckets[correct_index(key)])
        if (i.key == key)
            return true;

    return false;
}

template <typename key_t, typename value_t>
void HashMap<key_t, value_t>::Put(const key_t &key, const value_t &val)
{
    auto hash = std::hash<key_t>();
    auto index = correct_index(key);
    for (auto &i : buckets[index])
        if (i.key == key)
        {
            i.value = val;
            return;
        }
    buckets[index].push_back(Pair(key, val));
    occpied_buckets++;
    if (begin_iterator.m_ptr==nullptr || index < hash(begin_iterator->key))
    {
        begin_iterator = Iterator(&(buckets[index].back()), index,0);
    }
}

template <typename key_t, typename value_t>
void HashMap<key_t, value_t>::Remove(const key_t &key)
{
    for (auto i = buckets[correct_index(key)].begin(); i != buckets[correct_index(key)].end(); i++)
        if (i->key == key)
        {
            buckets[correct_index(key)].erase(i);
            occpied_buckets--;
            break;
        }
}

template <typename key_t, typename value_t>
value_t &HashMap<key_t, value_t>::Get(const key_t &key)
{
    for (auto i = buckets[correct_index(key)].begin(); i != buckets[correct_index(key)].end(); i++)
        if (i->key == key)
        {
            return i->value;
        }
    Put(key, value_t());
    return buckets[correct_index(key)].back().value;
}

template <typename key_t, typename value_t>
value_t &HashMap<key_t, value_t>::operator[](const key_t &key)
{
    return Get(key);
}

// template <typename key_t, typename value_t>
// void HashMap<key_t, value_t>::Resize(char direction)
// {
//     if (direction > 0)
//         if (size_table_index >= max_size_table_index)
//             return;
//         else
//             size_table_index++;
//     else if (size_table_index <= 0)
//         return;
//     else
//         size_table_index--;

//     auto new_buckets = std::make_unique<std::list<Pair<key_t, value_t>>[]>(size_table[size_table_index]);
//     for (auto &i : buckets)
//     {
//         std::cout<<i->size();

//     }
// }

template <typename key_t, typename value_t>
size_t HashMap<key_t, value_t>::TotalBuckets()
{
    return size_table[size_table_index];
}

template <typename key_t, typename value_t>
size_t HashMap<key_t, value_t>::Size()
{
    return occpied_buckets;
}

template <typename key_t, typename value_t>
void HashMap<key_t, value_t>::Clear()
{
    size_table_index = 0;
    occpied_buckets = 0;
    buckets = std::vector<std::list<Pair<key_t, value_t>>>(size_table[size_table_index]);
}

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::Iterator HashMap<key_t, value_t>::begin()
{
    return begin_iterator;
}

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::Iterator HashMap<key_t, value_t>::end()
{
    
    return Iterator(nullptr, size_table[size_table_index], 0);
}

// Iterator
template <typename key_t, typename value_t>
HashMap<key_t, value_t>::Iterator &
HashMap<key_t, value_t>::Iterator::operator++()
{
    if(bucket = size_table[size_table_index]){
        return *this;
    }
    if(pos == buckets[correct_index(m_ptr->key)].size()-1){
        while(bucket!=size_table[size_table_index] && buckets[bucket].size()==0){
            bucket++;
        }
    }
    else{
        pos++;
        m_ptr = &
    }
    
    m_ptr->key;
    m_ptr++;
    return *this;
}

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::Iterator
HashMap<key_t, value_t>::Iterator::operator++(int)
{
    Iterator tmp (*this);
    ++(*this);
    return tmp;
}

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::Iterator::pointer
HashMap<key_t, value_t>::Iterator::operator->()
{
    return m_ptr;
}

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::Iterator::reference
HashMap<key_t, value_t>::Iterator::operator*() const
{
    return *m_ptr;
}

template <typename key_t, typename value_t>
bool
HashMap<key_t, value_t>::Iterator::operator==(const Iterator & other)
{
    return m_ptr == other.m_ptr;
}

template <typename key_t, typename value_t>
bool
HashMap<key_t, value_t>::Iterator::operator!=(const Iterator & other) 
{
    return m_ptr != other.m_ptr;
}
