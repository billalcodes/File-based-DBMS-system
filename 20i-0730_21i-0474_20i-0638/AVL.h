#include <iostream>
#include <queue>
#include "LL.h"
#include "read.h"
#include<fstream>
using namespace std;
template <class T>
struct node {
public:
    int data;
    string charval;
    int height;
    node* left;
    node* right;
    LL<T>* list;
    




    node()
    {
        data = 0;
        left = NULL;
        right = NULL;
    }
    node(int data)
    {
        data = data;
        left = NULL;
        right = NULL;
    }
    node(string data)
    {
        charval = data;
        left = NULL;
        right = NULL;
    }
};



class AVL
{
private:

public:
    struct node* root;
    AVL() {
        this->root = NULL;

    }

    int calheight(node<string>* p) {




        if (p->left && p->right) {
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
        }


        else if (p->left && p->right == NULL) {
            return p->left->height + 1;
        }
        else if (p->left == NULL && p->right) {
            return p->right->height + 1;
        }


        return 0;

    }
    int Conversion(string iteratr)
    {
        int c = 0;
        for (int i = 0; i < iteratr.length(); i++)
        {
            char x = iteratr.at(i);
            c += int(x);
        }
        return c;
    }

    void LevelOrder(Node<string>* root)
    {
        if (root == NULL)
            return;

        //STL
        queue<Treenode<string>*> temp;
        Node<string>* T_Node;
        temp.push(root);
        temp.push(NULL);
        int j = root->height;



        for (j; j > 0; j--)
            cout << " ";



        while (temp.size() > 1)
        {
            int k = root->height;


            T_Node = temp.front();
            temp.pop();
            if (T_Node == NULL)



            {
                temp.push(NULL);
                cout << endl;
            }



            else {
                if (T_Node->left)
                    temp.push(T_Node->left);
                if (T_Node->right)
                    temp.push(T_Node->right);
                cout << T_Node->valstr << endl;
            }
            int i = j;
            for (j; i > 0; i--)
                cout << endl;
            j--;
        }

    }
    Node<string>* S_left(Node<string>* P)
    {
        Node<string>* P2;
        P2 = P->left;
        P->left = P2->right;
        P2->right = P;
        P->height = max(height(P->left), height(P->right)) + 1;
        P2->height = max(height(P2->left), P->height) + 1;
        return P2;
    }





    Node<string>* S_Right(Node<string>* P)
    {
        Node<string>* P2;

        P2 = P->right;
        P->right = P2->left;
        P2->left = P;
        P->height = max(height(P->left), height(P->right)) + 1;
        P2->height = max(height(P2->left), P->height) + 1;
        return n2;
    }



    Node<string>* R_Right(Node<string>* P)
    {




        P->right = S_left(P->right);
        return S_Right(n1);
    }

