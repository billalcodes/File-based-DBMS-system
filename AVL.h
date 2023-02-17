
#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template <class T>
class SNode
{
public:

	T data;
	SNode <T>* next;
	string file_n;
	int line_number;


	SNode()
	{
		data = '\0';
		next = NULL;
		data = NULL;
	}

	SNode(string file, int line)
	{
		line_number = line;
		file_n = file;
		next = NULL;

	}

};

template <class T>
class SLinkedList {

public:

	SNode<T>* head;


	SLinkedList()
	{
		head = NULL;
	}

	void insert(string f, int l) {


		SNode<T>* n = new SNode<T>(f, l);
		n->next = NULL;
		if (head == NULL) {
			head = n;
		}
		else {

			SNode<T>* temp = head;

			while (temp->next != NULL)
			{
				temp = temp->next;

			}
			temp->next = n;
		}

		print();
	}

	void insertAtHead(T data) {
		SNode<T>* n = new SNode<T>(data);
		n->next = head;
		head = n;

	}

	void InsertAtIndex(int v, int ind) {
		SNode<T>* n = new SNode<T>(v);
		SNode<T>* temp = head;
		int currindex = 1;

		while (currindex != ind) {
			temp = temp->next;
			currindex++;
		}
		n->next = temp->next;
		temp->next = n;
		//print();
	}

	int search(int x) {
		SNode<T>* temp = head;
		int i = 0;
		while (temp != NULL) {
			if (temp->data == x) {
				return i;
				break;
			}
			temp = temp->next;
			i++;
		}



	}

	void update(int index, int data2) {
		SNode<T>* temp = head;
		int i = 0;
		while (i != index) {
			temp = temp->next;
			i++;
		}
		temp->data = data2;

	}

	void remove(int ind) {
		SNode<T>* n = head;
		SNode<T>* temp = head;
		int i = 0;
		while (ind != i && n != NULL) {
			temp = n;
			n = n->next;
			i++;
		}
		temp->next = n->next;
		delete n;
	}


	void print() {

		SNode<T>* n = head;
		while (n->next != NULL) {

			cout << n->data << endl;
			cout << n->file_n << endl;
			cout << n->line_number << endl;
			n = n->next;
		}
		cout << n->data << endl;
		cout << n->file_n << endl;
		cout << n->line_number << endl;
		n = n->next;
	}

	void mergeLists(SLinkedList obj) {

		SLinkedList merge;
		SNode<T>* n = head;
		SNode<T>* n2 = obj.head;
		while (n != NULL && n2 != NULL) {
			merge.insert(n->data);
			merge.insert(n2->data);
			n = n->next;
			n2 = n2->next;
		}
		head = merge.head;

	}

};


template<class T>
class Treenode {
public:
	//SNode<T>* s;
	T data;
	Treenode<T>* leftchild;
	Treenode<T>* rightchild;
	int height;
	string filename;
	int line_num;

	Treenode() {
		data = '\0';
		leftchild = NULL;
		rightchild = NULL;
		height = 0;
		filename = '\0';
		line_num = 0;
	}

	Treenode(T d) {
		this->data = d;
	}

	Treenode(Treenode<T>* lc, Treenode<T>* rc) {
		leftchild = lc;
		rightchild = rc;
	}


	void storenode(ofstream& file) {
		file << data << endl;
		file << filename << endl;
		file << line_num << endl;

	}

	//void print(ofstream& f) {
	//	
	//	SLinkedList<T> sll;
	//	SNode<T>* n = sll.head;
	//	while (n != NULL) {
	//		f << n->data << endl;
	//		f << n->file_n << endl;
	//		f << n->line_number << endl;
	//		n = n->next;
	//	}
	//	//f << n->data << endl;
	//	f << n->file_n << endl;
	//	f << n->line_number << endl;
	//	n = n->next;
	//}

};



template <class T>
class Nodee
{
public:
	T data;
	Nodee<T>* next;
	Treenode<T>* t;


	Nodee()
	{
		next = NULL;
		data = NULL;
	}

