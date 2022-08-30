Templates: Implementing Stack and Queue Containers
cs 2010 lab 5
Mitchell VanderHoek

Description:

    This program creates templates for the stack and queue abstract data types using a list. Templates allow
    functions and classes to operate with generic types, so a programmer doesn't have to rewrite a function 
    for different data types.


Usage:

    Compile the program using the makefile provided by typing "make" within the command line. The program will
    demonstrate a stack and queue differ in how data is accessed.

    The stack is a first-in last-out data structure while the queue is a first-in first-out data structure. For
    example, when the elements are added in the follow order: 
    
                            hello, there, General, Kenobi

    The elements are stored the same but the elements are accessed differently. Using the curr() function with
    the Queue will return "hello", the first element in the collection; however, using the curr() function will 
    return "Kenobi" if using the stack. This will also apply to which element is removed.

    A test is included to ensure that each template can use primitative types. This shows following the string
    output.

Compatibility:

    This was compiled using a g++ compiler and tested with GDB. The environment it was developed in was WSL 2.0
    running Ubuntu 20.14LTS. It includes the list, iostream and string headers. Provided are the header files
    for stack, queue and container. To use the templates from the provided headers, stack.cpp and queue.cpp must
    be included (where the templates are defined). A makefile is provided along with "make clean" functionality.