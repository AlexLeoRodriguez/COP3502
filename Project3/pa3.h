//  pa3.h
//  pa3
// Alexander Rodriguez
// due: 04/10/17


#ifndef pa3_h
#define pa3_h

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int minimum(int a, int b, int c);

struct node{
    string val;
    node* next;
};

class mystack{
    node * top;
    int sz;
    
public:
    mystack();
    void stack_push(string str);
    string stack_pop();
};


bool isLowercaseOrEqualSign(string str);

bool is_file_exist(string fileName);

enum State {
    FOR_OR_EXP,
    
    FOR_1,
    FOR_2,
    FOR_3,
    FOR_BEGIN,
    EXP_OP,
    IDEN_OR_CONST,
    EXP_END,
    FOR_OR_END
    
};

class Inventory {
    string vars[100];
    int numVars = 0;
public:
    void addIfNotExist(string item);
    void print();
};

class Collection {
    // collection of inventories
    Inventory keywords;
    Inventory identifiers;
    Inventory constants;
    Inventory operators;
    Inventory delimiters;
    Inventory syntaxErrors;
    
    int fors = 0;
    int begins = 0;
    int ends = 0;
    int depth = 0;
    int newdepth = 0;
public:
    Collection(string input);
    Inventory getInventk();
    Inventory getInventI();
    Inventory getInventC();
    Inventory getInventO();
    Inventory getInventD();
    Inventory getInventSE();
    int getDepth();
    void print(Inventory ss);
};
#endif /* pa3_h */
