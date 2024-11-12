#include <iostream>
#include <memory_resource>
#include "src/MyMemoryResource.cpp"
#include "src/SinglyLinkedList.cpp"

struct ComplexType
{
    int id;
    std::string name;

    friend std::ostream &operator<<(std::ostream &os, const ComplexType &obj)
    {
        os << "{id: " << obj.id << ", name: " << obj.name << "}";
        return os;
    }
};

int main()
{
    MyMemoryResource memoryResource(SinglyLinkedList<ComplexType>::getNodeSize() * 3);

    SinglyLinkedList<ComplexType> complexList(&memoryResource);
    std::cout << "Hello, this is LAB5. Let's use ComplexType to test programm. Structure is: {id, name}\n";
    std::cout << "Now i'll push {1, Ann}, {2, Oleg}, {3, Vanya}\n";
    complexList.push_front({1, "Ann"});
    complexList.push_front({2, "Oleg"});
    complexList.push_front({3, "Vanya"});

    std::cout << "Now ComplexType list elements:\n";
    for (auto it = complexList.begin(); it != complexList.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "Size of it is: " << complexList.getSize() << std::endl;

    std::cout << "Now let's pop elements from list" << std::endl;

    while (!complexList.is_empty())
    {
        std::cout << "Popping: " << *complexList.begin() << std::endl;
        complexList.pop_front();
    }

    std::cout << "Now our list is empty. Size: " << complexList.getSize() << std::endl;

    return 0;
}