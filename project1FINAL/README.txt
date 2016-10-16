Project 1 - Group 32
CS325-400 F16

Meredith Kiessling
Evan Lyon
Fahmy Mohammed

Files included:
	-maxSubArrayAlgorithms.cpp
		- Contains all four max subarray algorithm implementations
	-maxSubArrayAlgorithms.hpp
		- Contains all four max subarray algorithm declarations
	-calMaxSubArray.cpp
		- Reads in data from "MSS_Problems.txt" and converts it into
		  a 2D vector with each vector inside representing an array from the input 
		  file. The input is then used to run each of the four max subarray
		  algortihms and the results from each algorithm run is written to
		  "MSS_Results.txt"
	-MSS_Problems.txt

Compiling instructions:
	-Command to compile the program:
		- g++ maxSubArrayAlgorithms.cpp maxSubArrayAlgorithms.hpp calcMaxSubArray.cpp -o calcMaxSubArray
	-Once compiled, run the program with:
		- ./calcMaxSubArray
	-MSS_Problems.txt file must be in the same directory