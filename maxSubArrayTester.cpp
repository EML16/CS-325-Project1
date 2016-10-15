/***********************************************************************
** CS325-400 F16 Project01
**
** Fahmy Mohammed
**
** Description - Reads input from file, finds maximum sub array of input
**               and writes results to file.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include "alg3.hpp" //Header file containing algorithm

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::stringstream;
using std::getline;

void readFromFile(ifstream*, vector<vector<int> > *);
void writeToFile(int[], int, int, int, int, ofstream*);
int* fillRandomArray(int);
void tester(int inputSize);
//void printInput(vector<vector<int> >*);

int main()
{
    /*
    ifstream inputFile;
    inputFile.open("./MSS_TestProblems-1.txt");
    if (!inputFile) //check if the file opened successfully
        cout << "Cannot open file for reading" << endl;
    
    vector<vector<int> > convertedInput; //2D vector to hold values from file
    readFromFile(&inputFile, &convertedInput); //Read values from file and insert into 2D vector
    inputFile.close();
    
    ofstream outputFile;
    outputFile.open("./Results.txt");
    if (!outputFile) //check if the file opened successfully
        cout << "Cannot open file for writing" << endl;
    
    //printInput(&convertedInput); //Print 2D vector **For Testing**
    
    vector<vector<int> >::iterator iter = convertedInput.begin();
    iter = convertedInput.begin();
    
    //Iterate through 2D vector
    while(iter != convertedInput.end())
    {
        vector<int>::iterator iter2 = iter->begin(); //Iterator for vector inside of 2D vector
        int size = (int) iter->size();
        int *input = new int[size];
        int i = 0;
        
        //Iterate though vector inside and convert to an array
        while(iter2 != iter->end())
        {
            input[i] = *iter2;
            iter2++;
            i++;
        }
        
        subArray result = maxSubArray(input, 0, size - 1); // Run maxSubArray algorithm with input
        writeToFile(input, result.start, result.end, size, result.sum, &outputFile); //Write results to file
        iter++;
        delete[] input;
    }
    outputFile.close();
    */
    srand ((int)time(NULL));
    tester(100000); //Run algorithm with given input size and print the average running time
    
    return 0;
}

/***********************************************************************
 ** Runs the maxSubArray algorithm ten times with randomly generated 
 ** array of size n and calculates and prints the average running time.
 ** Accepts: int representing input size
 ** Returns: -
 ***********************************************************************/
void tester(int inputSize)
{
    clock_t start;
    double time, sum = 0;
    
    cout << "Test run for input size " << inputSize << endl;
    for(int i = 0; i < 10; i++)
    {
        int* input = fillRandomArray(inputSize); //Fill array with random values
        start = clock();
        subArray result = maxSubArray(input, 0, inputSize - 1); //Find max subarray of input
        time = ( std::clock() - start )/(double)CLOCKS_PER_SEC; //Elapsed time
        cout << "Run " << i << " Time: " << time << endl;
        sum += time;
        delete[] input;
    }
    
    cout << "Average: " << sum/10.0 << endl;
}

/***********************************************************************
 ** Fills an array of size n with random values (At least one value in 
 ** array is positive)
 ** Accepts: int representing input size
 ** Returns: Array filled with random values
 ***********************************************************************/
int* fillRandomArray(int inputSize)
{
    bool positive = false;
    int *randomArray = new int[inputSize];
    do{
        for(int i = 0; i < inputSize; i++)
        {
            int value = rand() % + 100;
            //50/50 chance of a positive or a negative number
            if(value % 2)
                value *= -1; //Make number negative
            else
                positive = true;
            randomArray[i] = value;
        }
    }while (positive != true); //Run until at least one positive value is inserted
    
    return randomArray;
}

/***********************************************************************
** Reads input from file, converts each "array" of intergers and places 
** each into the correct position in a 2D vector.
** Accepts: ifstream inputFile pointer and a 2D vector by reference
** Returns: 2D vector contains all input from file in correct position
***********************************************************************/
void readFromFile(ifstream *inputFile, vector<vector<int> > *convertedInput)
{
    string line;
    vector<int> input;
    
    //Read line from file until end of "array" (until ']' is found)
    while(getline(*inputFile, line, ']'))
    {
        int number;
        stringstream inputLineStream (line); //Place line in stringstream for further processing
        string str;
        
        //Breack up line using ',' and place each piece into string
        while (getline(inputLineStream, str, ','))
        {
            str.erase(std::remove(str.begin(), str.end(), '['), str.end()); //Find and remove '['
            stringstream inputStream (str);
            
            if(inputStream >> number)
                input.push_back(number); //Convert to int and insert into vector
        }
        
        if((int)input.size() > 0)
            convertedInput->push_back(input); //Insert converted "array" into 2D vector
        
        input.clear(); //Clear for next iteration
    }
}

/***********************************************************************
** Writes the results of the algorithm run to the output file
** Accepts: input array, subarray start index, subarray end index, sum,
**          and ofstream outputFile pointer
** Returns: -
***********************************************************************/
void writeToFile(int values[], int start, int end, int size, int sum, ofstream *outputFile)
{
    *outputFile << "[";
    //Writes original input values to file
    for(int i = 0; i < size; i++)
    {
        if(i == (size - 1))
            *outputFile << values[i] << "]" << endl;
        else
            *outputFile << values[i] << ", ";
    }
    
    //Writes subarray values to file
    *outputFile << "[";
    for(int i = start; i <= end; i++)
    {
        if(i == end)
            *outputFile << values[i] << "]" << endl;
        else
            *outputFile << values[i] << ", ";
    }
    *outputFile << sum << endl << endl; //Writes sum to file
}

/*
//Prints output of 2D vector to verify input converted correcty. *******  For Testing  ******
void printInput(vector<vector<int> > *input)
{
    vector<vector<int> >::iterator iter = input->begin();
    while(iter != input->end())
    {
        vector<int>::iterator iter2 = iter->begin();
        while(iter2 != iter->end())
        {
            cout << *iter2 << " ";
            iter2++;
        }
        cout << endl;
        iter++;
    }
}
*/
