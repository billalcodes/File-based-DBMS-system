#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
#include<sstream>
#include <cstdio>
using namespace std;
int r1lf, r1ll;

//structure to store data in tree
struct data1 {
    int key;
    string f_name;
    int line;
    string year, cause, causename, state, deaths, age, rate;
};
template<typename T>
class Node {		//class for node of RB trees
public:
    T data;          //data for the nodes
    Node<T>* parent; //parent pointer
    Node<T>* left;   //left child
    Node<T>* right;  //right child
    int colour;      //0(black) 1(Red)
    Node<T>* makenull;

    Node() {
        //default constructor

        left = nullptr;
        right = nullptr;
        colour = 0;
    }
    /* Node(int colour, T data) {

         this->data = data;
         parent = new Node<T>;
         left = new Node<T>;
         right = new Node<T>;
         this->colour = colour;
     }*/





};

template<typename T>
class Rbtree {
public:
    Node<T>* root;
    Node<T>* makenull;

    Rbtree() {
        makenull = new Node<T>;
        root = makenull;
    }
    void rotateleft(Node<T>* node) {    //left rotation

        Node<T>* temp = node->right;
        node->right = temp->left;
        if (temp->left != makenull) {
            temp->left->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = temp;
        }
        else if (node == node->parent->left) {
            node->parent->left = temp;
        }
        else
            node->parent->right = temp;
        temp->left = node;
        node->parent = temp;
    }
    void rotateright(Node<T>* node) {   //right rotation
        Node<T>* temp = node->left;
        node->left = temp->right;
        if (temp->right != makenull) {
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = temp;
        }
        else if (node == node->parent->right) {
            node->parent->right = temp;
        }
        else
            node->parent->left = temp;
        temp->right = node;
        node->parent = temp;
    }


    Node<T>* min(Node<T>* node) {
        while (node->left != makenull) {
            node = node->left;
        }
        return node;
    }
    void postinsert(Node<T>* node) {
        Node<T>* temp;
        while (node->parent->colour == 1) {
            if (node->parent == node->parent->parent->right) {
                temp = node->parent->parent->left;
                if (temp->colour == 1) {
                    temp->colour = 0;
                    node->parent->colour = 0;
                    node->parent->parent->colour = 1;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateright(node);
                    }
                    node->parent->colour = 0;
                    node->parent->parent->colour = 1;
                    rotateleft(node->parent->parent);
                }
            }
            else {
                temp = node->parent->parent->right;
                if (temp->colour == 1) {
                    temp->colour = 0;
                    node->parent->colour = 0;
                    node->parent->parent->colour = 1;
                    node = node->parent->parent;
                }
                else {
                    if (node = node->parent->right) {
                        node = node->parent;
                        rotateleft(node);
                    }
                    node->parent->colour = 0;
                    node->parent->parent->colour = 1;
                    rotateright(node->parent->parent);
                }
            }
            if (node == root) {
                break;
            }
        }
        root->colour = 0;
    }
    void insert(data1* newnode) {
        Node<T>* node = new Node<T>;
        node->colour = 1;
        node->parent = nullptr;
        node->data.key = newnode->key;
        node->data.f_name = newnode->f_name;
        node->data.line = newnode->line;
        node->left = makenull;
        node->right = makenull;


        Node<T>* temp = nullptr;
        Node<T>* temp1 = this->root;
        while (temp1 != makenull) {
            temp = temp1;
            if (node->data.key < temp1->data.key) {
                temp1 = temp1->left;
            }
            else
                temp1 = temp1->right;
        }
        node->parent = temp;
        if (temp == nullptr) {
            root = node;
        }
        else if (node->data.key < temp->data.key) {
            temp->left = node;
        }
        else
            temp->right = node;
        if (node->parent == nullptr) {
            node->colour = 0;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }
        postinsert(node);


    }

    void storenodes(Node<T>* node) {
        if (node != makenull) {

            string name = "C:/Users/bilal/Documents/FAST/SEMESTER 4/Data structures/Project/RBtree/node" + to_string(node->data.key) + ".csv";
            ofstream temp(name);

            temp << node->data.key << "," << node->data.line << "," << node->data.f_name << "\n";
            temp.close();
            storenodes(node->left);
            storenodes(node->right);
        }
    }



};
void find(int searchedkey, int upperlimit) {   //Searching for record in given files
    int fl = 0;
    data1* temp1 = new data1;

    for (int i = 1; i <= upperlimit; i++) {
        string nodefilename = "C:/Users/bilal/Documents/FAST/SEMESTER 4/Data structures/Project/RBtree/node" + to_string(i) + ".csv";
        // string nodefilename = "test.csv";

        ifstream readnode(nodefilename);
        vector<string> row;         //reading data in form of string vector
        string line, word, temp;

        row.clear();

        getline(readnode, line);         //reading a line of file and storing in variable line

        stringstream s(line);       //breaking words
        while (getline(s, word, ',')) {

            row.push_back(word);    //storing each col data in row vector
        }
        if (searchedkey == stoi(row[0])) {
            cout << "Record is in the files named: " << row[2] << " on line number " << row[1] << ".\n";
            fstream file;
            file.open(row[2], ios::in);
            vector<data1*> elements1;

            vector<string> row1;
            string line1, word1, temp2;

            row1.clear();

            getline(file, line1);

            stringstream s1(line1);

            while (!file.eof()) {
                data1* index = new data1;
                fl++;
                row1.clear();
                getline(file, line1);

                stringstream s1(line1);
                if (stoi(row[1]) == fl) {

                    while (getline(s1, word1, ',')) {

                        row1.push_back(word1);
                    }

                    for (int i = 0; i < row1.size(); i++) {
                        if (i == row1.size() - 1) {
                            cout << row1[i] << "\n";
                            break;

                        }
                        cout << row1[i] << "\t";
                    }
                }


            }
            return;
        }


    }

}

