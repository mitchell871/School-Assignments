/*
    Templates: Implementing Stack and Queue Containers
    cs2010 lab5
    Mitchell VanderHoek
    Purpose: This is the header file for the stack container.
*/

#ifndef stack_hpp
#define stack_hpp

#include "container.hpp"

template<class E> 
class stack : public Collection<E>{
    public: 
        void add(E val);
        void remove();
        E curr();        
};
#endif
