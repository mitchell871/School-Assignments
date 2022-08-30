/*
    Templates: Implementing Stack and Queue Containers
    cs2010 lab5
    Mitchell VanderHoek
    Purpose: This is the header file for the queue container. 
*/

#ifndef queue_hpp
#define queue_hpp

#include "container.hpp"

template<class E> class Queue: public Collection<E>{
    public: 
        void add(E val);
        void remove();
        E curr();       
};

#endif




