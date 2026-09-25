#pragma once
//Memory Manager
#include "List.h"
#include "Program.h"
#include <iostream>
class MemoryManager {
public:
    list<Program>ProgramList;

    bool startProgram(int ID = -1,int memSize = 0) {
        for (list<Program>::iterator iter = ProgramList.begin();
            iter != ProgramList.end();
            ++iter) {
            if (*iter == Program(ID, memSize))
                return false;
        }
        ProgramList.push_back(Program(ID,memSize));
        return true;
    }
    bool accessPage(int ID, int pgID) {
        list<Program>::iterator iter = ProgramList.begin();
        list<int>::iterator pageIterator = NULL;
        for (;iter != ProgramList.end();
            ++iter) {
            if (*iter == Program(ID)) {
                //for (pageIterator =  (*iter).PageList.begin();
                //    pageIterator != (*iter).PageList.end();
                //    ++pageIterator) {
                //    if (*pageIterator == pgID)
                //    {
                //        (*iter).PageList.move_MRU(pgID);
                //        return true;
                //    }
                //}
                //(*iter).PageList.push_front(pgID);
                //return true;
                if((*iter).PageList.move_MRU(pgID))
                    return true;
                else
                {
                    (*iter).PageList.push_front(pgID);
                    return true;
                }
            }
        }
        return false;
    }
    bool endProgram(int ID) {
        for (list<Program>::iterator iter = ProgramList.begin();
            iter != ProgramList.end();
            ++iter) {
            if ((*iter).programID == ID)
            {
                ProgramList.remove(*iter);
                return true;
            }
        }
        return false;
    }
    void printState() {
        for (list<Program>::iterator iter = ProgramList.begin();
            iter != ProgramList.end(); ++iter) {
            cout << *iter << "+++++++++++++++++\n\t|\n\tV" << endl;
        }cout << "\tNULL\n***************\n";
    }
};