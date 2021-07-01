#include <shared_mutex>
using namespace std;

class Llist_node {
 public:  
  Llist_node(int d) {   
    data = d;
    next = NULL;
  }
  
  int data;
  Llist_node *next;
};

class CSE113_Stack {
 public:
  
  CSE113_Stack() {
    start = NULL;
  }
  
  int pop() {
    //This function writes so using the exclusive lock;
    mtx.lock();
    if (start == NULL) {
      mtx.unlock(); //Unlock before returning
      return -1;
    }
    
    if (start->next == NULL) {
      int ret = start->data;
      delete start;
      start = NULL;
      mtx.unlock(); //Unlock before returning
      return ret;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;
    while (current->next != NULL) {
      previous = current;
      current = current->next;
    }
    
    int ret = current->data;
    previous->next = NULL;
    delete current;
    mtx.unlock(); //Unlock before returning
    return ret;
  }

  
  int peek() {
    //This function just reads so we'll be using the shared lock
    mtx.lock_shared();
    
    if (start == NULL) {
      mtx.unlock_shared(); //Unlock before returning
      return -1;
    }
    
    Llist_node *current = start;
    while (current->next != NULL)
      current = current->next;
    
    mtx.unlock_shared(); //Unlock before returning
    return current->data;
  }
  
  void push(int p) {
    //Writing, so exclusive lock;
    mtx.lock();
    if (start == NULL) {
      start = new Llist_node(p);
      mtx.unlock(); //Unlock before returning
      return;
    }
    
    Llist_node *current = start;
    while (current->next != NULL)
      current = current->next;
    
    current->next = new Llist_node(p);
    mtx.unlock(); //Unlock before returning
  }

  private:
    Llist_node *start;
    shared_mutex mtx;
};