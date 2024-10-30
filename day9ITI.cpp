#include <iostream>
#include <vector>
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
            cout << "The Queue was empty, added: " << s->name << endl;
            return;
        }

        if (indx == 0) {
            s->next = first;
            first = s;
            cout << "Inserted " << s->name << " at index 0" << endl;
            return;
        }

        student* current = first;
        for (int i = 0; i < indx - 1 && current->next != NULL; i++) {
            current = current->next;
        }

        s->next = current->next;
        current->next = s;
        cout << "Inserted " << s->name << " at index " <<indx  << endl;
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
        student* s = first;
        first = first->next;
        s->next = NULL; 
        return s;
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

    void printTreeLikeStructure(studenttree* node, int space = 0, int height = 10) {
        if (node == NULL) {
            return;
        }

        space += height;

        printTreeLikeStructure(node->right, space);

        cout << endl;
        for (int i = height; i < space; i++) {
            cout << " ";
        }
        cout << node->id << " (" << node->name << ")" << endl;

        printTreeLikeStructure(node->left, space);
    }

    void printTree() {
        if (root == NULL) {
            cout << "The tree is empty." << endl;
        }
        else {
            printTreeLikeStructure(root);
        }
    }

    void remove(studenttree* st) {
        studenttree* current = root;
        studenttree* parent = NULL;
        bool isLeftChild = false;

        while (current != NULL && current->id != st->id) {
            parent = current;
            if (st->id < current->id) {
                current = current->left;
                isLeftChild = true;
            }
            else {
                current = current->right;
                isLeftChild = false;
            }
        }

        if (current == NULL) {
            cout << "Node with ID " << st->id << " not found." << endl;
            return; 
        }

        if (current->left == NULL && current->right == NULL) {
            if (current == root) {
                root = NULL; 
            }
            else if (isLeftChild) {
                parent->left = NULL; 
            }
            else {
                parent->right = NULL; 
            }
        }
        else if (current->left == NULL || current->right == NULL) {
            studenttree* child = (current->left != NULL) ? current->left : current->right;

            if (current == root) {
                root = child; 
            }
            else if (isLeftChild) {
                parent->left = child; 
            }
            else {
                parent->right = child;
            }
        }
        else {
            studenttree* s = current->right;
            studenttree* sP = current;

            while (s->left != NULL) {
                sP = s;
                s = s->left;
            }

            current->id = s->id; 
            current->name = s->name; 

            if (sP->left == s) {
                sP->left = s->right; 
            }
            else {
                sP->right = s->right; 
            }
            current = s; 
        }

        //delete current; 
    }
};

int main() {
    int i =-1;
    while (i != 0) {
        cout << "Please Enter 1 if you need to see queue \nPlease Enter 2 if you need to see BST\nPlease Enter 0 if you need to Exit" << endl;
        cin >> i;
        if (i == 1) {
            student* s1 = new student{ "merna", 1, NULL };
            student* s2 = new student{ "nabila", 2, NULL };
            student* s3 = new student{ "nour", 3, NULL };
            student* s4 = new student{ "nadeen", 4, NULL };
            student* s5 = new student{ "Reem", 5, NULL };

            queue q;
            q.enqueue(s1);
            q.enqueue(s2);
            q.enqueue(s3);
            q.enqueueWithIndex(s4, 1);
            q.enqueueWithIndex(s5, 0);

            int result = q.findwithid(2);
            if (result == -1) {
                cout << "Not found" << endl;
            }
            else {
                cout << "Student with ID 2 found at index: " << result << endl;
            }

            for (int i = 0; i < 5; i++) {
                student* dequeued = q.dequeue();
                if (dequeued != NULL) {
                    cout << dequeued->name << endl;
                    delete dequeued;
                }
            }
        }
        else if (i == 2) {
            studenttree st1, st2, st3, st4, st5;
            st1.id = 10; st1.name = "mohamed";
            st2.id = 2;  st2.name = "ahmed";
            st3.id = 30; st3.name = "osama";
            st4.id = 6;  st4.name = "hasan";
            st5.id = 100;  st5.name = "yossef";

            binarysearchtree bst;
            bst.insert(&st1);
            bst.insert(&st2);
            bst.insert(&st3);
            bst.insert(&st4);
            bst.insert(&st5);
            /*studenttree* st1 = new studenttree{"mohamed", 10, NULL, NULL};
            studenttree* st2 = new studenttree{ "ahmed", 2, NULL, NULL };
            studenttree* st3 = new studenttree{ "osama", 30, NULL, NULL };
            studenttree* st4 = new studenttree{ "hasan", 6, NULL, NULL };
            studenttree* st5 = new studenttree{ "yossef", 100, NULL, NULL };

            binarysearchtree bst;
            bst.insert(st1);
            bst.insert(st2);
            bst.insert(st3);
            bst.insert(st4);
            bst.insert(st5);*/
            bst.printTree();
            cout << "-----------------------------------------" << endl;
            bst.remove(&st3);
            bst.printTree();
            cout << "-----------------------------------------" << endl;
            bst.remove(&st4);
            bst.printTree();
            cout << "-----------------------------------------" << endl;
            bst.remove(&st1);
            bst.printTree();
            studenttree* foundStudent = bst.findbyId(100);
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
        }
        if (i == 0)break;
    }

    
    return 0;
}