    Node<string>* doubleLeft(Node<string>* P)
    {

        P->left = S_Right(P->left);
        return S_left(P);
    }
    struct node* llrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp;
    }


    struct node* rrrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp;
    }


    struct node* rlrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        struct node* tp2;
        p = n;
        tp = p->right;
        tp2 = p->right->left;

        p->right = tp2->left;
        tp->left = tp2->right;
        tp2->left = p;
        tp2->right = tp;

        return tp2;
    }

    struct node* lrrotation(struct node* n) {
        struct node* p;
        struct node* tp;
        struct node* tp2;
        p = n;
        tp = p->left;
        tp2 = p->left->right;

        p->left = tp2->right;
        tp->right = tp2->left;
        tp2->right = p;
        tp2->left = tp;

        return tp2;
    }

    struct node* INSERT_DATA(struct node* r, int data){

        if (r == NULL) {
            struct node* n;
            n = new struct node;
            n->data = data ;
            


            r = n;
            r->left = r->right = NULL;
            r->height = 1;
            return r;
        }
        else {
            if (data < r->data) {
                r->left = INSERT_DATA(r->left, data);
            }

            else
                r->right = INSERT_DATA(r->right, data);
        }

        r->height = calheight(r);

        if (bf(r) == 2 && bf(r->left) == 1) {
            r = llrotation(r);
        }
        else if (bf(r) == -2 && bf(r->right) == -1) {
            r = rrrotation(r);
        }
        else if (bf(r) == -2 && bf(r->right) == 1) {
            r = rlrotation(r);
        }
        else if (bf(r) == 2 && bf(r->left) == -1) {
            r = lrrotation(r);
        }

        return r;

    }

    void levelorder_newline() {
        if (this->root == NULL) {
            cout << endl;
            cout << "Empty tree";
            cout << endl;
            return;
        }
        levelorder_newline(this->root);
    }

    void levelorder_newline(struct node* v) {
        queue <struct node*> q;
        struct node* cur;
        q.push(v);
        q.push(NULL);

        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur == NULL && q.size() != 0) {
                cout << "\n";

                q.push(NULL);
                continue;
            }
            if (cur != NULL) {
                cout << " " << cur->data << ",";
                

                if (cur->left != NULL) {
                    q.push(cur->left);
                }
                if (cur->right != NULL) {
                    q.push(cur->right);
                }
            }


        }
    }

    struct node* deleteNode(struct node* p, int data) {

        if (p->left == NULL && p->right == NULL) {
            if (p == this->root)
                this->root = NULL;
            delete p;
            return NULL;
        }

        struct node* t;
        struct node* q;
        if (p->data < data) {
            p->right = deleteNode(p->right, data);
        }
        else if (p->data > data ) {
            p->left = deleteNode(p->left, data);
        }
        else {
            if (p->left != NULL) {
                q = inpre(p->left);
                p->data = q->data;
               
            }
            else {
                q = insuc(p->right);
                p->data = q->data;
            }
        }

        if (bf(p) == 2 && bf(p->left) == 1) { p = llrotation(p); }
        else if (bf(p) == 2 && bf(p->left) == -1) { p = lrrotation(p); }
        else if (bf(p) == 2 && bf(p->left) == 0) { p = llrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == -1) { p = rrrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == 1) { p = rlrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == 0) { p = llrotation(p); }


        return p;
    }

    struct node* inpre(struct node* p) {
        while (p->right != NULL)
            p = p->right;
        return p;
    }

    struct node* insuc(struct node* p) {
        while (p->left != NULL)
            p = p->left;

        return p;
    }
    int Balance(Node<string>* n)
    {
        if (n->left && n->right) {
            return n->left->height - n->right->height;
        }
        else if (n->left && n->right == NULL) {
            return n->left->height;
        }
        else if (n->left == NULL && n->right) {
            return -n->right->height;
        }
    }




    void Inorder(Node<string>* temp)
    {
        if (temp != NULL)
        {
            Inorder(temp->left);
            cout << temp->val << " ";
            Inorder(temp->right);
        }

    }


    Node<string>* Del(Node<string>* root, int key)
    {
        Node<string>* temp = root;




        if (root == NULL)
            return root;



        if (temp->val > key)
        {
            temp->left = Del(temp->left, key);
        }


        else if (temp->val < key)
        {
            temp->right = Del(temp->right, key);
        }





        else
        {
            if ((temp->left == NULL) || (temp->right == NULL))
            {
                Node<string>* temp1 = temp->left ? temp->left : temp->right;
                if (temp1 == NULL)
                {
                    temp1 = temp;
                    temp = NULL;
                }
                else
                    *temp = *temp1;
                free(temp1);
            }


            else
            {
                Treenode<string>* temp1 = getMin(temp->right);
                temp->val = temp1->val;
                temp->right = Del(temp->right, temp1->val);
            }

        }




        if (temp == NULL)
            return temp;
        temp->height = max(height(temp->left), height(temp->right)) + 1;
        if (height(temp->right) - height(temp->left) == 2)
        {
            Node<string>* da;
            da = temp->right ? temp->right : temp->left;
            da = da->right ? da->right : da->left;
            if (temp->right->val < da->val)
                return S_Right(temp);
            else
                return R_Right(temp);
        }


        if (height(temp->left) - height(temp->right) == 2)
        {
            Node<string>* da;
            da = temp->left ? temp->left : temp->right;
            da = da->left ? da->left : da->right;
            if (temp->left->val > da->val)
                return S_left(temp);
            else
                return doubleLeft(temp);
        }



        return temp;
    }
    bool Searc(string KEY)
    {




        node<string>* charval = root;


        if (!root)
        {
            return false;
        }
        else
        {
            while (charval != NULL)
            {





                if (Conversion(KEY) == Conversion(temp->charval))
                {
                    return true;
                }
                else if (Conversion(KEY) > Conversion(charval->valstr))
                {
                    if (charval->right)
                    {
                        charval = charval->right;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (Conversion(KEY) < Conversion(charval->charval))
                {
                    if (charval->left)
                    {
                        charval = charval->left;
                    }
                    else
                    {
                        return false;
                    }
                }
                
                else
                {
                    return true;
                }
            }
        }
    }



    LL<string>* ADD(Node<string>* l, string data, char type)
    {
        fstream input;
        string line = "";
        int ID;
        int year;
        string causename113;
        string causename;
        string state;
        int deaths;
        double deathRate;

        // opening file
        // TAKE FILE NAME AS INPUT FROM USER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        string fileName;
        string tempstring;
        fstream fileName;
        // converting string into int use sstream
        stringstream inputString(line);
        cout << "Enter the name of file to perform action: " << endl;
        cin >> fileName;
        input.open(fileName);
        cout << "1. Enter for ID: " << endl;
        cout << "2. Enter for year: " << endl;
        cout << "3. Enter  for Causename " << endl;
        cout << "4. Enter for state: " << endl;
        cout << "5. Enter for deaths: " << endl;
        int option;
        cin >> option;

        LL<string>* d = new LL<string>;

        switch (option) {
        case 1:

        {

            getline(input, line);
            while (getline(input, line)) {

                string tempstring;

                // converting string into int use sstream
                stringstream inputString(line);



                getline(inputString, tempstring, ',');
                ID = atoi(tempstring.c_str());

                tempstring = "";
                getline(inputString, tempstring, ',');
                year = atoi(tempstring.c_str());
                tempstring = "";

                getline(inputString, causename113, ',');

                getline(inputString, causename, ',');

                getline(inputString, state, ',');


                getline(inputString, tempstring, ',');

                deaths = atoi(tempstring.c_str());

                tempstring = "";
                getline(inputString, tempstring, ',');
                deathRate = atof(tempstring.c_str());

                line = "";

                while (!fileName.eof()) {
                    if (ID == data)
                    {
                       d->INSERT_DATA(ID);
                        d->INSERT_DATA(year);
                        d->INSERT_DATA(causename113);
                        d->INSERT_DATA(causename);
                        d->INSERT_DATA(state);
                        d->INSERT_DATA(deaths);
                        d->INSERT_DATA(deathRate);
                        d->INSERT_DATA("\n");
                    }







                    getline(fileName, ID, ',');
                    getline(fileName, year, ',');
                    getline(fileName, causename113, ',');
                    getline(fileName, causename, ',');
                    getline(fileName, state, ',');
                    getline(fileName, deaths, ',');
                    getline(fileName, deathRate, '\n');
                }
            }
        }
        
            case 2:
            
           

            {

                getline(input, line);
                while (getline(input, line)) {

                    string tempstring;

                    // converting string into int use sstream
                    stringstream inputString(line);



                    getline(inputString, tempstring, ',');
                    ID = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    year = atoi(tempstring.c_str());
                    tempstring = "";

                    getline(inputString, causename113, ',');

                    getline(inputString, causename, ',');

                    getline(inputString, state, ',');


                    getline(inputString, tempstring, ',');

                    deaths = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    deathRate = atof(tempstring.c_str());

                    line = "";

                    while (!fileName.eof()) {
                        if (year == data)
                        {
                            ->INSERT_DATA(ID);
                            d->INSERT_DATA(year);
                            d->INSERT_DATA(causename113);
                            d->INSERT_DATA(causename);
                            d->INSERT_DATA(state);
                            d->INSERT_DATA(deaths);
                            d->INSERT_DATA(deathRate);
                            d->INSERT_DATA("\n");
                        }







                        getline(fileName, ID, ',');
                        getline(fileName, year, ',');
                        getline(fileName, causename113, ',');
                        getline(fileName, causename, ',');
                        getline(fileName, state, ',');
                        getline(fileName, deaths, ',');
                        getline(fileName, deathRate, '\n');
                    }
                }
            }
    
            case 3:
           

            {

                getline(input, line);
                while (getline(input, line)) {

                    string tempstring;

                    // converting string into int use sstream
                    stringstream inputString(line);



                    getline(inputString, tempstring, ',');
                    ID = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    year = atoi(tempstring.c_str());
                    tempstring = "";

                    getline(inputString, causename113, ',');

                    getline(inputString, causename, ',');

                    getline(inputString, state, ',');


                    getline(inputString, tempstring, ',');

                    deaths = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    deathRate = atof(tempstring.c_str());

                    line = "";

                    while (!fileName.eof()) {
                        if (causename == data)
                        {
                            d->INSERT_DATA(ID);
                            d->INSERT_DATA(year);
                            d->INSERT_DATA(causename113);
                            d->INSERT_DATA(causename);
                            d->INSERT_DATA(state);
                            d->INSERT_DATA(deaths);
                            d->INSERT_DATA(deathRate);
                            d->INSERT_DATA("\n");
                        }







                        getline(fileName, ID, ',');
                        getline(fileName, year, ',');
                        getline(fileName, causename113, ',');
                        getline(fileName, causename, ',');
                        getline(fileName, state, ',');
                        getline(fileName, deaths, ',');
                        getline(fileName, deathRate, '\n');
                    }
                }
            }
            case 4:
            

            {

                getline(input, line);
                while (getline(input, line)) {

                    string tempstring;

                    // converting string into int use sstream
                    stringstream inputString(line);



                    getline(inputString, tempstring, ',');
                    ID = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    year = atoi(tempstring.c_str());
                    tempstring = "";

                    getline(inputString, causename113, ',');

                    getline(inputString, causename, ',');

                    getline(inputString, state, ',');


                    getline(inputString, tempstring, ',');

                    deaths = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    deathRate = atof(tempstring.c_str());

                    line = "";

                    while (!fileName.eof()) {
                        if (deaths == data)
                        {
                            d->INSERT_DATA(ID);
                            d->INSERT_DATA(year);
                            d->INSERT_DATA(causename113);
                            d->INSERT_DATA(causename);
                            d->INSERT_DATA(state);
                            d->INSERT_DATA(deaths);
                            d->INSERT_DATA(deathRate);
                            d->INSERT_DATA("\n");
                        }







                        getline(fileName, ID, ',');
                        getline(fileName, year, ',');
                        getline(fileName, causename113, ',');
                        getline(fileName, causename, ',');
                        getline(fileName, state, ',');
                        getline(fileName, deaths, ',');
                        getline(fileName, deathRate, '\n');
                    }
                }
            }
            case 5:

            {

                getline(input, line);
                while (getline(input, line)) {

                    string tempstring;

                    // converting string into int use sstream
                    stringstream inputString(line);



                    getline(inputString, tempstring, ',');
                    ID = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    year = atoi(tempstring.c_str());
                    tempstring = "";

                    getline(inputString, causename113, ',');

                    getline(inputString, causename, ',');

                    getline(inputString, state, ',');


                    getline(inputString, tempstring, ',');

                    deaths = atoi(tempstring.c_str());

                    tempstring = "";
                    getline(inputString, tempstring, ',');
                    deathRate = atof(tempstring.c_str());

                    line = "";

                    while (!fileName.eof()) {
                        if (state == data)
                        {
                            d->INSERT_DATA(ID);
                            d->INSERT_DATA(year);
                            d->INSERT_DATA(causename113);
                            d->INSERT_DATA(causename);
                            d->INSERT_DATA(state);
                            d->INSERT_DATA(deaths);
                            d->INSERT_DATA(deathRate);
                            d->INSERT_DATA("\n");
                        }







                        getline(fileName, ID, ',');
                        getline(fileName, year, ',');
                        getline(fileName, causename113, ',');
                        getline(fileName, causename, ',');
                        getline(fileName, state, ',');
                        getline(fileName, deaths, ',');
                        getline(fileName, deathRate, '\n');
                    }
                }
            }
            return d;
            }

        }
         Node<string>* INSERT_data(Node<string>*& root, string data, char t1)
        {
            Node<string>* n = new Node<string>(data);
            Node<string>* temp = root;




            if (root == NULL)
            {
                root = n;
                ADD(temp, data, t1);
                return root;
            }


            else if (Conversion(data) < Conversion(temp->charval))
            {
                temp->left = INSERT_DATA(temp->left, data, t1);
                if (height(temp->left) - height(temp->right) == 2)

                    if (Conversion(data) >Conversion(temp->left->charval))
                        temp = llrotation(temp);
                    else
                        temp = doubleLeft(temp);
            }
            else if (Conversion(temp->charval) < Conversion(data))
            {
                temp->right = INSERT_DATA(temp->right, data, t1);
                if (height(temp->right) - height(temp->left) == 2)
                    if (Conversion(temp->right->charval) < Conversion(data))
                        temp = S_Right(temp);
                    else
                        temp = R_Right(temp);
            }
            else if (Conversion(temp->) == Conversion(data))
            {
                ADD(temp, data, t1);
            }

            temp->height = max(height(temp->left), height(temp->right)) + 1;
            return temp;
        }
        
        
        
    ~AVL() {

    }
};

void run_avl() {
    string file;

    cout << " Enter file name to run: " << endl;
    cin >> file;
    ifstream fileName;
    if (!fileName) {
        cout << " File not open" << endl;
    }

    string I = "ID";
    string yr = "year";
    string c113 = "causename113";
    string cas = "causename";
    string st = "state";
    string d = "death";
    string DR = "Death Rate";
    Node<string>* temp = new Node<string>;
    cout << I << "   " << yr << "/t/t/t/t" << c113 << "   /t/t" << cas << "/t/t" << d << "     " << DR << endl;

    Node<string>* te = new Node<string>;
    string str;
    getline(fileName, str);
    cout << str << endl;
    string ID, year, causename113, causename, state, death, deathRate;
    AVL t;
    cout << "1. Enter for ID: " << endl;
    cout << "2. Enter for year: " << endl;
    cout << "3. Enter  for Causename " << endl;
    cout << "4. Enter for state: " << endl;
    cout << "4. Enter for deaths: " << endl;
    int option;
    cin >> option;
    char input;
    switch (option)
    {
    case 1:
        input = 'i';
        break;
    case 2:
        input = 'y';
        break;
    case 3:
        input = 's';
        break;
    case 4:
        input = 'd';
        break;
    case 5:
        input = 'a';
        break;
    default:
        break;
    }
    string line;
    getline(fileName, line);
    while (getline(fileName, line)) {

        string tempstring;

        // converting string into int use sstream
        stringstream inputString(line);



        getline(inputString, tempstring, ',');
        ID = atoi(tempstring.c_str());

        tempstring = "";
        getline(inputString, tempstring, ',');
        year = atoi(tempstring.c_str());
        tempstring = "";

        getline(inputString, causename113, ',');

        getline(inputString, causename, ',');

        getline(inputString, state, ',');


        getline(inputString, tempstring, ',');

        death = atoi(tempstring.c_str());

        tempstring = "";
        getline(inputString, tempstring, ',');
        deathRate = atof(tempstring.c_str());

        line = "";
    }

    while (!fileName.eof()) {
        if (input == 'i')
            t.root = t.INSERT_data(t.root, ID, input);
        else if (input == 'y')
            t.root = t.INSERT_data(t.root, year, input);
        else if (input == 's')
            t.root = t.INSERT_data(t.root, causename, input);
        else if (input == 'd')
            t.root = t.INSERT_data(t.root, state, input);
        else if (input == 'a')
            t.root = t.INSERT_data(t.root, death, input);
        getline(file, ID, ',');
        getline(file, year, ',');
        getline(file, causename113, ',');
        getline(file, causename, ',');
        getline(file, state, ',');
        getline(file, death, ',');
        getline(file, deathRate, ',');

    }

}




















































































/*  Node<string>* getMin(Node<string>* r)
        {
            while (r->left != NULL) {
                r = r->left;
            }
            return r;
        }*/
        /*void PreOrderTraversal(Treenode<string>* temp)
        {

            if (temp != NULL)
            {
                cout << temp->val;
                cout << " ";
                PreOrderTraversal(temp->left);
                PreOrderTraversal(temp->right);
            }
        }
        void PostOrderTraversal(Treenode<string>* temp)
        {
            if (temp != NULL)
            {

                PostOrderTraversal(temp->left);
                PostOrderTraversal(temp->right);
                cout << temp->val << " ";
            }

        }*/