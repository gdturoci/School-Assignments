#include <thread>
#include <chrono>
#include <iostream>
#include "util.h"
using namespace std;
using namespace std::chrono;

void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // write me in a SPMD parallel way!  partition the data using
  // "chunks" rather than strides.  That is thread 0 computes elements
  // 0 through size/num_threads.  thread 1 computes elements
  // size/num_threads through 2*(size/num_threads)
  int chunk_size = (size+(num_threads-1))/num_threads;
  int start = chunk_size * tid;
  int end = min(start+chunk_size, size);
  
  for (int i = start; i < end; i++) {
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
