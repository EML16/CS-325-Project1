# CS-325-Project1
Repo for CS 325 Project 1 

Contents of the files thus far, Please alter as you add. 

	Algo.h:		
		Header file that contains the declarations of the two functions

	Algo.cpp: 	
		Contains implementation of algorithm 1 and 2 for project 1. 

	calculateRunTime.cpp
		- The program used to calculate the average running time of the algorithms.
		- 20 arrays, each with varying size, are considered.
		- The elements in each array are generated randomly and each element is in the range [-100, 99)
		- The average running time is calculated by taking the average of 10 executions of 
			the algorithm on different arrays but identical size.
		- The average times are in milliseconds
	main.cpp
		- The program that generates the maximum subarray along with its sum
		- It expects its input from 'MSS_Problems.txt', where each line is the input array
			formatted as [a, b, c, d, ...]
		- For each input array a result is written in the file 'MSS_Results.txt'.
		- Make sure to rename/copy 'MSS_Results.txt' before rerunning this program.
    alg3.hpp:
        - Header file that contains declarations of the algorithm and helper function
    alg3.cpp
        - Contains implementation of algorithm 3
    maxSubArrayTester.cpp
        - Reads input from file ('MSS_problems.txt')
        - Converts the input and inserts into correct position in 2D vector
        - Converts each vector inside 2D vector to an array and runs algorithm with it
        - Writes results of algorithm run to results.txt file
        - Also contains a function that runs the algorithm 10 times with randomly generated input of 
            size n and calculates the average. Used for experimental analysis
    

Compiling Instructions:
	The programs utilize some c++11 constructs; hence, they have to be compiled with the flag '-std=c++11'

Compiling the main program
	$ g++ -std=c++11 -c Algo.cpp -o Algo.o
	$ g++ -std=c++11 -c main.cpp -o main.o
	$ g++ Algo.o main.o -o exeMain

Running the main program
	$ exeMain <algo_no>
		where <algo_no> is the algorithm identifier, 1:Enumeration, 2:ImprovedEnumeration

Compiling for the program to calculate the running times
	$ g++ -std=c++11 -c Algo.cpp -o Algo.o
	$ g++ -std=c++11 -c calculateRunTime.cpp -o calculateRunTime.o
	$ g++ calculateRunTime.o Algo.o -o exeCalculateRunTime

Running runtime calculator
	$ exeCalculateRunTime <algo_no> <initial_input_size> <size_increment> <logfile>
		where:
			<algo_no>:	Algorithm identifier
			<initial_input_size>:	The size of the first array
			<size_increment>:		The difference in the number of elements between two successive arrays
			<logfile>:	A file where each line contains an array size and average running time in milliseconds

Compiling alg3.hpp, alg3.cpp and maxSubArrayTester.cpp
    $ g++ alg3.cpp alg3.hpp maxSubArrayTester.cpp -o max
