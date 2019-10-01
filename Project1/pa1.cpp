//  Name: Alexander Rodriguez
//  UFID: 81135872
//  Project: PA1
//  Estimated time of completion: Feb 9, 2017: 2:57pm

#include "pa1.h"
#include <iostream>
using namespace std;

/* PRINT MAGIC SQUARE */
void printMS(int **mSquare, int size) {
    for(int i=0; i!=size; ++i) {
        for (int j=0; j!=size; ++j) {
            cout << mSquare[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/* TEST THE INPUT FROM USER */
int testSize(int &size) {
    double deciTest;
    int input;
    std::cout << "Please enter size of magic square: ";
    cin >> deciTest;
    input  = (int)deciTest;
    
    // test if input is a decimal
    if (input != deciTest) {
        cout << "Invalid input. Please enter an odd integer between 3 and 15" << endl;
        return 1;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    
    // test if value is out of range
    if (input > 15 || input < 3 || input % 2 != 1 ) {
        cout << "Invalid input. Please enter an odd number between 3 and 15" << endl;
        return 2;
    } else {
        size = input;
        return 0;
    }
}

/* ADD ALL ROWS */
void msRows(int **mSquare, int size) {
    cout << "Checking the sum of every row: ";
    int sum = 0;
    for(int i=0; i!=size; ++i) {
        for (int j=0; j!=size; ++j) {
            sum += mSquare[i][j];
        }
        cout << sum << " ";
        sum = 0;
    }
    cout << endl;
}

/* ADD ALL COLLUMNS */
void msColumns(int **mSquare,int size) {
    cout << "Checking the sum of every column: ";
    int sum = 0;
    for(int i=0; i!=size; ++i) {
        for (int j=0; j!=size; ++j) {
            sum += mSquare[j][i];
        }
        cout << sum << " ";
        sum = 0;
    }
    cout << endl;
}

/* ADD BOTH DIAGONALS */
void msDiagonals(int **mSquare, int size) {
    // Top left to bottom right
    cout << "Checking the sum of every diagonal: ";
    int sum = 0;
    for(int i=0; i!=size; ++i) {
        for (int j=0; j!=size; ++j) {
            if (i == j) {
                sum += mSquare[i][j];
            }
        }
    }
    
    cout << sum << " ";
    sum = 0;
    
    // Bottom Left to top right
    for(int i= size - 1; i >= 0; --i) {
        for (int j= size - 1 ; j >= 0; --j) {
            if (i == j) {
                sum += mSquare[i][j];
            }
        }
    }
    cout << sum << " ";
    cout << endl;
    cout << endl;

}

/* CREATE MAGIC SQUARE */
void createMS(int **mSquare , int size) {
    int cter = (size + 1) / 2;
    
    int k = 0;
    int h = cter - 1;
    int m = 1;
    bool done = false;
    
    mSquare[k][h] = 1;
    
    while(!(done)) {
        // Starting positions
        int i = k;
        int j = h;
        
        // Shift up and to the right in the array
        k -= 1;
        h += 1;
        m++;
        
        // Tests if out of range or space is filled
        if(k < 0) {
            k = size - 1;
        }
        if(h >= size) {
            h = 0;
        }
        if(mSquare[k][h] == 0) {
            mSquare[k][h] = m;
        }
        else {
            i += 1;
            if(i >= size) {
                i = 0;
            }
            k = i;
            h = j;
            mSquare[i][j] = m;
        }
        
        // Program believes it is done, prove it wrong
        done = true;
        for(int i=0; i!=size; ++i) {
            for (int j=0; j!=size; ++j) {
                if(mSquare[i][j] == 0) {
                    done = false;
                }
            }
        }
    }
}


/* TURN THE ARRAY */
void turnArray(int **mSquare , int size) {
    
    int **newMS = new int*[size];
    for(int i=0; i!=size; ++i) {
        newMS[i] = new int[size];
        // Zero Out Numbers
        for (int j=0; j!=size; ++j) {
            newMS[i][j] = 0;
        }
    }

    //  Rotates array
    for(int i=0; i!=size; ++i) {
        for (int j= 0, k = size -1; j != size; ++j, --k) {
            newMS[k][i] = mSquare[i][j];
        }
    }
    
    // Make new array equal to old array
    for(int i=0; i!=size; ++i) {
        for (int j=0; j!=size; ++j) {
            mSquare[i][j] = newMS[i][j];
        }
    }
    
    for(int i=0; i!=size; ++i) {
        delete [] newMS[i];
    }
    delete [] newMS;
}



int main() {
    int size = 0;
    int check = testSize(size);
    if(check != 0) {
        return 1;
    }
    
    // Determine size of the array
    int **mSquare = new int*[size];
    for(int i=0; i!=size; ++i) {
        mSquare[i] = new int[size];
        // Zero Out Numbers
        for (int j=0; j!=size; ++j) {
            mSquare[i][j] = 0;
        }
    }
    
    // First MS
    createMS(mSquare, size);
    printMS(mSquare, size);
    msRows(mSquare, size);
    msColumns(mSquare, size);
    msDiagonals(mSquare, size);
    
    // Repeat turn 3 times
    for(int i = 0; i < 3; ++i) {
        turnArray(mSquare, size);
        printMS(mSquare, size);
        msRows(mSquare, size);
        msColumns(mSquare, size);
        msDiagonals(mSquare, size);
    }
    
    // Delete the array
    for(int i=0; i!=size; ++i) {
        delete [] mSquare[i];
    }
    delete [] mSquare;
    
    return 0;
}