	Nodee(T d)
	{
		data = d;
		next = NULL;
	}

	Nodee(Treenode<T>* t_n)
	{
		t = t_n;
		next = NULL;
	}

};


template <class T>
class Queue
{
public:
	Nodee <T>* front;
	Nodee <T>* rear;
	int count = 0;


	Queue()
	{
		front = NULL;
		rear = NULL;
	}

	bool isEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		else
			return false;
	}

	void enqueue(Treenode<T>* p)
	{
		Nodee<T>* temp = new Nodee<T>(p);
		if (isEmpty())
		{
			front = temp;
			rear = temp;
			count++;
		}
		else
		{
			rear->next = temp;
			rear = rear->next;
			count++;
		}
	}

	void dequeue()
	{
		Nodee <T>* temp = front;
		front = temp->next;
		delete temp;
		count--;
	}

	Treenode<T>* Front()
	{
		return front->t;
	}

	void print()
	{
		Nodee <T>* temp = front;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

};



template<class T>
class AVLtree {
public:


	Treenode<T>* root;

	AVLtree() {
		root = NULL;
	}

	int TreeHeight(Treenode<T>* p) {
		if (p == NULL) {
			return -1;
		}
		else {
			return p->height;
		}
	}

	int Max_h(int a, int b) {
		if (a > b) {
			return a;
		}
		else {
			return b;
		}
	}

	int getBalance(Treenode<T>* N)
	{
		if (N == NULL)
			return -1;
		return TreeHeight(N->leftchild) - TreeHeight(N->rightchild);
	}




	Treenode<T>* newnode(T val, string name, int line) {
		Treenode<T>* Nodee = new Treenode<T>;
		Nodee->data = val;
		Nodee->filename = name;
		Nodee->line_num = line;
		Nodee->leftchild = NULL;
		Nodee->rightchild = NULL;
		Nodee->height = 0;
		return Nodee;
	}

	Treenode<T>* RR(Treenode<T> * n) {
		Treenode<T>* x = n->leftchild;
		Treenode<T>* temp = x->rightchild;

		x->rightchild = n;
		n->leftchild = temp;

		n->height = Max_h(TreeHeight(n->leftchild), TreeHeight(n->rightchild)) + 1;
		x->height = Max_h(TreeHeight(x->leftchild), TreeHeight(x->rightchild)) + 1;

		return x;
	}

	Treenode<T>* LL(Treenode<T> * x)
	{
		Treenode<T>* y = x->rightchild;
		Treenode<T>* T2 = y->leftchild;

		y->leftchild = x;
		x->rightchild = T2;

		x->height = Max_h(TreeHeight(x->leftchild), TreeHeight(x->rightchild)) + 1;
		y->height = Max_h(TreeHeight(y->leftchild), TreeHeight(y->rightchild)) + 1;

		return y;
	}

	Treenode<T>* Insert(Treenode<T> * n, T k, string file_nam, int no) {

		SLinkedList<string> SLL;

		if (n == NULL) {

			return newnode(k, file_nam, no);

		}

		if (k < n->data) {
			n->leftchild = Insert(n->leftchild, k, file_nam, no);

		}
		else if (k > n->data) {
			n->rightchild = Insert(n->rightchild, k, file_nam, no);
		}

		else {
			SLL.insert(file_nam, no);

			return n;
		}


		n->height = 1 + Max_h(TreeHeight(n->leftchild), TreeHeight(n->rightchild));

		int balance = getBalance(n);


		if (balance > 1 && k < n->leftchild->data)
			return RR(n);

		// Right Right Case
		if (balance < -1 && k > n->rightchild->data)
			return LL(n);

		// Left Right Case
		if (balance > 1 && k > n->leftchild->data)
		{
			n->leftchild = LL(n->leftchild);
			return RR(n);
		}

		// Right Left Case
		if (balance < -1 && k < n->rightchild->data)
		{
			n->rightchild = RR(n->rightchild);
			return LL(n);
		}


		return n;
	}


