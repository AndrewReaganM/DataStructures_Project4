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
    ttree(); //Default constructor

    ttree(int maxDepth, int depth); //Constructor that takes in a max level and current depth.

    ~ttree(); //Deletion method.

    void insert(string key); //Method to insert new elements.

    int search(string key); //Method to print elements matching the prefix 'key'.

    friend ostream &operator<<(std::ostream &os, ttree &tree); // ostream operator outputting the object.

    int toInt(char c); //Method that converts a UPPERCASE char to an int.

    char toChar(int i); //Method that converts an int value to an UPPERCASE char.

};


class tnode {
private:
    ttree *_nextLevel; // Pointer to the next level.
    list<string> *_words; //std::list of strings.
public:
    tnode(); //Default constructor for tnode.

    ~tnode(); //Deletion method for tnode.

    int findWord(string w); //Method to determine a word's presence in _words.

    bool insert(string w, int level); //Method that checks the validity of a given insert.

    list<string> *getWords(); //Returns the words given in a node.

    bool put(string key); //Method that inserts elements into _words in sorted order, and does not ask questions.

    int removeWord(string w); //Removes a given word from _words.

    void clearWords(); //Deletes elements from _words and sets equal to nullptr.

    int commonPrefix(string o, string n); // Determines the common prefix of two given words.

    ttree *getNext(); //Returns the _nextLevel variable.

    void setNext(ttree *t); //Sets the _netLevel variable.

    bool wordsIsNull(); // Determines if _words is nullptr.

    bool nextIsNull(); // Determines if _nextLevel is nullptr.

    void display(); //Displays all elements in _words.

    bool subSearch(string key); // Prints elements with prefixes matching the key.

    friend ostream &operator<<(ostream &os, tnode &t) { //ostream operator displaying _words.
        if (t.getWords() != nullptr) {
            auto it = t._words->begin();
            auto endIt = t._words->end();

            while (it != endIt) {
                os << " " << (*it);
                ++it;
            }
        }
        //os << endl;
        if (t._nextLevel != nullptr) os << *(t._nextLevel);
        return os;
    }
};
/**
 * Exception that is thrown if there is a general ttree exception.
 */
class ttreeException: public exception{
public:
    string what()
    {
        return "Error!";
    }
};
/**
 * Exception that is thrown if a search is unsuccessful.
 */
class ttreeNotFound: public exception{
public:
    string what(){
        return "not found";
    }
};

/**
 * Default Constructor for ttree.
 */
ttree::ttree() {
    _maxDepth = 5;
    _currentDepth = 1;
    _tnodes = new tnode[26];

}
/**
 * Constructor that specifies the maximum depth and the current depth.
 * @param maxDepth the maximum dept that the tree should reach.
 * @param depth the current depth that the tree is at.
 */
ttree::ttree(int maxDepth, int depth) {
    _maxDepth = maxDepth;
    _currentDepth = depth;
    _tnodes = new tnode[26];

}

/**
 * Insert method for the tree.
 * @param key the word to be inserted.
 */
void ttree::insert(string key) {
    if (_currentDepth > key.length()) throw std::runtime_error("RIP IN PEACE");

    int index = toInt(key.at(_currentDepth - 1));
    if (index < 0)
        throw std::runtime_error("RIP IN PEACE IN PEACE");

    if (((_currentDepth + 1) > _maxDepth) || key.length() == _currentDepth)
        _tnodes[index].put(key); //Inserts if in correct level.
    else if (!(_tnodes[index].nextIsNull())) {
        _tnodes[index].getNext()->insert(key); //Calls insert method on the next level, if it exists.
    } else {
        if (!_tnodes[index].insert(key, _currentDepth)) {
            ttree *newLevel = new ttree(_maxDepth, _currentDepth + 1);
            list<string> oldWords = (*(_tnodes[index].getWords()));

            for (string s : oldWords) {
                newLevel->insert(s);
            }
            newLevel->insert(key);

            _tnodes[index].setNext(newLevel);
            _tnodes[index].clearWords();

        }
    }
}
/**
 * ostream operator for ttree.
 * @param os the ostream object.
 * @param tree the ttree object to be output
 * @return the ostream containing the ttree, empty if no data.
 */
