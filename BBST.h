#ifndef BST_H
#define BST_H
#include <string>
#include "LL.h"
#include <queue>
using namespace std;

struct countyNode{
    std::string name;
    std::string state;
    string sTrumpVotes;
    int trumpVotes;
    string sBidenVotes;
    int bidenVotes;
    double trumpPercent;
    double bidenPercent;
    LLcounties duplicates;
    countyNode* parent;
    countyNode* leftChild;
    countyNode* rightChild;
    
    countyNode(std::string in_word, std::string sName, std::string tvotes, double tpct, string bvotes, double bpct){
        name = in_word;
        state = sName;
        sTrumpVotes = tvotes;
        trumpVotes = stoi(sTrumpVotes);
        trumpPercent = tpct;
        sBidenVotes = bvotes;
        bidenVotes = stoi(sBidenVotes);
        bidenPercent = bpct;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};


class BBST
{
    
public:
    BBST();
    void addCountyNode(std::string in_word, std::string sName, string tvotes, double tpct, string bvotes, double bpct); //Done
    void printInOrderBBST(); //Done
    void winningCountiesForState(std::string state, std::string candidate); //Done
    void countiesWithMinVoters(std::string state, int minVoterNum); //Done
    void closeElections(std::string state); //Done
    void printCountyStatistics(std::string state, std::string countyName); //Done
    void countryBenford_first(std::string candidate);  //Done
    void countryBenford_second(std::string candidate); //Done
    void stateBenford_first(std::string state, std::string candidate); //Done
    void stateBenford_second(std::string state, std::string candidate); //Done
    void showBenfordStats(std::string type); //Done
    vector<int> relFreq;
    //country report function

protected:
    
private:
    void printRelFreq(std:: string type);
    countyNode* searchBBST(std::string word); //DONE
    void insertToVector(int digit, vector<int> &relFreq, string type);
    
    void printBBST(countyNode *node);
    countyNode* root = NULL;
};

#endif