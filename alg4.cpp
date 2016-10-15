/*
 * alg1.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: meredithkiessling
 */

#include<iostream>
#include<limits.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<ctime>
#include<time.h>
#include<iomanip>
#include<cstdlib>
using namespace std;


void maxSum4(int arr[], int n);
int getSize(int min, int max);
int* randomArr(int n);
float getRunTime(int n);
bool makeNegative();


int main() {
	/* seed srand for random number generation with buffer*/
	int seed;
	seed = 0;
	seed = time(0);
	srand(seed);

	/*used to store user input for size of array*/
	int arraySize;

	/*
	 * stores average run-time of algorithm (10 test cases/ 10)
	 * avgTime = (total time to run 10 test cases/10)
	 */
	float avgTime;

	do {
		/*ask user to input a size n*/
		cout << "Enter a number n, representing the size of the array for run-time analysis." << endl;
		arraySize = getSize(0, INT_MAX);

		/*
		 * getData takes in the size of the array, randomly generates an array, runs
		 * algorithm4, and saves the run-time of the algorithm. It repeats this process
		 * 10 times, each time creating a new array and determining the amount of time
		 * it takes to run. It returns the average time
		 * avgTime = (total time to run 10 different test cases/10)
		 * NOTE: total time to run 10 different test cases is only measures the time it
		 * takes to compute the maximum sub-array using algorithm 4 (not the total time
		 * to create each new test case, etc)
		 */
		avgTime = getRunTime(arraySize);

		cout << "average running time for n= " << arraySize << " = " << setprecision(9) << avgTime << endl;
	}while (cin.good());

	return 0;
}



/****************************************************************************************
 ** Function:  maxSum4(int arr[], int n)
 ** Description: calculates maximum sub array sum using DP (algorithm 4) (NO PRINTING to file)
 ** Parameters:  int arr[], int n
 ** Pre-Conditions: array must have at least one non-negative value
 ** Post-Conditions:
****************************************************************************************/
void maxSum4(int arr[], int n) {
	int maxSum = INT_MIN;
	int endHereSum = INT_MIN;
	int endHereHigh = 0;
	int endHereLow = 0;
	int low = 0;
	int high = 0;

	for (int i = 0; i < n; i++) {
		endHereHigh = i;
		if (endHereSum > 0) {
			endHereSum += arr[i];
		} else {
			endHereLow = i;
			endHereSum = arr[i];
		}

		if (endHereSum > maxSum) {
			maxSum = endHereSum;
			low = endHereLow;
			high = endHereHigh;
		}
	}

}



/****************************************************************************************
 ** Function:  getRunTime(int n)
 ** Description: given an array size of n, getData runs the maxSum4() algorithm, and returns
 ** 			the average run-time from running 10 different randomly populated array's
 ** 			of size n
 ** Parameters:  int n
 ** Pre-Conditions:
 ** Post-Conditions:
****************************************************************************************/
float getRunTime(int n){
	clock_t t;
	float time;
	int *arr;
	clock_t totalTicks = 0;

	for (int i = 0; i < 10; i++) {
		arr = randomArr(n);

		t = clock();
		maxSum4(arr, n);
		t = clock() - t;
		//cout << "t = " << t;
		totalTicks += t;
		//cout << "totalTicks = " << totalTicks << endl;
		delete[] arr;
	}

	time = totalTicks / (float) CLOCKS_PER_SEC;

	float avgTime;

	avgTime = time/10.0000000;

	return avgTime;
}


/**************************************************************************************
 ** Function: randomArr(int n)
 ** Description: helper used to randomly populate an array of size n with positive and
 ** 			negative numbers in the range of [-100, 100]
 ** Parameters: int n (size of array)
 ** Pre-Conditions:
 ** Post-Conditions:
 **************************************************************************************/
int* randomArr(int n) {
	bool isPositive = false;
	int randValue;

	int *randArr = new int[n];

	for (int i = 0; i < n; i++){
		/*generates a random number between 0-100*/
		 randValue = rand() % + 100;

		 /*determines if the random number should be positive or negative*/
		 if (makeNegative()) {
			 randValue = 0 - randValue;
		 }
		 /*used to verify that at least one number in the array is positive*/
		 if (randValue >= 0){
			 isPositive = true;
		 }
		 randArr[i] = randValue;
	}

	return randArr;

}

/**************************************************************************************
 ** Function: getSize()
 ** Description: helper used to get size of array for testing
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions: int containing user's desired size
 **************************************************************************************/
int getSize(int min, int max) {

    int size;
    string mystr;
    getline(cin, mystr);
    stringstream(mystr) >> size;


    while (!cin) {
        cout << "Invalid selection. Enter " << min << " - " << max;
        getline(cin, mystr);
        stringstream(mystr) >> size;
    }
    while (size < min ||size > max) {
        cout << "Invalid selection. Enter " << min << " - " << max;
        getline(cin, mystr);
        stringstream(mystr) >> size;
    }

    return size;
}


/**************************************************************************************
 ** Function: makeNegative()
 ** Description: helper used to randomly determine if a number should be negative--
 ** 			(like flipping a coin)
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 **************************************************************************************/
bool makeNegative(){
	return rand() % + 2;
}

