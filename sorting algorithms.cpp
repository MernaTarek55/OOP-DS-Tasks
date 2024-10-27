#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int>* v, int index1, int index2) {
    int temp = (*v)[index1];
    (*v)[index1] = (*v)[index2];
    (*v)[index2] = temp;
}

void PrintVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}
void bubbleSort(vector<int>* v) {
    for (int i = 0; i < v->size(); i++) {
        for (int j = 0; j < v->size() - 1; j++) {
            if ((*v)[j] > (*v)[j + 1])swap(v, j, j + 1);
        }
    }
}
void InsertionSort(vector<int>* v) {
    for (int i = 1; i < v->size(); i++) {
        int key = (*v)[i];
        int j = i - 1;


        while (j >= 0 && (*v)[j] > key) {
            (*v)[j + 1] = (*v)[j];
            j--;
        }
        (*v)[j + 1] = key;
    }
}
vector<int> MargeSort(vector<int>* v) {
    if (v->size() <= 2) {
        if (v->size() == 2) {
            if ((*v)[0] > (*v)[1])swap(v, 0, 1);
            return *v;
        }
        else {
            return *v;
        }
    }
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < v->size(); i++) {
        if (i < v->size() / 2)v1.push_back((*v)[i]);
        else v2.push_back((*v)[i]);
    }
    v1 = MargeSort(&v1);
    v2 = MargeSort(&v2);
    int i1=0, i2=0 ,i=0;
    for (; i < v->size() && i1 < v1.size() && i2 < v2.size(); i++) {
        if (v1[i1] < v2[i2]) {
            (*v)[i] = v1[i1];
            i1++;
        }
        else {
            (*v)[i] = v2[i2];
            i2++;
        }
    }
    if (i1 < v1.size()) {
        for (; i < v->size(); i++) {
            (*v)[i] = v1[i1];
            i1++;
        }
    }
    if (i2 < v2.size()) {
        for (; i < v->size(); i++) {
            (*v)[i] = v2[i2];
            i2++;
        }
    }
    return *v;
}