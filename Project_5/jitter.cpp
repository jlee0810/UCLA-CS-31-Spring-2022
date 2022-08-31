#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std; 

const int MAX_WORD_LENGTH = 20;

int editStandards(int distance[],
                  char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int nStandards)
{
    if (nStandards < 0) { //Treat a negative nStandards as if it were 0
        nStandards = 0;
    }

    int deleted = 0; //Counter for deletions needed

    for (int i = 0; i < nStandards - deleted;) {
        bool correct = true; //Default assume that the current standard doesn't need a deletion

        if (distance[i] <= 0) { //The distance is not positive - Need deletion
            correct = false;
        }
        if (word1[i][0] == '\0' || word2[i][0] == '\0') { //Word contains no characters - Need Deletion
            correct = false;
        }
        
        for (int j = 0; word1[i][j] != '\0'; j++ ) { 
            if (!isalpha(word1[i][j])) { //Contains a character that is not a letter (for word1) - Need Deletion
                correct = false;
                break; //No need to look further this standard needs to be deleted
            }
            word1[i][j] = tolower(word1[i][j]); //Must transform all upper case letter to lower
        }

        for (int j = 0; word2[i][j] != '\0'; j++ ) { //Contains a character that is not a letter - Need Deletion
            if (!isalpha(word2[i][j])) {
                correct = false;
                break; //No need to look further this standard needs to be deleted
            }
            word2[i][j] = tolower(word2[i][j]); //Must transform all upper case letter to lower
        }

        for (int k = 0; k < i; k++) { //Compare every standard up until where index i is at 
            if ((strcmp(word1[i], word1[k]) == 0) && (strcmp(word2[i], word2[k]) == 0)) { //If the standards are equal
                correct = false; 
                if (distance[k] < distance[i]) { //The longer distance replace the shorter distance
                    distance[k] = distance[i];
                } 
            }
        }

        if (correct == false) { //Needs a deletion because it is either unnecessary or invalid
            //Save the incorrect standard into temps 
            //We will assign this temp later on to the very end of all three arrays
            int tempDistance = distance[i];
            char tempWord1 [MAX_WORD_LENGTH+ 1] = {'\0'};
            char tempWord2 [MAX_WORD_LENGTH+ 1] = {'\0'};
            strcpy(tempWord1, word1[i]);
            strcpy(tempWord2, word2[i]);

            //Remove the incorrect standard by replacing it with the last standard in the array
            distance[i] = distance[nStandards - 1 - deleted]; 
            strcpy(word1[i], word1[nStandards - 1 - deleted]);
            strcpy(word2[i], word2[nStandards - 1 - deleted]);

            //Assign to the last array the "need to be deleted" array so we never see it again
            distance[nStandards - 1 - deleted] = tempDistance; 
            strcpy(word1[nStandards - 1 - deleted], tempWord1);
            strcpy(word2[nStandards - 1 - deleted], tempWord2);

            deleted++;
            //We don't increment by 1 as we deleted the incorrect/not necessary standard by switching it with the last standard of array
            //We still need to stay on the current index as we need to examine the replacement standard
        }
        else {
            i++; //Move onto the next standard
        }
    }
    return nStandards - deleted; //Return how many standards survive
}
int determineMatchLevel(const int distance[],
                        const char word1[][MAX_WORD_LENGTH+1],
                        const char word2[][MAX_WORD_LENGTH+1],
                        int nStandards,
                        const char jeet[])
{
    if (nStandards < 0) { //Treat a negative nStandards as if it were 0
        nStandards = 0;
    }

    char translate[280] = {'\0'}; //Create an empty cstring array to exclude all non-alphabetic characters from the jeet
    int translateIndex = 0; //Counter for the translate array index

    //This step modifies the jeet so it exlcudes any character that is not alphabetic or space 
    bool wasSpace = false; //Default at start wasSpace is false
    for (int i = 0; jeet[i] != '\0'; i++) {
        if (isalpha(jeet[i])) { //If it is an alphabetic character
            wasSpace = false; //Since it was an alphabetic character wasSpace is set to false
            translate[translateIndex] = tolower(jeet[i]); //Save to the current index of translate the lower case of character
            translateIndex++; 
            translate[translateIndex] = '\0'; //Assigns a null character after the last character
        }
        else if (jeet[i] == ' ') { //If it is a space
            if(wasSpace == true) { //If the previous character of jeet was a space
                continue; //Move on we don't need to add this space as we only want one space with a separation
            }
            else {
                wasSpace = true; //We inputted in a space so wasSpace is set to true
                translate[translateIndex] = jeet[i]; //Since previous character of jeet wasn't a space we add this space to translate
                translateIndex++;
                translate[translateIndex] = '\0'; //Assigns a null character after the last character
            }
        }
        else { //If the current character of jeet wasn't alphabetic or a space skip to next character
            continue;
        }
    }

    //This step creates an array so we can observe each word as an element of an array
    char separate[1000][MAX_WORD_LENGTH + 1] = {'\0'}; //Create an empty cstring array to separate each word by space and save them as individual element
    int separateIndex = 0; //Saves how many index there are in the separate array
    int charIndex = 0; //Counter for character of each string in the separate array

    for (int i = 0; translate[i] != '\0'; i++) { //Loops through characters in the translate array
        if (translate[i] == ' ' || translate[i] == '\0') {
            separateIndex++; //Increment separate index by 1 as it is a new string
            charIndex = 0; //Reset to 0
        
        }
        else {
            separate[separateIndex][charIndex] = translate[i]; //Save to the character to each element of separate array until space or null
            charIndex++;
            separate[separateIndex][charIndex] = '\0';
        }
    }



    int foundStandard = 0; //Counter for standards matched

    for (int i = 0; i < nStandards; i++) { //Loops through each standard
        bool found = false; //-default false
        int indexWord1 = 0; //Holds index where word1 of standard is found -default 0
        int indexWord2 = 0; //Holds index where word2 of standard is found - default 0

        for (int j = 0; j <= separateIndex; j++) { //Loops through the separate array 
            if(strcmp(word1[i], separate[j]) == 0) { //If word1 of standard is found in the jeet/separate array
                indexWord1 = j; //Save index of word1
                
                for (int k = j; k <= separateIndex; k++) { //word2 comes after word1 so starting from the index of word1 loop
                    if(strcmp(word2[i], separate[k]) == 0) { //If word2 of standard is found in the jeet/separate array
                        indexWord2 = k; //Save index of word2
                        if(indexWord2 - indexWord1 <= distance[i] && indexWord2 - indexWord1 > 0) { //If the distance is valid and positive
                            found = true;
                            foundStandard++; //Increment counter for standards matched by 1 
                            break;
                        }
                    }
                }
            }
            if (found == true) { //Since match is found we want to move on to the next standard therefore break
                break;
            }
        }
    }

    
    return foundStandard; //Return number of standards found

}
int main() {
    const int TEST1_NSTANDARDS = 4;
            int test1dist[TEST1_NSTANDARDS] = {
                2,             4,         1,         13
            };
            char test1w1[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
                "eccentric",   "space",  "electric", "were"
            };
            char test1w2[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
                "billionaire", "capsule", "car",     "eccentric"
            };
            assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                "the eccentric fellow man is a billionaire eccentric billionaire.") == 1);
            cout << "All tests succeeded" << endl;
    
}