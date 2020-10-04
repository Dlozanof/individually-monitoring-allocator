#include "CustomAllocator/allocator.h"
#include <vector>
#include <iostream>
#include <string>
#include <scoped_allocator>


int main()
{
    std::cout << "== Vector ==" << std::endl;
    VECTOR(int, myVector)
    //std::cout << myVector[1] << std::endl;
    myVector.push_back(2);
    for (int i = 0; i < 10; i++)
    {
        myVector.push_back(2);
    }

    std::cout << "== End Vector ==" << std::endl;

    std::cout << "== String ==" << std::endl;
    
    STRING(myString, "asdf")
    std::cout << myString << std::endl;
    for (int i = 0; i < 100; i++)
    {
        myString += "a";
    }
    std::cout << "== End String ==" << std::endl;

    STRING(myString2, "asdf")
    std::cout << myString << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        myString2 += "a";
    }

    STRING(myString3, "asdf")
    std::cout << myString << std::endl;
    for (int i = 0; i < 10000; i++)
    {
        myString3 += "a";
    }

    /*using ipc_row = std::vector<int, CustomAllocator<int>>;
    using ipc_matrix = std::vector<ipc_row, std::scoped_allocator_adaptor<CustomAllocator<ipc_row>>>;
    ipc_matrix myMatrix{ {1}, {2} };*/
    return 0;

}