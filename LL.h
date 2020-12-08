#ifndef LL_H
#define LL_H
#include <iostream>
using namespace std;

struct LLcounty{
    std::string state;
    std::string countyName;
    int trumpVotes;
    string sTrumpVotes;
    double trumpPct;
    int bidenVotes;
    string sBidenVotes;
    double bidenPct;
    LLcounty *next;
    
    LLcounty(string cName, string sName, string trumpNum, double tPct, string bidenNum, double bPct)
    {
        state = sName;
        countyName = cName;
        sTrumpVotes = trumpNum;
        trumpVotes = stoi(sTrumpVotes);
        trumpPct = tPct;
        sBidenVotes = bidenNum;
        bidenVotes = stoi(sBidenVotes);
        bidenPct = bPct;
        next = NULL;
    }
};

class LLcounties
{
public:
    LLcounties(){};
    void printLLWords();
    void addCounty(string cName, string sName, string trumpNum, double tPct, string bidenNum, double bPct);
    bool isEmpty();
    void printStateCandidateCombo(std::string state, std::string candidate);
    void LLminVoterCount(std::string state, int minVoterNum);
    void LLcloseElections(std::string state);
    void LLprintCountyStatistics(std::string state, std::string countyName);
    void LLstateBenford_first(string state, string candidate, vector<int> &relFreq);
    void LLcountryBenford_first(std::string candidate, vector<int> &relFreq);
    //-------
    void LLstateBenford_second(string state, string candidate, vector<int> &relFreq);
    void LLcountryBenford_second(std::string candidate, vector<int> &relFreq);
private:
    LLcounty *first = NULL;
    void insertToVector(int digit, vector<int> &relFreq, string type);
};

#endif