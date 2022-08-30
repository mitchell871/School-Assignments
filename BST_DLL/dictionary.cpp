/*  
    Dictionary
    Author: Mitchell Vanderhoek
    CS2010 lab assignment2

    Purpose: To create a dictionary that is sorted alphabetically in a binary tree. Then uses a doubly
             linked list to sort, by frequency, the frequencies of a unique words in the dictionary. It
             defines the shared functions and declares locally used helper functions.
*/

#include "diction.hpp"

// Function prototypes exclusive to dictionary.cpp. Intended to be used as helper functions.

static Entry *addToTree(Entry*, MYWORD);
static void addToList(Entry*, int, Dictionary*);
static Entry *deleteLeaf(Entry*, MYWORD, Dictionary*);
static void deleteList(Entry*, Dictionary*);
static void inOrderTraversal(Entry*);


/*  
    Determines if the dictionary contains the word. If found, it will return a pointer. If the
    word is not found then it will return nullptr. 

    @param Entry* Words -- the root of the dictionary.
    @param Word word to look for in dictionary.
    @return Entry*  Entry containing the word. nullptr if not found.

*/
Entry *locateWord(Entry *root, MYWORD wordToFind){

    // Returns null if the word wasn't found.
    if(root == nullptr || root->entry.word == wordToFind){
        return root;
    }

    // The word being searched for is greater than root's word.
    if(root->entry.word < wordToFind){
        return locateWord(root->rightChild, wordToFind);
    }

    // The word being searched for is less than root's word.
    return locateWord(root->leftChild, wordToFind);
}

/*
    Add a unique word to the dictionary. Doesn't add words to the DLL until all words have been added to tree.

    @param Dictionary&  Dictionary location.
    @param Word     Candidate word. 
    @return bool    If the candidate word was unique and added to the dictionary.

*/
bool insertWord(Dictionary &dictionary, MYWORD wordCandidate){
    Entry *temporary = nullptr; // The memory is already alocated.
    bool success = false;

    temporary = addToTree(dictionary.Words, wordCandidate);
    // Root condition.
    if(dictionary.Words == nullptr){
        dictionary.Words = temporary;
        success = true;
    }    
    // Update the number of unique entries in the tree.
    else if(dictionary.numWords < dictionary.MAXENTRIES && temporary->entry.word != wordCandidate){
        dictionary.numWords++;  
        success = true;    
    }
    // When duplicate.
    if(temporary->entry.frequency >= 1)
        success = false;

    temporary = nullptr;
        
    return success;
}

/*
    Dumps the dictionary.
    @param Dictionary* dictionary to print.
*/
void dumpDictionary(Dictionary* dictionary){
    inOrderTraversal(dictionary->Words);
}

/*  
    If it doesn't exist then error message displayed. Deletes in DLL then in BST.

    @param MYWORD word to be deleted from list. 
    @param Dictionary* dictionary where the word exists.
*/
void deleteWord(Dictionary* dictionary, MYWORD wordToDelete){

    if(locateWord(dictionary->Words, wordToDelete)!=nullptr){
        deleteLeaf(dictionary->Words, wordToDelete, dictionary);
        std::cout << wordToDelete <<" deleted.\n";  
    }else{
        std::cout << "Word not deleted or doesn't exist.\n";
    }
}

/*
    @param Entry* The node to be deleted for the list.
*/
static void deleteList(Entry* node, Dictionary* dictionary){
    
    // Avoid deleting a nullptr.
    if(dictionary->wordLen == nullptr)
        return;
    if(dictionary->wordLen == node){
        dictionary->wordLen == node->nextSibling;
    }
    // Set forward node.
    if(node->nextSibling!= nullptr){
        node->nextSibling->prevSibling = node->prevSibling;
    }
    // Set previous node.
    if(node->prevSibling != nullptr){
        node->prevSibling->nextSibling = node->nextSibling;
    }
    // Will delete the memory with deleteLeaf
}

