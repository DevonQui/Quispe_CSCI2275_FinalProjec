#include <iostream>
#include "BBST.h"
#include "LL.h"
#include <queue>
#include <cmath>
using namespace std;

BBST::BBST(){}

countyNode* BBST::searchBBST(std::string name){
    countyNode *searcher = root;
    while(searcher != NULL && searcher->name != name){ //switched the order of these conditionals so that the program wouldn't try to find the word of a NULL value
        if(name < searcher->name){
            searcher = searcher->leftChild;
        } else if(name > searcher->name){
            searcher = searcher->rightChild;
        }
    }
    return searcher;
};

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

void BBST::winningCountiesForState(string state, string candidate){
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        if(n->state == state){
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


void BBST::countiesWithMinVoters(string state, int minVoterNum){
    countyNode * begin = root;
    queue<countyNode*> q;
    q.push(begin);
    while(!q.empty()){
        countyNode *n = q.front(); //front returns a value
        q.pop(); //pop removes from queue
        if(n->state == state){
            double decimal = n->bidenPercent/100;
            int voterCount = n->bidenVotes/decimal;
            if(voterCount >= minVoterNum){
                cout<<n->name<<" has "<<voterCount<<" registered voters"<<endl;
            }
        }
        else if(!n->duplicates.isEmpty()){
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

void BBST::stateBenford_first(string state, string candidate){
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

void BBST::showBenfordStats(string type){
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

void BBST::countryBenford_first(string candidate){
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

void BBST::stateBenford_second(string state, string candidate){
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

void BBST::countryBenford_second(string candidate){
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

void BBST::insertToVector(int digit, vector<int> &relFreq, string type){
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