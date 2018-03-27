#include <iostream>
#include <string>
#include <list>

using namespace std;
class tnode;
class ttree;

#ifndef DATASTRUCTURES_PROJECT4_TTREE_H
#define DATASTRUCTURES_PROJECT4_TTREE_H


class ttree {
private:
    tnode *_tnodes;
    int _maxDepth;
    int _currentDepth;
public:
    ttree();
    ttree(int maxDepth);
    ~ttree();

    void insert(string key);
    void search(string key);
    friend ostream& operator << (std::ostream& os, const ttree& tree);


    int toInt(char c);
    char toChar(int i);

};

ttree::ttree() {
    _maxDepth = 5;
    _currentDepth = 0;
    _tnodes = new tnode[26];

}
ttree::ttree(int maxDepth) {
    _maxDepth = maxDepth;
    _currentDepth = 0;
    _tnodes = new tnode[26];
}

void ttree::insert(string key) {

}

int ttree::toInt(char c) {
    return ((int) c) - 65;
}
char ttree::toChar(int i) {
    return((char) (i+65));
}
ttree::~ttree() {

}


#endif //DATASTRUCTURES_PROJECT4_TTREE_H
