#include "hashmap.h"
using namespace curs;

// Node
template <typename key_t, typename value_t>
Pair<key_t, value_t>::Pair(const key_t &key, const value_t &value, PairType type) : key(key), value(value), type(type) {}

// HashMap
template <typename key_t, typename value_t>
size_t
HashMap<key_t, value_t>::Size()
{
    return size_table[size_table_index];
}

template <typename key_t, typename value_t>
HashMap<key_t, value_t>::HashMap() : size_table_index(0), element_couner(0)
{
    element_list = std::list<Pair<key_t, value_t>>();
    iterators = std::vector<decltype(element_list.begin())>(Size() + 1);

    size_t i;
    for (i = 0; i < Size(); i++)
    {
        element_list.push_back(Pair(key_t(), value_t(), PairType::BUCKET_BEGIN));
    }
    element_list.push_back(Pair(key_t(), value_t(), PairType::LIST_END));
    i = 0;
    for (auto iter = element_list.begin(); iter != element_list.end(); i++, iter++)
    {
        std::cout << i << std::endl;
        iterators[i] = iter;
    }
}

template <typename key_t, typename value_t>
size_t
HashMap<key_t, value_t>::hash(const key_t &key, size_t size)
{
    auto hash = std::hash<key_t>();
    return hash(key) % size;
}

template <typename key_t, typename value_t>
void HashMap<key_t, value_t>::Print()
{
    size_t c = 0;
    for (auto i : element_list)
    {
        std::cout << c << ") ";
        switch (i.type)
        {
        case PairType::LIST_END:
            std::cout << "$END OF LIST";
            break;
        case PairType::BUCKET_BEGIN:
            std::cout << "$BEGINING OF BUCKET";
            break;
        case PairType::REGULAR:
            std::cout << i.key << " " << i.value;
            break;
        default:
            std::cout << "$UNKNOWN";
            break;
        }
        std::cout << std::endl;
        if (i.type == PairType::LIST_END)
            break;
        c++;
    }
}

template <typename key_t, typename value_t>
bool HashMap<key_t, value_t>::Contains(const key_t &key)
{
    auto i = iterators[hash(key, Size())];
    for (i++; i->type == PairType::REGULAR; i++)
        if (i->key == key)
            return true;
    return false;
}

template <typename key_t, typename value_t>
void HashMap<key_t, value_t>::Put(const key_t &key, const value_t &val)
{
    auto i = iterators[hash(key, Size())];

    for (i++; i->type == PairType::REGULAR; i++)
        if (i->key == key)
        {
            i->value = val;
            return;
        }
    element_list.insert(i, Pair(key, val, PairType::REGULAR));
}

////////////////////////////////////////////////////
// // HashMap

// template <typename key_t, typename value_t>
// void HashMap<key_t, value_t>::Put(const key_t &key, const value_t &val)
// {
//     auto hash = std::hash<key_t>();
//     auto index = correct_index(key);
//     for (auto &i : buckets[index])
//         if (i.key == key)
//         {
//             i.value = val;
//             return;
//         }
//     buckets[index].push_back(Pair(key, val));
//     occpied_buckets++;
//     if (begin_iterator.m_ptr==nullptr || index < hash(begin_iterator->key))
//     {
//         begin_iterator = Iterator(&(buckets[index].back()), index,0);
//     }
// }

// template <typename key_t, typename value_t>
// void HashMap<key_t, value_t>::Remove(const key_t &key)
// {
//     for (auto i = buckets[correct_index(key)].begin(); i != buckets[correct_index(key)].end(); i++)
//         if (i->key == key)
//         {
//             buckets[correct_index(key)].erase(i);
//             occpied_buckets--;
//             break;
//         }
// }

// template <typename key_t, typename value_t>
// value_t &HashMap<key_t, value_t>::Get(const key_t &key)
// {
//     for (auto i = buckets[correct_index(key)].begin(); i != buckets[correct_index(key)].end(); i++)
//         if (i->key == key)
//         {
//             return i->value;
//         }
//     Put(key, value_t());
//     return buckets[correct_index(key)].back().value;
// }

// template <typename key_t, typename value_t>
// value_t &HashMap<key_t, value_t>::operator[](const key_t &key)
// {
//     return Get(key);
// }

// // template <typename key_t, typename value_t>
// // void HashMap<key_t, value_t>::Resize(char direction)
// // {
// //     if (direction > 0)
// //         if (size_table_index >= max_size_table_index)
// //             return;
// //         else
// //             size_table_index++;
// //     else if (size_table_index <= 0)
// //         return;
// //     else
// //         size_table_index--;

// //     auto new_buckets = std::make_unique<std::list<Pair<key_t, value_t>>[]>(size_table[size_table_index]);
// //     for (auto &i : buckets)
// //     {
// //         std::cout<<i->size();

// //     }
// // }

// template <typename key_t, typename value_t>
// size_t HashMap<key_t, value_t>::TotalBuckets()
// {
//     return size_table[size_table_index];
// }

// template <typename key_t, typename value_t>
// size_t HashMap<key_t, value_t>::Size()
// {
//     return occpied_buckets;
// }

// template <typename key_t, typename value_t>
// void HashMap<key_t, value_t>::Clear()
// {
//     size_table_index = 0;
//     occpied_buckets = 0;
//     buckets = std::vector<std::list<Pair<key_t, value_t>>>(size_table[size_table_index]);
// }

// template <typename key_t, typename value_t>
// HashMap<key_t, value_t>::Iterator HashMap<key_t, value_t>::begin()
// {
//     return begin_iterator;
// }

// template <typename key_t, typename value_t>
// HashMap<key_t, value_t>::Iterator HashMap<key_t, value_t>::end()
// {

//     return Iterator(nullptr, size_table[size_table_index], 0);
// }

// // Iterator
// template <typename key_t, typename value_t>
// HashMap<key_t, value_t>::Iterator &
// HashMap<key_t, value_t>::Iterator::operator++()
// {
//     if(bucket = size_table[size_table_index]){
//         return *this;
//     }
//     if(pos == buckets[correct_index(m_ptr->key)].size()-1){
//         while(bucket!=size_table[size_table_index] && buckets[bucket].size()==0){
//             bucket++;
//         }
//     }
//     else{
//         pos++;
//         m_ptr = &
//     }

//     m_ptr->key;
//     m_ptr++;
//     return *this;
// }

// template <typename key_t, typename value_t>
// HashMap<key_t, value_t>::Iterator
// HashMap<key_t, value_t>::Iterator::operator++(int)
// {
//     Iterator tmp (*this);
//     ++(*this);
//     return tmp;
// }

// template <typename key_t, typename value_t>
// HashMap<key_t, value_t>::Iterator::pointer
// HashMap<key_t, value_t>::Iterator::operator->()
// {
//     return m_ptr;
// }

// template <typename key_t, typename value_t>
// HashMap<key_t, value_t>::Iterator::reference
// HashMap<key_t, value_t>::Iterator::operator*() const
// {
//     return *m_ptr;
// }

// template <typename key_t, typename value_t>
// bool
// HashMap<key_t, value_t>::Iterator::operator==(const Iterator & other)
// {
//     return m_ptr == other.m_ptr;
// }

// template <typename key_t, typename value_t>
// bool
// HashMap<key_t, value_t>::Iterator::operator!=(const Iterator & other)
// {
//     return m_ptr != other.m_ptr;
// }
