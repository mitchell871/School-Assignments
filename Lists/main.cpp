/*
    Templates: Implementing Stack and Queue Containers
    cs2010 lab5
    Mitchell VanderHoek
    Purpose: Test whether stack and queue work. Both should be able to accept any elements that std::list 
             would be able to. Test the behavior of add, remove, curr and empty functions. 
*/

#include "stack.hpp"
#include "queue.hpp"
#include "container.hpp"
#include "queue.cpp"     // Included so template works.
#include "stack.cpp"     // Included so template works.
#include <iostream>
#include <string>

int main(){
    stack<int> dishes;
    stack<std::string> stack;
    Queue<std::string> queue;
    Queue<int> queueint;

    std::cout << "Stack: ";
    // Test stack functions are working and behaving properly.
    stack.add("hello");
    stack.add("there");
    stack.add("General");
    stack.add("Kenobi");
    while(!stack.empty()){
        std::cout << stack.curr() << " ";
        stack.remove();
    }
    std::cout << std::endl;

    // Test for whether more than just the string class works.
    dishes.add(1);
    std::cout << dishes.curr() << " ";
    std::cout << std::endl;

    // Test queue functions are working and behaving properly.

    std::cout << "Queue: ";
    queue.add("hello");
    queue.add("there");
    queue.add("General");
    queue.add("Kenobi");
    while(!queue.empty()){
        std::cout << queue.curr() << " ";
        queue.remove();
    }
    std::cout << std::endl;

    // Test for whether more than just the string class works.
    queueint.add(1);
    std::cout << queueint.curr() << " ";

    return 0;
}