	/*void deleteNodeFromFile(T value)
	{
		Treenode<T>* node = findNode(value);
		cout << node->data << endl;
		cout << node->filename << endl;
		cout << node->line_num << endl;
		string str = node->filename;
		ifstream read;
		read.open(node->filename);
		string s;

		int line_count = 0;
		while (!read.eof()) {
			if (line_count == node->line_num) {
				break;
			}

			line_count++;
			getline(read, s);
		}

		cout << s << endl;
		delete_node(root, value);


	}*/

	Treenode<T>* getMinNode(Treenode<T> * r)
	{
		Treenode<T>* temp = r;
		while (temp->leftchild != NULL)
		{
			temp = temp->leftchild;
		}
		return temp;
	}


	//Treenode<T>* delete_node(Treenode<T>* node, T d) {
	//	if (root == NULL) {
	//		return root;
	//	}

	//	if (d < node->data) {
	//		node->leftchild = delete_node(node->leftchild, d);
	//	}
	//	else if (d > node->data) {
	//		node->rightchild = delete_node(node->rightchild, d);
	//	}

	//	else {
	//		if (node->leftchild == NULL || node->rightchild == NULL) {
	//			Treenode<T>* temp = node->leftchild ? node->leftchild : node->rightchild;
	//			if (temp == NULL) {
	//				temp = root;
	//				root = NULL;
	//				return NULL;
	//			}

	//			else {
	//				*node = *temp;
	//			}
	//			delete (temp);
	//		}
	//		else
	//		{
	//			
	//			Treenode<T>* temp = getMinNode(node->rightchild);

	//			
	//			root->data = temp->data;

	//			// Delete the inorder successor 
	//			root->rightchild = delete_node(node->rightchild, temp->data);
	//		}
	//	}

	//	
	//	if (root == NULL) {
	//		return root;
	//	}
	//	node->height = 1 + Max_h(TreeHeight(root->leftchild), TreeHeight(root->rightchild));

	//	int balance = getBalance(root);

	//	

	//	// Left Left Case 
	//	if (balance > 1 && getBalance(root->leftchild) >= 0)
	//		return RR(root);

	//	// Left Right Case 
	//	if (balance > 1 && getBalance(root->leftchild) < 0)
	//	{
	//		root->leftchild = LL(root->leftchild);
	//		return RR(root);
	//	}

	//	// Right Right Case 
	//	if (balance < -1 && getBalance(root->rightchild) <= 0)
	//		return LL(root);

	//	// Right Left Case 
	//	if (balance < -1 && getBalance(root->rightchild) > 0)
	//	{
	//		root->rightchild = RR(root->rightchild);
	//		return LL(root);
	//	}

	//	return root;
	//}



	void printInorder(Treenode<T> * node)
	{
		if (node == NULL)
			return;

		printInorder(node->leftchild);

		cout << node->data << " ";

		printInorder(node->rightchild);
	}

	void printPreorder(Treenode<T> * node)
	{
		if (node == NULL)
			return;

		cout << node->data << " ";

		printPreorder(node->leftchild);

		printPreorder(node->rightchild);
	}


	void printPostorder(Treenode<T> * node)
	{
		if (node == NULL)
			return;

		printPostorder(node->leftchild);

		printPostorder(node->rightchild);

		cout << node->data << " ";
	}

	void rangeSearch(Treenode<T> * root, T low, T high) {

		if (root == nullptr) {
			return;
		}

		// If the current node's value is in the range, print it
		if (root->data >= low && root->data <= high) {
			int line_count = 0;
			ifstream of;
			string s;
			of.open(root->filename);
			while (!of.eof()) {
				if (line_count == root->line_num) {
					break;
				}
				line_count++;

				getline(of, s);
			}

			cout << s << endl;
			//cout << root->data << " " << endl;
		}

		if (root->data > low) {
			rangeSearch(root->leftchild, low, high);

		}

		if (root->data < high) {
			rangeSearch(root->rightchild, low, high);
		}
	}


