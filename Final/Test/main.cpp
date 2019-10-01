
/*
 TypingTester.cpp
 Programming Fundimentals 2
 Dr. Liu
 Due Date: 04/17/17
 Team Members:
	Grayson Arneson
	Nataly Carbonell
	Brian Garner
	Nicholas Miller
	Alexander Rodriguez
	Matthew Weisfeld
	Ahad Virani
 
 Brief Description: This program outputs a prompt for the user to type as fast as they can. Only five words are output
 at a time in order to keep the terminal free of clutter. The goal for the user is to try to match the shown output,
 if they match a word correctly they receive points towards their words per minute(WPM). This is saved on a local
 scoreboard. Scoreboards and stories are written to and taken in as .txt files.
 */

#include "finalP.h"

//Console Tester Functions
//To compile:
//g++ -o TypingTester.out TypingTester.cpp -std=c++11

//Scoreboard Functions

//you must use "write" before you can use "read". if you want to use "read" first, just use "write" and set the score value to zero (it wont add anything).
//this will print the high score list
void Leaderboard::read(string file)
{
    //Output the rank, score, and name of user in the leaderboard.
    cout << "rank\tscore\tname" << endl;
    ifstream worm(file + "ScoreBoard.txt");
    string line;
    for (int i = 0; getline(worm, line); i++)
    {
        cout << "#" << i + 1 << "\t" << line << endl;
    }
    worm.close();
}

//write expects the file name to NOT include the ".txt" (it adds that on its own). "name" can be any string and score must be an int.
//for me, the files end up in the same place as the file with this code
void Leaderboard::write(string file, string name, int score)
{
    //Max of 10 names for each leaderboard.
    string names[10];
    int scores[10];
    for (int i = 0; i < 10; i++)
    {
        names[i] = "0\tnone";
        scores[i] = 0;
    }
    
    ifstream worm(file + "ScoreBoard.txt");
    string line;
    for (int i = 0; getline(worm, line); i++)
    {
        stringstream ss(line);
        string bit;
        ss >> bit;
        scores[i] = stoi(bit, nullptr, 10);
        names[i] = line;
    }
    
    for (int i = 9; i >= 0; i--)
    {
        if (score > scores[i])
        {
            if (i < 9)
                names[i + 1] = names[i];
            names[i] = to_string(score) + "\t" + name;
        }
    }
    
    //this code will make a file (if one with a matching names does not exit)
    //then it will write all the scores and names to it
    ofstream scoreBoardFile(file + "ScoreBoard.txt");
    for (int i = 0; i < 10; i++)
    {
        scoreBoardFile << names[i] << endl;
    }
    scoreBoardFile.close();
    
    worm.close();
    
}

//Random Text Functions
//Gets a random letter
char Rando::getRand()
{
    //Using ASCII codes, type cast a random int to a char to produce a random letter.
    return (char)(rand()%(122-97+1))+97;
}

//Gets a random punctuation
char Rando::getPunct()
{
    return punct[rand()%(sizeof(punct)-1)];
}

//Generates random word
string Rando::wordGenerator(){
    string s;
    int n = (rand()%10)+1;
    for(int i = 0; i<n; i++)
    {
        s+= getRand();
        
    }
    return s;
}

//Uses random words and punctuation to create a sentence.
string Rando::sentenceGenerator()
{
    int n = (rand()%10)+5;
    string s;
    for(int i = 0; i<n; i++){
        s += wordGenerator();
        if(i < n-1)
            s+= " ";
    }
    s+= getPunct();
    return s;
}

//Uses random sentences to create a random text file.
string Rando::randText(){
    string str;
    for(int counter = 0; counter <= 360;)
    {
        int n = (rand()%10)+5;
        counter += n;
        string s = "";
        for(int i = 0; i<n; i++){
            s += wordGenerator();
            if(i < n-1)
                s+= " ";
        }
        s+= getPunct();
        s+=" ";
        str += s;
    }
    return str;
}

//Linked List Implimentation

//Method to print out linked list.
void LinkedList::print()
{
    //Create temp ptr used for iterating
    Node *curr = first;
    cout << "Linked List State: ";
    //Loop while curr !=null
    while(curr)
    {
        cout<< curr->data << " -> ";
        curr = curr->next;
    }
    cout << "End" << endl;
}

//Method to add to linked list.
void LinkedList::add(string input)
{
    Node *curr = first;
    Node *end = nullptr;
    while(curr)
    {
        end = curr;
        curr = curr->next;
    }
    //Now curr is null and end is the last node
    //Create a new node and add it to end
    Node *newNode = new Node();
    newNode->data = input;
    if(end)
    {
        //If list is not empty
        end->next = newNode;
    }else{
        //If list is empty
        first = new Node();
        first->data = input;
    }
}

