// $Id: listmap.tcc,v 1.15 2019-10-30 12:44:53-07 - - $

#include "listmap.h"
#include "debug.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::~listmap() {
   DEBUGF ('l', reinterpret_cast<const void*> (this));
   
   
   
   
}

//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);

   node* newnode = new node(nullptr, nullptr, pair);
   node* prev = anchor();
   node* current = prev->next;
   while (current != anchor() and current < newnode) {
       current = current->next;
       prev = prev->next;
   }
   
   newnode->next = current;
   newnode->prev = current->prev;
   
   current->prev = newnode;
   prev->next = newnode;
   
   return newnode;
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   DEBUGF ('l', that);
   
   node* current = anchor();
   current = current->next;
   while (current != anchor() and current->value.first != that)
       current = current->next;
   
   return current;
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   
   node* prev = anchor();
   node* current = prev->next;
   
   while (current != position.where) {
       current = current->next;
       prev = prev->next;
   }
   
   node* oldnode = current;
   current = current->next;
   current->prev = prev;
   prev->next = current;
   
   delete oldnode;
   
   return current;
}