	bool pointSearch(Treenode<T> * root, T data) {
		if (root == nullptr) {
			cout << "Tree is Empty\n";

			return false;
		}

		if (root->data == data) {
			// If the value is present in the tree, return true
			cout << root->data << endl;
			cout << root->filename << endl;
			cout << root->line_num << endl;
			int line_count = 0;
			ifstream of;
			string s;
			of.open(root->filename);
			while (!of.eof()) {
				if (line_count == root->line_num) {
					break;
				}
				line_count++;

				getline(of, s);
			}

			cout << s << endl;


			return true;
		}

		if (data < root->data) {

			return pointSearch(root->leftchild, data);
			cout << root->data << endl;
			cout << root->filename << endl;
			cout << root->line_num << endl;
			int line_count = 0;
			ifstream of;
			of.open(root->filename);
			string s;
			while (!of.eof()) {
				if (line_count == root->line_num) {
					break;
				}
				line_count++;

				getline(of, s);
			}


			cout << s << endl;

		}

		else {
			return pointSearch(root->rightchild, data);
			cout << root->data << endl;
			cout << root->filename << endl;
			cout << root->line_num << endl;
			int line_count = 0;
			ifstream of;
			of.open(root->filename);
			string s;
			while (!of.eof()) {
				if (line_count == root->line_num) {
					break;
				}

				line_count++;
				getline(of, s);
			}

			cout << s << endl;

		}
	}

	void updateNode(T p_value, T n_value)
	{
		Treenode<T>* node = findNode(p_value);
		cout << node->data << endl;
		cout << node->filename << endl;
		cout << node->line_num << endl;
		string str = node->filename;
		ifstream read;
		read.open(node->filename);
		string s, s2;

		int line_count = 0;
		while (!read.eof()) {
			if (line_count == node->line_num) {
				break;
			}

			line_count++;
			getline(read, s);
		}

		cout << s << endl;

		read.close();
		// Update the node's value
		node->data = n_value;

		Insert(root, n_value, node->filename, node->line_num);

		balanceTree(node);
	}

	Treenode<T>* findNode(T value)
	{

		Treenode<T>* current = root;

		while (current && current->data != value)
		{
			if (value < current->data)
				current = current->leftchild;
			else
				current = current->rightchild;
		}
		return current;
	}



	void balanceTree(Treenode<T> * node)
	{
		// Calculate the balance factor of the node
		int balance = getBalance(node);

		// If the node is unbalanced, perform the appropriate rotation
		if (balance < -1)
		{
			if (getBalance(node->rightchild) > 0)
				node->rightchild = RR(node->rightchild);
			node = LL(node);
		}
		else if (balance > 1)
		{
			if (getBalance(node->leftchild) < 0)
				node->leftchild = LL(node->leftchild);
			node = RR(node);
		}
	}



	void LevelOrder(string datafield)

	{
		Queue<T>* q = new Queue<T>;
		ofstream output;
		string file = "AVL In ";

		file += datafield;
		file += ".txt";
		output.open(file, ios::app);



		if (root)
		{
			q->enqueue(root);
			while (!q->isEmpty())
			{
				if (q->Front()->leftchild)
					q->enqueue(q->Front()->leftchild);
				if (q->Front()->rightchild)
					q->enqueue(q->Front()->rightchild);
				Treenode<T>* temp = q->Front();
				temp->storenode(output);
				//temp->print(output);

				q->dequeue();
			}
		}
		delete q;
		output.close();

	}

};






