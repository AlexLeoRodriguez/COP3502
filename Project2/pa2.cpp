//  pa2.cpp
//  Created by Alexander Rodriguez on 3/3/17.
//  UFID: 81135872

#include "pa2.h"

/* Constructor */
LinkedList::LinkedList(): head(NULL), curr(NULL) {
}

/* Add Input */
void LinkedList::addData(string newData, int amount, string type) {
    
    // Test if user input is not already in the system
    
    bool available = true;
    curr = head;
    while (curr != NULL) {
        if (newData == curr->data){
            available = false;
        }
        curr = curr->next;
    }
    
    bool prevEmpty = false;
    int emptyCount = 0;
    int bestPos = 0;
    int total = 32;
    int position = 0;
    int prevSize = 0;
    int savedPos = 0;
    int countPages = 0;
    
    curr = head;
    if (available) {
        if(type == "worst") {
            if(head != NULL) {
                while (curr != NULL) {
                    if(curr->data == "") {
                        countPages++;
                        if (!(prevEmpty)) {
                            savedPos = position;
                        }
                        prevEmpty = true;
                        emptyCount++;
                        
                    }
                    else if (curr->data != "" && prevEmpty == true) {
                        if(countPages >= amount && countPages > prevSize){
                            prevSize = countPages;
                            bestPos = savedPos;
                        }
                        countPages = 0;
                        prevEmpty = false;
                    }
                    if (emptyCount == 32) {
                        prevSize = countPages;
                        bestPos = savedPos;
                    }
                    curr = curr->next;
                    total--;
                    position++;
                }
            
                if (total > 0 && countPages != 0){
                    while(total != 0) {
                        countPages++;
                        total--;
                    }
                    if(countPages >= amount && countPages > prevSize){
                        prevSize = countPages;
                        bestPos = savedPos;
                    }
                    countPages = 0;
                }
                else if (total > 0) {
                    while(total != 0) {
                        countPages++;
                        total--;
                    }
                    if(countPages >= amount && countPages > prevSize){
                        prevSize = countPages;
                        bestPos = -1;
                    }
                }
                if (prevSize >= amount) {
                    // determines where we are going to place the data
                    countPages = 0;
                    curr = head;
                    if (bestPos == -1) {
                        while (curr->next != NULL) {
                            curr = curr->next;
                        }
                        for(int i = 0; i != amount; i++) {
                            Node* n = new Node;
                            n->next = NULL;
                            n->data = newData;
                            curr->next = n;
                            curr = curr->next;
                        }
                        cout << "\nProgram " << newData << " added successfully: " << amount << " page(s) used.\n" << endl;
                    }
                    else if(bestPos >= 0) {
                        for (int i = 0;i != bestPos; i++) {
                            curr = curr->next;
                        }
                        while (curr->next != NULL) {
                            curr->data = newData;
                            countPages++;
                            curr = curr->next;
                            if(countPages == amount) {
                                break;
                            }
                        }
                        if(countPages != amount) {
                            for(int i = countPages; i < amount; i++) {
                                Node* n = new Node;
                                n->next = NULL;
                                n->data = newData;
                                curr->next = n;
                                curr = curr->next;
                            }
                        }
                        cout << "\nProgram " << newData << " added successfully: " << amount << " page(s) used.\n" << endl;
                    }
                }
                else {
                    cout << "\nError, not enough memory for Program " << newData << ".\n" << endl;
                }
            }
            else {
                if (amount > 32) {
                    cout << "\nError, not enough memory for Program " << newData << ".\n" << endl;
                }
                else {
                    Node* n = new Node;
                    n->next = NULL;
                    n->data = newData;
                    head = n;
                    curr = head;
                    countPages++;
                    while(countPages != amount) {
                        Node* n = new Node;
                        n->next = NULL;
                        n->data = newData;
                        curr->next = n;
                        curr = curr->next;
                        countPages++;
                    }
                    cout << "\nProgram " << newData << " added successfully: " << amount << " page(s) used.\n" << endl;
                }
            }
        }
    
        if (type == "best") { // best case scenario
            if(head != NULL) {
                int max = 32;
                bool firstTry = true;
                while (curr != NULL) {
                    if(curr->data == "") {
                        countPages++;
                        if (!(prevEmpty)) {
                            savedPos = position;
                        }
                        prevEmpty = true;
                        emptyCount++;
                    }
                    else if (curr->data != "" && prevEmpty == true) {
                        if (firstTry == true){
                            if(countPages >= amount && countPages < max){
                                prevSize = countPages;
                                bestPos = savedPos;
                                firstTry = false;
                            }
                        }
                        else {
                            if(countPages >= amount && countPages < prevSize){
                                prevSize = countPages;
                                bestPos = savedPos;
                            }
                        }
                        countPages = 0;
                        prevEmpty = false;
                    }
                    if (emptyCount == 32) {
                        prevSize = countPages;
                        bestPos = savedPos;
                    }
                    curr = curr->next;
                    total--;
                    position++;
                }
                
                if (total > 0 && countPages != 0){
                    while(total != 0) {
                        countPages++;
                        total--;
                    }
                    if (firstTry == true){
                        if(countPages >= amount && countPages < max){
                            prevSize = countPages;
                            bestPos = savedPos;
                            firstTry = false;
                        }
                    }
                    else {
                        if(countPages >= amount && countPages < prevSize){
                            prevSize = countPages;
                            bestPos = savedPos;
                        }
                    }
                    countPages = 0;
                }
                else if (total > 0) {
                    while(total != 0) {
                        countPages++;
                        total--;
                    }
                    if (firstTry == true) {
                        if(countPages >= amount && countPages < max){
                            prevSize = countPages;
                            bestPos = -1;
                        }
                    }
                    else {
                        if(countPages >= amount && countPages < prevSize){
                            prevSize = countPages;
                            bestPos = -1;
                        }
                    }
                }
                if (total == 0 && countPages != 0) {
                    prevSize = countPages;
                    bestPos = savedPos;
                }
                if (prevSize >= amount) {
                    // determines where we are going to place the data
                    countPages = 0;
                    curr = head;
                    if (bestPos == -1) {
                        while (curr->next != NULL) {
                            curr = curr->next;
                        }
                        for(int i = 0; i != amount; i++) {
                            Node* n = new Node;
                            n->next = NULL;
                            n->data = newData;
                            curr->next = n;
                            curr = curr->next;
                        }
                        cout << "\nProgram " << newData << " added successfully: " << amount << " page(s) used.\n" << endl;
                    }
                    else if(bestPos >= 0) {
                        for (int i = 0;i != bestPos; i++) {
                            curr = curr->next;
                        }
                        while (curr->next != NULL) {
                            curr->data = newData;
                            countPages++;
                            curr = curr->next;
                            if(countPages == amount) {
                                break;
                            }
                        }
                        if(countPages != amount) {
                            for(int i = countPages; i < amount; i++) {
                                Node* n = new Node;
                                n->next = NULL;
                                n->data = newData;
                                curr->next = n;
                                curr = curr->next;
                            }
                        }
                        cout << "\nProgram " << newData << " added successfully: " << amount << " page(s) used.\n" << endl;
                    }
                }
                else {
                    cout << "\nError, not enough memory for Program " << newData << ".\n" << endl;
                }
            }
            else {
                if (amount > 32) {
                    cout << "\nError, not enough memory for Program " << newData << ".\n" << endl;
                }
                else {
                    Node* n = new Node;
                    n->next = NULL;
                    n->data = newData;
                    head = n;
                    curr = head;
                    countPages++;
                    while(countPages != amount) {
                        Node* n = new Node;
                        n->next = NULL;
                        n->data = newData;
                        curr->next = n;
                        curr = curr->next;
                        countPages++;
                    }
                    cout << "\nProgram " << newData << " added successfully: " << amount << " page(s) used.\n" << endl;
                }
            }
        }
    }
    else { // No availability
        cout << "\nError, Program P1 already running.\n" << endl;
    }
}

