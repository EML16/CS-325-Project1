/*****************************************************************************************
 ** Program Filename:  maxSumTester.cpp
 ** Author:  Meredith Kiessling  (Project 1 - Group 32)
 ** Date:  10.16.2016
 ** Description: Tester to run all four algorithms against the test cases in MSS_TestProblems.txt
 ** 			and outputs the results to MSS_Results.txt
 ****************************************************************************************/


#include<iostream>
#include<limits.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include<cstdlib>
using namespace std;


void test();
void maxSum1(int arr[], int n);
void maxSum4(int arr[], int n);
void outputResults(int arr[], int n, int low, int high, int maxSum, string name);

int main() {


	/*tests all algorithms for correctness for correctness*/
	/*test imports test cases from file, and outputs the results to MSS_Results.txt*/
	test();
	cout << "Test Problems have been output to MSS_Results.txt." << endl;


	return 0;
}

/****************************************************************************************
 ** Function:  maxSum1(int arr[], int n)
 ** Description: calculates maximum sub array sum using enumeration (algorithm 1) &
 ** 			prints results to MSS_Results.txt file
 ** Parameters:  int arr[], int n
 ** Pre-Conditions: array must have at least one non-negative value
 ** Post-Conditions:
****************************************************************************************/
void maxSum1(int arr[], int n) {
//	for each pair (i,j) with 1 <= i < j <=n
//			compute a[i]... a[j]
//			keep max sum found
//	return max sum found

	int sum;
	int max = arr[0];
	int start = 0;
	int end = 0;

	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++){
			sum = 0;
			for(int k = i; k <= j; k++){
				sum += arr[k];
				if (sum > max) {
					max = sum;
					start = i;
					end = j;
				}
			}
		}
	}

	/*print results to output file MSS_Results.txt*/
	outputResults(arr, n, start, end, max, "Algorithm 1:");

}

/****************************************************************************************
 ** Function:  maxSum4(int arr[], int n)
 ** Description: calculates maximum sub array sum using DP (algorithm 4) & prints results
 ** 			to MSS_Results.txt file
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

	/*print results to output file MSS_Results.txt*/
	outputResults(arr, n, low, high, maxSum, "Algorithm 4:");

}




/****************************************************************************************
 ** Function:  test()
 ** Description: reads in test cases from MSS_TESTProblems.txt, and runs each test case
 ** 			 using algorithm 4 (maxSum4())
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
****************************************************************************************/
void test() {
	ifstream inputf;

	inputf.open("MSS_TestProblems.txt");

	if (!inputf) {
		cout << "Error opening file!" << endl;
	} else {
		string str;
		vector<int> temp;

		while (getline(inputf, str)) {

			/*changes string format [1, 2, 3, 4, 5, 6] to 1 2 3 4 5 6 for array processing*/
			for (string::iterator it = str.begin(); it != str.end(); ++it) {
				if (*it == '[') {
					*it = ' ';
				} else if (*it == ']') {
					*it = ' ';
				} else if (*it == ',') {
					*it = ' ';
				} else {
					continue;
				}
			}

			/*parse string into integers using stringstream*/
			stringstream ss;
			ss << str;
			int n;

			/*pulls integer value from each parsed string and pushes onto temp vector*/
			while (ss >> n) {
				temp.push_back(n);
			}

			int *arr = new int[temp.size()];

			/*copy elements from vector to array*/
			for (int i = 0; i < temp.size(); i++) {
				arr[i] = temp.at(i);
			}
			cout << endl;

			/*determine max sub-array using algorithm 1*/
			maxSum1(arr, temp.size());


			/*determine max sub-array using algorithm 4*/
			maxSum4(arr, temp.size());

			temp.clear();
			str.clear();
			delete[] arr;

		}
	}

	inputf.close();

}



/****************************************************************************************
 ** Function:  outputResults(..)
 ** Description: prints results (maximum Sum, maximum subarray) to MSS_Results.txt
 ** Parameters:  int arr[], int n, int low, int high, int maxSum
 ** Pre-Conditions:
 ** Post-Conditions:
****************************************************************************************/
void outputResults(int arr[], int n, int low, int high, int maxSum, string name) {
	ofstream outfile;
	outfile.open("MSS_Results.txt", ios::app);
	outfile << name << endl;
	outfile << "Test Case = [";
	for (int i = 0; i < n; i++) {
		outfile << arr[i] << ", ";
	}
	outfile << "]" << endl;
	outfile << "Max Sum = " << maxSum << endl;
	outfile << "max sub-array (A[" << low << "]...[" << high << "]) = [";

	for (int i = low; i <= high; i++) {
		outfile << arr[i] << ", ";
	}
	outfile << "]" << endl;

	outfile << endl;

	outfile.close();
}
