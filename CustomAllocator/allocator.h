#ifndef BBA0470B_F3D3_40F2_B6A7_9A46206F4F33
#define BBA0470B_F3D3_40F2_B6A7_9A46206F4F33
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
//#include "../Comms/IPC/Client.h"
#include "../Comms/IClient.h"

#ifdef DEBUG_MEMORY
int g_memory_used{0};
extern IClient myClient;
#endif

template <typename T>
class CustomAllocator : public std::allocator<T>
{
    private:
        using Base = std::allocator<T>;
        using Pointer = typename std::allocator_traits<Base>::pointer;
        using SizeType = typename std::allocator_traits<Base>::size_type;
        std::string name_;
#ifdef DEBUG_MEMORY
        int l_memory_used{0};
#endif
    
    public:
        CustomAllocator() = delete;
        CustomAllocator(std::string name = "default") : name_(name) {}
        template <class U> CustomAllocator(CustomAllocator<U> const&) noexcept {}

        template <typename U>
        struct rebind
        {
            using other = CustomAllocator<U>;
        };

        Pointer allocate(SizeType n)
        {
#ifdef DEBUG_MEMORY
            g_memory_used += n * sizeof(T);
            l_memory_used += n * sizeof(T);
            std::cout << "[ " << std::setw(15)  << "Allocated" << " ]" <<
                std::right <<  std::setw(15) << (n * sizeof(T)) << " Bytes | " <<  
                "Local -> " << std::left << std::setw(15) << l_memory_used << " Bytes | " << 
                "Total -> " << std::left << std::setw(15) << g_memory_used << " Bytes | " << 
                name_ << std::endl;
            myClient.NewData(name_, true, l_memory_used, g_memory_used);
#endif
            return Base::allocate(n);
        }

        void deallocate(Pointer p, SizeType n)
        {
#ifdef DEBUG_MEMORY
            g_memory_used -= n * sizeof(T);
            l_memory_used -= n * sizeof(T);
            std::cout << "[ " << std::setw(15)  << "Deallocated" << " ]" <<
                std::right << std::setw(15) << (n * sizeof(T)) << " Bytes | " <<
                "Local -> " << std::left << std::setw(15) << l_memory_used << " Bytes | " << 
                "Total -> " << std::left << std::setw(15) << g_memory_used << " Bytes | " <<
                name_ << std::endl;
            myClient.NewData(name_, false, l_memory_used, g_memory_used);
#endif
            Base::deallocate(p, n);
        }
};

template <class T, class U>
bool
operator==(CustomAllocator<T> const&, CustomAllocator<U> const&) noexcept
{
    return true;
}

template <class T, class U>
bool
operator!=(CustomAllocator<T> const& x, CustomAllocator<U> const& y) noexcept
{
    return !(x == y);
}

// Macros
#define SINGLE_ARG(...) __VA_ARGS__

#define VECTOR(type, name) std::vector<type, CustomAllocator<type>> name(CustomAllocator<type>(#name));
#define VECTOR_P(type, name, params) std::vector<type, CustomAllocator<type>> name({params}, (CustomAllocator<type>(#name)) );
typedef std::basic_string<char, std::char_traits<char>, CustomAllocator<char>> customAllocatorString;
#define STRING(name, contents) customAllocatorString name({contents}, CustomAllocator<char>(#name));
#endif /* BBA0470B_F3D3_40F2_B6A7_9A46206F4F33 */
