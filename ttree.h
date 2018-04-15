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
    ttree(int maxDepth, int depth);
    ~ttree();

    void insert(string key);
    void search(string key);
    friend ostream& operator<< (std::ostream& os, ttree& tree);

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
    bool put(string key);
    int removeWord(string w);
    void clearWords();
    int commonPrefix(string o, string n);
    ttree* getNext();
    void setNext(ttree* t);
    bool wordsIsNull();
    bool nextIsNull();
    void display();
    friend ostream& operator << (ostream& os, tnode& t) {
        if(t.getWords() != nullptr)
        {
            auto it = t._words->begin();
            auto endIt = t._words->end();

            while (it != endIt) {
                os << " " << (*it);
                ++it;
            }
        }
        //os << endl;
        if(t._nextLevel != nullptr) os << *(t._nextLevel);
        return os;
    }
};


ttree::ttree() {
    _maxDepth = 5;
    _currentDepth = 1;
    _tnodes = new tnode[26];

}
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
    if (index < 0 )
        throw std::runtime_error("RIP IN PEACE IN PEACE");

    if(((_currentDepth+1) > _maxDepth) || key.length() == _currentDepth)
        _tnodes[index].put(key);
    else if (!(_tnodes[index].nextIsNull())) {
            _tnodes[index].getNext()->insert(key);
        }
    else
    {
        if(!_tnodes[index].insert(key, _currentDepth))
        {
            ttree* newLevel = new ttree(_maxDepth, _currentDepth + 1);
            list<string> oldWords = (*(_tnodes[index].getWords()));

            for (string s : oldWords)
            {
                newLevel->insert(s);
            }
            newLevel->insert(key);

            _tnodes[index].setNext(newLevel);
            _tnodes[index].clearWords();

        }
    }
}

ostream& operator << (std::ostream& os, ttree& tree)
{
    for(int i=0; i< 26; i++)
    {
        if (tree._tnodes[i].getWords() == nullptr && tree._tnodes[i].getNext() == nullptr)
        {

        }
        else
        {

            os << endl;

            for(int i=0; i < 3*(tree._currentDepth-1); i++) os << ' ';

            os << tree.toChar(i);

            os << tree._tnodes[i];
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
    return ((int) c) - (int)'A';
}
/**
 * Function ot return the int value of a letter.
 * @param i the int value of a character.
 * @return char representing the character number input.
 */
char ttree::toChar(int i) {
    return((char) (i+'A'));
}

ttree::~ttree() {

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
bool tnode::insert(string w, int level)
{
    //cout << "Level " << level << " insert" << endl;
    if(_words == nullptr && _nextLevel == nullptr)
    {
        put(w);
        return true;
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
        ++it;
    }

    put(w); //Insert the given data.
    return true;
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
    if (_words == nullptr) return;
    _words = nullptr;
}

/**
 * Accessor for the list of words.
 * @return memory address for the _words variable.
 */
list<string>* tnode::getWords() {
    return _words;
}

bool tnode::put(string key)
{
    //cout << "put" << endl;
    if(_words == nullptr)
    {
        _words = new list<string>;
        _words->push_back(key);
        return true;
    }
    auto it = _words->begin();
    auto endIt = _words->end();
    while(it != endIt)
    {
        if(key < ((*it)))
        {
            //cout << key << " is less than " << (*it) << endl;
            _words->insert(it, key);
            //cout << "Size: " << _words->size() << endl;
            return true;
        }

        ++it;
    }
    if(it == endIt)
    {
        _words->push_back(key);
        //cout << "Size: " << _words->size() << endl;
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
        else return count;
        ++i;
    }
    //cout << count << endl;
    return count;
}

void tnode::setNext(ttree* t) {
    _nextLevel = t;
}

/**
 * Method to obtain a pointer to the next level.
 * @return ttree pointer representing the next level.
 */
ttree* tnode::getNext() {
        return _nextLevel;
}

bool tnode::wordsIsNull()
{
    return (_words == nullptr);
}
bool tnode::nextIsNull(){
    return (_nextLevel == nullptr);
}
void tnode::display() {
    auto it = _words->begin();
    auto endIt = _words->end();

    while(it != endIt)
    {
        cout << (*it) << " ";
        ++it;
    }
}

tnode::~tnode() {
    delete _words;
}


#endif //DATASTRUCTURES_PROJECT4_TTREE_H
