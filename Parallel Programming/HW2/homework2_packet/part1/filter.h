#pragma once

#include <atomic>
using namespace std;

class mutex {
 public:
  mutex() {}
  
  void init (int num_threads) {
    //Initialize our arrays and note how many threads we're working with
    level = new atomic_int[num_threads];
    victim = new atomic_int[num_threads];
    for (int x=0; x<num_threads; ++x)
        level[x].store(0);
    n_threads = num_threads;
  }
  
  void lock(int thread_id) {
    //for each thread, store what level we're on and spin until it's our turn
    for (int x=1; x<n_threads; ++x) {
        level[thread_id].store(x);
        victim[x].store(thread_id);
        while (level[thread_id].load() < x && victim[x].load() == thread_id) this_thread::yield();
  }
  
  void unlock(int thread_id) {
    level[thread_id].store(0); //place this thread on level 0
  }

  private:
    //Make the necessary variables
    atomic_int *level;
    atomic_int *victim;
    int n_threads;
};
