#include "hashmap.h"
#include <random>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(NULL));
    hash_map<string, int> map;
    for (int s = 1'000'000; s <= 1'000'000; s *= 10)
    {
        ofstream f("out" + to_string(s) + ".txt");

        while (map.size() < s)
        {
            auto x = random() % 1'000'000;
            map.put(to_string(x), x);
        }

        for (int i = 0; i < 1'300'000; i++)
        {
            bool x;
            auto begin = steady_clock::now();
            x = map.contains(to_string(i));
            auto end = steady_clock::now();
            f<<x<<"|"<<duration_cast<nanoseconds>(end-begin).count()<<endl;
        }

        f.close();
    }
}