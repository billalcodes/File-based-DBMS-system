#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
#include<sstream>
#include <cstdio>
using namespace std;

//Funtion to right shift and array 
template<typename T>
void rightshift(T* array, int index, int& size) {
    for (int i = size; i > index; i--) {
        array[i + 1] = array[i];
    }
    size++;
}

//structure to store data in tree
struct data2 {
    int key;
    string f_name;
    int line;
    string year, cause, causename, state, deaths, age, rate;
};

//node of btree
template<typename T>
class node {
public:
    node<T>** children;     //children array
    T** data;               //data array containing the data of file line and and file name
    int degree;             //degree of tree
    int div;                //index of data array at which node will be split
    int num;                //curr number of keys in a node
    int min_keys;           //minimum number of keys
    bool leaf;              //true if a leaf node(no children)

    node() {                //default constructor
        children = nullptr;
        data = nullptr;
    }


    node(int degree, bool leaf = true) :degree(degree), div(ceil(degree / 2.) - 1), min_keys(ceil(degree / 2.) - 1), leaf(leaf), num(0) {      //Parametrized constructor
        //min is set to m/2. to make it a double value which will remove of extra zeros
        //leaf is true as every node is a leaf node at first

//array memory allocations
        children = new node < T >  *[degree + 1];
        data = new T * [degree];
    }


    node<T>* split(T*& elementup) {       //Function for splitting of the node of btres  
        node<T>* r = new node<T>(degree, leaf);

        elementup = data[div];
        data[div] = nullptr;

        for (int i = div + 1; i < num; i++) {
            r->data[i - div - 1] = data[i];
            data[i] = nullptr;
            r->num++;
        }
        num -= r->num + 1;


        if (!leaf) {        //if a node has children
            for (int i = div + 1; i <= degree; i++) {
                r->children[i - div - 1] = children[i];
                children[i] = nullptr;
            }

        }
        return r;
    }

    node<T>* insert(T* element, T*& elementup) {        //Funtion to insert a a new key
        //returns new child which is created as well as updates the                                  refrance for emelemtnup variable which will be the new parent                              incase of splitting

//finding position for element
        int i = 0;
        while (i<num && element->key > data[i]->key) {
            i++;
        }
        if (leaf) {
            rightshift < T* >(data, i, num);
            data[i] = element;

            if (num == degree) {                        //split needed
                return split(elementup);
            }
        }
        else {
            node<T>* r = children[i]->insert(element, elementup);
            if (r) {            //split needed in child, return index to be splitted on and the rigt branch of the new                        parent

                rightshift<T*>(data, i, num);
                data[i] = elementup;

                int j = num;
                rightshift<node<T>*>(children, i + 1, j);
                children[i + 1] = r;
                if (num == degree) {
                    return split(elementup);
                }
            }
        }
        elementup = nullptr;
        return nullptr;
    }

    T* search(int key) {          //funtion to search and return the file and line of a searched index
        int i = 0;
        while (i < num && key >= data[i]->key) {
            if (key == data[i]->key) {  //element found
                return data[i];
            }
            i++;
        }
        if (leaf) {
            return NULL;
        }
        else
            return children[i]->search(key);

    }

    void traverse(void(itemviewer)(T* data)) { //Funtion to tranverse through tree return in ascending order from left to                                            right
        for (int i = 0; i < num; i++) {
            //children present
            if (!leaf) {
                children[i]->traverse(itemviewer);
            }
            itemviewer(data[i]);
        }
        if (!leaf) {
            children[num]->traverse(itemviewer); //rightmost child
        }

    }

};

//class to create btree
template<typename T>
class btree {
public:
    int degree;         //degree of the tree
    node<T>* root;      //root node to be used later


    btree(int degree) :degree(degree) {     //constructor
        root = new node<T>(degree, true);
        root->min_keys = 1;
    }

    T* getroot() {
        return root;
    }
    void traverse(void(itemviewer)(T* data)) {  //passes callback every time it runs into child
        root->traverse(itemviewer);
    }


    void insert(vector<T*>el) {                 //insert a list of data
        for (T* elemnts : el) {
            insert(el);
        }
    }
    void insert(T* el) {   //overload instance of insert function 

        T* newparent = nullptr;
        node<T>* r = root->insert(el, newparent);
        if (r) {
            //new root
            node<T>* nR = new node<T>(degree, false);

            //data
            nR->data[0] = newparent;
            nR->num = 1;

            //children
            nR->children[0] = root;

            nR->children[1] = r;

            root = nR;
        }
    }

