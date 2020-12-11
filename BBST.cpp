#include <iostream>
#include "BBST.h"
#include "LL.h"
#include <queue>
#include <cmath>
using namespace std;

BBST::BBST(){}

//Here is use a recursive algorithm to search through my Benford BST (BBST). For the while loop, I switched the conditions so that
//the program wouldn't try to find the ->word value of a NULL pointer and instead check if the pointer was NULL first
countyNode* BBST::searchBBST(std::string name){
    countyNode *searcher = root;
    while(searcher != NULL && searcher->name != name){
        if(name < searcher->name){
            searcher = searcher->leftChild;
        } else if(name > searcher->name){
            searcher = searcher->rightChild;
        }
    }
    return searcher;
};

//this is the method I use to add countyNodes to my Benford BST. It's a pretty standard insert function for a BST where if the root is NULL
//I'll automatically assign the root with the newNode. However, what's different about this insert() function is that if a duplicate
//is found I will instead place it into the duplicates linked list object that every countyNode has. This works because while every
//some counties may have the same name, they will all have a different state. Otherwise if the node doesn't already exist I'll place it into
//the BST based on the alphabetical order of the county names
void BBST::addCountyNode(string cName, string sName, string tvotes, double tpct, string bvotes, double bpct){
    countyNode *newNode = new countyNode(cName, sName, tvotes, tpct, bvotes, bpct);
    if(root == NULL){
        root = newNode;
        return;
    }
    countyNode* nF = searchBBST(cName);
    if(nF != NULL){
        nF->duplicates.addCounty(cName, sName, tvotes, tpct, bvotes, bpct);
        return;
    }
    else if(nF == NULL){
        countyNode *searcher = root;

        countyNode *searchLag;
        while(searcher != NULL){
            searchLag = searcher;

            if(cName < searcher->name){
                searcher = searcher->leftChild;
            } else {
                searcher = searcher->rightChild;
            }
        }

        if(cName < searchLag->name){
            searchLag->leftChild = newNode;
            newNode->parent = searchLag;
        } else {
            searchLag->rightChild = newNode;
            newNode->parent = searchLag;
        }

    }
};


//These two functions make up my helper private function and my public printInOrder() function. This function is also pretty standard
//besides the fact that at each call of the recursive function, the helper function will check if the currentCounty node has an
//empty duplicates linked list or not. If it's not empty, it will not only print the word at the BST node but it will also print
//all the nodes in its linked list object.
void BBST::printInOrderBBST(){
    printBBST(root);
};

void BBST::printBBST(countyNode* node){
    if(node != NULL){
        printBBST(node->leftChild);
        cout<<node->name<<"-----"<<node->state<<endl;
        if(!node->duplicates.isEmpty()){
            node->duplicates.printLLWords();
        }
        printBBST(node->rightChild);
    }
};


//This is my function that will print out all the counties that particular candidate won in a particular state which are both given by
//the user when the program is run. To traverse the Benford BST in this function I recognized the ability to do Breadth First Search on the BST
//and opted to do this instead of a recursive algorithm. Since everything is already ordered and has a direction in a BST I didn't need
//to include a visited boolean in the struct of the nodes as once a node was accessed it would never be accessed again. Within each iteration
//of the while loop, I'll pop from the queue and then check its properties against those given by the user and if there's a match
//I'll print out the county information accordingly. If the input is not either Trump or Biden the function will return an error statement
//In this function on line 117 you'll see that I also check if the linked list of a node is empty or not to see if they're might be a county
//within it that matches the parameters given by the user. At the end of the function I push the leftChild and rightChild of the node onto
//the queue
void BBST::winningCountiesForState(string state, string candidate){
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        if(n->state == state){
            if(candidate != "Biden" && candidate != "Trump"){
                cout<<"Invalid Input: Enter 'Biden' or 'Trump' and try again"<<endl;
                return;
            }
            if(candidate == "Trump"){
                if(n->trumpPercent > n->bidenPercent){
                    cout<<"Trump won in "<< n->name << " with " << n->trumpPercent<<" percent of the vote"<<endl;
                }
            }

            if(candidate == "Biden"){
                if(n->bidenPercent > n->trumpPercent){
                    cout<<"Biden/Harris won in "<< n->name << " with " << n->bidenPercent<<" percent of the vote"<<endl;
                }
            }
        }
        else if(!n->duplicates.isEmpty()){
            n->duplicates.printStateCandidateCombo(state, candidate);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }

    }
    return;
}

