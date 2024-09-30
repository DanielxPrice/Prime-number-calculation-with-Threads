This project leverages multithreading for concurrent prime number calculation, allowing for faster computation on multi-core systems.

    Data input with command-line argument:

        The program should accept a single command-line argument: an integer limit, which specifies the upper bound for prime number calculation. Example: If the user runs the program with the input 50, the program should output all prime numbers from 1 to 50. Example usage: ./prime_numbers 50 
        See code sample https://www.geeksforgeeks.org/command-line-arguments-in-cpp/ 

        Links to an external site. 

    Thread Creation:
        The program must create multiple threads to divide the prime number calculation.
        The number of threads should be determined by std::thread::hardware_concurrency(), which detects the number of available hardware threads on the system. See code sample below.
        Each thread will process a specific range of numbers to check for primes.

    Prime Calculation:
        Each thread will independently calculate primes within its assigned range.
        The prime checking function should efficiently determine if a number is prime.

    Thread Range Assignment:
        The range for each thread is determined by dividing the limit by the number of threads (numThreads).
        Example: For limit = 50 and numThreads = 4, thread 1 will handle numbers from 1 to 12, thread 2 from 13 to 24, thread 3 from 25 to 36, and thread 4 from 37 to 50.
        The last thread should handle any remaining numbers if the limit does not divide evenly by the number of threads.

    Result Collection:
        Each thread should store its prime numbers in a local vector.
        After all threads complete execution, the results from each thread should be combined into a single vector.
        The final list of prime numbers should be sorted before output to ensure correct order.

    Output:
        The program should output the prime numbers in ascending order.
        Example output for limit = 50

Prime numbers less than or equal to 50:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47

Additional Considerations: Ensure the program efficiently. Comment and document the code for clarity and maintainability. Test the program with various input cases to ensure correctness.
