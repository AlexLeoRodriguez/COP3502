//  pa2.h
//  Created by Alexander Rodriguez on 3/3/17.
//  UFID: 81135872

#ifndef pa2_h
#define pa2_h

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;

double testDoubleValue();

struct Node { // Public overall
    string data;
    Node* next;
};

class LinkedList{
    /* Node Pointers */
    
    Node* head; // Reference pointer (stays the same)
    Node* curr; // working pointer (may change)
    
public:
    // Basic Constructor
    LinkedList();
    //add to the end of the list
    void addData(string input, int amount, string type);
    //remove element specific to input
    void removeData(string input);
    // find amount of seperations between inputs
    int findFrags();
    //print func for debugging
    void print();
    // clear list to avoid leakage
    void clearList();
};

#endif /* pa2_h */
