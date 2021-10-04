//Galen Turoci (gturoci) and Ocean Hurd (ohurd), Assignment 2

#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

#include "debug.h"
#include "file_sys.h"

int inode::next_inode_nr {1};

struct file_type_hash {
    size_t operator() (file_type type) const {
        return static_cast<size_t> (type);
    }
};

ostream& operator<< (ostream& out, file_type type) {
    static unordered_map<file_type,string,file_type_hash> hash {
        {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
        {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
    };
    return out << hash[type];
}

//inode_state ---------------------------------------------------------

inode_state::inode_state() {
    
    //Step 1: Make that fucking root node
    root = make_shared<inode>(file_type::DIRECTORY_TYPE);
    
    //Set the cwd to the root
    cwd = root;
    
    //Step 2: Add "." and ".." to the root
    root->contents->insert_dirents(".", root);
    root->contents->insert_dirents("..", root);
    
    DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
}

inode_state::~inode_state() {
    //Free memory from the specified inode?
}

const string& inode_state::prompt() const { return prompt_; }

void inode_state::changeprompt(string newprompt) {prompt_ = newprompt;}

int inode_state::get_thisnum() {
    return cwd->inode_nr;
}

int inode_state::get_thissize() {
    return cwd->contents->get_thissize();
}

string inode_state::get_inodename(int x) {
    return cwd->contents->get_inodename(x);
}

int inode_state::get_inodenum(string s) {
    return cwd->contents->get_inodenum(s);
}

int inode_state::get_inodesize(string s) {
    return cwd->contents->get_inodesize(s);
}

void inode_state::set_dirents(const string& s) {
    inode_ptr newdir = make_shared<inode>(file_type::DIRECTORY_TYPE);
    cwd->contents->insert_dirents(s, newdir);
    if (newdir->contents->get_thissize() == 0) {
        newdir->contents->insert_dirents(".", newdir);
        newdir->contents->insert_dirents("..", cwd);
    }
        
}

void inode_state::get_parent() {
    cwd = cwd->contents->get_parent();
}

void inode_state::changedir(string s) {
    cwd = cwd->contents->changedir(s);
}

void inode_state::makefile(string s) {
    inode_ptr newfile = make_shared<inode>(file_type::PLAIN_TYPE);
    cwd->contents->insert_dirents(s, newfile);
}

void inode_state::writefile(string filename, const wordvec& words) {
    inode_ptr p = cwd->contents->changedir(filename);
    p->contents->writefile(words);
}

const wordvec& inode_state::readfile(string filename) {
    inode_ptr p = cwd->contents->changedir(filename);
    return p->contents->readfile();
}

int inode_state::get_inodetype(string inodename) {
    inode_ptr p = cwd->contents->changedir(inodename);
    return p->inode_type;
}


ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

//inode ---------------------------------------------------------------

inode::inode(file_type type): inode_nr (next_inode_nr++) {
    switch (type) {
        case file_type::PLAIN_TYPE:
            inode_type = 1;
            contents = make_shared<plain_file>();
            break;
        case file_type::DIRECTORY_TYPE:
            inode_type = 0;
            contents = make_shared<directory>();
            break;
    }
    DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

int inode::get_inode_nr() const {
    DEBUGF ('i', "inode = " << inode_nr);
    return inode_nr;
}

int inode::get_dirsize() {
    return contents->get_thissize();
}

//file_error ----------------------------------------------------------

file_error::file_error (const string& what):
            runtime_error (what) {
}

//base_file -----------------------------------------------------------

const wordvec& base_file::readfile() const {
    throw file_error ("is a " + error_file_type());
}

void base_file::writefile (const wordvec&) {
    throw file_error ("is a " + error_file_type());
}

void base_file::remove (const string&) {
    throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::mkdir (const string&) {
    throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::mkfile (const string&) {
    throw file_error ("is a " + error_file_type());
}

void base_file::insert_dirents (const string&, inode_ptr) {
    throw file_error ("is a " + error_file_type());
}

int base_file::get_thissize() {
    throw file_error ("is a " + error_file_type());
}

string base_file::get_inodename(int) {
    throw file_error ("is a " + error_file_type());
}

int base_file::get_inodenum(string) {
    throw file_error ("is a " + error_file_type());
}

int base_file::get_inodesize(string) {
    throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::get_parent() {
    throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::changedir(string) {
    throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::get_inode(const wordvec&) {
    throw file_error ("is a " + error_file_type());
}


//plain_file ----------------------------------------------------------

size_t plain_file::size() const {
    size_t size {0};
    DEBUGF ('i', "size = " << size);
    return size;
}

const wordvec& plain_file::readfile() const {
    DEBUGF ('i', data);
    return data;
}

void plain_file::writefile (const wordvec& words) {
    DEBUGF ('i', words);
    int x = words.size();
    for (int y = x-1; y != -1; --y)
        data.push_back(words[y]);
}

int plain_file::get_thissize() {
    return data.size();
}


//directory -----------------------------------------------------------

size_t directory::size() const {
    size_t size {0};
    DEBUGF ('i', "size = " << size);
    return size;
}

void directory::remove (const string& filename) {
    DEBUGF ('i', filename);
}

inode_ptr directory::mkdir (const string& dirname) {
    DEBUGF ('i', dirname);
    return nullptr;
}

inode_ptr directory::mkfile (const string& filename) {
    DEBUGF ('i', filename);
    return nullptr;
}

void directory::insert_dirents(const string &s, inode_ptr p) {
    dirents[s] = p;
}

int directory::get_thissize() {
    return dirents.size();
}

string directory::get_inodename(int x) {
    auto y = dirents.begin();
    while (x != 0) {
        ++y;
        --x;
    }
    return y->first;
}

int directory::get_inodenum(string s) {
    inode_ptr p = dirents[s];
    return p->get_inode_nr();
}

int directory::get_inodesize(string s) {
    inode_ptr p = dirents[s];
    return p->get_dirsize();
}

inode_ptr directory::get_parent() {
    return dirents[".."];
}

inode_ptr directory::changedir(string s) {
    return dirents[s];
}

inode_ptr directory::get_inode(const wordvec& directions) {
    int vecsize = directions.size();
    inode_ptr p;
    for (int x = 0; x < vecsize; ++x)
        p = changedir(directions[x]);
    return p;
}
