#include <atomic>
using namespace std;

class IOQueue {
 public:
  IOQueue() {
    head.store(0);
    tail.store(0);
  }


  // Use this function to initialize the queue to
  // the size that you need.
  void init(int size) {
      queue = new int[size];
  }

  // enqueue the element e into the queue
  void enq(int e) {
    //Store e at head in the buffer then increment head
    queue[head.load()] = e;
    atomic_fetch_add(&head, 1);
  }

  // return a value from the queue.
  // return -1 if there is no more values
  // from the queue.
  int deq() {
    //Return -1 if the queue is empty
    if (tail.load() == head.load()) return -1;
    
    //read the value at the tail then increment tail
    int ret = queue[tail.load()];
    atomic_fetch_add(&tail, 1);
    
    //Return the value we grabbed
    return ret;
  }

  // return 32 values from the queue. The
  // values should be returned through
  // the array passed in.
  // return 0 if successful. return -1 if not
  // i.e. if the queue does not have 32 elements
  int deq_32(int ret[32]) {
    //If queue is too empty, return 1
    if ((head.load() - tail.load()) < 32) return -1;
    
    for (int x=0; x<32; ++x)
        ret[x] = deq();
    
    //If successful, return 0
    return 0;
  }

 private:
  atomic_int head; //Where we enqueue
  atomic_int tail; //Where we dequeue
  int *queue;
};
