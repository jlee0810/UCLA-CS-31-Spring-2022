#include <iostream>
#include <string>

using namespace std; 

const double firstTier = 5.41; // First tier rate per HCF in both the high and low seasons 
const double secondTier_high = 9.79; //Second tier rate per HCF in the high season
const double secondTier_low = 7.77; //Second tier rate per HCF in the low season


int main() {
    //Initial Program interface for user to input information
    int initial;
    cout << "Initial meter reading: "; //Gets initial meter reading
    cin >> initial;
    
    int final;
    cout << "Final meter reading: "; //Gets final meter reading
    cin >> final;

    cin.ignore(10000, '\n');
    string name;
    cout << "Customer name: "; //Gets customer name
    getline(cin, name);

    int month;
    cout << "Month number (1=Jan, 2=Feb, etc.): "; //Gets month
    cin >> month;

    cout << "---" << endl; //Outputs three hyphens

    //Invalid input warning
    //Takes advantage of else if to write only the error message for the earliest erroneous input item
    if (initial < 0) {
        cout << "The initial meter reading must not be negative." << endl;
    }

    else if (final < initial) {
        cout << "The final meter reading must be at least as large as the initial reading." << endl;
    }

    else if (name == "") {
        cout << "You must enter a customer name." << endl;
    }

    else if (month < 1 || month > 12) {
        cout << "The month number must be in the range 1 through 12." << endl;
    }

    //Valid Output Calculations after checking for invalidity
    else {
        cout.setf(ios::fixed); //Restricts decimal points up to the second decimal
        cout.precision(2);

        double bill;
        int waterUsed = final - initial; 

        if (month >= 4 && month <= 10) { //High usage season
            if (waterUsed > 23) { //Checks if used HCF is bigger than 23
                bill = (23 * firstTier) + ((waterUsed - 23) * secondTier_high); //The first 23 HCF are first tier and the rest are secondTier high
            }
            else {
                bill = waterUsed * firstTier; //Calculation for used HCF smaller than 23 (High Usage)
            }
        }

        if (month <= 3 || month >= 11) { //Low usage season
            if (waterUsed > 15) { //Checks if used HCF is bigger than 15
                bill = (15 * firstTier) + ((waterUsed - 15) * secondTier_low); //The first 15 HCF are first tier and the rest are secondTier low
            }
            else {
                bill = waterUsed * firstTier; //Calculation for used HCF smaller than 15 (Low Usage)
            }
        }
        cout << "The bill for " << name << " is $" << bill << endl; // Outputs the bill
    }
}