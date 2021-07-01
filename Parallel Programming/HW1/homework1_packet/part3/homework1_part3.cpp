//Include all the necessary headers
#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

//Define the important macros
#define SIZE 1024
#define THREADS 4
#define K 1048576

//Store K into a sequentially
void sequential_store(volatile int *a) {
    for (int x=0; x<SIZE; ++x)
        a[x] = K;
}

//Use a Round-Robin algorithm to store K into b via threads
void RR_store(volatile int *b, int tid, int num_threads) {
    for (int x=tid; x<SIZE; x+=num_threads)
        b[x] = K;
}

//Use a reduction-like algorithm to store K into c via threads
void parallel_store(volatile int *c, int tid, int num_threads) {
    for (int x=tid; x<SIZE/num_threads; ++x)
        c[x] = K;
}


int main() {
    
    //Initialize the arrays to 0
    int *a = new int[SIZE];
    int *b = new int[SIZE];
    int *c = new int[SIZE];
    
    for (int x=0; x<SIZE; ++x) {
        a[x] = 0;
        b[x] = 0;
        c[x] = 0;
    }
    
    //Initialize an array of threads
    thread threads[THREADS];
    
    //Run the algorithms and time them
    auto seq_start = high_resolution_clock::now();
    sequential_store(a);
    delete[] a;
    auto seq_end = high_resolution_clock::now();
    auto seq_duration = duration_cast<nanoseconds>(seq_end-seq_start);
    double seq_seconds = seq_duration.count()/1000000000.0;

    auto RR_start = high_resolution_clock::now();
    for (int x=0; x<THREADS; ++x)
        threads[x] = thread(RR_store, b, x, THREADS);
    delete[] b;
    auto RR_end = high_resolution_clock::now();
    for (int x=0; x<THREADS; ++x)
        threads[x].join();
    auto RR_duration = duration_cast<nanoseconds>(RR_end-RR_start);
    double RR_seconds = RR_duration.count()/1000000000.0;

    auto par_start = high_resolution_clock::now();
    for (int x=0; x<THREADS; ++x)
        threads[x] = thread(parallel_store, c, x, THREADS);
    delete[] c;
    auto par_end = high_resolution_clock::now();
    for (int x=0; x<THREADS; ++x)
        threads[x].join();
    auto par_duration = duration_cast<nanoseconds>(par_end-par_start);
    double par_seconds = par_duration.count()/1000000000.0;

    //Print the timings
    cout << "sequential loop time: " << seq_seconds << endl; 
    cout << "RR loop time: " << RR_seconds << endl; 
    cout << "parallel loop time: " << par_seconds << endl;
    cout << "-----------------" << endl;
    cout << "speedups:" << endl;
    cout << "RR speedup over sequential: " << seq_seconds/RR_seconds << endl << endl;
    cout << "parallel speedup over sequential: " << seq_seconds/par_seconds << endl << endl;
    cout << "parallel speedup over RR: " << RR_seconds/par_seconds << endl << endl;

    return 0;
}