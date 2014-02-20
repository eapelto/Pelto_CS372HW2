// delegate.cpp
// Eric Pelto
// 17 Feb 2014
//
// For CS 372 Spring 2014
// cs 372 hw2


#include "sa2a.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <thread>
using std::thread;
#include <mutex>
using std::mutex;
using std::lock_guard;
#include <vector>
using std::vector;
#include <cstdlib>
using std::exit;
#include <queue>
using std::queue;

#include <time.h>
#include <stdio.h>

mutex first_lock; //to lock and unlock with first variable
mutex print_lock; //to lock and unlock with print function
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
		
		first_lock.lock();	//lock

		//if que is empty stop while loop
		if (input.empty())
		{
			first_lock.unlock();
			break;
		}
		
		
		first = input.front();
		input.pop();
		
		first_lock.unlock();	//unlock

		second = sa2a(first);


		//lock call print then unlock
		print_lock.lock();
		print(first, second);
		print_lock.unlock();


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
	while(true)
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


	const int NUMTHREADS = 6;  // Number of threads to spawn

	// Vector of thread objects, not yet holding actual threads
	vector<thread> ts(NUMTHREADS);

	// Spawn all threads
	for (int i = 0; i < NUMTHREADS; ++i)
	{
		try
		{
			
			ts[i] = thread(run);
			
		}
		catch (...)
		{
			cout << endl;
			cout << "ERROR: It appears that we can only spawn "
				<< i << " threads on this system." << endl;
			cout << "  Try reducing NUMTHREADS to " << i
				<< " and recompiling." << endl;
			exit(1);
		}
	
	}

	// Join all spawned threads
	for (int i = 0; i < NUMTHREADS; ++i)
	{
		ts[i].join();
	}

	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	cout << "Time elapsed in ms: " << elapsed;



	return 0;
}
