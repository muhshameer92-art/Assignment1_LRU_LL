#include <iostream>
using namespace std;
//LinkedList Implementation - Generic
template<class T>
class list {
    class node { // a node is a running program
    public:
        node* next;
        T val;
        node(T d, node* n = NULL) {
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
            }
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
    void show_List() const {
        node* curr = head;
        while (curr) {
            cout << "(" << curr->val << ")->";
            curr = curr->next;
        }cout << "NULL"<<endl;
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
