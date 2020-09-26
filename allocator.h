#include <memory>
#include <iostream>
#include <iomanip>
#include <string>

int g_memory_used{0};

template <typename T>
class CustomAllocator : public std::allocator<T>
{
    private:
        using Base = std::allocator<T>;
        using Pointer = typename std::allocator_traits<Base>::pointer;
        using SizeType = typename std::allocator_traits<Base>::size_type;
        std::string name_;
    
    public:
        CustomAllocator() = default;
        template <class U> CustomAllocator(CustomAllocator<U> const&) noexcept {}

        template <typename U>
        struct rebind
        {
            using other = CustomAllocator<U>;
        };

        Pointer allocate(SizeType n)
        {
            g_memory_used += n * sizeof(T);
            std::cout << std::setw(15) << std::left << "[Allocated] " << std::right <<  std::setw(6) << (n * sizeof(T)) << " Bytes. Total -> " << g_memory_used << " Bytes" << std::endl;
            return Base::allocate(n);
        }

        void deallocate(Pointer p, SizeType n)
        {
            g_memory_used -= n * sizeof(T);
            std::cout << std::setw(15) << std::left << "[Deallocated]" << std::right << std::setw(6) << (n * sizeof(T)) << " Bytes. Total -> " << g_memory_used << " Bytes" << std::endl;
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