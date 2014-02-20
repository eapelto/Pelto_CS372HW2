// noThread
// Eric Pelto
// 19 Feb 2014
//
// For CS 372 Spring 2014
// cs 372 hw2


#include "sa2a.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <cstdlib>
using std::exit;
#include <queue>
using std::queue;

#include <time.h>
#include <stdio.h>

queue<int> input; //que to hold integers from user.

void print(int, int);


//Run function for spawned threads
//the thread calls run() to then call sa2a
//Made thread-safe lock(), unlock()
void run()
{
	int first;
	int second;


	while (true)
	{

	

		//if que is empty stop while loop
		if (input.empty())
		{
			
			break;
		}


		first = input.front();
		input.pop();

	

		second = sa2a(first);


		//lock call print then unlock
	
		print(first, second);
	


	}



}

//print function for threads
void print(int first, int second)
{
	cout << "sa2a(" << first << ") = " << second << endl;
}


int main()
{
	clock_t start = clock();

	//Get integers from the user and put them into a vector of ints
	while (true)
	{
		int myint;
		cout << "Enter a positive integer (or 0 to end input):";
		cin >> myint;

		//If 0 stop getting integers
		if (myint < 1)
		{
			break;
		}

		//push integers into que
		input.push(myint);
	}


	run();  // No threads just call run()

	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	cout << "Time elapsed in ms: " << elapsed << endl;


	
	return 0;
}
