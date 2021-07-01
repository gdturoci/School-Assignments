#include <atomic>
using namespace std;

class barrier_object {
 public:
  barrier_object() {} //Intentionally left empty

  void init(int num_threads) {
    count.store(num_threads);
    size = num_threads;
    sense.store(false);
    threadSense = new atomic_bool[num_threads];
    for (int x=0; x<num_threads; ++x)
       threadSense[x].store(!sense.load());
  }

  void barrier(int tid) {
    bool mySense = threadSense[tid].load();
    int position = count--;
    
    if (position == 1) {
       count.store(size);
       sense.store(mySense);
    } else {
      while (sense.load() != mySense) {}
    }
    threadSense[tid].store(!mySense);
  }

private:
  atomic_int count;
  atomic_bool sense;
  int size;
  atomic_bool *threadSense;
};