#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<chrono>
#include "Algo.h"
using namespace std;
typedef void (*Algorithm)(const vector<int> &, int&, int&, int&);
int main(int argc, char *argv[]) {
	if(argc != 5) {
		cout<<"Usage: "<<argv[0]<<" algo_id[1|2] <Initial input size> <size increment> <logfile>"<<endl;
		return -1;
	}
	int algo_no = atoi(argv[1]);	//The id of the algorithm to execute, 1: Enumeration, 2: ImprovedEnumeration
	int start_n = atoi(argv[2]);	//The size of the first array
	int inc = atoi(argv[3]);		//The difference in size between two consecutive arrays
	ofstream logfile(argv[4], ios::out);	//An output file where a line contains the size of an array and average running time
	int rows = 20;					//The total number of different arrays considered
	int num_iter = 10;			
	vector<int> randomNumbers;		//Input array to the algorithm
	int startIdx;					//Starting index of the maximum subarray
	int endIdx;						//End index of the maximum subarray
	int maxSum;						//The sum of the elements in the maximum subarray
	int arraySize;					//The number of elements in the original array
	int duration;					//The average running time of the algorithm on a given input array

	Algorithm f;					//A pointer to the algorithm to execute
	if(algo_no == 1)
		f = Enumeration;
	else if(algo_no == 2)
		f = ImprovedEnumeration;
	else
	{
		cout<<"Invalid algorithm id: "<<algo_no<<endl;
		return -1;
	}
	
	const int RANGE = 200;
	srand(time(NULL));
	for(int i = 0; i < rows; ++i)
	{
		duration = 0;
		arraySize = start_n + i * inc;
		for(int j = 0; j < num_iter; ++j)
		{
			//Generate a vector of random numbers
			for(int k = 0; k < arraySize; ++k)
			{
				auto n = rand() % RANGE - (RANGE>>1);
				randomNumbers.push_back(n);
			}			

			//copy(randomNumbers.begin(), randomNumbers.end(), ostream_iterator<int>(cout, " "));
			//cout<<endl;

			//Execute the algorithm and measure the duration in milliseconds
			auto start =  chrono::high_resolution_clock::now();
			f(randomNumbers, startIdx, endIdx, maxSum); 	
			auto end = chrono::high_resolution_clock::now();
			duration += chrono::duration_cast<chrono::milliseconds>(end-start).count();
			
			randomNumbers.clear();	
		}

		duration /= num_iter;	//The average of 'num_iter' iterations
		
		logfile<<arraySize<<" "<<duration<<"ms"<<endl;
	}
	
	return 0;
}
