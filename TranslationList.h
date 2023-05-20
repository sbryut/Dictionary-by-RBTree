#ifndef TRANSLATION_LIST_H
#define TRANSLATION_LIST_H

#include <iostream>
#include <iomanip>
#include <string>

class TranslationList
{
private:
    struct Node
    {
        std::string value_;
        Node* nextNode_;

        Node()
        {
            value_ = "";
            nextNode_ = nullptr;
        }

        Node(std::string value, Node* nextNode = nullptr)
        {
            value_ = value;
            nextNode_ = nextNode;
        }
    };

    Node* head_;
    Node* tail_;

    void insert(Node* newNode);
    bool search(Node* node);

public:
    TranslationList();
    ~TranslationList();
    TranslationList(const TranslationList& list);
    TranslationList(TranslationList&& list) noexcept;
    TranslationList& operator=(TranslationList&& list) noexcept;

    void swap(TranslationList& other) noexcept;
    bool isEmpty();
    void outAll();
    void insert(std::string value);
    void deleteNode(std::string value);
    bool search(std::string value);
};

#endif