ostream &operator<<(std::ostream &os, ttree &tree) {
    for (int i = 0; i < 26; i++) {
        if (tree._tnodes[i].getWords() == nullptr && tree._tnodes[i].getNext() == nullptr) {// Do nothing :
        } else {
            os << endl;
            for (int i = 0; i < 3 * (tree._currentDepth - 1); i++) os << ' ';
            os << tree.toChar(i); // Outputs the level ID.
            os << tree._tnodes[i]; //Outputs the nodes.
        }
    }

    return os;
}

/**
 * Function to return the int value of a letter.
 * @param c a letter.
 * @return int representing the character input.
 */
int ttree::toInt(char c) {
    return ((int) c) - (int) 'A'; //Returns int
}

/**
 * Function to return the int value of a letter.
 * @param i the int value of a character.
 * @return char representing the character number input.
 */
char ttree::toChar(int i) {
    return ((char) (i + 'A')); //Returns char.
}
/**
 * The search method for ttree. This method searches for strings that match the
 * prefix specified by the key.
 * @param key the substring to be searched for.
 * @return
 */
int ttree::search(string key)
{
    //num of out
    int retVal = 0; //Tracks if something is output.
    if (_currentDepth < key.length()) //If not adequately deep, one step further.
    {
        int index = toInt(key.at(_currentDepth - 1));
        if(!_tnodes[index].nextIsNull()) retVal += _tnodes[index].getNext()->search(key);
        if(_tnodes[index].subSearch(key)) ++retVal;
    }
    else if(_currentDepth == key.length()) //If first adequate level, just return items at index.
    {
        int index = toInt(key.at(_currentDepth - 1));
        if(_tnodes[index].wordsIsNull() && _tnodes[index].nextIsNull())
        {
            //throw ttreeNotFound();
        }
        else {
            if ((!_tnodes[index].wordsIsNull())) {
                _tnodes[index].subSearch(key);
                ++retVal;
            }
            if (!_tnodes[index].nextIsNull()) retVal += _tnodes[index].getNext()->search(key);
        }
    }
    else //On further levels, output all tnodes.
    {
        for(int i=0; i < 26; i++)
        {
            if(_tnodes[i].wordsIsNull() && _tnodes[i].nextIsNull())
            {
                //throw ttreeNotFound();
            }
            else {
                if ((!_tnodes[i].wordsIsNull()))
                {
                    _tnodes[i].display();
                    ++retVal;
                }
                if (!_tnodes[i].nextIsNull()) retVal += _tnodes[i].getNext()->search(key);
            }
        }

    }
    if(retVal < 1 && _currentDepth == 1)
    {
        throw ttreeNotFound(); //Throws exception if nothing is output.
    }
    return retVal;

}
/**
 * Deletion method for ttree.
 */
ttree::~ttree() {
    // Nothing to be deleted.
}

/////////////////////////////////////////////////////////////////////////

/**
 * Default constructor for tnode.
 */
tnode::tnode() {
    _nextLevel = nullptr;
    _words = nullptr;
}

/**
 * This method adds words to the node.
 * @param w takes in word to add
 */
bool tnode::insert(string w, int level) {
    //cout << "Level " << level << " insert" << endl;
    if (_words == nullptr && _nextLevel == nullptr) {
        put(w);
        return true;
    }

    //Check Validity of Insert
    auto it = _words->begin();
    auto endIt = _words->end();

    while (it != endIt) {
        if (commonPrefix(w, (*it)) > level) {
            return false; //If prefix > current level, return false.
        }
        ++it;
    }

    put(w); //Insert the given data.
    return true; //Return true.
}

/**
 * Searches for an exact word.
 * @param w the word being searched for.
 * @return int representing method return status.
 */
