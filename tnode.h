#include <iostream>
#include <string>
#include <list>


using namespace std;

#ifndef DATASTRUCTURES_PROJECT4_TNODE_H
#define DATASTRUCTURES_PROJECT4_TNODE_H

class tnode;
class ttree;

class tnode {
private:
    ttree* _nextLevel;
    list<string> _words;
public:
    tnode();
    ~tnodes();
    friend ostream& operator << (ostream& os, const tnode& t);
};

tnode::tnode() {

}



#endif //DATASTRUCTURES_PROJECT4_TNODE_H
