#include <iostream>
using namespace std;

struct student {
    string name;
    int id;
    student* next;
};

struct queue {
    student* first = NULL;
    student* last = NULL;

    void enqueue(student* s) {
        if (first == NULL) {
            first = s;
            last = s;
            s->next = NULL;
            return;
        }
        last->next = s;
        last = s;
        s->next = NULL;
    }

    void enqueueWithIndex(student* s, int indx) {
        if (first == NULL) {
            first = s;
            last = s;
            s->next = NULL;
            cout << "The Queue was empty" << endl;
            return;
        }

        student* current = first;
        for (int i = 0; i < indx - 1 && current->next != NULL; i++) {
            current = current->next;
        }

        s->next = current->next;
        current->next = s;
        if (current == last) {
            last = s;
        }
    }

    int findwithid(int id) {
        student* current = first;
        int indx = 0;
        while (current != NULL) {
            if (current->id == id) {
                return indx;
            }
            current = current->next;
            indx++;
        }
        return -1;
    }

    student* dequeue() {
        if (first == NULL) {
            cout << "The Queue is Empty" << endl;
            return NULL;
        }
        else {
            student* s = first;
            first = first->next;
            return s;
        }
    }
};

struct studenttree {
    string name;
    int id;
    studenttree* left = NULL;
    studenttree* right = NULL;
    
};

struct binarysearchtree {
    studenttree* root = NULL;

    void insert(studenttree* s) {
        if (root == NULL) {
            root = s;
            return;
        }
        studenttree* current = root;
        studenttree* parent = NULL;

        while (current != NULL) {
            parent = current;
            if (s->id < current->id) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        if (s->id < parent->id) {
            parent->left = s;
        }
        else {
            parent->right = s;
        }
    }

    studenttree* findbyId(int id) {
        studenttree* current = root;
        while (current != NULL) {
            if (id < current->id) {
                current = current->left;
            }
            else if (id > current->id) {
                current = current->right;
            }
            else {
                return current;
            }
        }
        return NULL;
    }
};

int main() {
    student s1, s2, s3, s4;
    s1.name = "merna";
    s1.id = 1;
    s2.name = "nabila";
    s2.id = 2;
    s3.name = "nour";
    s3.id = 3;
    s4.name = "nadeen";
    s4.id = 4;

    queue q;
    q.enqueue(&s1);
    q.enqueue(&s2);
    q.enqueue(&s3);
    q.enqueueWithIndex(&s4, 1);

    int result = q.findwithid(2);
    if (result == -1) {
        cout << "Not found" << endl;
    }
    else {
        cout << "Student with ID 2 found at index: " << result << endl;
    }
    for (int i = 0; i < 4; i++) {
        student* dequeued = q.dequeue();
        if (dequeued != NULL) {
            cout << dequeued->name << endl;
        }
    }

    studenttree st1, st2, st3, st4;
    st1.id = 10; st1.name = "mohamed";
    st2.id = 2;  st2.name = "ahmed";
    st3.id = 30; st3.name = "osama";
    st4.id = 6;  st4.name = "hasan";

    binarysearchtree bst;
    bst.insert(&st1);
    bst.insert(&st2);
    bst.insert(&st3);
    bst.insert(&st4);

    studenttree* foundStudent = bst.findbyId(10);
    if (foundStudent == NULL) {
        cout << "Not found" << endl;
    }
    else {
        cout << "Name: " << foundStudent->name << " Id: " << foundStudent->id << endl;
    }

    foundStudent = bst.findbyId(1);
    if (foundStudent == NULL) {
        cout << "Not found" << endl;
    }
    else {
        cout << "Name: " << foundStudent->name << " Id: " << foundStudent->id << endl;
    }

    return 0;
}