Node<data1>* read(string filename, string name, Rbtree<data1> obj) {      //Creating btrees

    fstream fin;        // File pointer
    fstream rootfile;
    int f_line = 0;

    fin.open(name, ios::in);    // Open an existing file


    // vector<data1*> elements;    //storing data in vector

    vector<string> row;         //reading data in form of string vector
    string line, word, temp;

    row.clear();

    getline(fin, line);         //reading a line of file and storing in variable line

    stringstream s(line);       //breaking words

    while (!fin.eof()) {
        data1* index = new data1;
        if (f_line == 0) {
            row.clear();

            getline(fin, line);

            stringstream s(line);

            while (getline(s, word, ',')) {

                row.push_back(word);    //storing each col data in row vector
            }
            if (!fin.eof()) {

                f_line++;
                r1lf = stoi(row[0]);;
                index->f_name = name;
                index->line = f_line;
                index->key = stoi(row[0]);
                if (row.size() == 8) {
                    index->year = row[1];
                    index->cause = row[2] + row[3];
                    index->causename = row[4];
                    index->state = row[5];
                    index->deaths = row[6];
                    index->age = row[7];
                }
                else if (row.size() == 7) {
                    index->year = row[1];
                    index->cause = row[2];
                    index->causename = row[3];
                    index->state = row[4];
                    index->deaths = row[5];
                    index->age = row[6];
                }
                obj.insert(index);
            }
        }

        row.clear();

        getline(fin, line);

        stringstream s(line);

        while (getline(s, word, ',')) {

            row.push_back(word);    //storing each col data in row vector
        }
        if (!fin.eof()) {

            f_line++;
            index->f_name = name;
            index->line = f_line;
            index->key = stoi(row[0]);
            if (row.size() == 8) {
                index->year = row[1];
                index->cause = row[2] + row[3];
                index->causename = row[4];
                index->state = row[5];
                index->deaths = row[6];
                index->age = row[7];
            }
            else if (row.size() == 7) {
                index->year = row[1];
                index->cause = row[2];
                index->causename = row[3];
                index->state = row[4];
                index->deaths = row[5];
                index->age = row[6];
            }
            obj.insert(index);
            r1ll = stoi(row[0]);
        }


    }
    obj.storenodes(obj.root);
    //fstream rootfile(filename, ios::app);


    return obj.root;
}

