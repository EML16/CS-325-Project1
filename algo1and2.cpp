#include<vector>
#include "Algo.h"
void Enumeration(const std::vector<int> &arr, int &startIdx, int &endIdx, int &sum){
	int i,j,k,count;
	sum = 0, startIdx = -1, endIdx = -1;
	for(i = 0; i < arr.size(); ++i){
		for(j = i; j < arr.size(); ++j){
			count = 0;
			for(k = i; k <= j; ++k)
				count += arr.at(k);
			if(count > sum){
				sum = count;
				startIdx = i;
				endIdx = j;
			}	
		}
	}
}

void ImprovedEnumeration(const std::vector<int> &arr, int &startIdx, int &endIdx, int &sum){
	int i,j, count;
	sum = 0, startIdx = -1, endIdx = -1;
	for(i = 0; i < arr.size(); ++i){
		count = 0;
		for(j = i; j < arr.size(); ++j){
			count += arr.at(j);
			if(count > sum){
				sum = count;
				startIdx = i;
				endIdx = j;
			}	
		}
	}
}
