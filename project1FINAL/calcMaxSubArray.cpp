/****************************************************************************************
 ** Project 1 - Group 32
 ** CS325-400 F16
 **
 ** Meredith Kiessling
 ** Evan Lyon
 ** Fahmy Mohammed
 **
 **
 ** Description: This program reads in data from "MSS_Problems.txt" and converts it into
 **              a 2D vector with each vector inside representing an array from the input
 **              file. The input is then used to run each of the four max subarray
 **              algortihms and writes the results from each run to "MSS_Results.txt".
 ****************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "maxSubArrayAlgorithms.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::stringstream;
using std::getline;

void readFromFile(ifstream *inputFile, vector<vector<int> > *convertedInput);
void writeToFile(int values[], int start, int end, int size, int sum, ofstream *outputFile, string algorithmUsed);

int main()
{
    ifstream inputFile;
    inputFile.open("./MSS_Problems.txt", std::ios::in);
    if (!inputFile) //check if the file opened successfully
        cout << "Cannot open file for reading" << endl;
    
    vector<vector<int> > convertedInput; //2D vector to hold values from file
    readFromFile(&inputFile, &convertedInput); //Read values from file and insert into 2D vector
    inputFile.close(); //Close input file
    
    ofstream outputFile;
    outputFile.open("./MSS_Results.txt", std::ios::out);
    if (!outputFile) //check if the file opened successfully
        cout << "Cannot open file for writing" << endl;
    
    vector<vector<int> >::iterator iter = convertedInput.begin(); //Iterator used to iterate through all vectors inside 2D vector
    iter = convertedInput.begin();
    
    subArray result = {0, 0, 0}; //Struct used to store subarray start index, end index and sum
    
    //Iterate through 2D vector
    while(iter != convertedInput.end())
    {
        vector<int>::iterator iter2 = iter->begin(); //Iterator for vector inside of 2D vector
        int size = (int) iter->size(); //Number of elements inside the vector
        int *input = new int[size]; //Create a new array to match the size of vector
        int i = 0;
        
        //Iterate though vector inside and convert to an array
        while(iter2 != iter->end())
        {
            input[i] = *iter2; //Insert value in array
            iter2++;
            i++;
        }
        
        //Calculate max subarray using Enumeration algorithm
        maxSubArrayEnumeration(*iter, result.start, result.end, result.sum);
        writeToFile(input, result.start, result.end, size, result.sum, &outputFile, "Enumeration"); //Write results to file
       
        //Calculate max subarray using Better Enumeration algorithm
        maxSubArrayImprovedEnumeration(*iter, result.start, result.end, result.sum);
        writeToFile(input, result.start, result.end, size, result.sum, &outputFile, "Better Enumeration"); //Write results to file
        
        //Calculate max subarray using Divide & Conquer algorithm
        result = maxSubArrayDivideConquer(input, 0, size - 1);
        writeToFile(input, result.start, result.end, size, result.sum, &outputFile, "Divide & Conquer"); //Write results to file
        
        //Calculate max subarray using Linear-Time algorithm
        maxSubArrayLinearTime(input, size, result.start, result.end, result.sum);
        writeToFile(input, result.start, result.end, size, result.sum, &outputFile, "Linear-Time"); //Write results to file
        outputFile << "--------------------------------------" << endl <<endl;
        
        iter++; //Point to next vector inside 2D vector
        delete[] input; //Free up memory allocated to the array for next iteration
    }
    outputFile.close();
    
    return 0;
}

/****************************************************************************************
 ** Function: readFromFile(ifstream *, vector< vector<int> > *)
 ** Description: Reads input from file, converts each "array" of intergers and places
 **              each into the correct position in a 2D vector (convertedInput).
 ** Parameters:  ifstream *inputFile, vector<vector<int> > *convertedInput
 ** Pre-Conditions: File must have opened successfully
 ** Post-Conditions: convertedInput contains all input from file in correct position
 ****************************************************************************************/
void readFromFile(ifstream *inputFile, vector< vector<int> > *convertedInput)
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

/****************************************************************************************
 ** Function: writeToFile(int [], int, int, int, int, ofstream *, string)
 ** Description: Writes the results of the algorithm run to the output file
 ** Parameters: int values[], int start, int end, int size, int sum, ofstream *outputFile, 
 **             string algorithmUsed
 ** Pre-Conditions: File must have opened successfully
 ** Post-Conditions: output file contains results of algorithm run
 ****************************************************************************************/
void writeToFile(int values[], int start, int end, int size, int sum, ofstream *outputFile, string algorithmUsed)
{
    *outputFile << algorithmUsed << endl;;
    *outputFile << "[";
    //Write original input values to file
    for(int i = 0; i < size; i++)
    {
        if(i == (size - 1))
            *outputFile << values[i] << "]" << endl;
        else
            *outputFile << values[i] << ", ";
    }
    
    //Write subarray values to file
    *outputFile << "[";
    for(int i = start; i <= end; i++)
    {
        if(i == end)
            *outputFile << values[i] << "]" << endl;
        else
            *outputFile << values[i] << ", ";
    }
    *outputFile << sum << endl << endl; //Write sum to file
}
