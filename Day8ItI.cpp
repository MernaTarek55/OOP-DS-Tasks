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

		int size = 0;
		employee* current = this->first;
		while (current != NULL) {
			size++;
			current = current->next;
		}

		if (size == 2) {
			if (this->first->id > this->last->id) {
				employee* temp = this->first;
				this->first = this->last;
				this->last = temp;
				this->first->next = this->last;
				this->first->prev = NULL;
				this->last->prev = this->first;
				this->last->next = NULL;
			}
			return new doublelinkedList(*this); 
		}

		doublelinkedList* list1 = NULL;
		doublelinkedList* list2 = NULL;

		current = this->first;
		int mid = size / 2;
		for (int i = 0; i < size; i++) {
			if (i < mid) {
				list1->push_back(current);
			}
			else {
				list2->push_back(current);
			}
			current = current->next;
		}

		if (list1->last) list1->last->next = NULL;
		if (list2->first) list2->first->prev = NULL;

		list1 = list1->mergeSort();  
		list2 = list2->mergeSort();  

		doublelinkedList* sortedList = NULL;
		employee* current1 = list1->first;
		employee* current2 = list2->first;

		while (current1 != NULL && current2 != NULL) {
			if (current1->id <= current2->id) {
				sortedList->push_back(current1);
				current1 = current1->next;
			}
			else {
				sortedList->push_back(current2);
				current2 = current2->next;
			}
		}

		while (current1 != NULL) {
			sortedList->push_back(current1);
			current1 = current1->next;
		}
		while (current2 != NULL) {
			sortedList->push_back(current2);
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
	doublelinkedList list;
	list.push_back(emp3);
	list.push_back(emp2);
	list.push_back(emp1);
	list.push_back(emp5);
	list.print();

	list.delet(emp3);
	list.print();

	list.FindById(2)->printEmp();
	cout << endl;
	list.Repalce(emp4, 0);
	list.print();

	doublelinkedList* sortedList = list.mergeSort();
	cout << "sorted" << endl;
	sortedList->print();
	return 0;
}