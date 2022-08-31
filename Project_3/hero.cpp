#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

bool hasProperSyntax(string tune) { 
    if (tune.size() == 0) { //Empty tune is syntactically correct
        return true;
    }

    int i = 0;
    while (i < tune.size()) {
        while (tune[i] != '/') {//Allows us to examine parts of the tune one by one
        if (tune[i] != 'G' && tune[i] != 'g' && tune[i] != 'R' &&
        tune[i] != 'r' && tune[i] != 'Y' && tune[i] != 'y' &&
        tune[i] != 'B' && tune[i] != 'b' && tune[i] != 'O' &&
        tune[i] != 'o') { //Checks if color is valid
            return false;
        }
        else {
            i++; //Examine after color
            if (i >= tune.size()) { //Blocks undefined behavior
                return false;
            }
        }

        switch (tune[i]){
            case '/': //Part of the tune ends
                break;
            default:
                return false; //Anything other than slash or digit is false
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                i++; //Examine if next char is digit or slash
                if (i >= tune.size()) { //Blocks undefined behavior
                    return false;
                }
                switch (tune[i]){
                    case '/':
                        break; //Part of the tune ends
                    default:
                        return false; //Anything other than slash or digit is false
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        i++; 
                        if (i >= tune.size()) { //Blocks undefined behavior
                            return false;
                        }
                        switch (tune[i]) {
                            case '/':
                                break; //Part of the tune ends
                            default:
                                return false; //The char must be slash
                        }
                }
            }
        }
        i++;
    }
    return true; //If everything passes syntactically correct
}

int convertTune(string tune, string& instructions, int& badBeat) {
    
    //Tune is not syntactically correct
    if (!hasProperSyntax(tune)) {
        return 1;
    }

    //At this point tune is syntactically correct
    //Set up variables we need
    string translation = ""; 
    int beatnumber = 0; 
    char color = ' ';

    int i = 0;
    while (i < tune.size()) {
        int sustain = 1; //Default sustain is 1

        if (tune [i] == '/') { //If the beat is just a slash
            translation += 'x'; //Translate to x
            beatnumber++; //Increase beatnumber by 1
            i++; //Move onto next character in string
            continue; //Go back to condition
        }

        if (isalpha(tune[i])) { //Beat starts with a color
            color = tune[i]; //Save it to color
            beatnumber++; //Increase beatnumber by 1
        }

        if (isdigit(tune[i + 1])) { //Checks if char after color is digit
            color = toupper(color); //Color to upper case as it will be sustained

            if (isdigit(tune[i + 2])) { //Checks if char after digit is also digit
                sustain = 10 * (tune[i + 1] - 48) + (tune[i + 2] - 48); //Changes char digits to int (10* first digit + second digit)

                int countBeat = 0; //Checks if correct amount of slashes
                for (int j = i + 3; j <= i + 2 + sustain; j++) { //Jumps to first slash and loop to count if there are correct amount of slashes
                    if (tune[j] != '/') {//If incorrect amount return 2
                        if (j >= tune.size()) {//If it ends prematurely 
                            badBeat = beatnumber + countBeat;
                            return 4; //return 4
                        }
                        else {
                            badBeat = beatnumber + countBeat; //bad beat is current beat + the amount of slashes we had
                            return 2;

                        }
                    }
                    countBeat++; //Counts slashes
                }
                if (sustain < 2) { //If sustain is lower than 2 return 3
                    badBeat = beatnumber; //bad beat is current beat
                    return 3;
                }


                beatnumber += sustain - 1; //beatnumber is sustain -1; -1 from color letter being counted as beat
                translation += string(sustain, color); //Add to translation color letters sustain number of times
                i += sustain + 3; //skips the letter then the two digits then the sustain number of slashes
            }

            else {
                sustain = (tune[i + 1] - 48); //Sustain is one digit convert char digit to int

                int countBeat = 0; //Checks if correct amount of slashes
                for (int j = i + 2; j <= i + 1 + sustain; j++) { //Jumps to first slash and loop to count if there are correct amount of slashes
                    if (tune[j] != '/') { //If incorrect amount return 2
                        if (j >= tune.size()) { //If it ends prematurely
                            badBeat = beatnumber + countBeat; 
                            return 4; //return 4
                        }
                        else {
                            badBeat = beatnumber + countBeat; //bad beat is current beat + the amount of slashes we had
                            return 2;
                        }
                    }
                    countBeat++; //Counts slashes
                }
                if (sustain < 2) { //If sustain is lower than 2 return 3
                    badBeat = beatnumber; //bad beat is current beat
                    return 3;
                }

                beatnumber += sustain - 1; //beatnumber is sustain -1; -1 from color letter being counted as beat
                translation += string(sustain, color); //Add to translation color letters sustain number of times
                i+= sustain + 2; //skips the letter then the one digit then the sustain number of slashes
            }
        } 

        else {
            translation += tolower(color); //Not sustain so lower case and just added once
            i += sustain + 1; //skips the letter then the one slash that follows it
            beatnumber += sustain - 1; //beatnumber is sustain -1; -1 from color letter being counted as beat
        }
    }

    instructions = translation; //If convertible instruction = translation string
    return 0; //If convertible return 0
}

