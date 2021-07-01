#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include "util.h"
using namespace std;
using namespace std::chrono;

std::atomic_int counter(0);
void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // Write me a parallel way using the global counter
  // as an implicit worklist. That is, every thread
  // should get its index from incrementing the counter
  for (int i = atomic_fetch_add(&counter, 1); i < size; i = atomic_fetch_add(&counter, 1)) {
    float base = result[i];
    for (int w = 0; w < mult[i]-1; w++) {
      result[i] = result[i]+base;
    }
  }
}

int main() {
  float* result_parallel = new float[SIZE];
  int* mult = new int[SIZE];
  for (int i = 0; i < SIZE; i++) {
    result_parallel[i] = i;
  }
  linear_work(mult, SIZE);

  //Time these threads
  auto start = high_resolution_clock::now();
  
  // Launch NUM_THREADS threads and then join them
  //Initialize array of threads
  thread threads[NUM_THREADS];
  
  //Run the function with threads
  for (int x=0; x<NUM_THREADS; ++x)
      threads[x] = thread(parallel_mult, result_parallel, mult, SIZE, x, NUM_THREADS);
  
  //Join the threads
  for (int x=0; x<NUM_THREADS; ++x)
      threads[x].join();
  
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(end-start);
  double seconds = duration.count()/1000000000.0;
  
  //Print the time
  cout << "Time: " << seconds << endl; 
  
  return 0;
}
