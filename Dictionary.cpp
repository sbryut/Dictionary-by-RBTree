#include "Dictionary.h"

bool Dictionary::isEnglishString(const std::string& str) 
{
    for (char ch : str) 
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) continue;
        else return false;
    }
    return true;
}

bool Dictionary::isRussianString(const std::string& str)
{
    for (char ch : str) 
    {
        if (ch >= 'À' && ch <= 'ß' || ch >= 'à' && ch <= 'ÿ' || ch == '¨' || ch == '¸') continue;
        else return false;
    }
    return true;
}

void Dictionary::insert(const std::string& word, const std::string& translation)
{
    if (isEnglishString(word) && isRussianString(translation))
        rbTree.insert(word, translation);
    else if (!isEnglishString(word))
        throw std::runtime_error("The entry '" + word + "' as a key is incorrect.");
    else
        throw std::runtime_error("The entry '" + translation + "' as a translation is incorrect.");
}

void Dictionary::search(const std::string& word)
{
    if (isEnglishString(word))
        rbTree.printOneKey(word);
    else
        throw std::runtime_error("The entry '" + word + "' as a key is incorrect.");
}

void Dictionary::removeKey(const std::string& word)
{
    if (isEnglishString(word))
        rbTree.remove(word);
    else
        throw std::runtime_error("The entry '" + word + "' as a key is incorrect.");
}

void Dictionary::removeValue(const std::string& word, const std::string& translation)
{
    if (isEnglishString(word) && isRussianString(translation))
        rbTree.deleteTranslation(word, translation);
    else if (!isEnglishString(word))
        throw std::runtime_error("The entry '" + word + "' as a key is incorrect.");
    else if (!isRussianString(translation))
        throw std::runtime_error("The entry '" + translation + "' as a translation is incorrect.");
}

void Dictionary::printAllDictionary() 
{
    rbTree.inOrder();
}