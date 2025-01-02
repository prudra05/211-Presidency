#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

//Testing TotalEvs()
bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 12, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false;
    }
    printf(" Checking totalEVs() for 6 States:\n");
    res = totalEVs(aStates,6);
    if (res != 48) {
        printf("  individual state EVs are 5, 8, 12, 6, 7, 10\n");
        printf("  expected total EVs = 48, actual total EVs = %d\n",res);
        return false;
    }   
    
    return true;
}

//Testing TotalPVs()
bool test_totalPVs() {

    State aStates[10];
    int res;
    
    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 10;

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    if (res != 38) {
        printf("  individual state PVs are 5, 8, 12, 6, 7\n");
        printf("  expected total PVs = 38, actual total PVs = %d\n",res);
        return false;
    }
    printf(" Checking totalPVs() for 6 States:\n");
    res = totalPVs(aStates,6);
    if (res != 48) {
        printf("  individual state PVs are 5, 8, 12, 6, 7, 10\n");
        printf("  expected total PVs = 48, actual total PVs = %d\n",res);
        return false;
    }
    
    return true;
}

//Not Passing 3 Tests
/*
bool test_setSettings() {
    //-----------------------------------------------------------   
    // TODO: Task 2 - write your own test case for setSettings();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    int year = 0;
    bool fastMode, quietMode;

    // Test case 1: Valid arguments
    char* argv1[] = {"./app.exe", "-f", "-q", "-y", "2020"};
    if (setSettings(5, argv1, &year, &fastMode, &quietMode) == true) {
        if (year == 2020 && fastMode == true && quietMode == true) {
            printf("  Test case 1: Valid arguments success\n");
        }
    }
    else {
        printf("  Test case 1: Invalid arguments failure\n");
        return false;
    }

    // Test case 2: Invalid year argument
    char* argv2[] = {"./app.exe", "-q", "-y", "1800", "-f"};

    if (setSettings(5, argv2, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == true) {
            printf("  Test case 2: Invalid year argument success\n");
        }
    }
    else {
        printf("  Test case 2: Invalid year argument failure\n");
        return false;
    }

    // Test case 3: Invalid year argument
    char* argv3[] = {"./app.exe", "-q", "-y", "2024", "-f"};

    if (setSettings(5, argv3, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == true) {
            printf("  Test case 3: Invalid year argument success\n");
        }
    }
    else {
        printf("  Test case 3: Invalid year argument failure\n");
        return false;
    }

    // Test case 4: Invalid year argument not divisible by 4
    char* argv4[] = {"./app.exe", "-q", "-y", "2013", "-f"};

    if (setSettings(5, argv4, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == true) {
            printf("  Test case 4: Invalid year argument success\n");
        }
    }
    else {
        printf("  Test case 4: Invalid year argument failure\n");
        return false;
    }

    //Test case 5: no year argument
    char* argv5[] = {"./app.exe", "-q", "-f"};

    if (setSettings(3, argv5, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == true) {
            printf("  Test case 5: no year argument success\n");
        }
    }
    else {
        printf("  Test case 5: no year argument failure\n");
        return false;
    }

    //Test case 6: Invalid arguments
    char* argv6[] = {"./app.exe", "-f", "-t", "-y", "2016"};

    if (setSettings(5, argv6, &year, &fastMode, &quietMode) == false) {
        if (year == 2016 && fastMode == true && quietMode == false) {
            printf("  Test case 6: Invalid arguments success\n");
            return true;
        }
    }
    else {
        printf("  Test case 6: Invalid arguments failure\n");
        return false;
    }

    
    //Test case 7: Invalid year arguments
    char* argv7[] = {"./app.exe", "-f", "-y"};

    if (setSettings(3, argv7, &year, &fastMode, &quietMode) == false) {
        if (year == 0 && fastMode == true && quietMode == false) {
            printf("  Test case 7: Invalid year arguments success\n");
        }
    }
    else {
        printf("  Test case 7: Invalid year arguments failure\n");
        return false;
    }

    //Test case 8: no year argument
    char* argv8[] = {"./app.exe", "-q", "-y", "-f"};

    if (setSettings(4, argv8, &year, &fastMode, &quietMode) == false) {
        if (year == 0 && fastMode == false && quietMode == true) {
            printf("  Test case 8: no year argument success\n");
        }
    }
    else {
        printf("  Test case 8: no year argument failure\n");
        return false;
    }
    

    //Test case 9: valid two arguments
    char* argv9[] = {"./app.exe","-f"};

    if (setSettings(2, argv9, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == false) {
            printf("  Test case 9: valid two arguments success\n");
        }
    }
    else {
        printf("  Test case 9: valid two arguments failure\n");
        return false;
    }

    //Test case 10: valid 2 arguments
    char* argv10[] = {"./app.exe","-q"};

    if (setSettings(2, argv10, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == false && quietMode == true) {
            printf("  Test case 10: valid 2 arguments success\n");
        }
    }
    else {
        printf("  Test case 10: valid 2 arguments failure\n");
        return false;
    }

    //Test case 11: invalid year argument
    
    char* argv11[] = {"-f"};

    if (setSettings(1, argv11, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == false && quietMode == true) {
            printf("  Test case 11: Invalid arguments success\n");
        }
    }
    else {
        printf("  Test case 11: Invalid arguments failure\n");
        return false;
    }


    return true; //modify this
}
*/

