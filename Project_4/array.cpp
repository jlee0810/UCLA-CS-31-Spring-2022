#include <iostream>
#include <string>
#include <cassert>

using namespace std;


int enumerate(const string a[], int n, string target) {
    if (n < 0) { // Bad argument (negative array size)
        return -1;
    }

    int match = 0; //Counter for matches
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            match++; //Increase match by 1
        }
    }
    return match; //Return number of matches
}

int findMatch(const string a[], int n, string target) {
    if (n < 0) {// Bad argument (negative array size)
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i; //Return index
        }
    }
    //At this point there is no element that equals target
    return -1; //Return -1 as there is no such string target
}

bool findRun(const string a[], int n, string target, int& begin, int& end) {
    if (n < 0) {// Bad argument (negative array size)
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] == target) { 
            begin = i; //Begin is set to index i (first occurence)
            int j = i; 
            while (j < n && a[j] == target) {
                j++;
            }
            end = j - 1; //Subtract by 1 as last loop where last occurence of target incremented j by 1
            return true; //Return true as there was a match
        }
    }
    return false; //Return false as there was no match
}

int findMin(const string a[], int n) {
    if (n <= 0) { //Bad argument when n is negative and no elements are part of array
        return -1;
    }
    int min = 0; //Set min index to 0
    for (int i = 0; i < n; i++) {
        if (a[i] < a[min]) { //If the current element of an array examined is less than the current minimum element
            min = i; //Set min index to current index
        }
    }
    return min; //Return the min index
}

int moveToEnd(string a[], int n, int pos) {
    //Bad argument when either n or pos is negative or when pos is greater than the maximum index the array can have
    if (n < 0 || pos < 0 || pos > n - 1) {
        return -1;
    }
    
    string temp = a[pos]; 
    for (int i = pos + 1; i < n; i++){ //for every element after pos to end of the array
        a[i - 1] = a[i]; //set the element before current element to the current element
    }
    a[n - 1] = temp; //Set the last position of the array that the function knows about to temp (string at pos index) 
    return pos; //Return original position
}

int moveToBeginning(string a[], int n, int pos) {
    //Bad argument when either n or pos is negative or when pos is greater than the maximum index the array can have
     if (n < 0 || pos < 0 || pos > n - 1) {
        return -1;
     }
    
    string temp = a[pos]; 
    for (int i = pos - 1; i >= 0; i--){ //for every element before pos to beginning of the array
        a[i + 1] = a[i]; //set the element after current element to the current element
    }
    a[0] = temp; //Put the value that was thus eliminated (sting at pos index / temp) into the first position of the array
    return pos; //Return original position

}

int findDifference(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) { //Bad argument when either n1 or n2 is negative
        return -1;
    }
    for (int i = 0; i < n1 && i < n2; i++){ //Loop from index 0 to until either array a1 or a2 runs out
        if (a1[i] != a2[i]){ //If the elements are different return the index
            return i;
        }
    }
    //At this point arrays are equal up to the point where one or both runs out
    //return whichever value of n1 and n2 is less than or equal to the other
    if (n1 <= n2)
        return n1;
    else {
        return n2;
    }
}

int removeDups(string a[], int n) {
    if (n < 0) { //Bad argument (negative array size)
        return -1;
    }

    //Array size is 0 or 1 then simply return the array size
    //Array did not have to be changed
    if (n == 0 || n == 1) {
        return n;
    }

    // Counter for the unique index 
    int j = 0;

    for (int i = 0; i < n - 1; i++) { //Examine array from first to second last element
        if (a[i] != a[i+1]){ //If current element is not equal to the next element
            a[j] = a[i]; //Element of unique index is equal to the current element
            j += 1; // Increment the unique index by one
        }
    }

    a[j] = a[n-1]; //The last element of uniques is the last element of the array

    return j + 1; //Array size of up until only unique strings = index up until unique string + 1

}