/* Remove Input */
void LinkedList::removeData(string delType) {
    if(head != NULL) {
        int count = 0; // counts the number of times a program is removed
        curr = head;
        if (curr->data == delType) { // Checks if head pointer needs to be deleted
            curr->data = "";
            count++;
        }
        while (curr->next != NULL) { // Checks if any other parts of the list have to be deleted
            curr = curr->next;
            if (curr->data == delType) {
                curr->data = "";
                count++;
            }
        }
        if(count > 0) { // Success
            cout << "\nProgram " << delType << " successfully killed, " << count << " page(s) reclaimed.\n" << endl;
        }
        else { // Failure
            cout << "\nProgram " << delType << " was not found.\n" << endl;
        }
    }
    else {
        cout << "\nProgram " << delType << " was not found.\n" << endl;
    }
}

/* Find Fragments */
int LinkedList::findFrags() {
    
    // counters and comparisons
    int total = 32;
    int prev = 0;
    int test = 0;
    int frags = 0;
    int count = 0;
    
    if (head == NULL) {
        return 1;
    }
    else {
        Node* temp = NULL; // temporary Node Pointer
        curr = head;
        
        if (curr != NULL) {   // 0 if empty, 1 if filled (predetermines position)
            if (curr->data != ""){
                prev = 0;
            }
            else {
                prev = 1;
            }
        }
        
        while (curr != NULL) { // compares to every point in the list
            total--;
            temp = curr;
            curr = curr->next;
            if(curr != NULL) {
                if(curr->data != "") {
                    test = 0;
                }
                else {
                    test = 1;
                }
                if (test != prev) { // if it changes, there is a fragment
                    count++;
                    if (count % 2 != 0) {
                        frags++;
                    }
                }
                prev = test;
            }
        }
        // if the list is not complete and final value is filled, there is a fragment
        if(total > 1 && temp->data != "") {
            frags++;
        }
        temp = NULL;
    }
    return frags;
}

