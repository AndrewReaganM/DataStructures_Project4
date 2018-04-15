#include <iostream>
#include <string>
#include <list>

#include "ttree.h"

using namespace std;

int main() {
    char status = 'X';
    string keyword;
    ttree t = *new ttree();
    //cout << "### Autocorrect Tree ###" << endl;
    //cout << "# Please enter a valid command." << endl;
    while(cin >> status) {

        switch (status) {
            case 'I' :
                cin >> keyword;
                t.insert(keyword);
                break;
            case 'S' :
                //search
                break;
            case 'D' :
                cout << t;
                break;

        }
        //cout << "# Please enter a valid command." << endl;
    }




    /*
    t.insert("HELLO");
    t.insert("HAMS");
    t.insert("APRIL");
    t.insert("AMY");
    t.insert("KATIE");
    t.insert("KENNETH");
    t.insert("KATHERINE");
    t.insert("KAKE");
     */
}