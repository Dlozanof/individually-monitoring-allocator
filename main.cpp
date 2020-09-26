#include "CustomAllocator/allocator.h"
#include <vector>
#include <iostream>
#include <string>
#include <scoped_allocator>
#include "Comms/IPC/Client.h"

int main()
{
    std::cout << "== Vector ==" << std::endl;
    std::vector<int> normalVector({1, 2, 3});
    std::vector<int, CustomAllocator<int>> myVector( {1, 2, 3}, (CustomAllocator<int>("Small Vector")) );
    myVector.push_back(2);
    for (int i = 0; i < 10; i++)
    {
        myVector.push_back(2);
    }

    std::cout << "== End Vector ==" << std::endl;

    typedef std::basic_string<char, std::char_traits<char>, CustomAllocator<char>> customAllocatorString;

    std::cout << "== String ==" << std::endl;
    
    customAllocatorString myString(CustomAllocator<char>("String"));
    for (int i = 0; i < 100; i++)
    {
        myString += "a";
    }
    std::cout << "== End String ==" << std::endl;

    /*using ipc_row = std::vector<int, CustomAllocator<int>>;
    using ipc_matrix = std::vector<ipc_row, std::scoped_allocator_adaptor<CustomAllocator<ipc_row>>>;
    ipc_matrix myMatrix{ {1}, {2} };*/


    
    return 0;

}