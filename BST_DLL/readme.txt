Dictionary
cs2010 lab assignment 2
Author: Mitchell VanderHoek

Description:

    This program sorts unique words alphabetically into a binary search tree. If the word occurs more than
    once in a file then the dictionary will increment the frequency of the word, and once the reading of 
    the file is finished, the program will construct a sorted doubly-linked list from least frequent to 
    most frequent. 

    A word, or MYWORD, is a C++ style string. It contains only alphabetical characters(letters of the 
    alphabet) and ignores whether it is upper or lower-case.

Usage:

    A makefile is provided to compile the program and to clean out the .exe or .o files. Input is only
    read from a file that can be read by std::ifstream. To run the program the user must enter the 
    filename, including its path in the Linux filesystem with its extension, as the second argument.

    Make sure to have a .txt or other text file created and located before using this program. 

    Example to run the program so it reads a file from the current directory:

                                $./main ./readme.txt

    It should be noted that the ">>" operator for istream is overloaded. The operator will sanitize 
    input to be only alphabetical. When it encounters a non-alphabetical character, it considers it
    white-space. This replace the getNextWord function.

    Upon successful compilation and successfully running the program, file's contents will be read and
    will be sorted/sanitized as described earlier. The user will be presented with a menu of options. 
    Enter the character that corresponds to that menu option for the informationt to be displayed or
    to perform the task described. The user will then be brought back to the main menu where they'll
    be able to perform more tasks. 

    In the case of selecting the delete option. The user will need to enter the word for deletion Upon
    prompt. Successfulness is output to the console window, and the main menu is printed again. The user
    may terminate the program by selecting the last option.

    The maximum amount of unique words allowed for the dictionary, as defined by const int MAX is 50. 
    Frequency of occurance of that word will still be updated.

Compatibility:

    The program was created and tested in WSL2.0 from a Windows 11 PC. It was compiled using g++ (a 
    makefile is provided). A header file, diction.hpp, is provided. The diction.hpp file includes 
    string, iostream, iomanip, cstdio, cctype, vector, locale, sstream and fstream header files. There
    the function prototypes common to both .cpp files are declared, along with the declaration of the
    structs used in both files.

Acknowledgments or Possible Issues:

    The ">>" is overloaded for istream, so were the program to require inputs other than alphabetical 
    characters, then there'll be issues (I think).
    
    I could have probably added a way to change the maximum size of the dictionary, but for, as defined
    in main, it's 50.

    Reading from a new file or adding more words to the dictionary would have been a simple addition, 
    but there might be an issue with the ">>" operator being overloaded, and I don't know how to "force"
    it back to the default operator.