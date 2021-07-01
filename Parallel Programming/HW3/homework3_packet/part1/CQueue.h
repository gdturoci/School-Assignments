#include <atomic>
using namespace std;

#define CQUEUE_SIZE 2048

class CQueue {
 public:

  CQueue() {
    //Initialize head and tail to 0 and buffer to CQUEUE_SIZE
    head.store(0);
    tail.store(0);
    buffer = new int[CQUEUE_SIZE];
  }

  void enq(float e) {
    //store head+1 as a variable so we can make it 0 when need be
    int hpo = head.load()+1;
    if (hpo == CQUEUE_SIZE) hpo=0;
    
    //Spin while queue is full
    while (hpo == tail.load()) this_thread::yield();
    
    //If at the end of the buffer return to 0
    if (head.load() == CQUEUE_SIZE) head.store(0);
    
    //Store e at head in the buffer then increment head
    buffer[head.load()] = e;
    atomic_fetch_add(&head, 1);
  }

  void enq_8(float e[8]) {
    //Spin while queue is (close to) full (need 8 spots open)
    while (size() > CQUEUE_SIZE-8) this_thread::yield();
    
    //Store 8 values into the queue
    for (int x=0; x<8; ++x)
        enq(e[x]);
  }


  float deq() {
    //Spin while queue is empty
    while (tail.load() == head.load()) this_thread::yield();
    
    //If at the end of the buffer return to 0
    if (tail.load() == CQUEUE_SIZE) tail.store(0);
    
    //read the value at the tail then increment tail
    float ret = buffer[tail.load()];
    atomic_fetch_add(&tail, 1);
    
    //Return the value we grabbed
    return ret;
  }

  void deq_8(float e[8]) {
    //Spin while queue is (close to) empty
    while (size() < 8) this_thread::yield();
   
    for (int x=0; x<8; ++x)
        e[x] = deq();
  }


  int size() {
    //If head has looped back around and is now behind tail,
    //size is head's position + the distance between tail and the end
    if (head.load() < tail.load())
        return head.load() + (CQUEUE_SIZE - tail.load());
    
    //Else size is head - tail
    return head.load() - tail.load();
  }
  
 private:
  atomic_int head; //Where we enqueue
  atomic_int tail; //Where we dequeue
  int *buffer;
};