int tnode::findWord(string w) {
    if (_words == nullptr) return -1;
    auto it = _words->begin();
    auto endIt = _words->end();

    while (it != endIt) {
        if ((*it) == w) {
            return 1; //Returns 1 if word exists.
        }
        ++it;
    }
    return -1; //Returns -1 if word does not exist.
}

/**
 * Fully clears the _words variable in the node.
 */
void tnode::clearWords() {
    if (_words == nullptr) return; //If already null, simply return.
    _words = nullptr; //Else set to null.
}

/**
 * Accessor for the list of words.
 * @return memory address for the _words variable.
 */
list<string> *tnode::getWords() {
    return _words; //returns _words.
}
/**
 * The method for instantiating _words and inserting string elements.
 * This method does not check the input for validity.
 * @param key string to be inserted.
 * @return a boolean indicating the success of the method.
 */
bool tnode::put(string key) {
    //cout << "put" << endl;
    if (_words == nullptr) {
        _words = new list<string>;
        _words->push_back(key);
        return true;
    }
    auto it = _words->begin();
    auto endIt = _words->end();
    while (it != endIt) {
        if (key < ((*it))) {
            _words->insert(it, key); //Insert at the correct position.
            return true;
        }

        ++it;
    }
    if (it == endIt) {
        _words->push_back(key);
        return true;
    }
    cout << "PUT FAILED" << endl;
    return false;
}

/**
 * Method that removes a given word from the list.
 * @param w string, word to be removed.
 * @return 0 if successful, -1 if unsuccessful or list empty.
 */
int tnode::removeWord(string w) {
    if (_words == nullptr) return -1;
    auto it = _words->begin();
    auto endIt = _words->end();

    while (it != endIt) {
        if ((*it) == w) {
            _words->erase(it); //Removes a given element.
            return 0;
        }
        ++it;
    }
    return -1;
}

/**
 * This method return the common prefix between two strings.
 * @param o the word to be compared
 * @param n another word to be compared
 * @return int representing the chars in common
 */
int tnode::commonPrefix(string o, string n) {
    int i = 0;
    int count = 0;

    while (i < o.length() && i < n.length()) {
        if (o.at(i) == n.at(i)) {
            ++count;
        } else return count; //Returns the common prefix determined.
        ++i;
    }
    return count; //Returns 0 if no common chars.
}
/**
 * Method that allows the next level to be set.
 * @param t ttree representing the next level to be set.
 */
void tnode::setNext(ttree *t) {
    _nextLevel = t; //Sets _nextLevel.
}

/**
 * Method to obtain a pointer to the next level.
 * @return ttree pointer representing the next level.
 */
ttree *tnode::getNext() {
    return _nextLevel; // Gets _getNext.
}
/**
 * Method for determining the status of _words.
 * @return boolean true if _words is null, false if _words is valid.
 */
bool tnode::wordsIsNull() {
    return (_words == nullptr);
}
/**
 * Method for determining the status of _nextLevel
 * @return boolean true if _nextLevel is null, false if _nextLevel is valid.
 */
bool tnode::nextIsNull() {
    return (_nextLevel == nullptr);
}
/**
 * Display method for tnode.
 * Displays the string objects within _words, space separated. Prints nothing if _words is empty.
 */
void tnode::display() {
    auto it = _words->begin();
    auto endIt = _words->end();

    while (it != endIt) {
        cout << (*it) << " "; //Displays the given element.
        ++it; // Increments the iterator.
    }
}
/**
 * Prints all string elements in _words if the prefix matches the key.
 * @param key string representing the prefix being searched for.
 * @return boolean representing the success of the operation.
 */
bool tnode::subSearch(string key) {
    if(_words == nullptr) return false;

    int len = key.length();
    bool track = false;

    auto it = _words->begin();
    auto endIt = _words->end();

    while (it != endIt) {
        if ((*it).substr(0, len) == key) {
            cout << (*it) << ' '; //Outputs values.
            track = true;

        }
        ++it;
    }
    return track;
}
/**
 * Deletion method for tnode.
 */
tnode::~tnode() {
    delete _words;
    delete _nextLevel;
}


#endif //DATASTRUCTURES_PROJECT4_TTREE_H
