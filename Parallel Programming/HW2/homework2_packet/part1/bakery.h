#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {
    max = 0; //Start the maximum ticket value at 0
  }
  
  void init(int num_threads) {
    //Initialize the arrays
    entering = new atomic_bool[num_threads];
    ticket = new atomic_int[num_threads];
    for (int x=0; x<num_threads; ++x) {
        entering[x].store(0);   ticket[x].store(0);
    }
  }
  
  void lock(int thread_id) {
    //The thread enters
    entering[thread_id].store(1);
    int ticsize = sizeof(ticket)/sizeof(ticket[0].load());
    //The thread's ticket is set to 1 higher than the max
    for (int x=0; x<ticsize; ++x) {
        if (ticket[x].load() > max) max = ticket[x].load();
    }
    ticket[thread_id].store(max+1);
    entering[thread_id].store(0);
    //For each thread...
    for (int x=0; x<ticsize; ++x) {
        //For each thread that isn't the current one, spin until their ticket is called/it's their turn
        if (x != thread_id) {
            while (entering[x].load()) this_thread::yield();
            while (ticket[x].load() != 0 && (ticket[x].load() < ticket[thread_id].load() ||
                                    (ticket[x].load() == ticket[thread_id].load() && x<thread_id))) this_thread::yield();
        }
    }
  }
  
  void unlock(int thread_id) {
    ticket[thread_id].store(0); //Set this thread's ticket to 0 when it's done
  }

 private:
  //Set up our needed variables
  atomic_bool *entering;
  atomic_int *ticket;
  int max;
};
