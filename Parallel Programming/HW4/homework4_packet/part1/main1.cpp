#include "common.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


void repeated_blur(double *input, double *output, int size, int tid, int num_threads) {
   
   int chunk_size = (size+(num_threads-1))/num_threads;
   int start = chunk_size * tid;
   if (start == 0) start = 1;
   int end = min(start+chunk_size, size);
   if (end == size) end = size-1;
   
   for (int x=start; x<end; ++x)
      output[x] = (input[x] + input[x+1] + input[x-1])/3;
}

int main(int argc, char *argv[]) {
  int num_threads = 8;
  if (argc > 1) {
    num_threads = atoi(argv[1]);
  }

  double *input = new double[SIZE];
  double *output = new double[SIZE];


  for (int i = 0; i < SIZE; i++) {
    double randval = fRand(-100.0, 100.0);
    input[i] = randval;
    output[i] = randval;
  }

  //Create an array of threads
  thread *thread_array = new thread[num_threads];

  auto time_start = std::chrono::high_resolution_clock::now();
  for (int r = 0; r < REPEATS; r++) {
    // Launch threads to compute the blur
    for (int i = 0; i < num_threads; ++i)
       thread_array[i] = thread(repeated_blur, input, output, SIZE, i, num_threads);
    
    // Join threads
    for (int i = 0; i < num_threads; ++i)
       thread_array[i].join();
    
    // Swap input and output pointers.
    double *tmp = input;
    input = output;
    output = tmp;
  }

  auto time_end = std::chrono::high_resolution_clock::now();
  auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;
  std::cout << "timings: " << time_seconds << std::endl;
      
}
