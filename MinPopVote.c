
//---------------------------------------------------------------------------------------------------------------------------------------------------------
/*
Fall Semester 2024
Project 4: Win Presidency With Only 20% Support?
Course: CS 211 Programming Practicum
Section: 4pm Lecture Wed & Fri, 12pm Lab Tue
System: Zybooks Advanced IDE and Replitt
Author: Priyanjali Rudra

Description:
The purpose of this project is to answer the central question, 
What is the fewest number of popular votes you could get 
and still be elected President of the United States of America? 
My code uses data from previous election starting from 1828 til 2020 to calculate information such as 
Total Electoral Votes, Total Popular Votes, and gather data such as state information to then use on the functions
minPopVoteAtLeast() and minPopVoteAtLeastFast() to get the answer for our central question for every election year.
*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"


//Calculates and returns the total number of electoral votes
int totalEVs(State* states, int szStates) {

    //Iterates through the states array and adds the electoral votes for each state
    int sum = 0;
    for(int i = 0; i < szStates; i++) {
        sum += states[i].electoralVotes;
    }
    return sum; // modify or replace this line

}

//Calculates and returns the total number of popular votes
int totalPVs(State* states, int szStates) {

    //Iterates through the states array and adds the popular votes for each state
    int sum = 0;
    for(int i = 0; i < szStates; i++) {
        sum += states[i].popularVotes;
    }
    return sum;

}

/*
Sets the settings of the overall program by traversing the argv statements, if command line argument settings are invalid
Settings will be set interactively in main.
Application will handle the following commands:

[-y yr] = sets the election year for the program    
    valid [yr] values are perfect multiples of 4,    
    between 1828 and 2020, inclusively;
    if yr is not an election year, then set [year] to 0;  
    default is 0 ([year] then set by user-input later)

[-q] = quiet mode; if ON, do not print the full State list read-in    
    from file AND do not print the subset of States    
    needed to win with minimum popular votes;  
    default is OFF 

[-f] = fast mode; if ON, use the "fast" version of the functions    
    that include memoization to find the minimum     
    number of popular votes to win the election;   
    default is OFF   
*/
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    //Initialize Settings
    *year = 0; 
    *quietMode = false; 
    *fastMode = false; 

    //for loop iterates through the argv commands
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-y") == 0) {
            //if -y is not the last argument, the argument after -y is set as the year
            if (i + 1 < argc && sscanf(argv[i + 1], "%d", year) == 1) {
                //if the year is invalid ex. -f, less than 1828 or greater than 2020 or not divisible by 4, default year is 0
                if (*year < 1828 || *year > 2020 || *year % 4 != 0) {
                    *year = 0;
                }
                i++; // Skip the next argument as it is the year
            } else {
                *year = 0;
                return false; // Invalid year argument
            }
            //if -q is found quiet mode is turned on
        } else if (strcmp(argv[i], "-q") == 0) {
            *quietMode = true;
            //if -f is found fast mode is turned on
        } else if (strcmp(argv[i], "-f") == 0) {
            *fastMode = true;
        } else {
            return false; // Invalid argument
        }
    }

    //settings are succesfully set
    return true;
}

void inFilename(char* filename, int year) {
    
    //stores name of filename in variable filename
    sprintf(filename, "data/%d.csv", year);
    return;
}

void outFilename(char* filename, int year) {
    
    //stores name of filename in variable filename
    sprintf(filename, "toWin/%d_win.csv", year);
    return;
}

