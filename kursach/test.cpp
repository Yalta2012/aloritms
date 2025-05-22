#include <iostream>
#include <fstream>
#include "hashmap.h"
#include <unordered_map>
#include <hashtable.h>
using namespace std;
int main(){
    HashMap<string, int>a;
    a.Put("abc",1);
    string s("abc");
    unordered_map<string, int> map;
    cout<<map.contains(s)<<endl;
    cout<< map[s]<<endl;
    cout<<map.contains(s)<<endl;
    
}