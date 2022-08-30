/*  
    Dictionary
    Author: Mitchell Vanderhoek
    CS2010 lab assignment2

    Purpose: This header file declares the common functions used by main.cpp and dictionary.cpp.
*/

#ifndef diction_hpp 
#define diction_hpp

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cctype>
#include <vector>
#include <locale>
#include <sstream>
#include <fstream>

typedef std::string MYWORD ;

/*
    Contains a word and its frequency.
*/
typedef struct Pair{

    int frequency; //Frequency count of a word.
    MYWORD word;     //The unique word.

}Pair;

/*
    The node for a binary search tree and doubly linked list.
*/
typedef struct Entry{

    Pair entry;
    struct Entry *leftChild;    //left sub-tree -- words less than
    struct Entry *rightChild;   //right sub-tree -- words greater than
    struct Entry *nextSibling;  //next sibiling  -- ascending order
    struct Entry *prevSibling; //prev sibiling

}Entry;

/*
    The dictionary has a maximum amount of entries.
*/
typedef struct Dictionary{
    int MAXENTRIES; //Maximum number of entries in the dictionary

    int numWords;              //Count of words in dictionary
    Entry *Words;              //Pointer to binary tree of words. AKA the Root
    Entry *wordLen;            //Pointer to entries in thread. AKA the Head.

}Dictionary;

// Arranged as their appear in dictionary.cpp to make it easier. Not including
// the static ones.


Entry *locateWord(Entry*, MYWORD);
bool insertWord(Dictionary&, MYWORD);
void deleteWord(Dictionary*,MYWORD);
void histogram(Dictionary*); 
std::istream& operator>>(std::istream&, MYWORD&);
void dumpList(Dictionary*);
bool fullDictionary(Dictionary&);
void rebuildList(Entry*, Dictionary*);
void dumpDictionary(Dictionary*);

#endif