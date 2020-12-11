# Quispe_CSCI2275_FinalProject
For my final project, I will be creating a program that will read in election data from the 2020 election of every county in the US. This information will be of the election percentages and voter count for each presidential candidate and I will use this information to create a model from the first and second digits of each voter count to create a graph based on Benford’s Law. Benford’s Law is an observation about the frequency distribution of leading digits in many real-life sets of numerical data. Curiously, the frequency distribution creates a “universal” curve that many real-life data sets follow and I aim to create similar distributions to compare how well the election data matches up with Benford’s Law. Such comparisons are used to serve as a way to flag data for fraud or tampering and, amongst allegations of fraud in this current election, I aim to do this as well.

To store the data and interact with it, I plan to use a Binary Search Tree and Linked List to create nodes for each individual county and their election results. The two data structures will be connected together. The BST will store nodes with unique county names but given that some counties have the same name, each BST node will also have a linked list object which will hold all other counties that have the same name. The BST will be organized in alphabetical order according to the name of a county. **Program Note:** when asked to type in the candidate name enter either "Trump" or "Biden" not their full name like "Joe Biden"
	
When running the code, please use allElectionData.txt. All of the functions work to my knowledge but please let me know if you do find a bug. When calling option 10, compare the expected and actual relative frequencies. Large deviations from the expected relative frequencies is often a sign of data manipulation. However, when running the Benford's test on a specific state (**stateBenford()** not **countryBenford()**), you'll find that there is much more deviation when running the test on states because the data set is much smaller. In the 2020 election, many have tried to claim fraud in several key states using the results from a Benford's Law test on a given state's election data as proof. However, running this test on such a small data set produces highly skewed results. I've included the ability to run the test on states for learning-purposes but is otherwise useless in a real-world context.
For clarification when interpreting the results from my program I’d advise that you watch this video about Benford’s law. You only have to watch up to 5 minutes to get a sense of what’s happening.
https://www.youtube.com/watch?v=vIsDjbhbADY

**About Election Data**

I got all of the election data I used in this program from Politico.com. Unfortunately, they did not have data on Alaskan counties when I was creating a data file so it is not included in the published file. However, there are still 3,111 counties in the current file which is sufficient to create a reliable Benford analysis. There's also a few key US counties that are missing from the data file such as Los Angeles County, San Bernardino County, and other large counties. These counties happen to be some of the biggest in the USA so I'm rationalizing their absence to them not having an official ballot count at the time I created this data file. Nonetheless, their absence will not have a dramatic affect on the outcome of the analysis.

**Command Lines**

g++ finalProject.cpp BBST.cpp LL.cpp -std=c++11 -o finalProject

*to load in file...*

./finalProject allElectionData.txt

**Functions**
1. printInOrderBBST()
     -This will print out all of the counties in the BBST and all the counties from within the linked lists of each BST node.
2. winningCountiesForState()
     -This will return all of the counties that a candidate won in a given state
3. countiesWithMinVoters()
     -This will return counties with a given minimum voter registration amount. For example, maybe you want to see which counties have more than 150,000 registered voters in Colorado.
4. closeElections()
     -This will return all of the counties where the difference between Trump and Biden’s percentage points were within 2% of each other otherwise known as a close election.
5. printCountyStatistics()
     -For a given county, this will print out all of the statistics that have to do with that county.
6. countryBenford_first()
     -This will run a Benford’s Law test for the entire country to find the distribution of the first digit of every voter count for a particular candidate.Follow with option 10 to find the actual distribution of relative frequencies.
7. countryBenford_second()
     -This will run a Benford’s Law test for the entire country to find the distribution of the second digit of every voter count for a particular candidate. Follow with option 10 to find the actual distribution of relative frequencies.
8. stateBenford_first()
     -This will run a Benford’s Law test for the entire country to find the distribution of the first digit of every voter count for a given candidate in a given state. Follow with option 10 to find the actual distribution of relative frequencies.
9. stateBenford_second()
     -This will run a Benford’s Law test for the entire country to find the distribution of the second digit of every voter count for a given candidate in a given state. Follow with option 10 to find the actual distribution of relative frequencies.
10. showBenfordStats()
     -This will show the distribution of relative frequencies for each digit of a given data set. You will be asked to input what type of Benford’s test you used. If you used the second degree Benford’s test, type in “Second” otherwise type in “First”. In the code, I provide the expected the relative frequencies when this function is called.