//This is my function that will return all the counties that have a minimum number of registered voters in a specific state. The point
//of this function was to allow the user to compare the density/population of a county to which presidential candidate won in that county
//For example, we might be able to test if more densely populated areas are generally more democratic given this year's election data.
//I also used a BFS to traverse the Benford BST for this function and also make sure to check if the linked list of a node contains
//a node that will match the parameters of the user. I also do some algebra within the while loop to get the estimate for the amount
//of registered voters for a county. I convert the percent of bidenVotes into a decimal and then divide his amount of votes by that decimal
void BBST::countiesWithMinVoters(string state, int minVoterNum){
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front();
        q.pop();
        if(n->state == state){
            double decimal = n->bidenPercent/100;
            int voterCount = n->bidenVotes/decimal;
            if(voterCount >= minVoterNum){
                cout<<n->name<<" has "<<voterCount<<" registered voters"<<endl;
            }
        }
        if(!n->duplicates.isEmpty()){
            n->duplicates.LLminVoterCount(state, minVoterNum);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }

    }
    return;
}


/*
This is my function to print out all of the close county election within a state. To determine what a close election was, I
considered how divisive this current election was and thought that a difference of three percentage points would be sufficient to
determine if an election was close or not. For this function I also use a BST to traverse the BST and also use similar functions to check on
the values contained within the linked list object of every single node in the BST
*/
void BBST::closeElections(string state){
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front();
        q.pop();
        if(n->state == state){
            double electionDiff = abs(n->bidenPercent - n->trumpPercent);
            if(electionDiff <= 3){
                cout<<n->name<<" had a close election:"<<" within "<<electionDiff<<" election points"<<endl;
            }
        }
        else if(!n->duplicates.isEmpty()){
            n->duplicates.LLcloseElections(state);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }

    }
    return;
}
/*
This is my function to print out the statistics of a specific county within a specific state. For this function I again use a BFS to traverse the BST
and the check the user parameters with each and every BST node and its respective linked list nodes. If the parameters match then 
I'll print out the proper information accordingly
*/
void BBST::printCountyStatistics(string state, string countyName){
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        if(n->state == state){
            if(n->name == countyName){
                cout<<n->name<<", "<<n->state<<endl;
                cout<<n->bidenVotes<<" people voted for Joe Biden/Kamala Harris accounting for "<<n->bidenPercent<<" percent of this county's voter turnout"<<endl;
                cout<<n->trumpVotes<<" people voted for Donald Trump accounting for "<<n->trumpPercent<<" percent of this county's voter turnout"<<endl;
            }
        }
        else if(!n->duplicates.isEmpty()){
            n->duplicates.LLprintCountyStatistics(state, countyName);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        } 

    }
    return;
}

/*
This is my function to run a first-degree Benford test on county election data of a particular state. At the beginning of the function
I assign benfordCalled with true so that the use will be able to call showBenfordStats() after running this test. I also make sure to clear
out all of the values of the private vector I use to store all of the frequencies of the first digit of each data point. Then after that
I push_back() 9 zeros, one for each value 1-9, to "initialize the vector". I then use a BFS to traverse the BST and check all of the county
against the use input. If the user input matches the values of the current node then I'll take the string-type number and take the first
value of it (since strings are arrays of chars). From there I will do a type conversion of the char to an int. However, because of the way
ASCII works I have to subtract the cast by 48 to be able to get the actual value of the char. After doing this I'll push this onto the
frequencies vector using insertToVector() which checks which index to increment determined by what the first number of the statistic is
*/
void BBST::stateBenford_first(string state, string candidate){
    benfordCalled = true;
    relFreq.clear();
    for(int i = 0; i < 9; i++){
        relFreq.push_back(0);
    }
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front();
        q.pop();
        char firstDig;
        int fd;
        if(n->state == state){
            if(candidate == "Trump"){
                firstDig = n->sTrumpVotes.at(0);
                fd = (int)firstDig - 48;
            }
            else if(candidate == "Biden"){
                firstDig = n->sBidenVotes.at(0);
                fd = (int)firstDig - 48;
            }
            else {
                return;
            }
            insertToVector(fd, relFreq, "First");
            
        }
        else if(!n->duplicates.isEmpty()){
            n->duplicates.LLstateBenford_first(state, candidate, relFreq);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }

    }
    printRelFreq("First");
    return;
}

