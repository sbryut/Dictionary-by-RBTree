#include "TranslationList.h"

void TranslationList::insert(Node* newNode)
{
    if (isEmpty())
    {
        head_ = newNode;
        tail_ = newNode;
        return;
    }

    if (this->search(newNode)) return;

    if (newNode->value_ < head_->value_)
    {
        newNode->nextNode_ = head_;
        head_ = newNode;
    }
    else
    {
        Node* helper = head_;

        while (helper != tail_)
        {
            if (helper->nextNode_->value_ > newNode->value_)
            {
                break;
            }
            helper = helper->nextNode_;
        }

        if (helper == tail_)
        {
            newNode->nextNode_ = nullptr;
            helper->nextNode_ = newNode;
            tail_ = newNode;
            return;
        }
        newNode->nextNode_ = helper->nextNode_;
        helper->nextNode_ = newNode;
    }
}

bool TranslationList::search(Node* node)
{
    Node* helper = head_;

    while (helper)
    {
        if (helper->value_ == node->value_)
        {
            return true;
        }
        helper = helper->nextNode_;
    }
    return false;
}

TranslationList::TranslationList() :
    head_(nullptr),
    tail_(nullptr)
{}

TranslationList::~TranslationList()
{
    Node* current = head_;
    while (current)
    {
        Node* toDelete = current;
        current = current->nextNode_;
        delete toDelete;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

TranslationList::TranslationList(const TranslationList& list)
{
    if (list.head_ == nullptr)
    {
        head_ = nullptr;
        tail_ = nullptr;
        return;
    }
    head_ = new Node(list.head_->value_);
    Node* srcPtr = list.head_->nextNode_;
    Node* destPtr = head_;
    while (srcPtr != nullptr)
    {
        destPtr->nextNode_ = new Node(srcPtr->value_);
        destPtr = destPtr->nextNode_;
        srcPtr = srcPtr->nextNode_;
    }
    tail_ = destPtr;
}


TranslationList::TranslationList(TranslationList&& list) noexcept :
    head_(list.head_),
    tail_(list.tail_)
{
    list.head_ = nullptr;
    list.tail_ = nullptr;
}

TranslationList& TranslationList::operator=(TranslationList&& list) noexcept
{
    if (this != &list)
    {
        swap(list);
    }
    return *this;
}

void TranslationList::swap(TranslationList& other) noexcept
{
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
}

bool TranslationList::isEmpty()
{
    return head_ == nullptr;
}

void TranslationList::outAll()
{

    if (isEmpty()) return;
    Node* helper = head_;
    while (helper)
    {
        std::cout << helper->value_;
        if (!helper->nextNode_) std::cout << " \n";
        else std::cout << ", ";
        helper = helper->nextNode_;
    }

    std::cout << '\n';
}

void TranslationList::insert(std::string value)
{
    Node* newNode = new Node(value);
    this->insert(newNode);
}

void TranslationList::deleteNode(std::string value)
{
    if (isEmpty())
    {
        return;
    }

    if (!this->search(value))
    {
        return;
    }

    if (head_->value_ == value)
    {
        Node* helper = head_;
        head_ = helper->nextNode_;
        delete helper;
        return;
    }

    if (tail_->value_ == value)
    {
        Node* helper = head_;
        while (helper->nextNode_ != tail_) helper = helper->nextNode_;
        delete tail_;
        helper->nextNode_ = nullptr;
        tail_ = helper;
        return;
    }
    Node* first = head_;
    Node* second = first->nextNode_;

    while (second && second->value_ != value)
    {
        first = first->nextNode_;
        second = second->nextNode_;
    }

    if (!second)
    {
        return;
    }
    else
    {
        first->nextNode_ = second->nextNode_;
        delete second;
    }
}


bool TranslationList::search(std::string value)
{
    Node* current = head_;
    while (current != nullptr)
    {
        if (current->value_ == value)
        {
            return true;
        }
        current = current->nextNode_;
    }
    return false;
}