/*
    Recursively navigates a tree to delete the node. If you are returned the Entry* that was entered as
    the parameter then it wasn't deleted. If the word wasn't deleted from the DLL then it'll display as
    0, in some cases, when calling dumpList.

    @param Entry*   The node to be terminated.
    @param MYWORD   Word to be deleted.
    @param Dictionary* The dictionary for which the word, if it exists, is being deleted from.
    @return Entry*      
*/
static Entry *deleteLeaf(Entry *root, MYWORD wordToDelete, Dictionary* dictionary){

    // Base case for recursion. Also covers cases of someone using this with dictionary with no root.
    if(root == nullptr){
        return root;
    }

    // Leaf node cases.
    // If word of entry is after the word to delete then go to left child.
    if(root->entry.word > wordToDelete){
        root->leftChild = deleteLeaf(root->leftChild, wordToDelete, dictionary);
        return root;
    }
    // If word of entry is before the word to delete then go to right child.
    else if(root->entry.word < wordToDelete){
        root->rightChild = deleteLeaf(root->rightChild, wordToDelete, dictionary);
        return root;
    }

    // If a child entry is empty.
    if(root->leftChild == nullptr){    // Left child case.
        Entry* temporary = root->rightChild;
        // Delete in list.
        deleteList(root, dictionary);
        dictionary->numWords--;
        delete root;      // Return the memory or the OS gets mad.
        root = nullptr;  
        return temporary;
    }
    else if(root->rightChild == nullptr){ // Right child case.
        Entry* temporary = root->leftChild;
        // Delete in list.
        deleteList(root, dictionary);
        dictionary->numWords--;
        delete root;                   // Free memory.
        root = nullptr;
        return temporary;
    }
    // If both children exist then the Entry(parent) + the children are deleted.
    else{

        Entry *king = root;
        Entry *heir = root->rightChild; // Find an heir.

        while(heir->leftChild != nullptr){
            king = heir;        
            heir = heir->leftChild;
        }
        
        (king != root) ? king->leftChild = heir->rightChild : king->rightChild = heir->rightChild;

        root->entry = heir->entry; // Copy the successor's data.

        // In this case. I'll need to delete what was the heir.
        // Delete the heir.
        dictionary->numWords--;
        deleteList(heir, dictionary);   // Adjust the list.
        delete heir;
        heir = nullptr;

        return root;
    }
}

/*  
    Add word to tree.
    @param Entry* node to begin moving through tree at.
    @param Word   candidate word for whether it's added to tree.
    @return the node that was added. A entry of the dictionary that didn't exist before will
            have 0 as the entry's frequency.
*/
static Entry *addToTree(Entry *node, MYWORD wordCandidate){

    // The root. This Entry becomes *Words.
    if(node == nullptr){
        //dictionary->numWords++;
        return new Entry{{1,wordCandidate}, 0, 0, 0, 0};
    }
    // if the given key is less than the root node, recur for the left subtree
    if (wordCandidate < node->entry.word) {
        node->leftChild = addToTree(node->leftChild, wordCandidate);    
    }
    // if the given key is more than the root node, recur for the right subtree
    else if (wordCandidate > node->entry.word) {
        node->rightChild = addToTree(node->rightChild, wordCandidate);
            
    }
    // the word isn't unique.
    else{
        node->entry.frequency++;   
    }

    return node;
}

