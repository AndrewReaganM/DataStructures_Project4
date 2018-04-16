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
                cin >> keyword;
                try {
                    t.search(keyword);
                }
                catch(std::exception &e){
                    cout << e.what();
                }

                t.search(keyword);
                cout << endl; //???
                break;
            case 'D' :
                cout << t << endl;
                break;

        }
        //cout << "# Please enter a valid command." << endl;
        cout << endl;
    }
}