//Returns a value at an index of the linked list.
string LinkedList::get(size_t i)
{
    Node *curr = first;
    size_t count = 0;
    //Moves through the linked list couting each time
    while(curr && count != i)
    {
        curr = curr->next;
        ++count;
    }
    //If curr is null or count is not equal to i
    /*
     if(!curr || count != i)
     {
     throw out_of_range("Index out of range");
     }
     */
    return curr->data;
    
}

//Removes value at an index of the linked list.
void LinkedList::remove(size_t i)
{
    Node *curr = first;
    size_t count = 0;
    
    while(curr && count !=(i-1))
    {
        curr = curr->next;
        ++count;
    }
    
    /*
     if(!curr || count != (i-1))
     {
     throw out_of_range("Index out of range");
     }
     */
    //Assigns the curr to the new next and deletes then inbetween one.
    Node *del = curr->next;
    curr->next = del->next;
    delete del;
    del = nullptr;
    
}

//Inserts data at an index of the linked list.
void LinkedList::insert(size_t i, string input)
{
    Node *curr = first;
    size_t count = 0;
    
    while(curr && count !=(i-1))
    {
        curr = curr->next;
        ++count;
    }
    /*
     if(!curr || count != (i-1))
     {
     throw out_of_range("Index out of range");
     }
     */
    //Makes a new node, points it to the next node, and reassigns the previous node to point to it.
    Node *newNode = new Node();
    newNode->data = input;
    newNode->next = curr->next;
    curr->next = newNode;
    
}

//Returns size of linked list.
size_t LinkedList::size()
{
    Node *curr = first;
    size_t count = 0;
    
    while(curr)
    {
        curr = curr->next;
        ++count;
    }
    
    return count;
}

//Replaces element at an index of the linked list.
void LinkedList::replace(size_t i, string input)
{
    Node *curr = first;
    size_t count = 0;
    
    while(curr && count !=i)
    {
        curr = curr->next;
        ++count;
    }
    /*
     if(!curr || count != i)
     {
     throw out_of_range("Index out of range");
     }
     */
    curr->data = input;
    
}

//Removes first element of linked list
void LinkedList::removeFirst()
{
    Node *curr = first;
    first = curr->next;
    delete curr;
    curr = nullptr;
    
}

//TypingTest functions
int Typing::getScore(LinkedList ori, LinkedList gravy, int time)
{
    int wpm = 0;
    for(int i = 0; i < gravy.size(); ++i)
    {
        if(ori.get(i) == gravy.get(i))
        {
            ++wpm;
        }
    }
    wpm /= time;
    return wpm;
}

//Linux implementation of getch. Allows program to take in every keystroke as input
//User does not have to hit enter for in order for program to take in input.
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

