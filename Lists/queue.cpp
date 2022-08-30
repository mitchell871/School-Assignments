/*
    Templates: Implementing Stack and Queue Containers
    cs2010 lab5
    Mitchell VanderHoek
    Purpose: This is the definitions for the queue template.
*/

#include "queue.hpp"

/*
    Elements in a queue are added to the back of the list.

    @param E An element to add to the queue.
*/
template<class E> 
void Queue<E>::add(E val){
    Collection<E>::container.push_back(val);
}

/*
    Removes the first element in the queue.
*/
template<class E> 
void Queue<E>::remove(){ Collection<E>::container.pop_front();}

/*
    
    @return 
    Returns the first element in the queue. It does not affect the list.
*/
template<class E>
E Queue<E>::curr(){return Collection<E>::container.front();}
