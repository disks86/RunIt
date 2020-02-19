//
// Created by cschaefer on 2/18/20.
//

#ifndef RUNIT_CODEALLOCATOR_H
#define RUNIT_CODEALLOCATOR_H

#include <limits>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #ifdef _WIN64
        #include <Windows.h>
        #include <Memoryapi.h>
    #else
        #include <Windows.h>
        #include <Memoryapi.h>
    #endif
#elif __APPLE__
    #include <sys/mman.h>
#elif __linux__
    #include <sys/mman.h>
#elif __unix__
    #include <sys/mman.h>
#elif defined(_POSIX_VERSION)
    #include <sys/mman.h>
#else
#   error "Unknown compiler"
#endif

template <class T>
class CodeAllocator
{
public:
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    template <class U>
    struct rebind
    {
        typedef CodeAllocator<U> other;
    };

    pointer address (reference value) const
    {
        return &value;
    }

    const_pointer address (const_reference value) const
    {
        return &value;
    }

    CodeAllocator() throw()
    {
    }

    CodeAllocator(const CodeAllocator&) throw()
    {
    }

    template <class U>
    CodeAllocator (const CodeAllocator<U>&) throw()
    {
    }

    ~CodeAllocator() throw()
    {
    }

    size_type max_size () const throw()
    {
        //TODO: figure out max.
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    pointer allocate (size_type number, const void* = 0)
    {
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            #ifdef _WIN64
                pointer returnValue = VirtualAlloc(nullptr, number*sizeof(T), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE | PAGE_EXECUTE);
            #else
                pointer returnValue = VirtualAlloc(nullptr, number*sizeof(T), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE | PAGE_EXECUTE);
            #endif
        #elif __APPLE__
        pointer returnValue = mmap(nullptr,number*sizeof(T), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);
        #elif __linux__
            pointer returnValue = mmap(nullptr,number*sizeof(T), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);
        #elif __unix__
            pointer returnValue = mmap(nullptr,number*sizeof(T), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);
        #elif defined(_POSIX_VERSION)
            pointer returnValue = mmap(nullptr,number*sizeof(T), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);
        #else
        #   error "Unknown compiler"
        #endif

        return returnValue;
    }

    void construct (pointer ptr, const T& value)
    {
        new((void*)ptr)T(value);
    }

    void destroy (pointer ptr)
    {
        ptr->~T();
    }

    void deallocate (pointer ptr, size_type number)
    {
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            #ifdef _WIN64
                VirtualFree(ptr, number*sizeof(T), MEM_RELEASE);
            #else
                VirtualFree(ptr, number*sizeof(T), MEM_RELEASE);
            #endif
        #elif __APPLE__
            munmap(ptr, number*sizeof(T));
        #elif __linux__
            munmap(ptr, number*sizeof(T));
        #elif __unix__
            munmap(ptr, number*sizeof(T));
        #elif defined(_POSIX_VERSION)
            munmap(ptr, number*sizeof(T));
        #else
                #   error "Unknown compiler"
        #endif
    }
};

template <class T1, class T2>
bool operator== (const CodeAllocator<T1>&,const CodeAllocator<T2>&) throw()
 {
    return true;
}

template <class T1, class T2>
bool operator!= (const CodeAllocator<T1>&,const CodeAllocator<T2>&) throw()
{
    return false;
}

#endif //RUNIT_CODEALLOCATOR_H