/*
This is my function to print the frequencies of each number in the vector. Depending on whether the user ran a second-degree or
first-degree Benford test, the function will print out the values from either 0-9 or 1-9 respectively. 
*/
void BBST::printRelFreq(string type){
    if(type == "First"){
        for(int i = 0; i < relFreq.size(); i++){
            cout<<"Frequency of "<<(i+1)<<"'s :"<<relFreq[i]<<endl;
        }
    }
    if(type == "Second"){
        for(int i = 0; i < relFreq.size(); i++){
            cout<<"Frequency of "<<(i)<<"'s :"<<relFreq[i]<<endl;
        }
    }
}
/*
This is my function that will display the statistics from the Benford test. That statistics will just be the relative frequencies of
the data that we collected from calling the Benford test on the election data. Here you'll see that the first conditional checks if 
benfordCalled is true or false. benfordCalled is only set to true if the benfordTest is actually called and so if its never called
then this function will never run. Secondly, you can see another conditional beneath the first one which checks if all the values
of the vector are zero. If they're all zero then that means that proper input was never given so then the function will  tell you to
put in proper input. Otherwise the function will create a double from the total of the frequencies of each digit and the total amount of
data points that there were. Depending on whether the user ran a second-degree or first-degree Benford test, the function will print out
 the values from either 0-9 or 1-9 respectively.
*/
void BBST::showBenfordStats(string type){
    if(benfordCalled == false){
        cout<<"ERROR: CALL ONE OF THE OPTIONS 6-9 BEFORE YOU DISPLAY BENFORD STATISTICS"<<endl;
        return;
    }
    bool validInputs = false;
    for(int i = 0; i < relFreq.size(); i++){
        if(relFreq[i] != 0){
            validInputs = true;
        }
    }
    if(!validInputs){
        cout<<"ERROR: THE INPUTS FOR THE BENFORD TEST WERE INVALID"<<endl;
        return;
    }
    int total = 0;
    if(type == "First"){
        for(int i = 0; i < 9; i++){
            total = total + relFreq[i];
        }
        for(int i = 0; i < 9; i++){
            double relFrequency = (relFreq[i]/(double)total);
            cout<<"Relative Frequency of "<<(i+1)<<"'s :"<<relFrequency<<endl;
        }
    } else if (type == "Second"){
        for(int i = 0; i < 10; i++){
            total = total + relFreq[i];
        }
        for(int i = 0; i < 10; i++){
            double relFrequency = (relFreq[i]/(double)total);
            cout<<"Relative Frequency of "<<(i)<<"'s :"<<relFrequency<<endl;
        }
    }
}
/*
This is my function to call a first-degree Benford's test on the county data of the whole country. It's the same function as above but
it doesn't have to check against anything except which candidate we want to collect data. This is because we want to collect data from every state
and not just some particular state. Here is use the same technique of converting the first digit into an integer. 
*/
void BBST::countryBenford_first(string candidate){
    benfordCalled = true;
    relFreq.clear();
    for(int i = 0; i < 9; i++){
        relFreq.push_back(0);
    }
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        char firstDig;
        int fd;
        if(candidate == "Trump"){
            firstDig = n->sTrumpVotes.at(0);
            fd = (int)firstDig - 48;
        }
        else if(candidate == "Biden"){
            firstDig = n->sBidenVotes.at(0);
            fd = (int)firstDig - 48;
        }
        else {
            return;
        }
            //assigning the digit to the relative frequency vector
        insertToVector(fd, relFreq, "First");

        if(!n->duplicates.isEmpty()){
            n->duplicates.LLcountryBenford_first(candidate, relFreq);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }
    }
    printRelFreq("First");
    return;
}
/*
This is my function to run a second-degree Benford test on a specific state for a specific candidate. It uses the same logic as the other
Benford test functions but because we want to only see the second-digit of a data point and create our distribution from that (henve second-degree)
I had to change the way I got those values. I still had to get a char and convert into an integer and subtract 48 but I had to do it at an index of one.
I also had to make sure that there was a even a second digit to call. For example, I found that in Loving, Texas only 9 people voted from Kamala Harris
and Joe Biden which would only throw an error if I tried to get the second digit of that number. 
*/
void BBST::stateBenford_second(string state, string candidate){
    benfordCalled = true;
    relFreq.clear();
    for(int i = 0; i < 10; i++){
        relFreq.push_back(0);
    }
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        char secondDig;
        int sd;
        if(n->state == state){
            if(candidate == "Trump"){
                if(!(n->sTrumpVotes.length() < 2)){
                    secondDig = n->sTrumpVotes.at(1);
                    sd = (int)secondDig - 48;
                    insertToVector(sd, relFreq, "Second");
                }
            }
            else if(candidate == "Biden"){
                if(!(n->sBidenVotes.length() < 2)){
                    secondDig = n->sBidenVotes.at(1);
                    sd = (int)secondDig - 48;
                    insertToVector(sd, relFreq, "Second");
                }    
            }
            else {
                return;
            }
        }
        else if(!n->duplicates.isEmpty()){
            n->duplicates.LLstateBenford_second(state, candidate, relFreq);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }

    }
    printRelFreq("Second");
    return;
}
/*
This is my function to call a second-degree Benford's test on the entire country. This really just uses that same the logic as the
second-degree Benford test for the state level but instead we don't have to check any "state" condition and only the "candidate"
condition given by the user
*/
void BBST::countryBenford_second(string candidate){
    benfordCalled = true;
    relFreq.clear();
    for(int i = 0; i < 10; i++){
        relFreq.push_back(0);
    }
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        char secondDig;
        int sd;
        if(candidate == "Trump"){
            if(!(n->sTrumpVotes.length() < 2)){
                secondDig = n->sTrumpVotes.at(1);
                sd = (int)secondDig - 48;
                insertToVector(sd, relFreq, "Second");
            }
        }
        else if(candidate == "Biden"){
            if(!(n->sBidenVotes.length() < 2)){
                secondDig = n->sBidenVotes.at(1);
                sd = (int)secondDig - 48;
                insertToVector(sd, relFreq, "Second");
            }
        }
        if(!n->duplicates.isEmpty()){
            n->duplicates.LLcountryBenford_second(candidate, relFreq);
        }
        if(n->leftChild != NULL){
            q.push(n->leftChild);
        }
        if(n->rightChild != NULL){
            q.push(n->rightChild);
        }
    }
    printRelFreq("Second");
    return;
}