    T*& operator[](int key) {
        return root->search(key);
    }
    T* search(int key) {
        return root->search(key);
    }

};


void remove(node<data2>* obj, int temp_id) {            //removing record from given files

    int fl = 0;
    data2* temp1 = new data2;
    temp1 = obj->search(temp_id);
    if (temp1 == NULL) {
        cout << "Record not found";
    }
    else {
        cout << "Record is in the files named: " << temp1->f_name << " on line number " << temp1->line << ".\n";
        fstream file;
        fstream temp_f;
        string tempfilename = "temp.csv";

        temp_f.open(tempfilename, ios::out);
        file.open(temp1->f_name, ios::in | ios::app);
        vector<data2*> elements1;

        vector<string> row1;
        string line1, word1, temp2;

        row1.clear();


        getline(file, line1);       // store a row in a string variable 

        stringstream s1(line1);     // breaking words

        while (getline(s1, word1, ',')) {
            row1.push_back(word1);  //storing all the column elements of a row in word1
        }
        for (int i = 0; i < row1.size(); i++) {
            if (i == row1.size() - 1) {
                temp_f << row1[i] << "\n";
                break;

            }
            temp_f << row1[i] << ",";
        }

        while (!file.eof()) {
            fl++;
            row1.clear();

            getline(file, line1);   // store a row in a string variable 

            stringstream s1(line1); // breaking words


            if (temp1->line == fl) {
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
        const char* rename2 = temp1->f_name.c_str();
        remove(rename2);
        temp_f.close();
        fstream resultingfile;
        resultingfile.open(temp1->f_name, ios::out);
        temp_f.open(tempfilename, ios::in | ios::app);
        while (!temp_f.eof()) {
            row1.clear();

            getline(temp_f, line1);

            stringstream s1(line1); //breaking words

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


    }
}

void update(node<data2>* obj, int temp_id) {       //updating record in given files

    int fl = 0;
    data2* temp1 = new data2;
    temp1 = obj->search(temp_id);
    if (temp1 == NULL) {
        cout << "Record not found";
    }
    else {
        cout << "Record is in the files named: " << temp1->f_name << " on line number " << temp1->line << ".\n";
        fstream file;
        fstream temp_f;
        string tempfilename = "temp.csv";
        temp_f.open(tempfilename, ios::out);

        file.open(temp1->f_name, ios::in | ios::app);
        vector<data2*> elements1;

        vector<string> row1;
        string line1, word1, temp2;

        row1.clear();

        getline(file, line1);

        stringstream s1(line1);     //breaking words

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

        while (!file.eof()) {
            fl++;
            row1.clear();

            getline(file, line1);

            stringstream s1(line1);

            if (temp1->line == fl) {    //line matches

                string w, choice;
                temp_f << temp1->key << ",";
                cout << "Do you want to update year?(y/n): ";
                cin >> choice;
                if (choice == "y") {
                    cout << "Enter the new year: ";
                    cin >> w;
                    temp_f << w << ",";
                }
                else {
                    temp_f << temp1->year << ",";
                }
                cout << "Do you want to update cause113 field?(y/n): ";
                cin >> choice;
                if (choice == "y") {
                    cout << "Enter the new cause: ";
                    cin >> w;
                    temp_f << w << ",";
                }
                else {
                    temp_f << temp1->cause << ",";
                }
                cout << "Do you want to update cause name field?(y/n): ";
                cin >> choice;
                if (choice == "y") {
                    cout << "Enter the new causename: ";
                    cin >> w;
                    temp_f << w << ",";
                }
                else {
                    temp_f << temp1->causename << ",";
                }
                cout << "Do you want to update state field?(y/n): ";
                cin >> choice;
                if (choice == "y") {
                    cout << "Enter the new state: ";
                    cin >> w;
                    temp_f << w << ",";
                }
                else {
                    temp_f << temp1->state << ",";
                }
                cout << "Do you want to update Deaths field?(y/n): ";
                cin >> choice;
                if (choice == "y") {
                    cout << "Enter the new number of Deaths: ";
                    cin >> w;
                    temp_f << w << ",";
                }
                else {
                    temp_f << temp1->deaths << ",";
                }

                cout << "Do you want to update Age adjusted death rate field?(y/n): ";
                cin >> choice;
                if (choice == "y") {
                    cout << "Enter the new Age adjusted death rate: ";
                    cin >> w;
                    temp_f << w;
                }
                else {
                    temp_f << temp1->age;
                }
                temp_f << "\n";
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
        const char* rename2 = temp1->f_name.c_str();
        remove(rename2);
        temp_f.close();
        fstream resultingfile;
        resultingfile.open(temp1->f_name, ios::out);
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


    }
}


void find(node<data2>* obj, int sk) {   //Searching for record in given files
    int fl = 0;
    data2* temp1 = new data2;


    temp1 = obj->search(sk);
    if (temp1 == NULL) {
        cout << "Record not found";
    }
    else {
        cout << "Record is in the files named: " << temp1->f_name << " on line number " << temp1->line << ".\n";
        fstream file;
        file.open(temp1->f_name, ios::in);
        vector<data2*> elements1;

        vector<string> row1;
        string line1, word1, temp2;

        row1.clear();

        getline(file, line1);

        stringstream s1(line1);

        while (!file.eof()) {
            data2* index = new data2;
            fl++;
            row1.clear();
            getline(file, line1);

            stringstream s1(line1);
            if (temp1->line == fl) {

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
    }
}

node<data2>* read(string name, btree<data2> obj) {      //Creating btrees

    fstream fin;        // File pointer
    int f_line = 0;

    fin.open(name, ios::in);    // Open an existing file


    vector<data2*> elements;    //storing data in vector

    vector<string> row;         //reading data in form of string vector
    string line, word, temp;

    row.clear();

    getline(fin, line);         //reading a line of file and storing in variable line

    stringstream s(line);       //breaking words

    while (!fin.eof()) {
        data2* index = new data2;

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
        }
    }
    return obj.root;
}

//Operations using btree
int btreeops() {
    int choice;
    cout << "-> Press 1 to search a record.\n";
    cout << "-> Press 2 to update a record.\n";
    cout << "-> Press 3 to delete a record.\n";
    cout << "-> Press 4 to search a range of records.\n";
    cout << "-> Press 5 to update a range of records.\n";
    cout << "-> Press 6 to delete a range of records.\n";
    cout << "-> Press 7 to go back to main menu.\n";
    cin >> choice;
    return choice;
}
void makeBtree() {
    /***Declaring Btrees of degree 4***/
    btree<data2> obj1(4);
    btree<data2> obj2(4);
    btree<data2> obj3(4);
    btree<data2> obj5(4);
    btree<data2> obj6(4);
    btree<data2> obj7(4);
    btree<data2> obj8(4);
    btree<data2> obj9(4);
    btree<data2> obj10(4);


    /***Declaring paths of files***/
    string  name[2] = { "NCHS_-_Leading_Causes_of_Death__United_States_1.csv",
                        "NCHS_-_Leading_Causes_of_Death__United_States_8.csv"
    };

    /***Declaring temporary variables to store roots of files***/
    node<data2>* temp_root1;
    node<data2>* temp_root2;
    node<data2>* temp_root3;
    node<data2>* temp_root5;
    node<data2>* temp_root6;
    node<data2>* temp_root7;
    node<data2>* temp_root8;
    node<data2>* temp_root9;
    node<data2>* temp_root10;

    /***Creating Btrees of degree 4***/
    temp_root1 = read(name[0], obj1);
    temp_root2 = read(name[1], obj2);
    /*temp_root3 = read(name[2], obj3);
    temp_root5 = read(name[3], obj5);
    temp_root6 = read(name[4], obj6);
    temp_root7 = read(name[5], obj7);
    temp_root8 = read(name[6], obj8);
    temp_root9 = read(name[7], obj9);
    temp_root10 = read(name[8], obj10);*/
    int temp_id;    //temporary variable to store the id to perform avtion

    int btreeoperation = btreeops();
    while (btreeoperation != 7) {
      
      

        /*finding a record using btree*/
        if (btreeoperation == 1) {
            cout << "Enter the key of the element you want to search: ";
            cin >> temp_id;
            if (temp_id >= 1 && temp_id <= 50) {
                find(temp_root1, temp_id);

            }
            else if (temp_id >= 7111 && temp_id <= 7160) {
                find(temp_root2, temp_id);

            }
           /* else if (temp_id >= 2051 && temp_id <= 3116) {
                find(temp_root3, temp_id);

            }
            else if (temp_id >= 4041 && temp_id <= 5100) {
                find(temp_root5, temp_id);

            }
            else if (temp_id >= 4041 && temp_id <= 5100) {
                find(temp_root5, temp_id);

            }
            else if (temp_id >= 5101 && temp_id <= 6110) {
                find(temp_root6, temp_id);

            }
            else if (temp_id >= 6111 && temp_id <= 7100) {
                find(temp_root7, temp_id);

            }
            else if (temp_id >= 7111 && temp_id <= 8410) {
                find(temp_root8, temp_id);

            }
            else if (temp_id >= 8411 && temp_id <= 9500) {
                find(temp_root9, temp_id);

            }
            else if (temp_id >= 9501 && temp_id <= 10296) {
                find(temp_root10, temp_id);

            }*/
        }

        /*Updating a record using btree*/
        else if (btreeoperation == 2) {
            cout << "Enter the ID of the element you want to update: ";
            cin >> temp_id;
            if (temp_id >= 1 && temp_id <= 50) {
                update(temp_root1, temp_id);

            }
            else if (temp_id >= 7111 && temp_id <= 7160) {
                update(temp_root2, temp_id);

            }
            //else if (temp_id >= 2051 && temp_id <= 3116) {
            //    update(temp_root3, temp_id);

            //}
            //else if (temp_id >= 4041 && temp_id <= 5100) {
            //    update(temp_root5, temp_id);

            //}
            //else if (temp_id >= 4041 && temp_id <= 5100) {
            //    update(temp_root5, temp_id);

            //}
            //else if (temp_id >= 5101 && temp_id <= 6110) {
            //    update(temp_root6, temp_id);

            //}
            //else if (temp_id >= 6111 && temp_id <= 7100) {
            //    update(temp_root7, temp_id);

            //}
            //else if (temp_id >= 7111 && temp_id <= 8410) {
            //    update(temp_root8, temp_id);

            //}
            //else if (temp_id >= 8411 && temp_id <= 9500) {
            //    update(temp_root9, temp_id);

            //}
            //else if (temp_id >= 9501 && temp_id <= 10296) {
            //    update(temp_root10, temp_id);

            //}
            ////cout << "Record Updated Successfully! \n";

        }

        /*Deleting a record using btree*/
        if (btreeoperation == 3) {
            cout << "Enter the key of the element you want to delete: ";
            cin >> temp_id;
            if (temp_id >= 1 && temp_id <= 50) {
                remove(temp_root1, temp_id);

            }
            else if (temp_id >= 7111 && temp_id <= 7160) {
                remove(temp_root2, temp_id);

            }
            //else if (temp_id >= 2051 && temp_id <= 3116) {
            //    remove(temp_root3, temp_id);

            //}
            //else if (temp_id >= 4041 && temp_id <= 5100) {
            //    remove(temp_root5, temp_id);

            //}
            //else if (temp_id >= 4041 && temp_id <= 5100) {
            //    remove(temp_root5, temp_id);

            //}
            //else if (temp_id >= 5101 && temp_id <= 6110) {
            //    remove(temp_root6, temp_id);

            //}
            //else if (temp_id >= 6111 && temp_id <= 7100) {
            //    remove(temp_root7, temp_id);

            //}
            //else if (temp_id >= 7111 && temp_id <= 8410) {
            //    remove(temp_root8, temp_id);

            //}
            //else if (temp_id >= 8411 && temp_id <= 9500) {
            //    remove(temp_root9, temp_id);

            //}
            //else if (temp_id >= 9501 && temp_id <= 10296) {
            //    remove(temp_root10, temp_id);

            //}
            //// cout << "Record deleted Successfully! \n";
        }

        /*Searching a range of record using btree*/
        if (btreeoperation == 4) {
            int temp;
            cout << "Enter the starting key of the element you want to search: ";
            cin >> temp_id;
            cout << "Enter the ending key of the element you want to search: ";
            cin >> temp;
            while (temp_id <= temp) {
                if (temp_id >= 1 && temp_id <= 50) {
                    find(temp_root1, temp_id);

                }
                else if (temp_id >= 7111 && temp_id <= 7160) {
                    find(temp_root2, temp_id);

                }
             /*   else if (temp_id >= 2051 && temp_id <= 3116) {
                    find(temp_root3, temp_id);

                }
                else if (temp_id >= 4041 && temp_id <= 5100) {
                    find(temp_root5, temp_id);

                }
                else if (temp_id >= 4041 && temp_id <= 5100) {
                    find(temp_root5, temp_id);

                }
                else if (temp_id >= 5101 && temp_id <= 6110) {
                    find(temp_root6, temp_id);

                }
                else if (temp_id >= 6111 && temp_id <= 7100) {
                    find(temp_root7, temp_id);

                }
                else if (temp_id >= 7111 && temp_id <= 8410) {
                    find(temp_root8, temp_id);

                }
                else if (temp_id >= 8411 && temp_id <= 9500) {
                    find(temp_root9, temp_id);

                }
                else if (temp_id >= 9501 && temp_id <= 10296) {
                    find(temp_root10, temp_id);

                }*/
                temp_id++;
            }
        }

        /*Updating a range of record using btree*/
        else if (btreeoperation == 5) {
            int temp;
            cout << "Enter the starting key of the element you want to update: ";
            cin >> temp_id;
            cout << "Enter the ending key of the element you want to update: ";
            cin >> temp;
            while (temp_id <= temp) {
                if (temp_id >= 1 && temp_id <= 50) {
                    update(temp_root1, temp_id);

                }
                else if (temp_id >= 7111 && temp_id <= 7160) {
                    update(temp_root2, temp_id);

                }
                /*else if (temp_id >= 2051 && temp_id <= 3116) {
                    update(temp_root3, temp_id);

                }
                else if (temp_id >= 4041 && temp_id <= 5100) {
                    update(temp_root5, temp_id);

                }
                else if (temp_id >= 4041 && temp_id <= 5100) {
                    update(temp_root5, temp_id);

                }
                else if (temp_id >= 5101 && temp_id <= 6110) {
                    update(temp_root6, temp_id);

                }
                else if (temp_id >= 6111 && temp_id <= 7100) {
                    update(temp_root7, temp_id);

                }
                else if (temp_id >= 7111 && temp_id <= 8410) {
                    update(temp_root8, temp_id);

                }
                else if (temp_id >= 8411 && temp_id <= 9500) {
                    update(temp_root9, temp_id);

                }
                else if (temp_id >= 9501 && temp_id <= 10296) {
                    update(temp_root10, temp_id);

                }*/
                temp_id++;
            }
        }

        /*Deleting a range if record using btree*/
        if (btreeoperation == 6) {
            int temp;
            cout << "Enter the starting key of the element you want to update: ";
            cin >> temp_id;
            cout << "Enter the ending key of the element you want to update: ";
            cin >> temp;
            while (temp_id <= temp) {
                if (temp_id >= 1 && temp_id <= 50) {
                    remove(temp_root1, temp_id);

                }
                else if (temp_id >= 7111 && temp_id <= 7160) {
                    remove(temp_root2, temp_id);

                }
                /*else if (temp_id >= 2051 && temp_id <= 3116) {
                    remove(temp_root3, temp_id);

                }
                else if (temp_id >= 4041 && temp_id <= 5100) {
                    remove(temp_root5, temp_id);

                }
                else if (temp_id >= 4041 && temp_id <= 5100) {
                    remove(temp_root5, temp_id);

                }
                else if (temp_id >= 5101 && temp_id <= 6110) {
                    remove(temp_root6, temp_id);

                }
                else if (temp_id >= 6111 && temp_id <= 7100) {
                    remove(temp_root7, temp_id);

                }
                else if (temp_id >= 7111 && temp_id <= 8410) {
                    remove(temp_root8, temp_id);

                }
                else if (temp_id >= 8411 && temp_id <= 9500) {
                    remove(temp_root9, temp_id);

                }
                else if (temp_id >= 9501 && temp_id <= 10296) {
                    remove(temp_root10, temp_id);

                }*/
                temp_id++;
            }


        }
        btreeoperation = btreeops();
    }
}

