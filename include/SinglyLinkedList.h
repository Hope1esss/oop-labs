#include <memory_resource>

template <typename T>
class SinglyLinkedList
{
public:
    struct Node
    {
        T data;
        Node *next;
    };

    class Iterator
    {
    private:
        Node *current;
    
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(Node *node);
        reference operator*() const;
        pointer operator->() const;
        Iterator& operator++();
        bool operator!=(const Iterator &other) const;
    };

    SinglyLinkedList(std::pmr::memory_resource *resource);
    ~SinglyLinkedList();

    void push_back(const T &value);
    Iterator begin();
    Iterator end();

private:
    std::pmr::polymorphic_allocator<Node> allocator;
    Node *head;
    Node *tail;

};
