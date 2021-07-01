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
  //Unrolling this loop by a factor of 8
  for (int i = 0; i < size; i+=8) {
    //Set up our float to load into the array, pull it out, and then store it back
    float loaded = a[i];
    memory_to_trig.enq(loaded);
    float to_store = trig_to_memory.deq();
    a[i] = to_store;
    
    loaded = a[i+1];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+1] = to_store;
    
    loaded = a[i+2];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+2] = to_store;
    
    loaded = a[i+3];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+3] = to_store;
    
    loaded = a[i+4];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+4] = to_store;
    
    loaded = a[i+5];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+5] = to_store;
    
    loaded = a[i+6];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+6] = to_store;
    
    loaded = a[i+7];
    memory_to_trig.enq(loaded);
    to_store = trig_to_memory.deq();
    a[i+7] = to_store;
  }
}

void trig_thread_func(int size) {
  //Unrolling this loop by a factor of 8
  for (int i = 0; i < size; i+=8) {
    //Set up our float and then cosine 8 items at a time
    float target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
    
    target = memory_to_trig.deq();
    target = cos(target);
    trig_to_memory.enq(target);
  }
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
