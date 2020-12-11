#include <iostream>
#include <fstream>
#include <sstream>
#include "BBST.h"
#include <queue>
using namespace std;

string removeSpecialCharacters(string s){    
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z')){                             
            s.erase(i, 1);             
            i--;         
        }     
    }    
    return s; 
}

int main(int argc, char const *argv[]){
    string filename = argv[1];
    ifstream myFile(filename);
    string lineFromFile;
    BBST counties;
    while(getline(myFile, lineFromFile)){
        stringstream ss(lineFromFile);
        string state;
        getline(ss, state, ',');
        string county;
        getline(ss, county, ',');
        string trumpNum;
        getline(ss, trumpNum, ',');
        string trumpPct;
        getline(ss, trumpPct, ',');
        string bidenNum;
        getline(ss, bidenNum, ',');
        string bidenPct;
        getline(ss, bidenPct);
        double trumpPercent = stod(trumpPct);
        double bidenPercent = stod(bidenPct);
        counties.addCountyNode(county, state, trumpNum, trumpPercent, bidenNum, bidenPercent);
    }
    bool exitProgram = false; 
    while(exitProgram == false){
       //put menu here
           std::string dmenu = "======Main Menu=====\n"
                   "1. Print All Counties in USA\n"
                   "2. Get Counties Where Given Candidate Won\n"
                   "3. Find Counties with Minimum Amount of Registered Voters\n"
                   "4. Get Counties with Close Election Result (within 3%)\n"
                   "5. Print a Given County's Stats\n"
                   "6. Perform 1st-Degree Benford's Test on Country for Given Candidate\n"
                   "7. Perform 2nd-Degree Benford's Test on Country for Given Candidate\n"
                   "8. Perform 1st-Degree Benford's Test on State for Given Candidate\n"
                   "9. Perform 2nd-Degree Benford's Test on State for Given Candidate\n"
                   "10. Display Relative Frequencies from Benford's Test\n"
                   "11. Exit";
  
   int choice;
   bool exit = false;
  
   cout << dmenu << endl;
  
   while(cin >> choice) {
       // flush the newlines and other characters
       cin.clear();
       cin.ignore();
      
       switch (choice) {
           case 1:
           {
               cout<<"Printing All Counties in the United States...."<<endl;
               counties.printInOrderBBST();
               break;
           }
           case 2:
           {
               std::string state;
               std::string candidate;
               cout<<"For which state do you wish to see the election results..."<<endl;
               getline(cin, state);
               cout<<"Now, for which candidate ('Trump' or 'Biden')?"<<endl;
               getline(cin, candidate);
               cout<<"Printing the counties that "<<candidate<<" won in "<<state<<"..."<<endl;
               counties.winningCountiesForState(state, candidate);
               break;
           }
           case 3:
           {
               string sMinVoter;
               int minVoter;
               string state;
               cout<<"From which state do you wish to see registered voter statistcs?"<<endl;
               getline(cin, state);
               cout<<"What is the minimum registered voter count you wish to see?"<<endl;
               getline(cin, sMinVoter);
               bool breakB = false;
               for (int i = 0; i < sMinVoter.length(); i++){
                    if (isdigit(sMinVoter[i]) == false){
                        cout<<"Invalid Input: Input numbers only when prompted"<<endl;
                        breakB = true;
                    }
                    break;
                }
                if(breakB == true){
                    break;
                }
               minVoter = stoi(sMinVoter);
               cout<<"printing counties with given minimum registered voters......"<<endl;
               counties.countiesWithMinVoters(state, minVoter);
               break;
           }
           case 4:
           {
               string state;
               cout<<"From which state do you wish to see counties with close elections?"<<endl;
               getline(cin, state);
               counties.closeElections(state);
               break;
           }
           case 5:
           {
               string state;
               cout<<"In which state is the county located?"<<endl;
               getline(cin, state);
               string countyName;
               cout<<"What is the name of the county? (In the form 'Name' + 'County')"<<endl;
               getline(cin, countyName);
               //countyName = countyName + " County";
               counties.printCountyStatistics(state, countyName);
               break;
           }
           case 6:
           {
               string candidate;
               cout<<"Who is the candidate you wish to run a 1st-Degree Benford's Test on?"<<endl;
               getline(cin, candidate);
               cout<<"Printing frequencies of each digit 1-9"<<endl;
               counties.countryBenford_first(candidate);
               cout<<"Follow this command with choice 10 if you wish to see the relative frequencies of each digit"<<endl;
               break;
           }
           case 7:
           {
               string candidate;
               cout<<"Who is the candidate you wish to run a 2nd-Degree Benford's Test on?"<<endl;
               getline(cin, candidate);
               cout<<"Printing frequencies of each digit 0-9"<<endl;
               counties.countryBenford_second(candidate);
               cout<<"Follow this command with choice 10 if you wish to see the relative frequencies of each digit"<<endl;
               break;
           }
           case 8:
           {
               string candidate;
               string state;
               cout<<"Who is the candidate you wish to run a 1st-Degree Benford's Test on?"<<endl;
               getline(cin, candidate);
               cout<<"In which state?"<<endl;
               getline(cin, state);
               cout<<"Printing frequencies of each digit 1-9"<<endl;
               counties.stateBenford_first(state, candidate);
               cout<<"Follow this command with choice 10 if you wish to see the relative frequencies of each digit"<<endl;
               break;
           }
           case 9:
           {
               string candidate;
               string state;
               cout<<"Who is the candidate you wish to run a 2nd-Degree Benford's Test on?"<<endl;
               getline(cin, candidate);
               cout<<"In which state?"<<endl;
               getline(cin, state);
               cout<<"Printing frequencies of each digit 0-9"<<endl;
               counties.stateBenford_second(state, candidate);
               cout<<"Follow this command with choice 10 if you wish to see the relative frequencies of each digit"<<endl;
               break;
           }
           case 10:
           {
               string type;
               cout<<"Which degree of Benford did you use? 'First' or 'Second' depending on which you option you previously called."<<endl;
               cin>>type;
               if(type == "First"){
                   std::string expected = "Expected Relative Frequencies for 1st-Degree Benford\n"
                   "For 1's. Expect approximately 0.301\n"
                   "For 2's. Expect approximately 0.176\n"
                   "For 3's. Expect approximately 0.125\n"
                   "For 4's. Expect approximately 0.097\n"
                   "For 5's. Expect approximately 0.079\n"
                   "For 6's. Expect approximately 0.067\n"
                   "For 7's. Expect approximately 0.058\n"
                   "For 8's. Expect approximately 0.051\n"
                   "For 9's. Expect approximately 0.046\n";
                   cout<<expected<<"\n"<<endl;
                   cout<<"Printing Out Actual Frequencies"<<endl;
                   counties.showBenfordStats(type);
               }
               else if(type == "Second"){
                   std::string expected = "Expected Relative Frequencies for 2nd-Degree Benford\n"
                   "For 0's. Expect approximately 0.120\n"
                   "For 1's. Expect approximately 0.111\n"
                   "For 2's. Expect approximately 0.108\n"
                   "For 3's. Expect approximately 0.102\n"
                   "For 4's. Expect approximately 0.100\n"
                   "For 5's. Expect approximately 0.097\n"
                   "For 6's. Expect approximately 0.091\n"
                   "For 7's. Expect approximately 0.090\n"
                   "For 8's. Expect approximately 0.089\n"
                   "For 9's. Expect approximately 0.086\n";
                   cout<<expected<<"\n\n\n"<<endl;
                   cout<<"Printing Out Actual Frequencies"<<endl;
                   counties.showBenfordStats(type);
               }
               break;
           }
           case 11:
           {
               exitProgram = true;
               break;
           }
       }
       if (exitProgram) {
            break;
        }
        
        cout << dmenu << endl;
   }
   }

}
