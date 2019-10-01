//  pa3.h
//  pa3
// Alexander Rodriguez
// due: 04/10/17

#include "pa3.h"

int main() {
    string input;
    cout << "Please enter a file name: ";
    cin >> input;
    bool test = is_file_exist(input);
    if (!test) {
        cout << "ERROR: file was not found. Ending program.";
        //error message
        return 1;
    }
    
    Collection *gravy = new Collection(input);
    
    cout << "The depth of nested loop(s) is " << gravy->getDepth() << endl;
    
    
    cout << "Keywords: ";
    gravy->print(gravy->getInventk());
    cout << endl;
    
    cout << "Identifiers: ";
    gravy->print(gravy->getInventI());
    cout << endl;
    
    cout << "Constants: ";
    gravy->print(gravy->getInventC());
    cout << endl;
    
    cout << "Operators: ";
    gravy->print(gravy->getInventO());
    cout << endl;
    
    cout << "Delimiters: ";
    gravy->print(gravy->getInventD());
    cout << endl;
    
    cout << "Syntex Errors: ";
    gravy->print(gravy->getInventSE());
    cout << endl;
    
    return 0;
};


mystack::mystack() {
    top = NULL;
    sz = 0;
};

void mystack::stack_push(string str) {
    node * temp = new node;
    temp->val = str;
    temp->next = top;
    sz++;
    top = temp;
};

string mystack::stack_pop() {
    if (top == NULL)		return "";
    string str = top->val;
    sz--;
    top = top->next;
    return str;
};



bool isLowercaseOrEqualSign(string str) {
    string sub = str;
    transform(sub.begin(), sub.end(), sub.begin(), (int(*)(int))tolower);
    bool equal = false;
    for (int i = 0; i < str.length(); i++){
        if (str.at(i) == '='){
            equal = true;
        }
    }
    
    if(sub == str || equal){
        return true;
    }
    else {
        return false;
    }
    
    return true;
};

bool is_file_exist(string fileName) {
    ifstream infile(fileName);
    return infile.good();
};

// Keeps data for each inventory
void Inventory::addIfNotExist(string item) {
    bool exists = false;
    for (int i = 0; i != numVars; ++i) {
        if (vars[i] == item) {
            exists = true;
            break;
        }
        // make sure item isn't in the array
        // if it is, break.
    }
    // otherwise, add it to the array
    if (!exists) {
        vars[numVars] = item;
        numVars++;
    }
    
};

void Inventory::print() {
    for (int i = 0; i != numVars; ++i) {
        cout << vars[i] << " ";
    }
};

int minimum(int a, int b, int c) {
    int d = 0;
    d = min(a, b);
    d = min(c, d);
    return d;
};

