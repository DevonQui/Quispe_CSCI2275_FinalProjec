#include <iostream>
#include "LL.h"
#include <cmath>
#include <vector>
using namespace std;


void LLcounties::printLLWords(){
    if(first == NULL){
        cout<<"No new words have been added"<<endl;
        return;
    }
    LLcounty *crawler = first;
    while(crawler != NULL){
        cout<<crawler->countyName<<"------"<<crawler->state<<endl;
        crawler = crawler->next;
    }
};

void LLcounties::addCounty(string cName, string sName, string trumpNum, double tPct, string bidenNum, double bPct){
    LLcounty * tmp = first;
    if(first == NULL){
        first = new LLcounty(cName, sName, trumpNum, tPct, bidenNum, bPct);
        return;
    }
    LLcounty * newNode = new LLcounty(cName, sName, trumpNum, tPct, bidenNum, bPct);
    while( tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = newNode;
    return;
};

bool LLcounties::isEmpty(){
    if(first != NULL){
        return false;
    }
    return true;
}

void LLcounties::printStateCandidateCombo(std::string state, std::string candidate){
    LLcounty *currentWord = first;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(currentWord->state == state){
                if(candidate == "Trump"){
                    if(currentWord->trumpPct > currentWord->bidenPct){
                        cout<<"Trump won in "<< currentWord->countyName << " with " << currentWord->trumpPct<<" percent of the vote"<<endl;
                    }
                }
                if(candidate == "Biden"){
                    if(currentWord->bidenPct > currentWord->trumpPct){
                        cout<<"Biden/Harris won in "<< currentWord->countyName << " with " << currentWord->bidenPct<<" percent of the vote"<<endl;
                    }
                }
            }
            currentWord = currentWord->next;
        }
    }
    return;
};

void LLcounties::LLminVoterCount(std::string state, int minVoterNum){
    LLcounty *currentWord = first;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(currentWord->state == state){
                double decimal = currentWord->bidenPct/100;
                int voterCount = currentWord->bidenVotes/decimal;
                if(voterCount >= minVoterNum){
                    cout<<currentWord->countyName<<" has "<<voterCount<<" registered voters"<<endl;
                }
            }
            currentWord = currentWord->next;
        }
    }
    return;
};

void LLcounties::LLcloseElections(std::string state){
    LLcounty *currentWord = first;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(currentWord->state == state){
                double electionDiff = abs(currentWord->bidenPct - currentWord->trumpPct);
                if(electionDiff <= 3){
                    cout<<currentWord->countyName<<" had a close election:"<<" within "<<electionDiff<<" election points"<<endl;
                }
            }
            currentWord = currentWord->next;
        }
    }
    return;
};

void LLcounties::LLprintCountyStatistics(std::string state, std::string countyName){
    LLcounty *currentWord = first;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(currentWord->state == state){
                if(currentWord->countyName == countyName){
                    cout<<currentWord->countyName<<", "<<currentWord->state<<endl;
                    cout<<currentWord->bidenVotes<<" people voted for Joe Biden/Kamala Harris accounting for "<<currentWord->bidenPct<<" percent of this county's voter turnout"<<endl;
                    cout<<currentWord->trumpVotes<<" people voted for Donald Trump accounting for "<<currentWord->trumpPct<<" percent of this county's voter turnout"<<endl;
                }
            }
            currentWord = currentWord->next;
        }
    }
    return;
};

void LLcounties::LLstateBenford_first(string state, string candidate, vector<int> &relFreq){
    LLcounty *currentWord = first;
    char firstDig;
    int fd;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(currentWord->state == state){
                if(candidate == "Trump"){
                    firstDig = currentWord->sTrumpVotes.at(0);
                    fd = (int)firstDig - 48;
                    insertToVector(fd, relFreq, "First");
                }
                else if(candidate == "Biden"){
                    firstDig = currentWord->sBidenVotes.at(0);
                    fd = (int)firstDig - 48;
                    insertToVector(fd, relFreq, "First");
                }
                else {
                    return;
                }                
            }
            currentWord = currentWord->next;
        }
    }
    return;
}

void LLcounties::LLcountryBenford_first(std::string candidate, vector<int> &relFreq){
    LLcounty *currentWord = first;
    char firstDig;
    int fd;
    while(currentWord != NULL){
            if(candidate == "Trump")
            {
                firstDig = currentWord->sTrumpVotes.at(0);
                fd = (int)firstDig - 48;
                insertToVector(fd, relFreq, "First");
            }
            if(candidate == "Biden")
            {
                firstDig = currentWord->sBidenVotes.at(0);
                fd = (int)firstDig - 48;
                insertToVector(fd, relFreq, "First");
            }
            currentWord = currentWord->next;
        }
}

void LLcounties::LLstateBenford_second(string state, string candidate, vector<int> &relFreq){
    LLcounty *currentWord = first;
    char secondDig;
    int sd;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(currentWord->state == state){
                if(candidate == "Trump"){
                    secondDig = currentWord->sTrumpVotes.at(1);
                    sd = (int)secondDig - 48;
                }
                else if(candidate == "Biden"){
                    secondDig = currentWord->sBidenVotes.at(1);
                    sd = (int)secondDig - 48;
                }
                else {
                    return;
                }
                insertToVector(sd, relFreq, "Second");
            }
            currentWord = currentWord->next;
        }
    }
    return;
}

void LLcounties::LLcountryBenford_second(std::string candidate, vector<int> &relFreq){
    LLcounty *currentWord = first;
    char secondDig;
    int sd;
    if(currentWord == NULL){
        return;
    }
    else{
        while(currentWord != NULL){
            if(candidate == "Trump")
            {
                if(!(currentWord->sTrumpVotes.length() < 2)){
                    secondDig = currentWord->sTrumpVotes.at(1);
                    sd = (int)secondDig - 48;
                    insertToVector(sd, relFreq, "Second");
                }
            }
            else if(candidate == "Biden")
            {
                if(!(currentWord->sBidenVotes.length() < 2)){
                    secondDig = currentWord->sBidenVotes.at(1);
                    sd = (int)secondDig - 48;
                    insertToVector(sd, relFreq, "Second");
                }
            }
            currentWord = currentWord->next;
        }

    }
}

void LLcounties::insertToVector(int digit, vector<int> &relFreq, string type){
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
        return;
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
        return;
    }
    return;
}