//Not Passing 3 Tests

bool test_setSettings() {
    //-----------------------------------------------------------   
    // TODO: Task 2 - write your own test case for setSettings();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    int year = 0;
    bool fastMode, quietMode;

    // Test case 1: Valid arguments
    char* argv1[] = {"./app.exe", "-f", "-q", "-y", "2020"};
    if (setSettings(5, argv1, &year, &fastMode, &quietMode) == true) {
        if (year == 2020 && fastMode == true && quietMode == true) {
            printf("  Test case 1: Valid arguments success\n");
            return true;
        }
    }
    else {
        printf("  Test case 1: Invalid arguments failure\n");
        return false;
    }

    // Test case 2: Invalid year argument
    char* argv2[] = {"./app.exe", "-q", "-y", "55", "-f"};
    if (setSettings(5, argv2, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == true) {
            printf("  Test case 2: Invalid year argument success\n");
        }
    }
    else {
        printf("  Test case 2: Invalid year argument failure\n");
        return false;
    }

    //Test Case 3: no year
    char* argv3[] = {"./app.exe", "-q", "-f"};
    if (setSettings(3, argv3, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == true) {
            printf("  Test case 3: Invalid year argument success\n");
        }
    }
    else {
        printf("  Test case 3: Invalid year argument failure\n");
        return false;
    }

    //Test Case 4: Invalid arguments
    char* argv4[] = {"./app.exe", "-f", "-t", "-y", "2016"};
    if (setSettings(5, argv4, &year, &fastMode, &quietMode) == false) {
        if (year == 2016 && fastMode == true && quietMode == false) {
            printf("  Test case 4: Invalid arguments success\n");
            return true;
        }
    }
    else {
        printf("  Test case 4: Invalid arguments failure\n");
        return false;
    }

    //Test Case 5: Invalid arguments
    char* argv5[] = {"./app.exe", "-f", "-y"};
    if (setSettings(3, argv5, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == true && quietMode == false) {
            printf("  Test case 5: Invalid arguments success\n");
        }
    }
    else {
        printf("  Test case 5: Invalid arguments failure\n");
        return false;
    }

    //Test Case 6
    char* argv6[] = {"./app.exe", "-q", "-y", "-f"};
    if (setSettings(4, argv5, &year, &fastMode, &quietMode) == true) {
        if (year == 0 && fastMode == false && quietMode == true) {
            printf("  Test case 6: Invalid arguments success\n");
        }
    }
    else {
        printf("  Test case 6: Invalid arguments failure\n");
        return false;
    }

    return false;
}

//Testing inFilename()
bool test_inFilename() {

    char filename[50];
    inFilename(filename, 2020);  
    if (strcmp(filename, "data/2020.csv") == 0) {
        printf("  Test case 1: inFilename() success\n");
    }
    else{
        printf("  Test case 1: inFilename() failure\n");
        return false;
    }

    char filename2[50];
    inFilename(filename2, 2008);

    if (strcmp(filename2, "data/2008.csv") == 0) {
        printf("  Test case 2: inFilename() success\n");
    }
    else{
        printf("  Test case 2: inFilename() failure\n");
        return false;
    }

    return true;
}

//Testing outFilename()
bool test_outFilename() {

    char filename[50];
    outFilename(filename, 2020);

    if (strcmp(filename, "toWin/2020_win.csv") == 0) {
        printf("  Test case 1: outFilename() success\n");
    }
    else{
        printf("  Test case 1: outFilename() failure\n");
        return false;
    }

    char filename2[50];
    outFilename(filename2, 2008);

    if (strcmp(filename2, "toWin/2008_win.csv") == 0) {
        printf("  Test case 2: outFilename() success\n");
    }
    else{
        printf("  Test case 2: outFilename() failure\n");
        return false;
    }

    return true;
}

