#include <iostream>
#include "List.h"
#include "Program.h"
#include "MemoryManager.h"
using namespace std;
int main()
{
    MemoryManager mm;

    // start a few programs, one with a memory footprint that's kind of a lot
    mm.startProgram(101, 64);
    mm.startProgram(102, 128);
    mm.startProgram(103, 32);

    // shouldn't be able to start 101 twice
    if (!mm.startProgram(101, 64))
        cout << "#101 is already running, good, that was supposed to fail\n";

    // give 101 some pages to work with
    mm.accessPage(101, 5);
    mm.accessPage(101, 12);
    mm.accessPage(101, 3);
    mm.accessPage(101, 8);

    // touch 12 again so it jumps back to the front (MRU)
    mm.accessPage(101, 12);

    // 102 gets a couple pages too
    mm.accessPage(102, 1);
    mm.accessPage(102, 2);
    mm.accessPage(102, 3);

    // this one should just fail quietly, no program 999
    mm.accessPage(999, 1);

    cout << "\n#state before killing anything:\n";
    mm.printState();

    // now kill 102 and see if it's actually gone
    mm.endProgram(102);
    mm.endProgram(102); // and again, just to make sure it doesn't blow up

    cout << "\n#state after removing 102:\n";
    mm.printState();
    return 0;
}
