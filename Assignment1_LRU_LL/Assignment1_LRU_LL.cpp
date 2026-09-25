#include <iostream>
#include "List.h"
#include "Program.h"
#include "MemoryManager.h"
using namespace std;
int main()
{
    list<int>l;
    list<int>::iterator iter;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    for (iter = l.begin(); iter != l.end(); ++iter) {
        cout << *iter << endl;  
    }
    return 0;
}
