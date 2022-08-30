/*
    Templates: Implementing Stack and Queue Containers
    cs2010 lab5
    Mitchell VanderHoek
    Purpose: Definitions for the stack template.
*/

#include "stack.hpp"

/*
    Adds an element to the stack.

    @param E element to be added to the stack.
*/
template<class E> 
void stack<E>::add (E val){
    Collection<E>::container.push_back(val);
}

/*
    The most recently added element is removed from the stack.
*/
template<class E> 
void stack<E>::remove(){ Collection<E>::container.pop_back();}

/*
    Returns a copy of the most recently added element of the stack.
*/
template<class E>
E stack<E>::curr(){return Collection<E>::container.back();}