/*
    Since the binary tree has accounted for all the duplicates, the list can be created here. Organizes the
    frequencies from least to greatest.

    @param Entry* This must the node that has the word and its frequency in the binary tree. 
    @param int frequency to look for
    @param Dictionary* dictionary to find the value in.
*/
static void addToList(Entry *node, int frequency, Dictionary *dictionary){
    Entry *current; // Used for navigating the list.
    
    // Root condition.
    if(dictionary->wordLen == nullptr )
        dictionary->wordLen = node;
    else if (dictionary->wordLen->entry.frequency > node->entry.frequency){
        node->nextSibling = dictionary->wordLen;
        node->nextSibling->prevSibling = node;
        dictionary->wordLen = node;
    }
    else{
        current = dictionary->wordLen;

        while(current->nextSibling != nullptr 
        && current->nextSibling->entry.frequency < node->entry.frequency){
            current = current->nextSibling;
        }
        node->nextSibling = current->nextSibling;

        if(current->nextSibling != nullptr)
            node->nextSibling->prevSibling = node;
        
        current->nextSibling = node;
        node->prevSibling = current;

         // This node already exists, so current doesn't need to point anymore.
    }    
     
}


/*
    Displays elements in alphabetical order and the histogram of their frequencies. The doubly-linked list must exist before
    it is called to avoid a segmentation fault.

    @param Entry   
*/
void histogram(Dictionary* dictionary){
    Entry* current; // Current node.
    Entry* pre;     // Previous node.
    int maxfreq = 0;    // Tail
    int maxLength = 0;
    int row;
    int emptyspace;

    // If the dictionary has no words then there's no point in showing. Will also cause several segmentation faults.
    if(dictionary->Words == nullptr){
        std::cout << "\nDictionary is empty!\n";
        return;
    }

    // Find the word with the highest frequency. Will cause segmentation fault if wordLen hasn't been initialized.
    current = dictionary->wordLen;
    while(current != nullptr){
        if(current->entry.frequency > maxfreq)
            maxfreq = current->entry.frequency;
        if(current->entry.word.length() > maxLength)
            maxLength = current->entry.word.length();
        current = current->nextSibling;
    }
    
    // Title splash.
    std::cout << "\n";
    std::cout << "Histogram:\n\n";

    
    row = maxfreq;  // Row begins at highest frequency until 0. 

    /*
        Performs an inorder Morris Traversal. If I added two more pointers then I could create a threaded BST with a DLL which would be
        optimal.
    */
    while(row>0){
        current = dictionary->Words;
        
        while(current!= nullptr){

            if(current->leftChild == nullptr){

                if(current->entry.frequency >= row)
                    std::cout << " * ";
                else    
                    std::cout << "   ";  

                current = current->rightChild;
            }
            else{
                // Find inorder predecessor. 
                pre = current->leftChild;
                while(pre->rightChild != nullptr && pre->rightChild != current){
                    pre = pre->rightChild;
                }
                // Current made rightchild 
                if(pre->rightChild == nullptr){
                    pre->rightChild = current;
                    current = current->leftChild;
                }
                // Restore changes.
                else{
                    pre->rightChild = nullptr;
                    if(current->entry.frequency >= row)
                        std::cout << " * ";
                    else    
                        std::cout << "   ";     
                    current = current->rightChild;
                }
            }   
        }
        
        row--; // go to next row
        // Display row numbers on the furthest right axis to make it look nice.
        if((row+1) % 5  == 0 && row != 0)
            std::cout << "   " << row+1; 
        std::cout << std::endl;
    } // End of graph.   
    std::cout << std::endl;;

    // Set x axis labels.
    row = maxLength;
    int chartoprint = 0;
    // Another Morris Traversal, but this time I use it to write the words on the x-axis.
    while(row>0){
        current = dictionary->Words;
        
        while(current!= nullptr){       
            if(current->leftChild == nullptr){  
                // Check for whether the character of the word has length great enough for character to be printed. 
                if(chartoprint < current->entry.word.length())
                    std::cout << " " << current->entry.word[chartoprint] << " "; 
                else    
                    std::cout << "   ";       
                current = current->rightChild;
            }
            else{
                pre = current->leftChild;
                while(pre->rightChild != nullptr && pre->rightChild != current){
                    pre = pre->rightChild;
                }
                if(pre->rightChild == nullptr){
                    pre->rightChild = current;
                    current = current->leftChild;
                }
                else{
                    pre->rightChild = nullptr;
                    // Check for whether to print the character. Prints either a char flanked by spaces or 3 spaces.
                    if(chartoprint < current->entry.word.length() )
                        std::cout << " " << current->entry.word[chartoprint] << " ";
                    else
                        std::cout << "   ";    
                    current = current->rightChild;
                }
            }  
        }
        chartoprint++; // Increase character of strings to print. There's check for whether this would be out-of-bounds.
        row--;         // Next row because it's setup vertically.
        std::cout << std::endl;; // Next line.
    }

    // End of histogram. X and Y axis are labeled with contents being word frequencies.  
}

