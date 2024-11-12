#include "../include/SinglyLinkedList.h"

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::pmr::memory_resource *resource) : head(nullptr), listSize(0), allocator(resource) {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    while (head)
    {
        pop_front();
    }
}
template <typename T>
void SinglyLinkedList<T>::push_front(const T &value)
{
    Node<T> *newNode = allocator.allocate(1);
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    ++listSize;
}

template <typename T>
void SinglyLinkedList<T>::pop_front()
{
    if (head)
    {
        Node<T> *temp = head;
        head = head->next;
        allocator.deallocate(temp, 1);
        --listSize;
    }
}

template <typename T>
bool SinglyLinkedList<T>::is_empty() const
{
    return head == nullptr;
}

template <typename T>
size_t SinglyLinkedList<T>::getSize() const
{
    return listSize;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator::reference SinglyLinkedList<T>::Iterator::operator*() const
{
    return current->data;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator::pointer SinglyLinkedList<T>::Iterator::operator->() const
{
    return &(current->data);
}

template <typename T>
typename SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
bool SinglyLinkedList<T>::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}

template <typename T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator &other) const
{
    return current != other.current;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin()
{
    return Iterator(head);
}

template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end()
{
    return Iterator(nullptr);
}
