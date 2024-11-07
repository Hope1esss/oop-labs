#include <iostream>
#include "src/MyMemoryResource.cpp"
#include "src/SinglyLinkedList.cpp"

struct ComplexType
{
    int id;
    std::string name;

    ComplexType(int id, const std::string &name) : id(id), name(name) {}
    friend std::ostream &operator<<(std::ostream &os, const ComplexType &obj)
    {
        os << "{id: " << obj.id << ", name: " << obj.name << "}";
        return os;
    }
};

int main()
{
    MyMemoryResource memoryResource;

    SinglyLinkedList<int> intList(&memoryResource);
    intList.push_back(10);
    intList.push_back(20);
    intList.push_back(30);

    std::cout << "Элементы intList: ";
    for (auto it = intList.begin(); it != intList.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    SinglyLinkedList<ComplexType> complexList(&memoryResource);
    complexList.push_back(ComplexType(1, "Alice"));
    complexList.push_back(ComplexType(2, "Bob"));
    complexList.push_back(ComplexType(3, "Charlie"));

    std::cout << "Элементы complexList: ";
    for (auto it = complexList.begin(); it != complexList.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