// State Machine
Collection::Collection(string input) {
    ifstream file(input);
    State state = FOR_OR_EXP;
    string nextWord;
    bool prevEnd = false;
    
    for (;;) {
        file >> nextWord;
        if (!file.good()) {
            if (prevEnd) {
                newdepth = minimum(fors,begins,ends);
                depth = max(depth,newdepth);
            }
            break;
        }
        
        if (nextWord == "BEGIN"){
            if (prevEnd) {
                prevEnd = false;
                newdepth = minimum(fors,begins,ends);
                depth = max(depth,newdepth);
                fors = 0;
                begins = 0;
                ends = 0;
            }

            begins++;
        }
        else if (nextWord == "FOR"){
            if (prevEnd) {
                prevEnd = false;
                newdepth = minimum(fors,begins,ends);
                depth = max(depth,newdepth);
                fors = 0;
                begins = 0;
                ends = 0;
            }
            fors++;
        }
        else if (nextWord == "END"){
            ends++;
            prevEnd = true;
        }
        switch (state) {
            case FOR_OR_EXP:
                if (nextWord == "FOR") {
                    keywords.addIfNotExist(nextWord);
                    state = FOR_1;
                }
                else if (isLowercaseOrEqualSign(nextWord)) {
                    string left;
                    string right;
                    state = EXP_OP;
                    int index;
                    for (int i = 0; i < nextWord.length(); i++) {
                        if (nextWord[i] == '=') {
                            index = i;
                        }
                        else {
                            index = -1;
                        }
                        if (index > 0 ) {
                            operators.addIfNotExist("=");
                            left = nextWord.substr(0, index);
                            identifiers.addIfNotExist(left);
                        }
                        if (index != nextWord.length() - 1 && right.length() > 0) {
                            right = nextWord.substr(0, index);
                            if (right[0] > 0 || right[0] < 10) {
                                constants.addIfNotExist(right);
                            }
                            else {
                                identifiers.addIfNotExist(right);
                            }
                        }
                        if (index == -1) {
                            identifiers.addIfNotExist(right);
                        }
                    }
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                    if (nextWord == "End") {
                        state = FOR_OR_END;
                    }
                    else if (nextWord == "BEGINS") {
                        state = FOR_OR_EXP;
                    }
                }
                break;
            case FOR_1: {
                bool test = true;
                if (nextWord.length() < 3) {
                    test = false;
                }
                if (nextWord[0] != '(' || nextWord[nextWord.length() - 1] != ',') {
                    test = false;
                }
                if (nextWord[nextWord.length() - 1] == ',') {
                    delimiters.addIfNotExist(nextWord.substr(nextWord.length() - 1, 1));
                }
                if (test) {
                    identifiers.addIfNotExist(nextWord.substr(1, 1));
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                }
                state = FOR_2;
            }
                break;
            case FOR_2: {// FIX
                bool test = true;
                if (nextWord.length() < 2) {
                    test = false;
                }
                if (nextWord[nextWord.length() - 1] != ',') {
                    test = false;
                }
                else {
                    delimiters.addIfNotExist(nextWord.substr(nextWord.length() - 1, 1));
                }
                if (test) {
                    constants.addIfNotExist(nextWord.substr(0, nextWord.length() - 1));
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                }
                
                state = FOR_3;
            }
                break;
            case FOR_3: {// Fix
                bool test = true;
                if (nextWord.length() < 3 || nextWord[nextWord.length() - 1] != ')') {
                    test = false;
                }
                else if (test) {
                    string ops[8] = { "+","-","=","++","--","*","/" };
                    for (int i = 0; i < 8; i++) {
                        if (ops[i] == nextWord.substr(0,nextWord.length()-1)) {
                            operators.addIfNotExist(nextWord.substr(0,nextWord.length()-1));
                        }
                    }
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                }
                state = FOR_BEGIN;
            }
                break;
            case FOR_BEGIN:
                if (nextWord == "FOR") {
                    keywords.addIfNotExist(nextWord);
                    state = FOR_1;
                }
                else if (nextWord == "BEGIN") {
                    keywords.addIfNotExist(nextWord);
                    state = FOR_OR_EXP;
                }
                else if (nextWord == "END") {
                    state = FOR_OR_END;
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                    state = FOR_OR_EXP;
                }
                
                break;
            case EXP_OP: {
                state = IDEN_OR_CONST;
                string ops[8] = { "+","-","=","++","--","*","/" };
                for (int i = 0; i < 8; i++) {
                    if (ops[i] == nextWord) {
                        operators.addIfNotExist(nextWord);
                    }
                }
            }
                break;
            case IDEN_OR_CONST: // NEEDS STATE
                state = EXP_OP;
                if (nextWord.length() > 0) {
                    if (nextWord[0] > 0 && nextWord[0] < 10) {
                        constants.addIfNotExist(nextWord);
                    }
                    else if (nextWord.at(nextWord.length() - 1) == ';') {
                        delimiters.addIfNotExist(";");
                        
                        state = EXP_END;
                    }
                    else {
                        identifiers.addIfNotExist(nextWord);
                    }
                }
                break;
            case EXP_END:
                if (nextWord == "END") {
                    keywords.addIfNotExist(nextWord);
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                }
                state = FOR_OR_END;
                break;
            case FOR_OR_END:
                if (nextWord == "FOR") {
                    state = FOR_1;
                    keywords.addIfNotExist(nextWord);
                }
                else if (nextWord == "END") {
                    keywords.addIfNotExist(nextWord);
                    state = FOR_OR_END;
                }
                else {
                    syntaxErrors.addIfNotExist(nextWord);
                }
                break;
        }
    }
    file.close();
};


// Getters
Inventory Collection::getInventk() {
    return keywords;
};

Inventory Collection::getInventI() {
    return identifiers;
};

Inventory Collection::getInventC() {
    return constants;
};

Inventory Collection::getInventO() {
    return operators;
};

Inventory Collection::getInventD() {
    return delimiters;
};

Inventory Collection::getInventSE() {
    return syntaxErrors;
};

int Collection::getDepth() {
    return depth;
};

void Collection::print(Inventory ss) {
    return ss.print();
};







