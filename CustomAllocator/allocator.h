#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include "../Comms/IPC/Client.h"

int g_memory_used{0};

static IPCClient myClient;

template <typename T>
class CustomAllocator : public std::allocator<T>
{
    private:
        using Base = std::allocator<T>;
        using Pointer = typename std::allocator_traits<Base>::pointer;
        using SizeType = typename std::allocator_traits<Base>::size_type;
        std::string name_;
        int l_memory_used{0};
        
    
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
            g_memory_used += n * sizeof(T);
            l_memory_used += n * sizeof(T);
            std::cout << "[ " << std::setw(15)  << "Allocated" << " ]" <<
                std::right <<  std::setw(15) << (n * sizeof(T)) << " Bytes | " <<  
                "Local -> " << std::left << std::setw(15) << l_memory_used << " Bytes | " << 
                "Total -> " << std::left << std::setw(15) << g_memory_used << " Bytes | " << 
                name_ << std::endl;
            myClient.NewData(name_, true, l_memory_used, g_memory_used);
            return Base::allocate(n);
        }

        void deallocate(Pointer p, SizeType n)
        {
            g_memory_used -= n * sizeof(T);
            l_memory_used -= n * sizeof(T);
            std::cout << "[ " << std::setw(15)  << "Deallocated" << " ]" <<
                std::right << std::setw(15) << (n * sizeof(T)) << " Bytes | " <<
                "Local -> " << std::left << std::setw(15) << l_memory_used << " Bytes | " << 
                "Total -> " << std::left << std::setw(15) << g_memory_used << " Bytes | " <<
                name_ << std::endl;
            myClient.NewData(name_, false, l_memory_used, g_memory_used);
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

#ifdef DEBUG_MEMORY
#define VECTOR(type, name, params) std::vector<type, CustomAllocator<type>> name({params}, (CustomAllocator<type>(#name)) );
typedef std::basic_string<char, std::char_traits<char>, CustomAllocator<char>> customAllocatorString;
#define STRING(name, contents) customAllocatorString name({contents}, CustomAllocator<char>(#name));
#else
#define VECTOR(type, name, params) std::vector<type> name {params};
#define STRING(name, contents) std::string name {contents};
#endif