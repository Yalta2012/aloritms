#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <map>
#include <unordered_map>
#include <functional>

using namespace std;

struct Date
{
    int Year;
    int Month;
    Date(int a, int b)
    {
        Year = a;
        Month = b;
    }
    Date()
    {
        Month = 0;
        Year = 0;
    }
    bool operator==(const Date &d) const
    {
        return Year == d.Year && Month == d.Month;
    }
};
namespace std
{
    template <>
    struct hash<Date>
    {
        std::size_t operator()(const Date &obj) const
        {
            return obj.Year * 12 + obj.Month;
        }
    };

}

void DateGen(Date *array, int n)
{
    int i, j, c;
    c = 0;
    for (i = 1972; i <= 1992 && c < n; i++)
        for (j = 1; j <= 12 && c < n; j++)
        {
            array[c] = Date{i, j};
            c++;
        }
}

void HashMapping(int *map, Date *dates, int m, int k)
{
    hash<Date> haser;
    for (int i = 0; i < k; i++)
        map[haser(dates[i]) % m]++;
}

double xiFun(int *map, int n, int m)
{
    double result = 0;
    for (int i = 0; i < m; i++)
        result += ((double)map[i] - (double)n / m) * ((double)map[i] - (double)n / m);
    result *= (double)m / n;
    return result;
}

int main()
{
    ofstream file1("m1.txt");
    ofstream file2("m2.txt");

    int k = 200;
    Date dates[k];
    DateGen(dates, k);

    int m1 = 64, m2 = 67;
    int map1[m1] = {0}, map2[m2] = {0};

    HashMapping(map1, dates, m1, k);
    HashMapping(map2, dates, m2, k);

    for (auto i : map1)
        file1 << i << endl;

    for (auto i : map2)
        file2 << i << endl;

    file1 << "xi:" << xiFun(map1, k, m1);
    file2 << "xi:" << xiFun(map2, k, m2);

    int c = 0;
    for (auto i : map1)
    {
        c += i;
    }
    cout << "m1:" << c << "/" << k << endl;

    c = 0;
    for (auto i : map1)
    {
        c += i;
    }
    cout << "m2:" << c << "/" << k << endl;
    file1.close();
    file2.close();
}
