/***********************************************************************
 ** CS325-400 F16 Project01
 **
 ** Fahmy Mohammed
 **
 ** Description - Algorithm finds the maximum sub-array of a given input
 **               using a divide and conquer approach.
 ***********************************************************************/

#ifndef alg3_hpp
#define alg3_hpp

struct subArray {
    int start, end, sum;
};

subArray maxSubArray(int [], int, int);
subArray maxCrossSubArray(int [], int , int, int);

#endif