//Error in 1 Test after implementation of test readElectionData
//Testing parseLine
bool test_parseLine() {
    char line[100];
    State myState;

    strcpy(line, "Illinois,IL,18,10");
    if (parseLine(line, &myState) == true) {

        if (strcmp(myState.name, "Illinois") == 0 && strcmp(myState.postalCode, "IL") == 0) {

            if (myState.electoralVotes == 18 && myState.popularVotes == 10) {

                printf("  Test case 1: parseLine() success\n");

            } 
            else {
                printf("  Test case 1: parseLine() failure\n");
                return false;
            }
        } 
        else {
            printf("  Test case 1: parseLine() failure\n");
            return false;
        }
    } 
    else {

        printf("  Test case 1: parseLine() failure\n");
        return false;
    }
    return true;
}

//Not Passing 1 Test
//Testing readElectionData()
bool test_readElectionData() {

    State allStates[51];
    int nStates;
    if (readElectionData("data/2008.csv", allStates, &nStates) == true) {
        if (nStates <= 51) {
            if(strcmp(allStates[0].name, "Alabama") == 0 && strcmp(allStates[0].postalCode, "AL") == 0) {
                if(allStates[0].electoralVotes == 9 && allStates[0].popularVotes == 2099819) {
                    printf("  Test case 1: readElectionData() success\n");
                }
                else {
                    printf("  Test case 1: readElectionData() failure (Votes)\n");
                    return false;
                }
            }
            
            else {
                printf("  Test case 1: readElectionData() failure (Name)\n");
                return false;
            }
        }
        else {
            printf("  Test case 1: readElectionData() failure (#States)\n");
            return false;
        }
    }
    else {
        printf("  Test case 1: readElectionData() failure (file open failure)\n");
        return false;
    }

    if (readElectionData("data/nonexistent.csv", allStates, &nStates) == false) {
        printf("Test case 2: readElectionData() success (Invalid file)\n");
    } 
    else {
        printf("Test case 2: readElectionData() failure (Invalid file)\n");
        return false;
    }

    if (readElectionData("data/2012.csv", allStates, &nStates) == true) {
        if (nStates <= 51) {
            if (strcmp(allStates[1].name, "Alaska") == 0 && strcmp(allStates[1].postalCode, "AK") == 0 &&
                allStates[1].electoralVotes == 3 && allStates[1].popularVotes == 301694) {
                printf("Test case 3: readElectionData() success\n");
            } 
            else {
                printf("Test case 3: readElectionData() failure (Data mismatch)\n");
                return false;
            }
        } 
        else {
            printf("Test case 3: readElectionData() failure (#States)\n");
            return false;
        }
    } 
    else {
        printf("Test case 3: readElectionData() failure (File open failure)\n");
        return false;
    }

    return true;
}

//Testing slow recursion function, minPopVoteAtLeast() using wrapper function minPopVoteToWin()
bool test_minPVsSlow() {

    State states[4] = {
        {"State1", "S1", 10, 1000},
        {"State2", "S2", 20, 2000},
        {"State3", "S3", 30, 3000},
        {"State4", "S4", 40, 4000}
    };

    // Test case: Predictable MinInfo values
    MinInfo result = minPopVoteToWin(states, 4);
    int expectedEVs = (10 + 20 + 30 + 40) / 2 + 1; // 51 EVs required to win
    int expectedPVs = 3002; // Minimum popular votes to win State3 and State4

    if (result.sufficientEVs && result.subsetPVs == expectedPVs && result.szSomeStates == 2) {
        bool correctStates = (strcmp(result.someStates[0].name, "State2") == 0 && strcmp(result.someStates[1].name, "State4") == 0) ||
        (strcmp(result.someStates[0].name, "State4") == 0 && strcmp(result.someStates[1].name, "State2") == 0);
        if (correctStates) {
            printf("Test case: minPopVoteToWin() success\n");
        } 
        else {
            printf("Test case: minPopVoteToWin() failure (Incorrect states)\n");
            return false;
        }
    } 
    else {
        printf("Test case: minPopVoteToWin() failure (Incorrect MinInfo values)\n");
        return false;
    }

    return true;
}

//How to test this!!
//Testing fast recursion function, minPopVoteAtLeastFast() using wrapper function minPopVoteToWinFast()
bool test_minPVsFast() {

    return false; //modify this
}

//Main function starts here
int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}