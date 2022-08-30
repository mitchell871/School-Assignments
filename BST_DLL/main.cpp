/*  
    Dictionary
    Author: Mitchell Vanderhoek
    CS2010 lab assignment2

    Purpose: The main.cpp file is facilitates the adding of words to the dictionary. After adding words,
             it allows the user to delete words, view a histogram, see frequencies and alphabetized 
             words that exist in the dictionary. It captures inputs from the istream, sanitizes them, then
             adds the words.
             
*/

#include "diction.hpp"

const int MAX = 50; // Maximum number of words in the dictionary.
MYWORD word;        
Dictionary* mydictionary = new Dictionary{MAX, 0, 0, 0};

// Can't directly modify a global variable, so use a function to facilitate it.
Dictionary &getdictionary(){
    return *mydictionary;
}

int main(int argc, char *argv[]){
    MYWORD &wordToAdd = word;
    MYWORD wordToDelete, filename, choice; // choice is for the menu. 
    std::ifstream inFile;   // The operator here is overloaded.
    Dictionary *dictionary = mydictionary;
    Entry *changefreq;
    
    if(argc != 2){
        std::cout << "Not enough arguments.";
        exit(1);
    }

    filename = argv[1]; // This becomes the file name.

    // File where words are.
    inFile.open(filename);
    if(!inFile){
        std::cout << "unable to open text file: " << filename << ". Must be exact.";
        exit(1);
    }
    
    // Intake for words.
    while(inFile >> wordToAdd){
        if(wordToAdd.empty())
            continue;
        if(dictionary->numWords< dictionary->MAXENTRIES && insertWord(*dictionary, wordToAdd))
            std::cout << wordToAdd << "<< added\n";  
        
        else{
            // while numWord < MAX this is covered by insertWord. It avoid more operations.
            if((changefreq = locateWord(dictionary->Words, wordToAdd)) != nullptr ^ dictionary->numWords < MAX){
                changefreq->entry.frequency++;
                std::cout<< changefreq->entry.word << "'s frequency increased to " << changefreq->entry.frequency << std::endl;
            }else
                std::cout << "dictionary full." << std::endl;
        }
        changefreq = nullptr;    
        wordToAdd.clear();
    }
    rebuildList(dictionary->Words, dictionary); // Not so much a rebuild but more a create.
    inFile.close();
    
    /*
        Optional tasks can be perfomed. Mostly to make testing easier.
    */
    while(1){
        std::cout << "\n\nDictionary created from wordsfile.txt\n\n"
                  << "Main Menu.\n\n"
                  << "Choose an option: \n"
                  << "a. display words in order of frequency\n"
                  << "b. display words in alphabetic order\n"
                  << "c. display histogram\n"
                  << "d. delete word\n"
                  << "e. display number of unique words\n"
                  << "f. exit\n";

        std::cin >> choice;
        if(choice == "a"){
            std::cout << "\nFrequencies : \n";
            dumpList(dictionary);
        }
        else if(choice == "b"){
            std::cout << "\nWords: \n";
            dumpDictionary(dictionary);     
        }
        else if(choice == "c"){
            histogram(dictionary);  
        }
        else if(choice == "d"){
            std::cout << "\n\nWord to delete : ";
            std::cin >> wordToDelete;
            deleteWord(dictionary, wordToDelete); 
            wordToDelete.clear();
        }
        else if(choice == "e"){
            std::cout << "\nThere are: " <<dictionary->numWords
                      <<" in this dictionary. Maximum is: " 
                      << dictionary->MAXENTRIES << std::endl;  
        }
        else if(choice == "f"){
            std::cout << "\n\nThanks for using this dictionary\n";
            exit(1);
        }   

        std::cin.clear();
        choice.clear();
    }

    // Don't need to delete dictionary, OS can do that when program finishes. 
    
    return 0;
}