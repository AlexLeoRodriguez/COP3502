//
//  finalP.h
//  ProgrammingFundimentals
//
//  Created by Matthew Weisfeld on 4/10/17.
//  Copyright © 2017 Gateway3. All rights reserved.
//

#ifndef finalP_h
#define finalP_h

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <termios.h>
#include <cstdio>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

class Leaderboard
{
public:
    void read(string file);
    void write(string file, string name, int score);
};

class Rando
{
    const char punct [4] = {'?', '!', '.', ','};
public:
    char getRand();
    char getPunct();
    string wordGenerator();
    string sentenceGenerator();
    string randText();
};

struct Node
{
    Node *next = nullptr;
    string data;
};

class LinkedList
{
private:
    Node *first = nullptr;;
public:
    //Prints the list
    void print();
    //Add to the end of the list
    void add(string input);
    //Returns element at index i
    string get(size_t i);
    //Remove element at index i
    void remove(size_t i);
    //Add element at index i
    void insert(size_t i, string input);
    //Returns the size of the list
    size_t size();
    //Replaces a node
    void replace(size_t i, string input);
    //Removes the first node.
    void removeFirst();
};

class Typing
{
public:
    //Computes the wpm using the original and typed linked lists and the time limit.
    int getScore(LinkedList ori, LinkedList gravy, int time);
    //Runs the test by displaying the next 5 words with the first highlighted and taking inputs for the test.
    void consoleTest(LinkedList ori, int test ,int time);
    //Runs the main menu and exicutes the different options based on user input.
    void mainMenu();
    //Runs the typing test with the preset time and test.
    void test(int time, int test);
    //Changes the time of the test based on user input. 1-3 Minutes.
    int chooseTime();
    //Changes the text of the test based on user input. Story 1, Story 2, User-Input, Random.
    int chooseText();
    //Takes the numerical value of the text and returns the name of the text.
    string getText(int a);
    //Runs the test menu and exicutes the different options based on user input.
    void testMenu();
    //Runs the leaderboards.
    void leaderboards();
    //Puts all of the words of the string into the LinkedList where each word is a node.
    void limiter(string str, LinkedList &a);
};

#endif /* finalP_h */
