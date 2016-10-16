/****************************************************************************************
 ** Project 1 - Group 32
 ** CS325-400 F16
 **
 ** Meredith Kiessling
 ** Evan Lyon
 ** Fahmy Mohammed
 **
 **
 ** Description - Contains all four max subarray algorithm declarations
 ****************************************************************************************/

#ifndef maxSubArrayAlgorithms_hpp
#define maxSubArrayAlgorithms_hpp

#include <vector>
#include <limits.h>

struct subArray {
    int start, end, sum;
};

//Enumeration max subarray algorithm (algorithm #1)
void maxSubArrayEnumeration(const std::vector<int> &arr,  int &startIdx,  int &endIdx,  int &sum);

//Better enumeration max subarray algorithm (algorithm #2)
void maxSubArrayImprovedEnumeration(const std::vector<int> &arr,  int &startIdx,  int &endIdx,  int &sum);

//Divide and Conquer max subarray algorithm (algorithm #3)
subArray maxSubArrayDivideConquer(int input [], int low, int high);
subArray maxCrossSubArray(int input [], int low, int mid, int high); //Helper function for #3

//Linear time max subarray algorithm (algorithm #4)
void maxSubArrayLinearTime(int arr[], int  inputSize, int &low, int &high, int &maxSum);

#endif
