#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<iterator>
#include "Algo.h"
using namespace std;
typedef void(*Algorithm)(const vector<int>&, int&, int&, int&);

int main(int argc, char* argv[]) {
	if(argc != 2){
		cout<<"Usage: "<<argv[0]<<" algo_id[1|2]"<<endl;
		return -1;
	}

	int algo_no = atoi(argv[1]);		//Algorithm identifier, 1:Enumeration, 2:ImprovedEnumeration

	ifstream inputFile("MSS_Problems.txt", ios::in);

	//Each time the program executes, this file is overwritten; hence, make sure to rename it
	ofstream outputFile("MSS_Results.txt", ios::out);		
	
	int maxSum;		//The sum of the elements in the maximum subarray list
	int startIdx;	//The start index of the maximum subarray list
	int endIdx;		//The end index of the maximum subarray list
	
	Algorithm f;		//A function pointer to the algorithms
	if(algo_no == 1)
		f = Enumeration;
	else if(algo_no == 2)
		f = ImprovedEnumeration;
	else {
		cout<<"Invalid Algo_id: "<<algo_no<<endl;
		return -1;
	}

	//Read from the input file, apply the algorithm on each line, and write results in the output file	
	string line;
	while(getline(inputFile, line)){		
		if(line.size() > 1){
			int num;
			vector<int>row;
			stringstream ss(line);
			ss.ignore(1, '[');	//skip the open bracket
			while(ss>>num){
				row.push_back(num);
				ss.ignore(1, ','); //skip the comma
			}
		
			//Run the algorithm
			f(row, startIdx, endIdx, maxSum);
			
			outputFile<<line<<endl;		//Write the original array
			outputFile<<"[";	//Begin the maximum subarray list by [

			//Write the maximum subarray
			copy(row.begin() + startIdx, row.begin() + endIdx + 1, ostream_iterator<int>(outputFile, ","));			
			outputFile.seekp(-1, ios::cur);	//Overwrite the trail comma
			outputFile<<"]\n";	//Append the maxium subarray list by ]

			outputFile<<maxSum<<endl<<endl;	//Write the sum of the maximum subarray list
		}
	}
	return 0;
}
