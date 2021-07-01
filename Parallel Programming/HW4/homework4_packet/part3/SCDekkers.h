#include <atomic>
using namespace std;

class dekkers_mutex {
public:
  dekkers_mutex() {
    wants_to_enter = new atomic_bool[2];
    wants_to_enter[0].store(false);
    wants_to_enter[1].store(false);
    
    turn.store(0);
  }

  void lock(int tid) {
    wants_to_enter[tid].store(true);
    while (wants_to_enter[1-tid].load()) {
      if (turn.load() != tid) {
          wants_to_enter[tid].store(false);
          while (turn.load() != tid) {}
      }
      wants_to_enter[tid].store(true);
    }
  }

  void unlock(int tid) {
    turn.store(1-tid);
    wants_to_enter[tid].store(false);
  }

private:
  atomic_bool *wants_to_enter;
  atomic_int turn;
};