/*  
    Displays the BST. With the case of the dictionary, it will be in alphabetical order.
    
    @param Entry* should be the tree's root or the tree will be drawn missing some stuff.
*/
static void inOrderTraversal(Entry* root){
    if(root == nullptr){  
        return;
    }
    
    inOrderTraversal(root->leftChild);
    std::cout << root->entry.word << std::endl;
    inOrderTraversal(root->rightChild);  
}

/*  
    This replaces the "getNextWord" function.

    Overloads the >> operator. Coverts to a string that only contains letters of the alphabet.

    @param istream& input stream
    @param MYWORD&
    @return a word that ends when a character that isn't alpha is encountered
*/
std::istream& operator>>(std::istream &inputStream, MYWORD &word){
    std::istream::sentry sent(inputStream);



    // See https://www.cplusplus.com/reference/istream/istream/sentry/.
    if(sent) while(inputStream.good()){
        char c = inputStream.get();

        // Stop when it's not a letter in the alphabet. 
        if(!std::isalpha(c, inputStream.getloc())) 
            break;
        word.push_back(tolower(c)); // All letters are lowercase.

    }
    return inputStream;
}

/*
    Displays the doubly linked list ordered from least to greatest. Will cause segment fault if list has not been created, so ensure
    that rebuildList had been called, or the frequency list has been set manually.
    @param Dictionary* dictionary to print frequencies in ascending order.
*/
void dumpList(Dictionary* dictionary){
    Entry *current;

    current = dictionary->wordLen;

    // Traverse through the list.
    while(current != nullptr){
        // For avoiding an uglier output.
        if(current->nextSibling == nullptr){
            std::cout << current->entry.word << ": " << current->entry.frequency;
            break;
        }
        std::cout << current->entry.word << ": " << current->entry.frequency << std::endl;; // word then its frequency of occurance.
        current = current->nextSibling;  // go to next one.
    }

    // Since the memory address of current shouldn't be modified, current will be set to nullptr
    // to avoid any shenanigans instead of deleting it.
    current = nullptr;
    
}

/*
    Returns true or false for whether the dictionary is full.

    @param &Dictionary Dictionary to check.
    @return returns true if dictionary is full.
*/
bool fullDictionary(Dictionary &dictionary){
    return (dictionary.numWords < dictionary.MAXENTRIES);  
}

/*
    Traverses the bst and adds to list. Must be called before interacting with the doublylinked list in anyway.
    Uses morris traversal to accomplish it. 
    @param Entry* Root node of a binary search tree.
    @param Dictionary* dictionary of the root.
*/
void rebuildList(Entry* root, Dictionary* dictionary){
    Entry* current;     // Current node.
    Entry* pre;         // Previous node.
    
    if(root == nullptr)
        return;

    current = root;
    while(current!= nullptr){
        if(current->leftChild == nullptr){ 
            addToList(current, current->entry.frequency, dictionary);
            current = current->rightChild;
        }
        else{
            pre = current->leftChild;
            while(pre->rightChild != nullptr && pre->rightChild != current){
                pre = pre->rightChild;
            }
            if(pre->rightChild == nullptr){
                pre->rightChild = current;
                current = current->leftChild;
            }
            else{
                pre->rightChild = nullptr;
                addToList(current, current->entry.frequency, dictionary);
                current = current->rightChild;
            }
        }
    }
    current = nullptr;
    pre = nullptr;
}