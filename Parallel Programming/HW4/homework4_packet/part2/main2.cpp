#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

#include "SRBarrier.h"
barrier_object B;

#define TEST_ITERATIONS (1024*256)

atomic_int x(0);
atomic_int y(0);
int v0;
int v1;
void t0_function() {
  x.store(1, memory_order_relaxed);
  v0 = y.load(memory_order_relaxed);
  B.barrier(0);
}

void t1_function() {
  y.store(1, memory_order_relaxed);
  v1 = x.load(memory_order_relaxed);
  B.barrier(1);
}


int main() {

  int output0 = 0;
  int output1 = 0;
  int output2 = 0;
  int output3 = 0;
  B.init(2);
  
  //Make two threads
  thread t0;
  thread t1;
  
  for (int i = 0; i < TEST_ITERATIONS; i++) {
    // Run a test iteration
    t0 = thread(t0_function);
    t1 = thread(t1_function);
    
    // Record a histogram, fill in the conditions
    if (v0 == 1 and v1 == 1) {
      output0++;
    }
    else if (v0 == 0 and v1 == 1) {
      output1++;
    }
    else if (v0 == 1 and v1 == 0) {
      output2++;
    }
    // This should be the relaxed behavior
    else if (v0 == 0 and v1 == 0) {
      output3++;
    }
    
    t0.join();
    t1.join();
    
  }

  // Complete the print out using your output instantiations
  cout << "histogram of different observations:" << endl;
  cout << "output0: 1 1: " << output0 << endl;
  cout << "output1: 0 1: " << output1 << endl;
  cout << "output2: 1 0: " << output2 << endl;
  cout << "output3: 0 0: " << output3 << endl << endl;
  cout << "relaxed behavior frequency: " << float(output3)/float(TEST_ITERATIONS) << endl;
  
  return 0;
  
}
