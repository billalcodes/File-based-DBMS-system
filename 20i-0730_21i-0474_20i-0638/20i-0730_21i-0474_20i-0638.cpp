// i200730_i210474_i200638 Final Project

#include <iostream>
#include"RBtrees.h"
#include"Btrees.h"
#include"AVL.h"
#include"LL.h"
using namespace std;

int treechoice() {
    int choice;
    cout << "-> Press 1 to work with RBtrees.\n";
    cout << "-> Press 2 to work with AVLtrees.\n";
    cout << "-> Press 3 to work with Btrees.\n";
    cout << "-> Press 4 to exit.\n";

    cin >> choice;
    return choice;
}
int main()
{
    cout << "\t\tWelcome To BSDB\n";
    cout << "\t\t***************\n";

    int treechoicemade = treechoice();
    while(treechoicemade!=4){
        if (treechoicemade == 1) {
            makeRBtrees();
        }
        else if (treechoicemade == 2) {
            //makeAVLtrees();
        }
        
        else if(treechoicemade==3) {
            makeBtree();
        }
        treechoicemade = treechoice();
    }

}

