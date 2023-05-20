#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "RBTree.h"

class Dictionary 
{
private:

    RBTree rbTree;

    bool isEnglishString(const std::string& str);
    bool isRussianString(const std::string& str);

public:
    void insert(const std::string& word, const std::string& translation);
    void search(const std::string& word);
    void removeKey(const std::string& word);
    void removeValue(const std::string& word, const std::string& translation);
    void printAllDictionary();
};

#endif 