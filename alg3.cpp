/***********************************************************************
 ** CS325-400 F16 Project01
 **
 ** Fahmy Mohammed
 **
 ** Description - Algorithm finds the maximum subarray of a given input
 **               using a divide and conquer approach.
 ***********************************************************************/

#include "alg3.hpp"

/***********************************************************************
 ** Finds the maximum subarray of a given input array recursively using 
 ** a divide and conquer approach.
 ** Accepts: int array, start index, end index
 ** Returns: Struct containing start index, end index and sum of subarray
 ***********************************************************************/
subArray maxSubArray(int input [], int low, int high)
{
    //Base case
    if(high == low)
    {
        subArray arr = {low, high, input[low]};
        return arr;
    }
    int mid = (low + high) / 2; //Midpoint of input array
    
    subArray left = maxSubArray(input, low, mid); //Sub array of left half
    subArray right = maxSubArray(input, mid + 1, high); //Sub array of right half
    subArray cross = maxCrossSubArray(input, low, mid, high); //Sub array crossing midpoint
    
    if((left.sum >= right.sum) && (left.sum >= cross.sum)) //Sub array in left half
        return left;
    else if((right.sum >= left.sum) && (right.sum >= cross.sum)) //Sub array in right half
        return right;
    else
        return cross; //Sub array crosses midpoint
}

/***********************************************************************
 ** Finds the maximum subarray that crosses the midpoint.
 ** Accepts: int array, start index, end index, and mid index
 ** Returns: Struct containing start index, end index and sum of subarray
 ***********************************************************************/
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
