#pragma once

#include <atomic>
#include <vector>
#include <mutex>
using namespace std;

class rw_mutex {
    public:
        rw_mutex() {
            writer = false;
            num_readers = 0;
            ticket.store(1); //Ticket starts at 1
        }

    void lock_reader() {
        bool acquired = false;
        //Lock the vector as it's being operated on
        internal_mutex.lock();
        readtic.push_back(ticket++);
        internal_mutex.unlock();
        
        while (!acquired) {
            internal_mutex.lock();              //Check that it's the reader's turn
            if (!writer && (writetic.empty() || readtic.front() < writetic.front())) {
                num_readers++;
                acquired = true;
            }
            internal_mutex.unlock();
        }
    }
  
    void unlock_reader() {
        internal_mutex.lock();
        num_readers--;
        readtic.erase(readtic.begin()); //Toss the used ticket out
        internal_mutex.unlock();
    }

  
    void lock() {
        bool acquired = false;
        //Lock the vector as it's being operated on
        internal_mutex.lock();
        writetic.push_back(ticket++);
        internal_mutex.unlock();
        
        while (!acquired) {
            internal_mutex.lock();              //Check that it's the writer's turn
            if (!writer && num_readers == 0 && (readtic.empty() || writetic.front() <= readtic.front())) {
                writer = true;
                acquired = true;
            }
            internal_mutex.unlock();
        }
    }
  
    void unlock() {
        internal_mutex.lock();
        writer = false;
        writetic.erase(writetic.begin()); //Toss the used ticket out
        internal_mutex.unlock();
    }

    private:
        mutex internal_mutex;
        bool writer;
        int num_readers;
        atomic_int ticket; //Tickets for whose turn it is
        vector<int> readtic; //The readers' tickets
        vector<int> writetic; //The writers' tickets
};
