#include <memory_resource>
#include <iterator>

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
class SinglyLinkedList
{
public:
    explicit SinglyLinkedList(std::pmr::memory_resource *resource = std::pmr::get_default_resource());
    ~SinglyLinkedList();

    void push_front(const T &value);
    void pop_front();
    bool is_empty() const;
    size_t getSize() const;

    class Iterator;
    Iterator begin();
    Iterator end();
    static size_t getNodeSize()
    {
        return sizeof(Node<T>);
    }

private:
    Node<T> *head;
    size_t listSize;
    std::pmr::polymorphic_allocator<Node<T>> allocator;
};

template <typename T>
class SinglyLinkedList<T>::Iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    Iterator() : current(nullptr) {}
    explicit Iterator(Node<T> *node) : current(node) {}

    reference operator*() const;
    pointer operator->() const;
    Iterator &operator++();
    Iterator operator++(int);
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;

private:
    Node<T> *current;
};