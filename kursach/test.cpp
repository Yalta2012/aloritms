#include <iostream>
#include <fstream>
#include "hashmap.h"
#include <unordered_map>
#include <hashtable.h>
#include <random>
#include <chrono>
using namespace std;
int main()
{
    ofstream f("out.txt");
    hash_map<string, int> a;
    auto end = chrono::steady_clock::now();
    auto begin = chrono::steady_clock::now();

    for (int i = 0; i < 10000; i++)
    {
        a.put(to_string(i), i);
    }

    cout << a.total_buckets() << endl;
    cout << a.size() << endl;

    hash_map<string,int> b;
    b=a;

    b["9999"] = -123;
    for (auto i : a)
    {
        f << i.key() << "|" << i.value() << endl;
    }
}