bool subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0 || n1 < n2) { //Bad arguments
        return false;
    }

    if (n2 == 0) { //zero elements therefore always true
        return true;
    }

    int i = 0; //Counter for a1
    int j = 0; //Counter for a2

    while (i < n1 && j < n2) { //Until one runs out
        if (a1[i] == a2[j]) { //When elements match
            j++; //Move onto next element for a2
        }
        i++; //Move onto the next element for a1

        if (j == n2) { //If it found a match for all a2 elements and j is now equal to a2 size
            return true; //Return true as it is verified that it is a subsequence
        }
    }
    return false; //Didn't find a match for all elements for a2 so return false


}

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
    if (n1 + n2 > max || n1 < 0 || n2 < 0) { //Bad arguments
        return -1;
    }

    for (int i = 0; i < n1; i++){ //Sees if a1 is in nondecreasing order
        for (int j = i + 1; j < n1; j++){ 
            if (a1[i] > a1[j]){
                return -1; //If it is not in nondecreasing order return -1
            }
        }
    }

    for (int i = 0; i < n2; i++){ //Sees if a2 is in nondecreasing order
        for (int j = i + 1; j < n2; j++){
            if (a2[i] > a2[j]){
                return -1; //If it is not in nondecreasing order return -1
            }
        }
    }

    //Now combines or merges the two arrays
    int i = 0; //Index Counter for a1
    int j = 0; //Index Counter for a2
    int k = 0; //Index Counter for result array

    while (i < n1 && j < n2) { //Loop until the a1 or a2 runs out
        if (a1[i] <= a2[j]) { //If current element in a1 is smaller or equal to current element in a2
            result[k] = a1[i]; //The current index at result is set to current element of a1
            i++; //Move onto next element in a1
        }
        else { //Current element in a2 is smaller than current element in a1
            result[k] = a2[j]; //Save it to the current index at result 
            j++; //Move onto next element in a2
        }
        k++; //Move onto next index of result array
    }

    //At this point one of the arrays ran out for comparison to happen
    while (i < n1) { //If a1 array has elements still remaining
        result[k] = a1[i]; //Add the remaining elements to result array
        i++;
        k++;
    }

    while (j < n2) { //If a2 array has elements still remaining
        result[k] = a2[j]; //Add the remaining elements to result array
        j++;
        k++;
    }
    
    return n1 + n2; //Result array size is a1 size + a2 size
}



int divide(string a[], int n, string divider) {
    if (n < 0) { //Bad argument
        return -1;
    }
    
    // sorts the array alphabetically - similar approach to observing if it is nondecreasing order from makeMerger
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (a[i] > a[j]){
                string temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    
    //Now that it is alphabetically ordered
    for (int i = 0; i < n; i++) {
        if ((a[i] >= divider)) //The index where the element is greater or equal to divider
            return i; //Is our index and return it
    }

    //At this point the divider is bigger than the last element in array
    //return last index + 1 = n (size of array)
    return n;
}



int main () {
    string arr8[5] = {
		"a,", "b", "c", "c", "d"
	};
	string arr9[4] = {
		"a,", "b", "c", "d"
	};
	assert(findDifference(arr8, 5, arr9, 4) == 3);
	cout << "[findDifference] 1 *" << endl;
	assert(findDifference(arr8, -1, arr9, 4) == -1);
	cout << "[findDifference] 2 *" << endl;
	assert(findDifference(arr8, 5, arr9, -1) == -1);
	cout << "[findDifference] 3 *" << endl;
	assert(findDifference(arr8, 0, arr9, 0) == 0);
	cout << "[findDifference] 4 *" << endl;
	assert(findDifference(arr8, 0, arr9, 3) == 0);
	cout << "[findDifference] 5 *" << endl;
	assert(findDifference(arr8, 1, arr9, 3) == 1);
	cout << "[findDifference] 6 *" << endl;
	cout << "[findDifference] tests succeeded" << endl;

    



}