void makeAVL()
{
	int option;
	int datatype;
	AVLtree<string> obj;
	AVLtree<int> obj2;
	AVLtree<double> obj3;







	ifstream* input = new ifstream[10];
	ifstream input2, input3, input4, input5, input6, input7, input8, input9, input10;

	string s;
	int line_no = 1;
	int size = 10;
	string* filename = new string[10];
	filename[0] = "1.csv";
	filename[1] = "2.csv";
	filename[2] = "3.csv";
	filename[3] = "4.csv";
	filename[4] = "5.csv";
	filename[5] = "6.csv";
	filename[6] = "7.csv";
	filename[7] = "8.csv";
	filename[8] = "9.csv";
	filename[9] = "10.csv";

	input[0].open("1.csv");
	input[1].open("2.csv");
	input[2].open("3.csv");
	input[3].open("4.csv");
	input[4].open("5.csv");
	input[5].open("6.csv");
	input[6].open("7.csv");
	input[7].open("8.csv");
	input[8].open("9.csv");
	input[9].open("10.csv");

	string low, high;

	int field;
	int choice;
	int iD;
	int Y;
	int death_no;
	double ID;
	double years;
	double Rate;
	double dea_ths;

	string str;
	string id, year, cause1, cause_name, state, deaths, rate;


	getline(input[1], str);
	getline(input[2], str);
	getline(input[3], str);
	getline(input[4], str);
	getline(input[5], str);
	getline(input[6], str);
	getline(input[7], str);
	getline(input[8], str);
	getline(input[9], str);



	cout << endl;
	cout << "You can perform indexing on the following data fields\n" << endl;
	getline(input[0], str, ',');
	cout << "1) " << str << endl;
	getline(input[0], str, ',');
	cout << "2) " << str << endl;
	getline(input[0], str, ',');
	cout << "3) " << str << endl;
	getline(input[0], str, ',');
	cout << "4) " << str << endl;
	getline(input[0], str, ',');
	cout << "5) " << str << endl;
	getline(input[0], str, ',');
	cout << "6) " << str << endl;
	getline(input[0], str, '\n');
	cout << "7) " << str << endl;
	cout << endl;
	cout << "Now please specify the data field to perform indexing\n";
	cin >> field;
	cout << "Please specify the data type of the field\n";
	cout << "1) Integer " << endl << "2) Double" << endl << "3) String" << endl;
	cin >> datatype;
	cout << endl;
	if (field == 1 && datatype == 1) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {

				getline(input[i], str, ',');
				if (str == "") {
					break;
				}
				line_no++;
				id = str;
				iD = stoi(str);
				obj2.root = obj2.Insert(obj2.root, iD, filename[i], line_no);

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}

		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the ID you want to search\n";
			int val;
			cin >> val;
			obj2.pointSearch(obj2.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			int l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			int h = stoi(high);
			obj2.rangeSearch(obj2.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the ID you want to update\n";
			int prev_id;
			cin >> prev_id;
			cout << "Please enter the ID you need to replace the old ID with\n";
			int new_id;
			cin >> new_id;
			obj2.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the ID you want to delete\n";
			int del_id;
			cin >> del_id;
			//obj2.deleteNodeFromFile(del_id);

		}
		obj2.LevelOrder("ID");

	}


	else if (field == 1 && datatype == 2) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {

				getline(input[i], str, ',');
				if (str == "") {
					break;
				}
				line_no++;
				id = str;
				ID = stod(str);
				obj3.root = obj3.Insert(obj3.root, ID, filename[i], line_no);

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}

		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the ID you want to search\n";
			double val;
			cin >> val;
			obj3.pointSearch(obj3.root, val);
		}

		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			double l = stod(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			double h = stod(high);
			obj3.rangeSearch(obj3.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the ID you want to update\n";
			int prev_id;
			cin >> prev_id;
			cout << "Please enter the ID you need to replace the old ID with\n";
			int new_id;
			cin >> new_id;
			obj3.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the ID you want to delete\n";
			int del_id;
			cin >> del_id;
			//obj3.deleteNodeFromFile(del_id);
		}
		obj3.LevelOrder("ID");
	}


	else if (field == 1 && datatype == 3) {
		cout << "Please enter a valid datatype\n";
	}


	else if (field == 2 && datatype == 1) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');


				getline(input[i], str, ',');
				if (str == "") {
					break;
				}
				year = str;
				Y = stoi(str);
				line_no++;
				obj2.root = obj2.Insert(obj2.root, Y, filename[i], line_no);


				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Year you want to search\n";
			int val;
			cin >> val;
			obj2.pointSearch(obj2.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			int l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			int h = stoi(high);
			obj2.rangeSearch(obj2.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the Year you want to update\n";
			int prev_id;
			cin >> prev_id;
			cout << "Please enter the Year you need to replace the old Year with\n";
			int new_id;
			cin >> new_id;
			obj2.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the Year you want to delete\n";
			int del_id;
			cin >> del_id;
			//obj2.deleteNodeFromFile(del_id);
		}

		obj2.LevelOrder("Year");
	}


	else if (field == 2 && datatype == 2) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');

				getline(input[i], str, ',');
				if (str == "") {
					break;
				}
				year = str;
				years = stod(str);
				line_no++;
				obj3.root = obj3.Insert(obj3.root, years, filename[i], line_no);


				getline(input[i], str, ',');


				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Year you want to search\n";
			double val;
			cin >> val;
			obj3.pointSearch(obj3.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			double l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			double h = stoi(high);
			obj3.rangeSearch(obj3.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the Year you want to update\n";
			int prev_id;
			cin >> prev_id;
			cout << "Please enter the Year you need to replace the old Year with\n";
			int new_id;
			cin >> new_id;
			obj3.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the Year you want to delete\n";
			int del_y;
			cin >> del_y;
			//obj3.deleteNodeFromFile(del_y);
		}

		obj3.LevelOrder("Year");
	}


	else if (field == 2 && datatype == 3) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 3 && datatype == 1) {
		cout << "Please enter a valid data type\n";
	}
	else if (field == 3 && datatype == 2) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 3 && datatype == 3) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');

				getline(input[i], str, ',');


				getline(input[i], str, ',');
				line_no++;
				cause1 = str;
				obj.root = obj.Insert(obj.root, cause1, filename[i], line_no);

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Cause you want to search\n";
			string val;
			cin >> val;
			obj.pointSearch(obj.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			//int l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			//int h = stoi(high);
			obj.rangeSearch(obj.root, low, high);
		}
		if (option == 3) {
			cout << "Please enter the Cause you want to update\n";
			string prev_id;
			cin >> prev_id;
			cout << "Please enter the Cause you need to replace the old ID with\n";
			string new_id;
			cin >> new_id;
			obj.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the Cause you want to delete\n";
			string del_id;
			cin >> del_id;
			//obj.deleteNodeFromFile(del_id);
		}
		obj.LevelOrder("Cause");
	}

	else if (field == 4 && datatype == 1) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 4 && datatype == 2) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 4 && datatype == 3) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');
				line_no++;
				cause_name = str;
				obj.root = obj.Insert(obj.root, cause_name, filename[i], line_no);

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Cause Name you want to search\n";
			string val;
			cin >> val;
			obj.pointSearch(obj.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			//int l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			//int h = stoi(high);
			obj.rangeSearch(obj.root, low, high);
		}
		if (option == 3) {
			cout << "Please enter the Cause Name you want to update\n";
			string prev_id;
			cin >> prev_id;
			cout << "Please enter the Cause Name you need to replace the old Cause Name with\n";
			string new_id;
			cin >> new_id;
			obj.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the Cause Name you want to delete\n";
			string del_id;
			cin >> del_id;
			//obj.deleteNodeFromFile(del_id);
		}
		obj.LevelOrder("CN");
	}


	else if (field == 5 && datatype == 1) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 5 && datatype == 2) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 5 && datatype == 3) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');
				line_no++;
				state = str;
				obj.root = obj.Insert(obj.root, state, filename[i], line_no);

				getline(input[i], str, ',');

				getline(input[i], str, '\n');

			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the State you want to search\n";
			string val;
			cin >> val;
			obj.pointSearch(obj.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			//int l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			//int h = stoi(high);
			obj.rangeSearch(obj.root, low, high);
		}
		if (option == 3) {
			cout << "Please enter the State you want to update\n";
			string prev_id;
			cin >> prev_id;
			cout << "Please enter the State you need to replace the old State with\n";
			string new_id;
			cin >> new_id;
			obj.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the State you want to delete\n";
			string del_id;
			cin >> del_id;
			//obj.deleteNodeFromFile(del_id);
		}
		obj.LevelOrder("State");
	}


	else if (field == 6 && datatype == 1) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');
				if (str == "") {
					break;
				}
				line_no++;
				deaths = str;
				death_no = stoi(str);
				obj2.root = obj2.Insert(obj2.root, death_no, filename[i], line_no);


				getline(input[i], str, '\n');

			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Deaths you want to search\n";
			int val;
			cin >> val;
			obj2.pointSearch(obj2.root, val);
		}
		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			int l = stoi(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			int h = stoi(high);
			obj2.rangeSearch(obj2.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the Deaths you want to update\n";
			int prev_id;
			cin >> prev_id;
			cout << "Please enter the Deaths you need to replace the old Deaths with\n";
			int new_id;
			cin >> new_id;
			obj2.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the deaths you want to delete\n";
			int del_id;
			cin >> del_id;
			//obj2.deleteNodeFromFile(del_id);
		}
		obj2.LevelOrder("D");
	}

	else if (field == 6 && datatype == 2) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');
				if (str == "") {
					break;
				}
				line_no++;
				deaths = str;
				dea_ths = stod(deaths);

				obj3.root = obj3.Insert(obj3.root, dea_ths, filename[i], line_no);


				getline(input[i], str, '\n');
			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Death you want to search\n";
			double val;
			cin >> val;
			obj3.pointSearch(obj3.root, val);
		}

		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			double l = stod(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			double h = stod(high);
			obj3.rangeSearch(obj3.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the deaths you want to update\n";
			double prev_id;
			cin >> prev_id;
			cout << "Please enter the deaths you need to replace the old deaths with\n";
			double new_id;
			cin >> new_id;
			obj3.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the deaths you want to delete\n";
			double del_id;
			cin >> del_id;
			//obj3.deleteNodeFromFile(del_id);
		}
		obj3.LevelOrder("D");
	}

	else if (field == 6 && datatype == 3) {
		cout << "Please enter a valid data type\n";
	}


	else if (field == 7 && datatype == 1) {
		cout << "Please enter a valid data type\n";
	}

	else if (field == 7 && datatype == 2) {
		for (int i = 0; i < size; i++) {
			while (!input[i].eof()) {
				getline(input[i], str, ',');

				getline(input[i], str, ',');


				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, ',');

				getline(input[i], str, '\n');
				if (str == "") {
					break;
				}
				line_no++;
				rate = str;
				Rate = stod(rate);
				obj3.root = obj3.Insert(obj3.root, Rate, filename[i], line_no);


			}
			line_no = 0;
		}
		cout << "What else function do you need to perform\n";
		cout << "These are the following functions which you can perform on the following set of data\n";
		cout << "1) Point Search\n";
		cout << "2) Range Search\n";
		cout << "3) Update key, field, old value, new value\n";
		cout << "4) Delete key\n";
		cin >> option;
		if (option == 1) {
			cout << "Please enter the Death Rate you want to search\n";
			double val;
			cin >> val;
			obj3.pointSearch(obj3.root, val);
		}

		if (option == 2) {

			cout << "Enter the lower bound of the range: ";
			cin >> low;
			double l = stod(low);
			cout << "Enter the upper bound of the range: ";
			cin >> high;
			double h = stod(high);
			obj3.rangeSearch(obj3.root, l, h);
		}
		if (option == 3) {
			cout << "Please enter the rate you want to update\n";
			double prev_id;
			cin >> prev_id;
			cout << "Please enter the rate you need to replace the old rate with\n";
			double new_id;
			cin >> new_id;
			obj3.updateNode(prev_id, new_id);
			cout << "Update successful\n";
		}
		if (option == 4) {
			cout << "Please enter the ID you want to delete\n";
			double del_id;
			cin >> del_id;
			//obj3.deleteNodeFromFile(del_id);
		}
		obj3.LevelOrder("R");
	}

	else if (field == 7 && datatype == 3) {
		cout << "Please enter a valid data type\n";
	}





}