/*
Parses through a single line of data from the election data file and sets the following member variables
[stateName],[postalCode],[electoralVotes],[popularVotes]
Function accepts anything for the four parsed items and does NOT check if each individual item is valid.
Returns true if there are four items, and return false if there are more or less than four items. 
*/
bool parseLine(char* line, State* myState) {

    char* token; //stores State name
    char* tokens[4]; //stores line in tokenized format
    int tokenCount = 0;  //number of tokens collected

    // Make a copy of the line to avoid modifying the original string
    char lineCopy[100];
    strncpy(lineCopy, line, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0'; // Ensure null-termination

    // Tokenize the line
    token = strtok(lineCopy, ",");
    while (token != NULL && tokenCount < 4) {
        tokens[tokenCount++] = token;
        token = strtok(NULL, ",");
    }
    // Check if we have exactly 4 tokens
    if (tokenCount != 4) {
        return false;
    }

    // Assign tokens to the State structure
    //State name
    strncpy(myState->name, tokens[0], sizeof(myState->name));
    myState->name[sizeof(myState->name) - 1] = '\0'; // Ensure null-termination

    //State postalCode
    strncpy(myState->postalCode, tokens[1], sizeof(myState->postalCode));
    myState->postalCode[sizeof(myState->postalCode) - 1] = '\0'; // Ensure null-termination

    //State electoral Votes
    myState->electoralVotes = atoi(tokens[2]);

    //State popular Votes
    myState->popularVotes = atoi(tokens[3]);

    return true;
}


/*
Opens the election data file filename for reading, and read in the data one line at a time. 
Immediately return false if filename cannot be found. 
After file is opened use repeated calls to the parseLine() function to fill the struct array allStates.
Returns true once entire file is read.
*/
bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0; //required initialization prior to incrementing. 

    FILE* file = fopen(filename, "r"); //opens file
    if (file == NULL){
        return false; //if file is invalid immediately returns false
    }
    char line[100]; //stores each line of file, continues if line contains information
    while (fgets(line, sizeof(line), file) != NULL){
        //uses parseLine function to store info from line into State member variables
        if (parseLine(line, &allStates[*nStates])){
            //# of states increases
            (*nStates)++;
        }
        else { //if data members were not succesfully set returns false
            return false;
        }
    }
    //file has been succesfully read to completion
    return true; 
}

//Main Recursion Function:
/*
Returns the MinInfo associated with the subset of states that has the minimum popular vote total 
While still having enough electoral votes to win the election.
Considers every possible combination of States in the array, 
Checks if the total electoral votes for that subset is enough to win the election, 
And calculates the total popular votes for the subset.
The subset chosen is the one with the least number of popular votes but enough electoral votes to win the election.
*/
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    
    MinInfo result; //associated with the subset of states that has the min popular vote total
    //Initializes MinInfo member variables
    result.subsetPVs = 0;
    result.sufficientEVs = false;
    result.szSomeStates = 0;

    // Base case 1: No more states to consider
    if (start == szStates) {
        result.sufficientEVs = (EVs <= 0);  // Sufficient if EVs are met or exceeded
        return result;
    }

    // Base case 2: Electoral votes threshold is met or exceeded
    if (EVs <= 0) {
        result.sufficientEVs = true;  // We met or exceeded the required electoral votes
        return result;
    }

    // Recursive case 1: Exclude the current state
    MinInfo exclude = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    // Recursive case 2: Include the current state
    MinInfo include = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    //Include the popular votes of the state being added to subset
    include.subsetPVs += (states[start].popularVotes/2) + 1;

    // Add the state to the subset in the include path
    include.someStates[include.szSomeStates] = states[start];
    //Increases number of states in suubset
    include.szSomeStates++;

    // Compare the two subsets: include vs exclude
    if (exclude.sufficientEVs && include.sufficientEVs) {
        // Both are sufficient, return the one with the smaller popular votes
        if (include.subsetPVs < exclude.subsetPVs) {
            
            return include;
        } else {
            
            return exclude;
        }
    } else if (include.sufficientEVs) {
        // Only include is sufficient, return include
        
        return include;
    } else {
        // Only exclude is sufficient or both are insufficient, return exclude
        
        return exclude;
    }
}


//Given wrapper function, calls recursive function
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}


