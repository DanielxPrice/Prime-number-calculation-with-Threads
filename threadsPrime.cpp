/* 
Author: Daniel Price
Last Updated: 9/30/2024
*/
#include <iostream>
#include <thread>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Note: My computer creates 5 threads

// Calculating the prime numbers
bool isPrime(int num) 
{
    if (num <= 1) 
    {
        return false;
    }
    for (int i = 2; i * i <= num; ++i) 
    {
        if (num % i == 0) return false;
    }
    return true;
}

// Storing the prime numbers
void workerFunction(vector<int>& array, int start, int end, vector<int>& returnResults) 
{
    vector<int> localResults = {};
    for (int i = start; i <= end; ++i) 
    {
        // Example processing: store prime numbers
        if (isPrime(array[i])) 
        {
            localResults.push_back(array[i]);
        }
    }
    returnResults = localResults;
}

int main(int argc, char* argv[]) 
{
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        numThreads = 2;  // Default to 2 threads if hardware_concurrency() can't determine the value
    }

    std::cout << "Creating " << numThreads << " threads.\n";

    int limit;
    // Convert the argument from string to int
    if (argc > 1) 
    {
        limit = atoi(argv[1]); 
    } 
    else 
    {
        limit = 50;
    }
    cout << "Limit: " << limit << endl;


    // Creation of Containters
    vector<int> myArray(limit);
    unordered_map<int, int> startEnd;

    // Filling the array with the limit
    for (int i = 0; i < limit; ++i)
    {
        myArray[i] = i + 1;
    }

    // Calculating the range
    int range = limit / numThreads;
    cout << "Range for the limit: " << range << endl;

    // Assigning the start and end indicies to an unordered map. The key is the starting element and the value is the ending element
    for (int i = 0; i < numThreads; ++i) 
    {
        // Start index
        int start = i * range; 
        // End index
        int end; 

        if (i == numThreads - 1) 
        {
            // Last thread should cover the rest of the array
            end = limit - 1; 
        } 
        else 
        {
            end = start + range - 1;
        }
        // Store the indices in the map
        startEnd[start] = end; 
    }
    
    // Testing output to make sure that the indicies are correct
    std::cout << "Start and End indices for each thread:\n";
    for (const auto& entry : startEnd) 
    {
        std::cout << "Thread starting at index " << entry.first << " ends at index " << entry.second << std::endl;
    }


    // Vector for Threads
    vector<thread> threads;
    // Vector of Vectors for the results of the prime function
    vector<vector<int>> results(numThreads);

    int i = 0;
    // Loop through the unordered_map to create threads
    for (const auto& entry : startEnd) 
    {
        // Start index from the key
        int start = entry.first; 
        // End index from the value   
        int end = entry.second;  


        // Create a thread for each range
        threads.emplace_back(workerFunction, ref(myArray), start, end, ref(results[i]));
        ++i;
    }


    for (auto& t : threads) {
        t.join();  // Wait for all threads to finish
    }

    // Combine results from all threads
    vector<int> combinedResults;
    for (const auto& localResults : results) 
    {
        combinedResults.insert(combinedResults.end(), localResults.begin(), localResults.end());
    }

    // Sort the combined vector
    sort(combinedResults.begin(), combinedResults.end());

    // Print combined results
    cout << "Prime numbers found: ";
    for (const auto& prime : combinedResults) 
    {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}