void testone(int n)
{
	string ins;
	int bb = 666;
	switch (n)
	{
			         default: {
	    cout << "Bad argument" << endl;
			} break; case  1: {
	    assert(hasProperSyntax(""));
			} break; case  2: {
	    assert(!hasProperSyntax("g"));
			} break; case  3: {
	    assert(!hasProperSyntax("3"));
			} break; case  4: {
	    assert(!hasProperSyntax("x"));
			} break; case  5: {
	    assert(hasProperSyntax("/"));
			} break; case  6: {
	    assert(hasProperSyntax("g/"));
			} break; case  7: {
	    assert(hasProperSyntax("r/"));
			} break; case  8: {
	    assert(hasProperSyntax("y/"));
			} break; case  9: {
	    assert(hasProperSyntax("b/"));
			} break; case 10: {
	    assert(hasProperSyntax("o/"));
			} break; case 11: {
	    assert(hasProperSyntax("G/"));
			} break; case 12: {
	    assert(hasProperSyntax("R/"));
			} break; case 13: {
	    assert(hasProperSyntax("Y/"));
			} break; case 14: {
	    assert(hasProperSyntax("B/"));
			} break; case 15: {
	    assert(hasProperSyntax("O/"));
			} break; case 16: {
	    assert(!hasProperSyntax("x/"));
			} break; case 17: {
	    assert(!hasProperSyntax("2r/"));
			} break; case 18: {
	    assert(!hasProperSyntax("23/"));
			} break; case 19: {
	    assert(!hasProperSyntax("23"));
			} break; case 20: {
	    assert(hasProperSyntax("o4/"));
			} break; case 21: {
	    assert(hasProperSyntax("y56/"));
			} break; case 22: {
	    assert(!hasProperSyntax("r456/"));
			} break; case 23: {
	    assert(hasProperSyntax("b07/"));
			} break; case 24: {
	    assert(hasProperSyntax("G00/"));
			} break; case 25: {
	    assert(hasProperSyntax("Y01/"));
			} break; case 26: {
	    assert(hasProperSyntax("R0/"));
			} break; case 27: {
	    assert(hasProperSyntax("B1/"));
			} break; case 28: {
	    assert(hasProperSyntax("//"));
			} break; case 29: {
	    assert(hasProperSyntax("/o/"));
			} break; case 30: {
	    assert(hasProperSyntax("y//"));
			} break; case 31: {
	    assert(hasProperSyntax("r/b/"));
			} break; case 32: {
	    assert(hasProperSyntax("G8/Y91/"));
			} break; case 33: {
	    assert(hasProperSyntax("O/B/B/"));
			} break; case 34: {
	    assert(!hasProperSyntax("G/G/Y"));
			} break; case 35: {
	    assert(!hasProperSyntax("G/G/X/"));
			} break; case 36: {
	    assert(hasProperSyntax("g/g99/g88/g77/g6/g5/"));
			} break; case 37: {
	    assert(hasProperSyntax("y//o///y////"));
			} break; case 38: {
	    assert(!hasProperSyntax("r/r/r321/"));
			} break; case 39: {
	    assert(convertTune("/",ins,bb) == 0);
			} break; case 40: {
	    convertTune("/",ins,bb);
	    assert(ins == "x");
			} break; case 41: {
	    convertTune("/",ins,bb);
	    assert(bb == 666);
			} break; case 42: {
	    assert(convertTune("g/",ins,bb) == 0);
			} break; case 43: {
	    convertTune("g/",ins,bb);
	    assert(ins == "g");
			} break; case 44: {
	    convertTune("g/",ins,bb);
	    assert(bb == 666);
			} break; case 45: {
	    ins = "@@@";
	    convertTune("g/",ins,bb);
	    assert(ins == "g");
			} break; case 46: {
	    assert(convertTune("G/",ins,bb) == 0  &&  ins == "g");
			} break; case 47: {
	    assert(convertTune("g/o/",ins,bb) == 0  &&  ins == "go");
			} break; case 48: {
	    assert(convertTune("g//",ins,bb) == 0  &&  ins == "gx");
			} break; case 49: {
	    assert(convertTune("r//b/y/o//g/r/",ins,bb) == 0  &&
						ins == "rxbyoxgr");
			} break; case 50: {
	    assert(convertTune("r2//",ins,bb) == 0  &&  ins == "RR");
			} break; case 51: {
	    assert(convertTune("y02//",ins,bb) == 0  &&  ins == "YY");
			} break; case 52: {
	    assert(convertTune("g12////////////",ins,bb) == 0  &&
						ins == "GGGGGGGGGGGG");
			} break; case 53: {
	    assert(convertTune("/g12////////////",ins,bb) == 0  &&
						ins == "xGGGGGGGGGGGG");
			} break; case 54: {
	    assert(convertTune("r3///g2//",ins,bb) == 0  &&
						ins == "RRRGG");
			} break; case 55: {
	    assert(convertTune("/g/o3////r2//r3///b/b2//",ins,bb) == 0  &&
						ins == "xgOOOxRRRRRbBB");
			} break; case 56: {
	    assert(convertTune("",ins,bb) == 0  &&  ins == "");
			} break; case 57: {
	    assert(convertTune("g/y",ins,bb) == 1);
			} break; case 58: {
	    ins = "@@@";
	    convertTune("g/y",ins,bb);
	    assert(ins == "@@@");
			} break; case 59: {
	    convertTune("g/y",ins,bb);
	    assert(bb == 666);
			} break; case 60: {
	    assert(convertTune("y2/y/",ins,bb) == 2);
			} break; case 61: {
	    ins = "@@@";
	    convertTune("y2/y/",ins,bb);
	    assert(ins == "@@@");
			} break; case 62: {
	    convertTune("y2/y/",ins,bb);
	    assert(bb == 2);
			} break; case 63: {
	    assert(convertTune("g/y3//y/",ins,bb) == 2);
			} break; case 64: {
	    ins = "@@@";
	    convertTune("g/y3//y/",ins,bb);
	    assert(ins == "@@@");
			} break; case 65: {
	    convertTune("g/y3//y/",ins,bb);
	    assert(bb == 4);
			} break; case 66: {
	    assert(convertTune("o/r/y10/////////y/g/",ins,bb) == 2);
			} break; case 67: {
	    convertTune("o/r/y10/////////y/g/",ins,bb);
	    assert(bb == 12);
			} break; case 68: {
	    assert(convertTune("b/r4///",ins,bb) == 4);
			} break; case 69: {
	    ins = "@@@";
	    convertTune("b/r4///",ins,bb);
	    assert(ins == "@@@");
			} break; case 70: {
	    convertTune("b/r4///",ins,bb);
	    assert(bb == 5);
			} break; case 71: {
	    assert(convertTune("/r/y1//g/",ins,bb) == 3);
			} break; case 72: {
	    ins = "@@@";
	    convertTune("r/y1//g/",ins,bb);
	    assert(ins == "@@@");
			} break; case 73: {
	    convertTune("r/y1//g/",ins,bb);
	    assert(bb == 2);
			} break; case 74: {
	    assert(convertTune("y/g//r//y0///",ins,bb) == 3);
			} break; case 75: {
	    convertTune("y/g//r//y0///",ins,bb);
	    assert(bb == 6);
			} break; case 76: {
	    assert(convertTune("/r/y01//g/",ins,bb) == 3);
			} break; case 77: {
	    assert(convertTune("/g3//y/r1//b2/",ins,bb) == 2  &&  bb == 4);
			} break; case 78: {
	    assert(convertTune("//r0/g3//y/r1//b2/",ins,bb) == 3  &&  bb == 3);
			} break; case 79: {
	    int r = convertTune("//g4//r1///",ins,bb);
	    assert((r == 2  ||  r == 3)  &&  bb == 5);
			}
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed!" << endl;
}