//Heart of the program.
//Handles output of stories, comparing of strings, refreshing of terminal
//Compares time of user test start to current time to tell if the test is over
//
void Typing::consoleTest(LinkedList ori, int test, int time)
{
    
    LinkedList gravy;
    
    //Declarations
    char userChar;
    string userTyping;
    string testing;
    
    //Gets current time at beginning of program and stores it in variable called timeBegin
    //clock_t timeBegin;
    
    timeval a;
    timeval b;
    cout << "\033[2J\033[1;1H";
    cout << "Press any button to begin" << endl;
    while(true)
    {
        userChar = getch();
        if (((int)userChar >= 0 && (int)userChar < 240) && (int)userChar != 10) {
            gettimeofday(&a, 0);
            cout << "\033[2J\033[1;1H";
            break;
        }
    }
    
    int size = ori.size();
    
    for (int i = 0; i < size;) {
        gettimeofday(&b, 0);
        if (i < size-5) {
            cout << ori.get(i) << " ";
            cout << ori.get(i + 1) << " " << ori.get(i + 2) << " ";
            cout << ori.get(i + 3) << " " << ori.get(i + 4);
            cout << endl;
        }
        if (i == size-4) {
            cout << ori.get(i) << " ";
            cout << ori.get(i + 1) << " " << ori.get(i + 2) << " " << ori.get(i + 3) << endl;
        }
        else if (i == size-3) {
            cout << ori.get(i) << " ";
            cout << ori.get(i + 1) << " " << ori.get(i + 2) << endl;
        }
        else if (i == size-2) {
            cout << ori.get(i) << " ";
            cout << ori.get(i + 1) << endl;
        }
        else if (i == size-1) {
            cout << ori.get(i);
            cout << endl;
        }
        
        //_getch(); causes the program to update after every keyboard stroke
        userChar = getch();
        
        //Booleans
        //earlyEnd tells if user hits esc to end the test early
        //timeUp keeps track of if user has run out of time in the test.
        bool earlyEnd = false;
        bool timeUp = false;
        
        //While userChar isnt space bar
        while (userChar != ' ') {
            
            
            //Compare current time to time of program beginning. If time > preset time seconds, display "Times up" and end the program. In seconds.
            if ((b.tv_sec-a.tv_sec) > time*60) {
                //First cout refreshed the console. Second prints "Times up" to let the user know the test is over
                cout << "\033[2J\033[1;1H";
                cout << "Times up";
                //Set boolean timeUp = true
                timeUp = true;
                break;
            }else{
                //If user enters backspace (Since terminal doesnt handle it).
                if ((int)userChar == 127) {
                    if (userTyping.length() != 0) {
                        userTyping = userTyping.substr(0, userTyping.length() - 1);
                    }
                    //Refresh terminal
                    cout << "\033[2J\033[1;1H";
                    //If statements are required to show fewer words as the story ends
                    //If there were no if statements, program would go out of bounds in the linked list.
                    if (i < size-5) {
                        cout << ori.get(i) << " ";
                        cout << ori.get(i + 1) << " " << ori.get(i + 2) << " ";
                        cout << ori.get(i + 3) << " " << ori.get(i + 4);
                        cout << endl;
                    }
                    if (i == size-4) {
                        cout << ori.get(i) << " ";
                        cout << ori.get(i + 1) << " " << ori.get(i + 2) << " " << ori.get(i + 3) << endl;
                    }
                    else if (i == size-3) {
                        cout << ori.get(i) << " ";
                        cout << ori.get(i + 1) << " " << ori.get(i + 2) << endl;
                    }
                    else if (i == size-2) {
                        cout << ori.get(i) << " ";
                        cout << ori.get(i + 1) << endl;
                    }
                    else if (i == size-1) {
                        cout << ori.get(i);
                        cout << endl;
                    }
                    //Output the string that the user has typed so far after the refresh.
                    cout << userTyping;
                }
                //Else if, ESC button is hit = end program early. (NO SCORE)
                else if ((int)userChar == 27) {
                    earlyEnd = true;
                    break;
                }
                //Else if, one of the unnecessary inputs is hit = IGNORE
                else if (((int)userChar >= 0 && (int)userChar < 32) || (int)userChar > 126){
                    // leave this blank
                }
                //Else, just add the key stroke to userTyping string and output the character to the console.
                
                else{
                    userTyping += userChar;
                    cout << userChar;
                }
            }
            //Retake input so that while loop runs again..
            userChar = getch();
        }
        //Add user string to linked list
        gravy.add(userTyping);
        userTyping = "";
        //Increment if statement
        i++;
        //Refresh terminal
        cout << "\033[2J\033[1;1H";
        
        if (i == size)
        {
            cout << "Cheater!" << endl;
        }
        //If time is up
        if (timeUp) {
            //Gives user score
            cout << "Your Score (WPM): " << getScore(ori, gravy, time) << "\n" << endl;
            Leaderboard a;
            string name = "aaa";
            //Lets user enter name to associate with their score
            cout << "Enter Name: ";
            //Take in user name
            cin >> name;
            cout << endl;
            string file = "Text" + to_string(test);
            cout << file;
            a.write(file, name, getScore(ori, gravy, time));
            
            //User can press any key to continue to main menu
            cout << "Press any button to continue" << endl;
            userChar = getch();
            if ((int)userChar >= 0 && (int)userChar < 240) {
                //Refresh terminal
                cout << "\033[2J\033[1;1H";
                break; // fix this so it will go back to main menu
            }
        }
        //If user hit escape to end early
        else if (earlyEnd) {
            //Do not assign score to user
            cout << "Exited early: No Score\n" << endl;
            //Allow them to continue to main method
            cout << "Press any button to continue" << endl;
            userChar = getch();
            if ((int)userChar >= 0 && (int)userChar < 240) {
                cout << "\033[2J\033[1;1H";
                break; // fix this so it will go back to main menu
            }
        }
    }
    
}

//Sets space as a delimiter
void Typing::limiter(string str, LinkedList &ori)
{
    string delimiter = " ";
    
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        ori.add(token);
        str.erase(0, pos + delimiter.length());
    }
    ori.add(str);
}

//Runs the actual test
void Typing::test(int time, int test)
{
    string str;
    if(test == 4)
    {
        Rando a;
        str = a.randText();
    }else{
        string textFile = "text" + to_string(test) + ".txt";
        //cout << textFile;
        ifstream file(textFile); //"/Users/MatthewWeisfeld/Desktop/ProgrammingFundimentals/ProgrammingFundimentals/code.txt"
        string temp;
        while(getline(file, temp))
        {
            str += temp;
        }
    }
    
    //cout << str;
    
    LinkedList ori;
    
    limiter(str, ori);
    //ori.print();
    
    consoleTest(ori, test ,time);
    
}

