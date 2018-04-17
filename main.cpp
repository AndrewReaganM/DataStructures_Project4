#include <iostream>
#include <string>
#include <list>

#include "ttree.h"

using namespace std;

int main() {
    char status = 'X';
    string keyword;
    ttree t = *new ttree();
    while(cin >> status) { //Takes in input

        switch (status) {
            case 'I' : // Input
                cin >> keyword;
                t.insert(keyword);
                break;
            case 'S' : //Searching
                cin >> keyword;
                try {
                    t.search(keyword);
                }
                catch(ttreeNotFound &e){
                    cout << e.what();
                }
                cout << endl << endl;
                break;
            case 'D' : //Full tree display.
                cout << t << endl;
                break;
        }
    }
    cout << endl;
}