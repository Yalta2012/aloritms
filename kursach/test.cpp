#include <iostream>
#include <fstream>
#include "hashmap.h"
#include <unordered_map>
#include <hashtable.h>
using namespace std;
int main()
{
    // HashMap<string, int> a;
    // cout<<"C:"<<a.Contains("abc")<<endl;
    // a.Put("abc",123);
    // cout<<"C:"<<a.Contains("abc")<<endl;

    // a.Print();

    HashMap<int, int> a;
    cout << "C:" << a.Contains(0) << endl;
    a.Put(0, 123);
    a.Put(5, 123);

    cout << "C:" << a.Contains(0) << endl;

    a.Print();
}