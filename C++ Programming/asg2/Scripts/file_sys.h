//Galen Turoci (gturoci) and Ocean Hurd (ohurd), Assignment 2

#ifndef __INODE_H__
#define __INODE_H__

#include <exception>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
using namespace std;

#include "util.h"

// inode_t -
//    An inode is either a directory or a plain file.

enum class file_type {PLAIN_TYPE, DIRECTORY_TYPE};
class inode;
class base_file;
class plain_file;
class directory;
using inode_ptr = shared_ptr<inode>;
using base_file_ptr = shared_ptr<base_file>;
ostream& operator<< (ostream&, file_type);

// inode_state -
//    A small convenient class to maintain the state of the simulated
//    process:  the root (/), the current directory (.), and the
//    prompt.

class inode_state {
   friend class inode;
   friend ostream& operator<< (ostream& out, const inode_state&);
   private:
      inode_ptr root {nullptr};
      inode_ptr cwd {nullptr};
      string prompt_ {"% "};
   public:
      inode_state (const inode_state&) = delete; // copy ctor
      inode_state& operator= (const inode_state&) = delete; // op=
      inode_state();
      ~inode_state();
      const string& prompt() const;
      
      void changeprompt(string newprompt);
      int get_thisnum();
      int get_thissize();
      string get_inodename(int x);
      int get_inodenum(string s);
      int get_inodesize(string s);
      string get_parent(string s);
      void set_dirents(const string& s);
      void get_parent();
      void changedir(string s);
      void makefile(string s);
      void writefile(string filename, const wordvec& words);
      const wordvec& readfile(string filename);
      int get_inodetype(string inodename);
};

// class inode -
// inode ctor -
//    Create a new inode of the given type.
// get_inode_nr -
//    Retrieves the serial number of the inode.  Inode numbers are
//    allocated in sequence by small integer.
// size -
//    Returns the size of an inode.  For a directory, this is the
//    number of dirents.  For a text file, the number of characters
//    when printed (the sum of the lengths of each word, plus the
//    number of words.
//    

class inode {
   friend class inode_state;
   private:
      static int next_inode_nr;
      int inode_nr;
      int inode_type; //0 = directory, 1 = file
      base_file_ptr contents;
   public:
      inode (file_type);
      int get_inode_nr() const;
      int get_dirsize();
};

// class base_file -
// Just a base class at which an inode can point.  No data or
// functions.  Makes the synthesized members useable only from
// the derived classes.

class file_error: public runtime_error {
   public:
      explicit file_error (const string& what);
};

class base_file {
   protected:
      base_file() = default;
      virtual const string error_file_type() const = 0;
   public:
      virtual ~base_file() = default;
      base_file (const base_file&) = delete;
      base_file& operator= (const base_file&) = delete;
      virtual size_t size() const = 0;
      virtual const wordvec& readfile() const;
      virtual void writefile (const wordvec& newdata);
      virtual void remove (const string& filename);
      virtual inode_ptr mkdir (const string& dirname);
      virtual inode_ptr mkfile (const string& filename);
      
      virtual void insert_dirents(const string &, inode_ptr) = 0;
      virtual int get_thissize();
      virtual string get_inodename(int);
      virtual int get_inodenum(string);
      virtual int get_inodesize(string);
      virtual inode_ptr get_parent();
      virtual inode_ptr changedir(string);
      virtual inode_ptr get_inode(const wordvec&);
};

// class plain_file -
// Used to hold data.
// synthesized default ctor -
//    Default vector<string> is a an empty vector.
// readfile -
//    Returns a copy of the contents of the wordvec in the file.
// writefile -
//    Replaces the contents of a file with new contents.

class plain_file: public base_file {
   private:
      wordvec data;
      virtual const string error_file_type() const override {
         return "plain file";
      }
   public:
      virtual size_t size() const override;
      virtual const wordvec& readfile() const override;
      virtual void writefile (const wordvec& newdata) override;
      void insert_dirents(const string &s, inode_ptr p)
        { base_file::insert_dirents(s, p); }
      int get_thissize();
};

// class directory -
// Used to map filenames onto inode pointers.
// default ctor -
//    Creates a new map with keys "." and "..".
// remove -
//    Removes the file or subdirectory from the current inode.
//    Throws an file_error if this is not a directory, the file
//    does not exist, or the subdirectory is not empty.
//    Here empty means the only entries are dot (.) and dotdot (..).
// mkdir -
//    Creates a new directory under the current directory and 
//    immediately adds the directories dot (.) and dotdot (..) to it.
//    Note that the parent (..) of / is / itself.  It is an error
//    if the entry already exists.
// mkfile -
//    Create a new empty text file with the given name.  Error if
//    a dirent with that name exists.

class directory: public base_file {
   private:
      // Must be a map, not unordered_map, so printing is lexicographic
      map<string,inode_ptr> dirents;
      virtual const string error_file_type() const override {
         return "directory";
      }
   public:
      virtual size_t size() const override;
      virtual void remove (const string& filename) override;
      virtual inode_ptr mkdir (const string& dirname) override;
      virtual inode_ptr mkfile (const string& filename) override;
      
      void insert_dirents(const string &s, inode_ptr p);
      int get_thissize();
      string get_inodename(int x);
      int get_inodenum(string s);
      int get_inodesize(string s);
      inode_ptr get_parent();
      inode_ptr changedir(string s);
      inode_ptr get_inode(const wordvec& directions);
};

#endif
