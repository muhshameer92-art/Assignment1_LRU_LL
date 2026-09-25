#pragma once
//LinkedList Implementation - Generic
#include<iostream>
using namespace std;
template<class T>
class list {
    class node { // a node is a running program
    public:
        node* next;
        T val;
        node(T d = T(), node* n = NULL) {
            val = d;
            next = n;
        }
    };
    node* head;
public:
    list() {
        head = NULL;
    }
    ~list() {
        if (head) {
            node* curr = head->next;
            while (curr) {
                delete head;
                head = curr;
                curr = curr->next;
            }delete head;
        }
    }
    void push_front(T d) {
        node* newNode = new node(d);
        if (head == NULL) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }
    void push_back(T d) {
        node* newNode = new node(d, NULL);
        if (head == NULL) {
            head = newNode;
            return;
        }
        node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    void pop_front() {
        if (head == NULL)
            return;
        node* del = head;
        head = head->next;
        delete del;
    }
    void pop_back() {
        if (head == NULL) {
            return;
        }
        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }
        node* curr = head;
        while (curr->next->next) {
            curr = curr->next;
        }
        node* del = curr->next;
        curr->next = del->next;
        delete del;
    }
    bool move_MRU(T d) {
        if (!head)
            return false;
        if (head->val == d)
            return true;
        node* prev = head;

        while (prev->next && prev->next->val != d) {
            prev = prev->next;
        }
        if (prev->next == NULL) {
            return false;
        }

        node* page = prev->next;
        prev->next = page->next;
        page->next = head;
        head = page;

        return true;
    }
    bool remove(T d) {
        if (!head)
            return false;
        if (head->val == d)
        {
            pop_front();
            return true;
        }
        node* curr = head;
        while (curr) {

        }
    }
    void show_List() const {
        node* curr = head;
        while (curr) {
            cout << "(" << curr->val << ")->";
            curr = curr->next;
        }cout << "NULL" << endl;
    }
    class iterator {
        node* current;
    public:
        iterator(node* c = NULL) {
            current = c;
        }
        iterator(const iterator& iter) {
            current = iter.current;
        }
        T operator *() {
            if (current != NULL)
                return current->val;
        }
        iterator operator ++() {
            current = current->next;
            return *this;
        }
        iterator operator ++(int) {
            iterator it(current);
            current = current->next;
            return it;
        }
        bool operator == (iterator it) {
            return current == it.current;
        }
        bool operator != (iterator it) {
            return current != it.current;
        }
    };
    iterator begin() {
        return head;
    }
    iterator end() {
        return NULL;
    }
};