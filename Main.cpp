#include <iostream> 
#include <clocale>
#include <vector>
#include "Dictionary.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Dictionary dictionary;

    std::cout << "//TESTING THE DICTIONARY ON VALID VALUES//" << "\n\n";

    std::vector<std::pair<std::string, std::string>> words = {
        {"abject", "жалкий"},
        {"subdue", "подчинять"},
        {"avocado", "авокадо"},
        {"family", "фамильный"},
        {"subdue", "покорять"},
        {"family", "семья"},
        {"zealous", "ревностный"},
        {"cat", "кошка"},
        {"family", "содружество"},
        {"cat", "трактор"},
        {"family", "род"},
        {"abject", "презренный"},
        {"subdue", "подавлять"},
        {"abject", "низкий"},
        {"zealous", "рьяный"},
        {"abject", "несчастный"},
        {"family", "родовой"},
        {"zealous", "усердный"},
        {"abject", "униженный"}
    };

    dictionary.printAllDictionary();
    std::cout << "\n";

    for (const auto& pair : words) {
        try
        {
            dictionary.insert(pair.first, pair.second);
        }
        catch (std::exception& error) {
            std::cerr << "Exception caught: " << error.what() << "\n";
        }
    }

    std::cout << "Dictionary after adding words: \n";
    dictionary.printAllDictionary();
    std::cout << "\n";

    std::cout << "Meanings of the word 'abject': \n\n";
    try {
        dictionary.search("abject");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << '\n';
    }

    std::cout << "Let's delete a word 'family' from the dictionary. \n\n";
    try {
        dictionary.removeKey("family");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << '\n';
    }

    dictionary.printAllDictionary();
    std::cout << "\n";

    std::cout << "Let's remove the translation 'трактор' from the word 'cat' from the dictionary. \n\n";
    try {
        dictionary.removeValue("cat","трактор");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << '\n';
    }

    dictionary.printAllDictionary();
    std::cout << "\n";
    
    std::cout << "//TESTING THE DICTIONARY FOR INVALID VALUES//" << "\n\n";

    std::cout << "\nLet's insert the word '123456' into the dictionary. \n\n";
    try {
        dictionary.insert("123456", "недопустимый ключ");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << "\n\n";
    }

    std::cout << "\nLet's insert the word 'собака' as a key into the dictionary. \n\n";
    try {
        dictionary.insert("собака", "dog");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << "\n\n";
    }

    std::cout << "\nLet's find out the translations of the word '123456'. \n\n";
    try {
        dictionary.search("123456");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << "\n\n";
    }

    std::cout << "\nLet's delete a word '&()$@!' from the dictionary. \n\n";
    try {
        dictionary.removeKey("&()$@!");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << "\n\n";
    }

    std::cout << "\nLet's remove the translation 'трактор' from the word 'cat' from the dictionary. \n\n";
    try {
        dictionary.removeValue("cat", "трактор");
    }
    catch (std::exception& error) {
        std::cerr << "Exception caught: " << error.what() << "\n\n";
    }

    return 0;
}