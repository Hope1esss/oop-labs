#include "../include/SinglyLinkedList.h"

template <typename T>
SinglyLinkedList<T>::Iterator::Iterator(Node *node) : current(node) {}

template <typename T>
typename SinglyLinkedList<T>::Iterator::reference SinglyLinkedList<T>::Iterator::operator*() const
{
    return current->data;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator::pointer SinglyLinkedList<T>::Iterator::operator->() const
{
    return &current->data;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator &other) const
{
    return current != other.current;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::pmr::memory_resource *resource) : allocator(resource), head(nullptr), tail(nullptr) {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        allocator.deallocate(temp, 1);
    }
}

template <typename T>
void SinglyLinkedList<T>::push_back(const T &value)
{
    Node *new_node = allocator.allocate(1);
    allocator.construct(new_node, Node{value, nullptr});

    if (!head)
    {
        head = tail = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = new_node;
    }
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