void maketree(string rootfilename) {
    fstream rootfile(rootfilename, ios::out);
    rootfile << "key" << ", " << "low limit" << "," << "upperlimit\n";
    /***Declaring RBtrees***/
    Rbtree<data1> obj1;
    Rbtree<data1> obj2;
    Rbtree<data1> obj3;
    Rbtree<data1> obj4;
    Rbtree<data1> obj5;
    Rbtree<data1> obj6;
    Rbtree<data1> obj7;
    Rbtree<data1> obj8;
    Rbtree<data1> obj9;
    Rbtree<data1> obj10;


    /***Declaring paths of files***/
    string  name[10] = { "NCHS_-_Leading_Causes_of_Death__United_States_1.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_2.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_3.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_4.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_5.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_6.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_7.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_8.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_9.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_10.csv",
    };

    /***Declaring temporary variables to store roots of files***/
    Node<data1>* temp_root1;
    Node<data1>* temp_root2;
    Node<data1>* temp_root3;
    Node<data1>* temp_root4;
    Node<data1>* temp_root5;
    Node<data1>* temp_root6;
    Node<data1>* temp_root7;
    Node<data1>* temp_root8;
    Node<data1>* temp_root9;
    Node<data1>* temp_root10;

    /***Creating RBtrees***/
    temp_root1 = read(rootfilename, name[0], obj1);
    rootfile << temp_root1->data.key << "," << r1lf << "," << r1ll << "\n";
    temp_root2 = read(rootfilename, name[1], obj2);
    rootfile << temp_root2->data.key << "," << r1lf << "," << r1ll << "\n";
    temp_root3 = read(rootfilename, name[2], obj3);
    rootfile << temp_root3->data.key << "," << r1lf << "," << r1ll << "\n";
    temp_root4 = read(rootfilename, name[2], obj4);
    rootfile << temp_root4->data.key << "," << r1lf << "," << r1ll << "\n";

    temp_root5 = read(rootfilename, name[3], obj5);
    rootfile << temp_root5->data.key << "," << r1lf << "," << r1ll << "\n";

    temp_root6 = read(rootfilename, name[4], obj6);
    rootfile << temp_root6->data.key << "," << r1lf << "," << r1ll << "\n";

    temp_root7 = read(rootfilename, name[5], obj7);
    rootfile << temp_root7->data.key << "," << r1lf << "," << r1ll << "\n";

    temp_root8 = read(rootfilename, name[6], obj8);
    rootfile << temp_root8->data.key << "," << r1lf << "," << r1ll << "\n";

    temp_root9 = read(rootfilename, name[7], obj9);
    rootfile << temp_root9->data.key << "," << r1lf << "," << r1ll << "\n";

    temp_root10 = read(rootfilename, name[8], obj10);
    rootfile << temp_root10->data.key << "," << r1lf << "," << r1ll << "\n";
    rootfile.close();
}
void update(string rootfilename, int searchedkey, int upperlimit) {   //updating record in given files
    int fl = 0;


    for (int i = 1; i <= upperlimit; i++) {
        string nodefilename = "C:/Users/bilal/Documents/FAST/SEMESTER 4/Data structures/Project/RBtree/node" + to_string(i) + ".csv";
        // string nodefilename = "test.csv";

        ifstream readnode(nodefilename);
        vector<string> row;         //reading data in form of string vector
        string line, word, temp;

        row.clear();

        getline(readnode, line);         //reading a line of file and storing in variable line

        stringstream s(line);       //breaking words
        while (getline(s, word, ',')) {

            row.push_back(word);    //storing each col data in row vector
        }
        if (searchedkey == stoi(row[0])) {
            cout << "Record is in the files named: " << row[2] << " on line number " << row[1] << ".\n";
            fstream file;
            file.open(row[2], ios::in);
            fstream temp_f;
            string tempfilename = "temp.csv";
            temp_f.open(tempfilename, ios::out);
            vector<data1*> elements1;

            vector<string> row1;
            string line1, word1, temp2;

            row1.clear();

            getline(file, line1);

            stringstream s1(line1);

            while (!file.eof()) {
                data1* index = new data1;
                fl++;
                row1.clear();
                getline(file, line1);

                stringstream s1(line1);
                if (stoi(row[1]) == fl) {
                    while (getline(s1, word1, ',')) {

                        row1.push_back(word1);
                    }
                    string w, choice;
                    if (row1.size() == 8) {
                        temp_f << row1[0] << ",";
                        cout << "Do you want to update year?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new year: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[1] << ",";
                        }
                        cout << "Do you want to update cause113 field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new cause: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[2] + row1[3] << ",";
                        }
                        cout << "Do you want to update cause name field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new causename: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[4] << ",";
                        }
                        cout << "Do you want to update state field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new state: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[5] << ",";
                        }
                        cout << "Do you want to update Deaths field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new number of Deaths: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[6] << ",";
                        }

                        cout << "Do you want to update Age adjusted death rate field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new Age adjusted death rate: ";
                            cin >> w;
                            temp_f << w;
                        }
                        else {
                            temp_f << row1[7];
                        }
                        temp_f << "\n";
                        continue;
                    }
                    else if (row1.size() == 7) {
                        temp_f << row1[0] << ",";
                        cout << "Do you want to update year?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new year: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[1] << ",";
                        }
                        cout << "Do you want to update cause113 field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new cause: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[2] << ",";
                        }
                        cout << "Do you want to update cause name field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new causename: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[3] << ",";
                        }
                        cout << "Do you want to update state field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new state: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[4] << ",";
                        }
                        cout << "Do you want to update Deaths field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new number of Deaths: ";
                            cin >> w;
                            temp_f << w << ",";
                        }
                        else {
                            temp_f << row1[5] << ",";
                        }

                        cout << "Do you want to update Age adjusted death rate field?(y/n): ";
                        cin >> choice;
                        if (choice == "y") {
                            cout << "Enter the new Age adjusted death rate: ";
                            cin >> w;
                            temp_f << w;
                        }
                        else {
                            temp_f << row1[6];
                        }
                        temp_f << "\n";
                        continue;
                    }
                }
                while (getline(s1, word1, ',')) {

                    row1.push_back(word1);
                }
                for (int i = 0; i < row1.size(); i++) {
                    if (i == row1.size() - 1) {
                        temp_f << row1[i] << "\n";
                        break;

                    }
                    temp_f << row1[i] << ",";
                }


            }
            const char* rename1 = tempfilename.c_str();
            const char* rename2 = row[2].c_str();
            remove(rename2);
            temp_f.close();
            fstream resultingfile;
            resultingfile.open(row[2], ios::out);
            temp_f.open(tempfilename, ios::in | ios::app);
            while (!temp_f.eof()) {
                row1.clear();

                getline(temp_f, line1);

                stringstream s1(line1);

                while (getline(s1, word1, ',')) {

                    row1.push_back(word1);
                }
                for (int i = 0; i < row1.size(); i++) {
                    if (i == row1.size() - 1) {
                        resultingfile << row1[i] << "\n";
                        break;

                    }
                    resultingfile << row1[i] << ",";
                }
            }
            resultingfile.close();
            maketree(rootfilename);
            return;
        }


    }


}
void remove(string rootfilename, int searchedkey, int upperlimit) {   //Deleting record in given files
    int fl = 0;


    for (int i = 1; i <= upperlimit; i++) {
        string nodefilename = "C:/Users/bilal/Documents/FAST/SEMESTER 4/Data structures/Project/RBtree/node" + to_string(i) + ".csv";
        // string nodefilename = "test.csv";

        ifstream readnode(nodefilename);
        vector<string> row;         //reading data in form of string vector
        string line, word, temp;

        row.clear();

        getline(readnode, line);         //reading a line of file and storing in variable line

        stringstream s(line);       //breaking words
        while (getline(s, word, ',')) {

            row.push_back(word);    //storing each col data in row vector
        }
        if (searchedkey == stoi(row[0])) {
            cout << "Record is in the files named: " << row[2] << " on line number " << row[1] << ".\n";
            fstream file;
            file.open(row[2], ios::in);
            fstream temp_f;
            string tempfilename = "temp.csv";
            temp_f.open(tempfilename, ios::out);
            vector<data1*> elements1;

            vector<string> row1;
            string line1, word1, temp2;

            row1.clear();

            getline(file, line1);

            stringstream s1(line1);

            while (!file.eof()) {
                data1* index = new data1;
                fl++;
                row1.clear();
                getline(file, line1);

                stringstream s1(line1);
                if (stoi(row[1]) == fl) {
                    continue;
                }
                while (getline(s1, word1, ',')) {

                    row1.push_back(word1);
                }
                for (int i = 0; i < row1.size(); i++) {
                    if (i == row1.size() - 1) {
                        temp_f << row1[i] << "\n";
                        break;

                    }
                    temp_f << row1[i] << ",";
                }


            }
            const char* rename1 = tempfilename.c_str();
            const char* rename2 = row[2].c_str();
            remove(rename2);
            temp_f.close();
            fstream resultingfile;
            resultingfile.open(row[2], ios::out);
            temp_f.open(tempfilename, ios::in | ios::app);
            while (!temp_f.eof()) {
                row1.clear();

                getline(temp_f, line1);

                stringstream s1(line1);

                while (getline(s1, word1, ',')) {

                    row1.push_back(word1);
                }
                for (int i = 0; i < row1.size(); i++) {
                    if (i == row1.size() - 1) {
                        resultingfile << row1[i] << "\n";
                        break;

                    }
                    resultingfile << row1[i] << ",";
                }
            }
            resultingfile.close();
            maketree(rootfilename);
            return;
        }


    }


}
//Operations using btree
int Rbtreeops() {
    int choice;
    cout << "-> Press 1 to search a record.\n";
    cout << "-> Press 2 to update a record.\n";
    cout << "-> Press 3 to delete a record.\n";
    cout << "-> Press 4 to search a range of records.\n";
    cout << "-> Press 5 to update a range of records.\n";
    cout << "-> Press 6 to delete a range of records.\n";
    cin >> choice;
    return choice;
}
int intitialmenu() {
    int choice;
    cout << "-> Press 1 to make new trees.\n";
    cout << "-> Press 2 to run queries.\n";
    cout << "-> Press 3 to to go back to main menu.\n";
    cin >> choice;
    return choice;
}
void runqueries(string rootfilename) {
    int temp_id;    //temporary variable to store the id to perform action

    int Rbtreeoperation = Rbtreeops();
    while (Rbtreeoperation != 1 && Rbtreeoperation != 2 && Rbtreeoperation != 3 && Rbtreeoperation != 4 && Rbtreeoperation != 5 && Rbtreeoperation != 6) {
        cout << "Envalid entry please enter again\n";
        Rbtreeoperation = Rbtreeops();
    }
    if (Rbtreeoperation == 1) {
        cout << "Enter the key of the element you want to search: ";
        cin >> temp_id;
        ifstream readroot(rootfilename);
        vector<string> row;         //reading data in form of string vector
        string line, word, temp;
        row.clear();

        getline(readroot, line);         //reading a line of file and storing in variable line

        stringstream s(line);       //breaking words
        while (!readroot.eof()) {
            row.clear();

            getline(readroot, line);         //reading a line of file and storing in variable line

            stringstream s(line);       //breaking words
            while (getline(s, word, ',')) {

                row.push_back(word);    //storing each col data in row vector
            }
            if (temp_id <= stoi(row[0])) {
                find(temp_id, stoi(row[2]));
                break;
            }
        }
    }
    else if (Rbtreeoperation == 2) {
        cout << "Enter the key of the element you want to update: ";
        cin >> temp_id;
        ifstream readroot(rootfilename);
        vector<string> row;         //reading data in form of string vector
        string line, word, temp;
        row.clear();

        getline(readroot, line);         //reading a line of file and storing in variable line

        stringstream s(line);       //breaking words
        while (!readroot.eof()) {
            row.clear();

            getline(readroot, line);         //reading a line of file and storing in variable line

            stringstream s(line);       //breaking words
            while (getline(s, word, ',')) {

                row.push_back(word);    //storing each col data in row vector
            }
            if (temp_id <= stoi(row[0])) {
                update(rootfilename, temp_id, stoi(row[2]));
                break;
            }
        }
    }
    else if (Rbtreeoperation == 3) {
        cout << "Enter the key of the element you want to delete: ";
        cin >> temp_id;
        ifstream readroot(rootfilename);
        vector<string> row;         //reading data in form of string vector
        string line, word, temp;
        row.clear();

        getline(readroot, line);         //reading a line of file and storing in variable line

        stringstream s(line);       //breaking words
        while (!readroot.eof()) {
            row.clear();

            getline(readroot, line);         //reading a line of file and storing in variable line

            stringstream s(line);       //breaking words
            while (getline(s, word, ',')) {

                row.push_back(word);    //storing each col data in row vector
            }
            if (temp_id <= stoi(row[0])) {
                remove(rootfilename, temp_id, stoi(row[2]));
                break;
            }
        }
    }
    else if (Rbtreeoperation == 4) {
        int temp;
        cout << "Enter the starting key of the element you want to search: ";
        cin >> temp_id;
        cout << "Enter the ending key of the element you want to search: ";
        cin >> temp;
        while (temp_id <= temp) {
            ifstream readroot(rootfilename);
            vector<string> row;         //reading data in form of string vector
            string line, word, temp;
            row.clear();

            getline(readroot, line);         //reading a line of file and storing in variable line

            stringstream s(line);       //breaking words
            while (!readroot.eof()) {
                row.clear();

                getline(readroot, line);         //reading a line of file and storing in variable line

                stringstream s(line);       //breaking words
                while (getline(s, word, ',')) {

                    row.push_back(word);    //storing each col data in row vector
                }
                if (temp_id <= stoi(row[0])) {
                    find(temp_id, stoi(row[2]));
                    temp_id++;
                    break;
                }
            }
        }
    }
    else if (Rbtreeoperation == 5) {
        int temp;
        cout << "Enter the starting key of the element you want to update: ";
        cin >> temp_id;
        cout << "Enter the ending key of the element you want to update: ";
        cin >> temp;
        while (temp_id <= temp) {
            ifstream readroot(rootfilename);
            vector<string> row;         //reading data in form of string vector
            string line, word, temp;
            row.clear();

            getline(readroot, line);         //reading a line of file and storing in variable line

            stringstream s(line);       //breaking words
            while (!readroot.eof()) {
                row.clear();

                getline(readroot, line);         //reading a line of file and storing in variable line

                stringstream s(line);       //breaking words
                while (getline(s, word, ',')) {

                    row.push_back(word);    //storing each col data in row vector
                }
                if (temp_id <= stoi(row[0])) {
                    update(rootfilename, temp_id, stoi(row[2]));
                    temp_id++;
                    break;
                }
            }
        }
    }
    else if (Rbtreeoperation == 6) {
        int temp;
        cout << "Enter the starting key of the element you want to update: ";
        cin >> temp_id;
        cout << "Enter the ending key of the element you want to update: ";
        cin >> temp;
        while (temp_id <= temp) {
            ifstream readroot(rootfilename);
            vector<string> row;         //reading data in form of string vector
            string line, word, temp;
            row.clear();

            getline(readroot, line);         //reading a line of file and storing in variable line

            stringstream s(line);       //breaking words
            while (!readroot.eof()) {
                row.clear();

                getline(readroot, line);         //reading a line of file and storing in variable line

                stringstream s(line);       //breaking words
                while (getline(s, word, ',')) {

                    row.push_back(word);    //storing each col data in row vector
                }
                if (temp_id <= stoi(row[0])) {
                    remove(rootfilename, temp_id, stoi(row[2]));
                    temp_id++;
                    break;
                }
            }
        }
    }

}
void makeRBtrees() {
    string rootfilename = "C:/Users/bilal/Documents/FAST/SEMESTER 4/Data structures/Project/RBtree/roots.csv";
    int intitialchoice = intitialmenu();
    while (intitialchoice != 3) {
        if (intitialchoice == 1) {
            maketree(rootfilename);
        }
        else if (intitialchoice == 2) {
            runqueries(rootfilename);
        }
        intitialchoice = intitialmenu();
    }
}