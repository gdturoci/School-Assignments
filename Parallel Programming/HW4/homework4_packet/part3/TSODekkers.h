#include <atomic>
using namespace std;

// this should be the same as RDekkers with the change that every
// relaxed access should be memory_order_relaxed.
// your job is to use the following MACRO to fix the mutex.
// Think about the reorderings allowed under TSO and where the fence
// needs to be placed.

#define FENCE asm volatile("mfence":::"memory");

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
    FENCE;
    while (wants_to_enter[1-tid].load(memory_order_relaxed)) {
      if (turn.load(memory_order_relaxed) != tid) {
          wants_to_enter[tid].store(false, memory_order_relaxed);
          while (turn.load(memory_order_relaxed) != tid) {}
      }
      wants_to_enter[tid].store(true, memory_order_relaxed);
      FENCE;
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