/*
This is my function for incrementing the frequency of a specific digit within the private vector variable stored included within
the BBST.h header file. For this depending on whether or not we are inserting for a second or first degree Benford's Law test we will
insert for numbers from 0-9 or 1-9 respectively. 
*/
void BBST::insertToVector(int digit, vector<int> &relFreq, string type){
    benfordCalled = true;
    if(type == "Second"){
        if(digit == 0){
            relFreq[0] = relFreq[0] + 1;
        }
        else if(digit == 1){
            relFreq[1] = relFreq[1] + 1;
        }
        else if(digit == 2){
            relFreq[2] = relFreq[2] + 1;
        }
        else if(digit == 3){
            relFreq[3] = relFreq[3] + 1;
        }
        else if(digit == 4){
            relFreq[4] = relFreq[4] + 1;
        }
        else if(digit == 5){
            relFreq[5] = relFreq[5] + 1;
        }
        else if(digit == 6){
            relFreq[6] = relFreq[6] + 1;
        }
        else if(digit == 7){
            relFreq[7] = relFreq[7] + 1;
        }
        else if(digit == 8){
            relFreq[8] = relFreq[8] + 1;
        }
        else if(digit == 9){
            relFreq[9] = relFreq[9] + 1;
        }
    }
    else if(type == "First"){
        if(digit == 1){
            relFreq[0] = relFreq[0] + 1;
        }
        else if(digit == 2){
            relFreq[1] = relFreq[1] + 1;
        }
        else if(digit == 3){
            relFreq[2] = relFreq[2] + 1;
        }
        else if(digit == 4){
            relFreq[3] = relFreq[3] + 1;
        }
        else if(digit == 5){
            relFreq[4] = relFreq[4] + 1;
        }
        else if(digit == 6){
            relFreq[5] = relFreq[5] + 1;
        }
        else if(digit == 7){
            relFreq[6] = relFreq[6] + 1;
        }
        else if(digit == 8){
            relFreq[7] = relFreq[7] + 1;
        }
        else if(digit == 9){
            relFreq[8] = relFreq[8] + 1;
        }
    }
    return;
}
