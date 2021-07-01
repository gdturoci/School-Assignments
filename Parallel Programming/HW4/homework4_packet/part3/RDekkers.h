#include <atomic>
using namespace std;

class dekkers_mutex {
public:
  dekkers_mutex() {
    wants_to_enter = new atomic_bool[2];
    wants_to_enter[0].store(false, memory_order_relaxed);
    wants_to_enter[1].store(false, memory_order_relaxed);
    
    turn.store(0, memory_order_relaxed);
  }

  void lock(int tid) {
    wants_to_enter[tid].store(true, memory_order_relaxed);
    while (wants_to_enter[1-tid].load(memory_order_relaxed)) {
      if (turn.load(memory_order_relaxed) != tid) {
          wants_to_enter[tid].store(false, memory_order_relaxed);
          while (turn.load(memory_order_relaxed) != tid) {}
      }
      wants_to_enter[tid].store(true, memory_order_relaxed);
    }
  }

  void unlock(int tid) {
    turn.store(1-tid, memory_order_relaxed);
    wants_to_enter[tid].store(false, memory_order_relaxed);
  }

private:
  atomic_bool *wants_to_enter;
  atomic_int turn;
};