//Fast and Optimized version of minPopVoteAtLeast() function using memorization table
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    
    //Checks whether either Base Cases have been met or if position has already been checked
    if (start < szStates && EVs >= 0 && memo[start][EVs].subsetPVs != -1) { //Memory Issue Here??
        return memo[start][EVs];
    }
    

    MinInfo result; 
    result.szSomeStates = 0;

    // Base case 1
    if (start == szStates) {
        result.sufficientEVs = (EVs <= 0);
        if (start < szStates && EVs >= 0) {
            memo[start][EVs] = result;
        }
        return result;
    }

    // Base case 2
    if (EVs <= 0) {
        result.sufficientEVs = true;
        result.subsetPVs = 0;
        if (start < szStates && EVs >= 0) {
            memo[start][EVs] = result;
        }
        return result;
    }

    // Recursive case: exclude the current state
    MinInfo exclude = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo); //Memory Issue

    // Recursive case: include the current state
    MinInfo include = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);
    include.subsetPVs += (states[start].popularVotes / 2) + 1;

    // Add the state to the subset
    include.someStates[include.szSomeStates] = states[start];
    include.szSomeStates++;

    // Compare the two subsets: include vs exclude
    if (exclude.sufficientEVs && include.sufficientEVs) {
        // Both are sufficient, return the one with the smaller popular votes
        if (include.subsetPVs < exclude.subsetPVs) {
            memo[start][EVs] = include;
            result = include;
        } 

        else {
            memo[start][EVs] = exclude;
            result = exclude;
        }
    } 
    //if only include meets EVs requirement, returns include
    else if (include.sufficientEVs) {
        memo[start][EVs] = include;
        return include;
    } 
    //if only exclude meets EVs requirement, returns exclude
    else {
        memo[start][EVs] = exclude;
        return exclude;
    }

    // Store the result in the memoization table
    if (start < szStates && EVs >= 0) {
        memo[start][EVs] = result;
    }

    return result;
}


//Wrapper function, calls FAST recursive function
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*)); //Allocates memory for memo table
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo)); //Allocates memory for each row in memo table
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1; //sets each value to -1, to indicate it has not been set yet
        }
    }
    MinInfo result = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    //Calls FAST recursive function to find best subset

    //frees all haep allocated memory within memo
    for (int i = 0; i <= szStates; i++) {
        free(memo[i]);
    }
    free(memo);

    return result;
}

//Prints summary to console and winning strategy data to output file
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {

    //Sorts Name, PostalCode, Electoral Votes and Popular Votes to be in Alaphabetical Order
    int i;
    int j;
    char TempStateName[100];
    char TempPostCode[4];
    int TempElectoralVotes = 0;
    int TempPopularVotes = 0;
    for (i = 1; i < toWin.szSomeStates; ++i) {
        j = i;
        // Insert data[i] into sorted part
        // stopping once data[i] in correct position
        while (j > 0 && toWin.someStates[j].name > toWin.someStates[j-1].name) {
            strcpy(TempStateName, toWin.someStates[j].name);
            strcpy(TempPostCode, toWin.someStates[j].postalCode);
            TempElectoralVotes = toWin.someStates[j].electoralVotes;
            TempPopularVotes = toWin.someStates[j].popularVotes;

            strcpy(toWin.someStates[j].name, toWin.someStates[j-1].name);
            strcpy(toWin.someStates[j].postalCode, toWin.someStates[j-1].postalCode);
            toWin.someStates[j].electoralVotes = toWin.someStates[j-1].electoralVotes;
            toWin.someStates[j].popularVotes = toWin.someStates[j-1].popularVotes;

            strcpy(toWin.someStates[j-1].name, TempStateName);
            strcpy(toWin.someStates[j-1].postalCode, TempPostCode);
            toWin.someStates[j-1].electoralVotes = TempElectoralVotes;
            toWin.someStates[j-1].popularVotes = TempPopularVotes;

            --j;
        }
    }
    
    //File for writing strategy is opened, if invalid returns null
    FILE* file = fopen(filenameW, "w");
    if (file == NULL) {
        return false;
    }
    else { //first line is different and prints [TotalEVs],[TotalPVs],[EVsWon],[PVsWon]
        fprintf(file, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);
    }

    // prints summary for all states in console
    for(int i = 0; i < toWin.szSomeStates; i++){
        fprintf(file, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, 
            toWin.someStates[i].electoralVotes, toWin.someStates[i].popularVotes/2 + 1);
    }

    //output file is closed
    fclose(file);

    return true;
}