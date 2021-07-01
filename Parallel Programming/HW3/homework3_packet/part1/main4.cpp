#include <math.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include "CQueue.h"
using namespace std;
using namespace std::chrono;

#define SIZE (1024 * 1024 * 8)

CQueue memory_to_trig;
CQueue trig_to_memory;

void memory_thread_func(float *a, int size) {
  //Make the array we're gonna pass to enq_8/deq_8
  float *b = new float[8];
  for (int i = 0; i < size; i+=8) {
    //fill b with 8 of a's values
    for (int x=0; x<8; ++x)
        b[x] = a[i+x];
    
    //Pass b to enq_8 and deq_8
    memory_to_trig.enq_8(b);
    trig_to_memory.deq_8(b);
  }
  
  //free b's allocated memory
  delete[] b;
}

void trig_thread_func(int size) {
//Make the array we're gonna pass to enq_8/deq_8
  float *b = new float[8];
  for (int i = 0; i < size; i+=8) {
    //fill b with values
    memory_to_trig.deq_8(b);
    
    //Get the cosine of those values
    for (int x=0; x<8; ++x) {
        float target = b[x];
        target = cos(target);
        b[x] = target;
    }
    
    //Pass b to enq_8
    trig_to_memory.enq_8(b);
  }
  
  //free b's allocated memory
  delete[] b;
}

int main() {
  float *a = new float[SIZE];
  for (int i = 0; i < SIZE; i++) {
    a[i] = 0.5 + i;
  }
  
  //time these threads
  auto start = high_resolution_clock::now();
  
  std::thread memory_thread(memory_thread_func,a,SIZE);
  std::thread trig_thread(trig_thread_func, SIZE);

  memory_thread.join();
  trig_thread.join();
  
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(end-start);
  double seconds = duration.count()/1000000000.0;
  
  //Print the time
  cout << "Time: " << seconds << endl; 
  
  return 0;
}
