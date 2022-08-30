/*
    Templates: Implementing Stack and Queue Containers
    cs2010 lab5
    Mitchell VanderHoek
    Purpose: This is the header file for a container class. It has pure virtual functions
             for checking if empty, adding to the container, removing from the container
             and checking the current element of the list.
*/

#ifndef container_hpp
#define container_hpp

#include <list>

template <class E>  class Collection {

protected:
    std::list<E> container;     
public :
    virtual bool empty() { return container.empty();}
    virtual void add (E val) =0;
    virtual void remove () =0;
    virtual E curr() =0;
};

#endif