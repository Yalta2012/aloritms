#include "redblacktree.h"
#include <iostream>

using namespace std;


int main(){
    RBTree<int>*a = new RBTree<int>();
    a->Insert(6);
    a->Insert(7);
    a->Insert(5);
    a->Insert(3);
    a->Insert(1);
    a->Insert(4);
    a->Insert(2);
    a->Print();
    delete a;
}