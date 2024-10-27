#include <iostream>
#include <vector>
using namespace std;

struct employee {
    string name;
    int id;
    employee* next = NULL;
    employee* prev = NULL;

    void printEmp() {
        cout << "Name : " << name << " Id : " << id << endl;
    }
};

struct doublelinkedList {
    employee* first;
    employee* last;
    int size = 0;

    doublelinkedList() {
        first = NULL;
        last = NULL;
    }

    void push_back(employee* emp) {
        if (first == NULL) {
            first = emp;
            last = emp;
            emp->next = NULL;
            emp->prev = NULL;
        }
        else {
            emp->prev = last;
            last->next = emp;
            emp->next = NULL;
            last = emp;
        }
        size++;
    }

    void delet(employee* emp) {
        if (emp == NULL) return;

        if (emp == first) {
            first = emp->next;
            if (first) first->prev = NULL;
            if (emp == last) last = NULL;
        }
        else if (emp == last) {
            last = emp->prev;
            if (last) last->next = NULL;
        }
        else {
            emp->prev->next = emp->next;
            emp->next->prev = emp->prev;
        }
        size--;
        delete emp;
    }

    employee* FindById(int id) {
        employee* current = first;
        while (current != NULL) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void Repalce(employee* emp, int index) {
        if (index < 0 || first == NULL) return;

        employee* current = first;
        int i = 0;

        while (current != NULL && i < index) {
            current = current->next;
            i++;
        }

        if (current != NULL && i == index) {
            emp->next = current->next;
            emp->prev = current->prev;

            if (current->prev != NULL) {
                current->prev->next = emp;
            }
            else {
                first = emp;
            }

            if (current->next != NULL) {
                current->next->prev = emp;
            }
            else {
                last = emp;
            }

            delete current;
        }
    }

    doublelinkedList* mergeSort() {
        if (!this || !this->first || this->first == this->last) {
            return new doublelinkedList(*this);
        }


        int mid = size / 2;
        doublelinkedList* list1 = new doublelinkedList();
        doublelinkedList* list2 = new doublelinkedList();

        employee* current = this->first;
        for (int i = 0; i < size; i++) {
            if (i < mid) {
                list1->push_back(new employee(*current));
            }
            else {
                list2->push_back(new employee(*current));
            }
            current = current->next;
        }

        list1 = list1->mergeSort();
        list2 = list2->mergeSort();

        doublelinkedList* sortedList = new doublelinkedList();
        employee* current1 = list1->first;
        employee* current2 = list2->first;


        while (current1 != NULL && current2 != NULL) {
            if (current1->id <= current2->id) {
                sortedList->push_back(new employee(*current1));
                current1 = current1->next;
            }
            else {
                sortedList->push_back(new employee(*current2));
                current2 = current2->next;
            }
        }

        while (current1 != NULL) {
            sortedList->push_back(new employee(*current1));
            current1 = current1->next;
        }
        while (current2 != NULL) {
            sortedList->push_back(new employee(*current2));
            current2 = current2->next;
        }

        return sortedList;
    }

    void print() {
        employee* current = first;
        while (current != NULL) {
            current->printEmp();
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    employee* emp1 = new employee{ "Merna", 1, NULL, NULL };
    employee* emp2 = new employee{ "Nadeen", 2, NULL, NULL };
    employee* emp3 = new employee{ "Reem", 3, NULL, NULL };
    employee* emp4 = new employee{ "Heba", 4, NULL, NULL };
    employee* emp5 = new employee{ "Nabila", 5, NULL, NULL };
    employee* emp6 = new employee{ "Nour", 6, NULL, NULL };
    doublelinkedList list;
    list.push_back(emp5);
    list.push_back(emp3);
    list.push_back(emp6);
    list.push_back(emp2);
    list.push_back(emp1);
    list.print();

    list.delet(emp3);
    list.print();

    list.FindById(2)->printEmp();
    cout << endl;
    list.Repalce(emp4, 0);
    list.print();

    doublelinkedList* sortedList = list.mergeSort();
    cout << "sorted Linked List : " << endl;
    sortedList->print();
    return 0;
}
