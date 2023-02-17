#pragma once
#include <iostream>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node<T>* next;

	Node<T>() {
		this->data = 0;
		this->next = NULL;
	}

	Node<T>(Node<T>* next, int data) {
		this->data = data;
		this->next = next;

	}

	T dataGetter() {
		return data;
	}

	void dataSetter(T data) {
		this->data = data;
	}

	Node<T>* nextGetter() {
		return next;
	}

	void nextSetter(Node<T>* next) {
		this->next = next;
	}
};

//template<class T>
//Node<T> ::Node() {
//	this->data = 0;
//	this->next = NULL;
//}







template<class T>
class LL {
public:
	Node<T>* head;

	LL() {
		head = NULL;
	}

	void INSERT_DATA(T data) {
		Node<T>* current = new Node<T>(NULL, data);

		if (head == NULL) {
			head = current;
		}

		else {
			Node<T>* charval = head;
			while (charval->next != NULL) {

				charval = charval->next;
			}
			charval->next = current;
		}
	}

	void insertAtHead(T data) {
		Node<T>* current = new Node<T>(head, data);
		head = current;
	}

	bool isEmpty() {
		if (head == NULL) {
			return true;
		}
		return false;
	}

	T search(T data) {
		int counter = 0;

		Node<T>* charval = head;

		while (charval) {
			if (charval->data == data) {
				return counter;
			}
			counter++;
			charval = charval->next;
		}

		return -1;
	}

	bool update(T replace, T add) {
		Node<T>* charval = head;

		while (charval) {
			if (charval->data == replace) {
				charval->data = add;
				return true;
			}
			charval = charval->next;
		}

		return false;
	}

	void InsertAtIndex(T data, T index) {
		Node<T>* charval = head;
		Node<T>* current = new Node<T>(NULL, data);
		int counter = 0;

		while (charval) {
			counter++;
			if (counter == index) {
				current->next = charval->next;
				charval->next = current;
				current->data = data;
			}
			charval = charval->next;
		}
	}

	void remove(T data) {
		Node<T>* charval = head;
		Node<T>* prev = NULL;

		while (charval) {
			if (charval->data == data) {
				prev->next = charval->next;
				delete charval;
				return;

			}
			prev = charval;
			charval = charval->next;
		}
	}

	void print() {
		Node<T>* charval = head;

		while (charval) {
			cout << charval->data << " ";
			charval = charval->next;
		}
	}

	void mergeLists(LL obj) {
		Node<T>* temp1 = head;
		Node<T>* temp2 = obj.head;

		while (temp1) {
			Node<T>* bridge = new Node<T>();
			bridge->data = temp2->data;
			bridge->next = temp1->next;
			temp1->next = bridge;

			temp1 = temp1->next->next;
			temp2 = temp2->next;
		}

	}


};