//Allows user to choose their time
int Typing::chooseTime()
{
    bool run = true;
    while(run)
    {
        cout << "------------------------------" << endl;
        cout << "Time Options:" << endl;
        cout << "1. 1 Minute" << endl;
        cout << "2. 2 Minutes" << endl;
        cout << "3. 3 Minutes" << endl;
        
        int selection;
        cin >> selection;
        
        //Removes strings.
        cin.clear();
        cin.ignore(1000, '\n');
        
        
        switch(selection)
        {
            case 1:
                return 1;
                break;
                
            case 2:
                return 2;
                break;
                
            case 3:
                return 3;
                break;
            default:
                cout << "Invalid: Try Again" << endl;
                break;
        }
        
    }
    return 0;
}

//Allows user to choose their story
int Typing::chooseText()
{
    bool run = true;
    while(run)
    {
        cout << "------------------------------" << endl;
        cout << "Text Options:" << endl;
        cout << "1. Story 1" << endl;
        cout << "2. Story 2" << endl;
        cout << "3. Story 3" << endl;
        cout << "4. Random" << endl;
        
        int selection;
        cin >> selection;
        
        switch(selection)
        {
            case 1:
                return 1;
                break;
                
            case 2:
                return 2;
                break;
                
            case 3:
                return 3;
                break;
                
            case 4:
                return 4;
                break;
                
            default:
                //Removes strings.
                cin.clear();
                cin.ignore(1000, '\n');
                
                cout << "Invalid: Try Again" << endl;
                break;
        }
        
    }
    return 0;
}

//Returns text from text files included in folder
string Typing::getText(int a)
{
    switch(a)
    {
        case 1:
            return "Story 1";
            break;
            
        case 2:
            return "Story 2";
            break;
            
        case 3:
            return "Story 3";
            break;
            
        case 4:
            return "Random";
            break;
    }
    return "Invalid: Try Again";
}

//Outputs and controls test menu
void Typing::testMenu()
{
    int minTime = 1;
    int textOptions = 1;
    
    bool run = true;
    while(run)
    {
        cout << "------------------------------" << endl;
        cout << "Test Options:" << endl;
        cout << "1. Start Test" << endl;
        cout << "2. Choose Time Limit: " << "Current Time Limit(minutes)-" << minTime <<endl;
        cout << "3. Choose Text: " << "Current Text-" << getText(textOptions) << endl;
        cout << "4. Back To Main Menu" << endl;
        
        int selection;
        cin >> selection;
        
        switch(selection)
        {
            case 1:
                test(minTime, textOptions);
                break;
                
            case 2:
                minTime = chooseTime();
                break;
                
            case 3:
                textOptions = chooseText();
                break;
                
            case 4:
                run = false;
                break;
                
            default:
                //Removes strings.
                cin.clear();
                cin.ignore(1000, '\n');
                
                cout << "Invalid: Try Again" << endl;
                break;
        }
    }
}

//Handles leaderboard I/O
void Typing::leaderboards()
{
    Leaderboard a;
    cout << "------------------------------" << endl;
    cout << "Text1 Leaderboards:" << endl;
    a.read("Text1");
    cout << endl;
    cout << "Text2 Leaderboards:" << endl;
    a.read("Text2");
    cout << endl;
    cout << "Text3 Leaderboards:" << endl;
    a.read("Text3");
    cout << endl;
    cout << "Random Leaderboards:" << endl;
    a.read("Text4");
}

//Handles main menu I/O
void Typing::mainMenu()
{
    cout << "WELCOME TO THE TYPING TESTER!" << endl;
    
    bool run = true;
    while(run)
    {
        cout << "------------------------------" << endl;
        cout << "Options:" << endl;
        cout << "1. Test" << endl;
        cout << "2. LeaderBoards" << endl;
        cout << "3. Quit" << endl;
        int selection;
        cin >> selection;
        
        switch(selection)
        {
            case 1:
                testMenu();
                break;
                
            case 2:
                leaderboards();
                break;
                
            case 3:
                run = false;
                cout << "Thanks For Playing!" << endl;
                break;
                
            default:
                //Removes strings.
                cin.clear();
                cin.ignore(1000, '\n');
                
                cout << "Invalid: Try Again!" << endl;
                break;
        }
    }
}

//Starts main menu
int main()
{
    //Creates a new instance of the typing texter and runs the main menu.
    Typing a;
    a.mainMenu();
    return 0;
}


/*
 all:
 g++ recursion.cpp -Wall -o recursion.exe
 */
