/*
    Function, Pointers, Protypes
    CS 2010 lab 5
    Author: Mitchell VanderHoek
    Purpose :   Demonstrate knowledge of pointers and how pointers can also point to functions.

*/


#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef int (*bin_op)(int, int);
typedef int (*un_op)(int);
typedef bool (*bool_op)(int);
typedef vector<int> int_vec;

int C; //This variable is used to test the test_all function.

/*
    Reduce:   

    summary Iterates over the vector and returns an integer based on the binary operation being performed.

    @param int_vec Vector's elements will be used to compute a number.
    @param bin_op A unary fuction that returns bool. Do not include the bracketsfor the parameter.
    @return Tnt the integer returned is dependent upon the function passed. A function that sums two
            numbers will return the sum of elements 0 to n.
*/
int reduce(int_vec &v, bin_op op){
    int number = v[0];

    for(int i = 1; i<v.size(); i++){
        number = op(number,v[i]);
    }

    return number;
}

/*
    transform:  

      Changes every element based on the function in the parameters.

    @param int_vec Vector to have its elements changed.
    @param un_op A unary fuction that returns bool. Do not include the bracketsfor the parameter.
*/
void transform(int_vec &v, un_op op){

    for(auto i = 0; i<v.size(); i++){
        v[i] = op(v[i]);
    }
}

/*
    test_all:   

    Compares every element of the vector and pushes the comparison to another vector.
    The results of each comparison is stored in a vector of the same size.

    @param int_vec Vector to be tested.
    @param bool_op A unary fuction that returns bool. Do not include the bracketsfor the parameter.
    @return int_vec Vector contains result of comparison.
*/
int_vec test_all(int_vec &v, bool_op op){
    int_vec r;
    for(int i = 0; i < v.size(); i++){     
        op(v[i]) ? r.push_back(1) : r.push_back(0); 
    }
    return r;
}

/*
    Generate:  

    Generate a vector of a ints from 1 to, and including n.

    @param int Number of elements to be in the vector.
    @param un_op A unary fuction. Do not include the brackets.
    @return int_vec Vector of size n with elements 1, 2, 3, ..., n. 
*/
int_vec generate(int n, un_op op){
    int_vec vector;
    
    for(int i = 1; i <= n; i++){
        vector.push_back(op(i));
    }

    return vector;
}

/*
    findMax:  

    Compares two numbers for which is greater then returns the greater number.

    @param int  First value
    @param int   Second value
    @return int Greater value.
*/
int findMax(int a, int b){
    return (a > b) ? a : b;
}

/*
    Add:  

    Adds two integers.

    @param int 
    @param int
    @return int The result of the addition.
*/
int add(int a, int b){
    return a + b;
}

/*
    Multiply:  

    Multiplies two integers using '*'. There's nothing fancy going on.

    @param int
    @param int
    @return int Product.
*/
int multiply(int a, int b){
    return a * b;
}

/*
    counter:  

    Counts elements in vector less than a number. 

    @param int_vec This vector will have its elements compared to a number.
    @param int This is the number the elements are being compared to.
    @return int Returns the count of the comparisons. 
*/
int counter(int_vec &v, int c){

    int count = 0;

    for(int i = 0; i<v.size(); i++){
        if(v[i] < c)
            count++;
    }
    return count;
}

/*
    setVec:  

    Helper function for initializing vector in reduce.

    @param int Element to be returned.
    @return int Element.
*/
int setVec(int x){
    return x;
}

/*  
    great:  

    Compares an int to the global variable C.

    @param "int a" to be compared to.
    @return Returns true if C > a
*/
bool great(int a){
    return (C>a);
}

/*
    compare:  

    Compares a number to the global variable C. If the number being compared to C is greater
    than C it will return 1. If equal then 0. If less than it'll return -1. Uses nested ternary 
    to perform the comparison.
    
    @param int Integer to be compared to C.
    @return Return 1, 0 or -1.
*/
int compare(int x){
    
    return x > C ?  1 : (x < C ? -1 : 0);
}

/*
    changeC:    Changes the value of C which is used for comparisons.
    @param int  Value to change C to.
*/
void changeC(int newc){
    C = newc;
}

int main(){

    int_vec tvec, grtVec;
    int sum, mulSum, max = 0, greaterCount, vecSize;
    double changeglobal;

    //Title screen
    cout << "\n\nUsing Prototypes of a Function to Resemble " << "Generarics\n\n";

    /*
        Prompts to set vector length and which element to compare to. It should be noted that, depending
        on the size, an overflow will occur when mul*=tvec[0, ... , n-1 ] if it's too large, ie it becomes
        a factorial.
    */
    cout << "How many elements would you like the vector to have?(express as an integer) : ";
    cin >> vecSize;
    cout << "What number would you like to use for comparisons? (express as an integer)  : ";
    cin >> changeglobal;
    changeC((double)changeglobal); //Changes the value of global variable C.

    //Generate the vector, then perform a test to make sure that it was initialized as intended.
    tvec = generate(vecSize, setVec); //generates a vector of  1, 2,...,n
    cout << "\n\nVector Generated                        : ";
    for(int i = 0; i<tvec.size(); i++){
        cout << tvec[i] << " ";
    } 
    
    //Sum the elements of the vector. It's n(n+1)/2 to get sum. Test for outcome.
    sum = reduce(tvec, add);
    cout << "\nSummation of Elements                   : " << sum;

    //Multiply every element by the previous element. Will end up with overflow above certain n.
    //Console output after to ensure desired results.
    mulSum = reduce(tvec, multiply);
    cout << "\nMultiply elements                       : " << mulSum;

    //Find the max value of the vector. Test to make sure it's 12.
    max = reduce(tvec, findMax);
    cout << "\nGreatest value of elements              : " << max;
    
    //Finds which numbers are greater than the global variable C.
    grtVec = test_all(tvec, great);
    cout << "\nVector of which elements are greater    : ";
    for(int i = 0; i<grtVec.size(); i++){
        cout << grtVec[i] << " ";
    }
    
    //Counts how many elements are greater than the global variable C by adding the bools.
    greaterCount = reduce(grtVec, add);
    cout << "\nCount of how many are greater than      : " << greaterCount << "\n" ;

    //Creates a vector of the result.
    transform(tvec, compare);
    cout << "Vector resulting from the transformation: ";
    for(int i = 0; i<tvec.size(); i++){
        cout << tvec[i] << " ";
    }
    cout << "\n\n";

    return 0;
}

