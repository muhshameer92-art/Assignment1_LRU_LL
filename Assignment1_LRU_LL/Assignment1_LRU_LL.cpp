#include <iostream>
#include "List.h"
#include "Program.h"
#include "MemoryManager.h"
using namespace std;
int main()
{
    //list<int>l;
    //list<int>::iterator iter;
    //l.push_back(1);
    //l.push_back(2);
    //l.push_back(3);
    //for (iter = l.begin(); iter != l.end(); ++iter) {
    //    cout << *iter << endl;  
    //}
    MemoryManager mm;

    cout << "==========================================" << endl;
    cout << "     MEMORY MANAGER SIMULATION TEST       " << endl;
    cout << "==========================================" << endl << endl;

    // ----------------------------------------------------
    // TEST 1: Starting Programs & Duplicate ID Handling
    // ----------------------------------------------------
    cout << "[TEST 1] Starting Programs..." << endl;

    if (mm.startProgram(101, 64))
        cout << "  -> Program 101 started successfully." << endl;
    if (mm.startProgram(102, 128))
        cout << "  -> Program 102 started successfully." << endl;
    if (mm.startProgram(103, 32))
        cout << "  -> Program 103 started successfully." << endl;

    // Test Duplicate ID Guard
    if (!mm.startProgram(101, 64)) {
        cout << "  -> Duplicate ID Check Passed: Program 101 rejected." << endl;
    }
    cout << endl;

    // ----------------------------------------------------
    // TEST 2: Page Access (Page Miss vs. Page Hit / MRU)
    // ----------------------------------------------------
    cout << "[TEST 2] Accessing Pages for Program 101..." << endl;

    // Page Misses: Pushing pages into empty memory
    mm.accessPage(101, 5);  // List: [5]
    mm.accessPage(101, 12); // List: [12, 5]
    mm.accessPage(101, 3);  // List: [3, 12, 5]
    mm.accessPage(101, 8);  // List: [8, 3, 12, 5]
    cout << "  -> Added pages 5, 12, 3, 8 to Program 101 (Page Misses)." << endl;

    // Page Hit: Accessing page 12 again should shift it to the front (MRU)
    cout << "  -> Accessing Page 12 again (Page Hit - MRU Shift)..." << endl;
    mm.accessPage(101, 12); // Expected List: [12, 8, 3, 5]

    // Access pages for Program 102
    mm.accessPage(102, 1);
    mm.accessPage(102, 2);
    mm.accessPage(102, 3);

    // Test access on a non-existent program
    if (!mm.accessPage(999, 1)) {
        cout << "  -> Invalid Access Guard Passed: Program 999 not found." << endl;
    }
    cout << endl;

    // ----------------------------------------------------
    // TEST 3: Print Initial Memory State
    // ----------------------------------------------------
    cout << "[TEST 3] Current Memory Manager State:" << endl;
    cout << "------------------------------------------" << endl;
    mm.printState();
    cout << "------------------------------------------" << endl << endl;

    // ----------------------------------------------------
    // TEST 4: Terminating Programs (endProgram)
    // ----------------------------------------------------
    cout << "[TEST 4] Terminating Program 102..." << endl;
    if (mm.endProgram(102)) {
        cout << "  -> Program 102 successfully removed." << endl;
    }

    if (!mm.endProgram(102)) {
        cout << "  -> Removal Guard Passed: Program 102 already deleted." << endl;
    }
    cout << endl;

    // ----------------------------------------------------
    // TEST 5: Final Memory State Verification
    // ----------------------------------------------------
    cout << "[TEST 5] Final Memory State After Cleanup:" << endl;
    cout << "------------------------------------------" << endl;
    mm.printState();
    cout << "------------------------------------------" << endl;
    return 0;
}
