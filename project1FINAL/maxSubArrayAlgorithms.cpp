/****************************************************************************************
 ** Project 1 - Group 32
 ** CS325-400 F16
 **
 ** Meredith Kiessling
 ** Evan Lyon
 ** Fahmy Mohammed
 **
 **
 ** Description - Contains all four max subarray algorithm implementations
 ****************************************************************************************/

#include "maxSubArrayAlgorithms.hpp"

/****************************************************************************************
 ** Function: maxSubArrayEnumeration(const std::vector<int>, int &, int &, int &)
 ** Description: Calculates maximum sub array using enumeration (algorithm #1)
 ** Parameters:  const std::vector<int> &arr, int &startIdx, int &endIdx, int &sum
 ** Pre-Conditions: Array must have at least one non-negative value
 ** Post-Conditions: startIdx and endIdx contain subarray start and end index, and sum
 **                  contains subarray sum
 ** Author: Evan Lyon
 ****************************************************************************************/
void maxSubArrayEnumeration(const std::vector<int> &arr, int &startIdx, int &endIdx, int &sum){
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

/****************************************************************************************
 ** Function: maxSubArrayImprovedEnumeration(const std::vector<int>, int &, int &, int &)
 ** Description: Calculates maximum sub array using better enumeration (algorithm #2)
 ** Parameters:  const std::vector<int> &arr, int &startIdx, int &endIdx, int &sum
 ** Pre-Conditions: Array must have at least one non-negative value
 ** Post-Conditions: startIdx and endIdx contain subarray start and end index, and sum
 **                  contains subarray sum
 ** Author: Evan Lyon
 ****************************************************************************************/
void maxSubArrayImprovedEnumeration(const std::vector<int> &arr, int &startIdx, int &endIdx, int &sum){
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


/****************************************************************************************
 ** Function: maxSubArrayDivideConquer(int [], int, int)
 ** Description: Calculated the maximum subarray of a given input array recursively using
 **              a divide and conquer approach (algorithm #3).
 ** Paramerters: int input [], int low, int high
 ** Pre-Conditions: Array must have at least one non-negative value
 ** Post-Conditions: Struct containing start index, end index and sum of subarray
 ** Author: Fahmy Mohammed
 ****************************************************************************************/
subArray maxSubArrayDivideConquer(int input [], int low, int high)
{
    //Base case
    if(high == low)
    {
        subArray arr = {low, high, input[low]};
        return arr;
    }
    int mid = (low + high) / 2; //Midpoint of input array
    
    subArray left = maxSubArrayDivideConquer(input, low, mid); //Sub array of left half
    subArray right = maxSubArrayDivideConquer(input, mid + 1, high); //Sub array of right half
    subArray cross = maxCrossSubArray(input, low, mid, high); //Sub array crossing midpoint
    
    if((left.sum >= right.sum) && (left.sum >= cross.sum)) //Sub array in left half
        return left;
    else if((right.sum >= left.sum) && (right.sum >= cross.sum)) //Sub array in right half
        return right;
    else
        return cross; //Sub array crosses midpoint
}

/****************************************************************************************
 ** Function: maxCrossSubArray(int [], int, int, int)
 ** Description: Finds the maximum subarray that crosses the midpoint. Helper function for
 **              maxSubArrayDivideConquer algorithm
 ** Parameters: int input [], int low, int mid, int high
 ** Pre-Conditions: Called from maxSubArrayDivideConquer
 ** Post-Conditions: Struct containing start & end indexes, and subarray sum
 ** Author: Fahmy Mohammed
 ****************************************************************************************/
subArray maxCrossSubArray(int input [], int low, int mid, int high)
{
    subArray cross = {0,0,0};
    
    int leftCrossSum = 0;
    int sum = 0;
    
    //Loop from middle index to start index find max sum
    for(int i = mid; i >= low; i--)
    {
        sum += input[i];
        if(sum > leftCrossSum)
        {
            leftCrossSum = sum; //Update if higher sum is found
            cross.start = i; //Save index
        }
    }
    int rightCrossSum = sum = 0;
    
    //Loop from middle index to end index find max sum
    for(int i = mid + 1; i <= high; i++)
    {
        sum += input[i];
        if(sum > rightCrossSum)
        {
            rightCrossSum = sum; //Update if higher sum is found
            cross.end = i; //Save index
        }
    }
    cross.sum = leftCrossSum + rightCrossSum; //Combined sum of crossing sub array
    return cross;
}

/****************************************************************************************
 ** Function:  maxSubArrayLinearTime(int [], int, int &, int &, int &)
 ** Description: Calculates maximum sub array sum using DP (algorithm #4)
 ** Parameters:  int arr[], int inputSize, int &low, int &high, int &maxSum
 ** Pre-Conditions: Array must have at least one non-negative value
 ** Post-Conditions: low and high contain subarray start and end index, and maxSum
 **                  contains subarray sum
 ** Author: Meredith Kiessling
 ****************************************************************************************/
void maxSubArrayLinearTime(int arr[], int inputSize, int &low, int &high, int &maxSum ) {
    maxSum = INT_MIN;
    int endHereSum = INT_MIN;
    int endHereHigh = 0;
    int endHereLow = 0;
    low = 0;
    high = 0;
    
    for (int i = 0; i < inputSize; i++) {
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
