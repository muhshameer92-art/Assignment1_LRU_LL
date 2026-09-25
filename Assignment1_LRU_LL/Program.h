#pragma once
//program
#include "List.h"
#include<iostream>
using namespace std;
class Program {
public:
    list<int> PageList;
    int programID;
    double memoryUsage;

    Program(int id = -1, int mem = 0) {
        programID = id;
        memoryUsage = mem;
    }
    friend ostream& operator << (ostream& os, const Program& p) {
        os << "\n+++Program+++\nProgramID : " << p.programID << "\nMemory Usage: " << p.memoryUsage 
            << endl;
        p.PageList.show_List();
        return os;
    }
    bool operator == (const Program& p) const {
        return p.programID == programID;
    }
    bool operator != (const Program& p) const {
        return p.programID != programID;
    }

};