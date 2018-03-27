#include <iostream>
#include <string>
#include <list>

#include "ttree.h"
#include "tnode.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;


    ttree t = *new ttree();

    int i = t.toInt('Z');

    cout << i << endl;

    cout << t.toChar(i) << endl;
}