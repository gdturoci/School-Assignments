#include <atomic>
using namespace std;

class CQueue {
 public:

  CQueue() {
    //Initialize box to 0 and flag to false
    box.store(0);
    flag.store(0);
  }

  void enq(float e) {
    //Spin while flag is green (true)
    while (flag.load()) this_thread::yield();
    
    //Put e in the box
    box.store(e);
    
    //set flag to green (true)
    flag.store(1);
  }

  float deq() {
    //Spin while flag has not been set
    while (!flag.load()) this_thread::yield();
    
    //Once flag is set, grab the value of box and set the flag back to red (false)
    float ret = box.load();
    flag.store(0);
    
    //Return box's former value
    return ret;
  }
  
  private:
    atomic_int box; //Where the producer stores values
    atomic_bool flag; //Can the consumer deque?
};
