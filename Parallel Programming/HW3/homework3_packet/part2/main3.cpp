#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include "util.h"
#include "IOQueue.h"
using namespace std;
using namespace std::chrono;

IOQueue Q[NUM_THREADS];
std::atomic_int finished_threads(0);
void parallel_enq(int size, int tid, int num_threads) {
  // Use this function to equeue indexes to each of the local
  // workstealing queues
  int chunk_size = size/num_threads;
  int start = chunk_size * tid;
  int end = start+chunk_size;
  for (int x=start; x<end; ++x)
      Q[tid].enq(x);
}


void parallel_mult(float * result, int *mult, int size, int tid, int num_threads) {
  // Implement me using a workstealing approach.
  // You should use the Q IOQueues to compute
  // local work and then try to steal work
  // from others until all the work is completed
  int task = Q[tid].deq();
  while (task != -1) {
    float base = result[task];
    for (int w = 0; w < mult[task]-1; w++)
      result[task] = result[task]+base;

    task = Q[tid].deq();
  }
  atomic_fetch_add(&finished_threads, 1);
  
  //While there are still threads with workloads, steal work from them
  while (finished_threads.load() != num_threads) {
      //steal work from your neighbor
      int target = tid-1;
      if (tid == 0) target = tid+1;
      
      //Get your target's task and do it
      task = Q[target].deq();
      while (task != -1) {
         float base = result[task];
         for (int w = 0; w < mult[task]-1; w++)
            result[task] = result[task]+base;
        task = Q[target].deq();
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
  
  // Launch NUM_THREADS threads to intialize the IOQueues in Q with
  // the indexes for each thread. Remember to initialize the Queues
  // with the size that they will need. Join the threads afterwards.
  //Initialize the queues
  for (int x=0; x<NUM_THREADS; ++x)
      Q[x].init(SIZE/NUM_THREADS);
  
  //Initialize array of threads
  thread threads[NUM_THREADS];
  
  //Initialize the queues for each thread
  for (int x=0; x<NUM_THREADS; ++x)
      threads[x] = thread(parallel_enq, SIZE, x, NUM_THREADS);
  
  //Join the threads
  for (int x=0; x<NUM_THREADS; ++x)
      threads[x].join();

  // Next, launch the parallel function that performs the parallel_mult
  // function from main1.cpp and main2.cpp but using workstealing
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
