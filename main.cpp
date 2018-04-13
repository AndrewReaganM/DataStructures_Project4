#include <iostream>
#include <string>
#include <list>

#include "ttree.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    ttree t = *new ttree();

    t.insert("HELLO");
}