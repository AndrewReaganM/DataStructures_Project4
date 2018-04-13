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
    ttree(int maxDepth, int depthOffset);
    ~ttree();

    void insert(string key);
    void search(string key);
    friend ostream& operator << (std::ostream& os, const ttree& tree);


    int toInt(char c);
    char toChar(int i);

};

class tnode {
private:
    ttree* _nextLevel;
    list<string> *_words;
public:
    tnode();
    ~tnode();
    int findWord(string w);
    bool insert(string w, int level);
    list<string>* getWords();
    void put(string key);
    int removeWord(string w);
    void clearWords();
    int commonPrefix(string o, string n);
    ttree getNext();
    void setNext(ttree t);
    bool wordsIsNull();
    friend ostream& operator << (ostream& os, const tnode& t);
};


ttree::ttree() {
    _maxDepth = 5;
    _currentDepth = 1;
    _tnodes = new tnode[26];

}
ttree::ttree(int maxDepth, int depthOffset) {
    _maxDepth = maxDepth;
    _currentDepth = 1;
    _tnodes = new tnode[26];
}
/**
 * Insert method for the tree.
 * @param key the word to be inserted.
 */
void ttree::insert(string key) {
    ttree* newLevel;
    int index = toInt(key.at(_currentDepth - 1));
    if(_tnodes[index].wordsIsNull())
    {
        cout <<  "Next Level!" << endl;
        _tnodes[index].getNext().insert(key);
    }
    else
    {
        if(_tnodes[index].insert(key, _currentDepth) == false)
        {
            if((_currentDepth+1) > _maxDepth) _tnodes[index].put(key);

            else
            {
                newLevel = new ttree(_maxDepth, _currentDepth + 1);
                list<string> oldWords = (*(_tnodes[index].getWords()));

                auto iter = oldWords.begin();

                for(; iter != oldWords.end(); ++iter)
                {
                    newLevel->insert(*iter);
                }
                newLevel->insert(key);

                _tnodes[index].setNext(*newLevel);
                _tnodes[index].clearWords();
            }
        }
    }




}
/**
 * Function to return the int value of a letter.
 * @param c a letter.
 * @return int representing the character input.
 */
int ttree::toInt(char c) {
    return ((int) c) - 65;
}
/**
 * Function ot return the int value of a letter.
 * @param i the int value of a character.
 * @return char representing the character number input.
 */
char ttree::toChar(int i) {
    return((char) (i+65));
}

ttree::~ttree() {

}

/////////////////////////////////////////////////////////////////////////

/**
 * Default constructor for tnode.
 */
tnode::tnode() {
    _nextLevel = NULL;
    _words = NULL;
}

/**
 * This method adds words to the node.
 * @param w takes in word to add
 */
bool tnode::insert(string w, int level)
{
    if (_words == NULL) {
        _words = new list<string>(); //Initialize the list.
        _words->push_back(w);
    }
    //Check Validity of Insert
    auto it = _words->begin();
    auto endIt = _words->end();

    while (it != endIt)
    {
        if (commonPrefix(w, (*it)) > level)
        {
            return false;
        }
    }
    if (_words == NULL) {
        _words = new list<string>(); //Initialize the list.
    }

    it = _words->begin();
    auto nextIt = _words->begin();
    ++nextIt;

    put(w); //Insert the given data.
    return true;
}
/**
 * Searches for an exact word.
 * @param w the word being searched for.
 * @return int representing method return status.
 */
int tnode::findWord(string w) {
    if (_words == NULL) return -1;
    auto it = _words->begin();
    auto endIt = _words->end();
    //--endIt;

    while(it != endIt)
    {
        if((*it) == w)
        {
            return 1;
        }
        ++it;
    }
    return -1;
}
/**
 * Fully clears the _words variable in the node.
 */
void tnode::clearWords() {
    if (_words == NULL) return;
    delete _words;
    _words = NULL;
}

/**
 * Accessor for the list of words.
 * @return memory address for the _words variable.
 */
list<string>* tnode::getWords() {
    return _words;
}

void tnode::put(string key)
{
    auto it = _words->begin();
    auto endIt = _words->end();
    while(it != endIt)
    {
        if(!((*it)< key))
        {
            _words->insert(it, key);
        }
        ++it;
    }
}

/**
 * Method that removes a given word from the list.
 * @param w string, word to be removed.
 * @return 0 if successful, -1 if unsuccessful or list empty.
 */
int tnode::removeWord(string w) {
    if (_words == NULL) return -1;
    auto it = _words->begin();
    auto endIt = _words->end();

    while(it != endIt)
    {
        if((*it) == w)
        {
            _words->erase(it);
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

    while(i < o.length() && i < n.length())
    {
        if(o.at(i) == n.at(i))
        {
            ++count;
        }
        ++i;
    }
    return count;
}

void tnode::setNext(ttree t) {
    _nextLevel = &t;
}

/**
 * Method to obtain a pointer to the next level.
 * @return ttree pointer representing the next level.
 */
ttree tnode::getNext() {
        return *_nextLevel;
}

bool tnode::wordsIsNull()
{
    return (_words != NULL);
}

tnode::~tnode() {
    delete _words;
}


#endif //DATASTRUCTURES_PROJECT4_TTREE_H