void LinkedList::print() {
    cout << endl;
    int total = 32;
    curr = head;
    while (curr != NULL) {
        total--;

        if (curr->data != "") {
            cout << curr->data << " ";
        }
        else {
            cout << "FREE ";
        }
        if((total) % 8 == 0 && (total) != 32) { // "End line" after every 8 inputs
            cout << endl;
        }
        curr = curr->next;
    }
    
    while (total > 0) {
        cout << "FREE ";
        total--;
        if((total) % 8 == 0 && (total) != 32) {
            cout << endl;
        }
    }
    
    cout << endl;
}

/* Remove All Data */
void LinkedList::clearList() {
    if(head != NULL) {
        curr = head->next;
        delete head;
        while (curr != NULL) {
            head = curr;
            curr = curr->next;
            delete head;
        }
    }
}

/* Test User Input */
double testDoubleValue() {
    bool check = false;
    double input = 0;
    double test;
    while(!(check)) {
        cout << "Program size(KB) - ";
        cin >> test;
        
        if (test <= 0) {
            cout << "\nERROR: Invalid input, please try again.\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else  {
            check = true;
            input = test;
        }
    }
    return input;
}


int main(int argc, char * argv[]) {
    string type = argv[1];
    transform(type.begin(), type.end(), type.begin(), (int(*)(int))tolower);
    if (type == "best") {
        
    }
    else if (type == "worst") {
        
    }
    else {
        cout << "Error: Invalid Argument" << endl;
        return 1;
    }
    cout << "\nUsing " << type << " fit algorithm\n" << endl;
    
    LinkedList Gravy;
    int choice = 0;
    
    cout << "1. Add program\n2. Kill program\n3. Fragmentation\n4. Print memory \n5. Exit\n" << endl;
    while (choice != 5) {
        cout << "choice -  ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                const double fileSize = 4;
                int pages;
                string data;
                double progSize;
                
                cout << "Program name - ";
                cin >> data;
                while (data.length() > 20) { // Limit string length to 20
                    cout << "Error: Program name is too large. Please either change the name of the program or choose another program.\n" << endl;
                    cout << "Program name - ";
                    cin >> data;
                }
                while(data == "FREE" || data.length() > 20) {
                    if (data == "FREE") {
                    cout << "Error: Please do not use the word 'FREE' with all letters capitalized.\n" << endl;
                    }
                    else if (data.length() > 20) {
                        cout << "Error: Program name is too large. Please either change the name of the program or choose another program.\n" << endl;
                    }
                    cout << "Program name - ";
                    cin >> data;
                }
                
                progSize = testDoubleValue();
                if (progSize <= 128) {
                    pages = (int)(ceil(progSize/fileSize));
                    Gravy.addData(data, pages, type);
                }
                else {
                     cout << "\nError, not enough memory for Program " << data << ".\n" << endl;
                }
            } break;
            case 2: {
                string data;
                cout << "Program name - ";
                cin >> data;
                Gravy.removeData(data);
            } break;
            case 3: {
                cout << "\nThere are " << Gravy.findFrags() << " fragment(s)\n" << endl;
            } break;
            case 4: {
                Gravy.print();
            } break;
            case 5: {
                cout << "\nYou have successfully exited the program.\n" << endl;
                Gravy.clearList();
                // While loop ends
            } break;
            default: {
                cout << "\nERROR: Invalid input, please try again.\n" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            } break;
        }
    }
    return 0;
}
