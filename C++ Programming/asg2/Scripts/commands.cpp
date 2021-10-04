//Galen Turoci (gturoci) and Ocean Hurd (ohurd), Assignment 2

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"#"     , fn_com   },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such function");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
    int status = exec::status();
    cout << exec::execname() << ": exit(" << status << ")" << endl;
    return status;
}

//Print the contents of a given directory according to the
//specifications given for ls
void printcontents(inode_state& state) {
    
    //Get the size of the directory
    int dirsize = state.get_thissize();
    
    for (int x = 0; x < dirsize; ++x) {
        //A string that stores the name of the file/directory we are
        //currently on - directories end in /;
        string inodename = state.get_inodename(x);
        //An int that finds the inode number of the file/directory we
        //are currently on
        int inodenum = state.get_inodenum(inodename);
        //An int for the size of the file we are currently on
        int inodesize = state.get_inodesize(inodename);
        
        
        cout << "  " << inodenum;
        cout << "  " << inodesize;
        cout << "  " << inodename;
        //check this inode's type
        int inodetype = state.get_inodetype(inodename);
        if (inodetype == 1 or inodename == "." or inodename == "..")
            cout << endl;
        else
            cout << "/" << endl;
    }
}

void fn_cat (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    if (words.size() == 1)
        throw command_error (words[0] + ": Please specify a file");
    
    //Initialize a new wordvec using what the user typed
    wordvec dir_names = split(words[1], "/");
    
    //Initalize the wordvec we will be printing
    wordvec contents;
    
    //If that vec is > 1, that means a directory other than the cwd was
    //specified and must then be pointed at
    int newvecsize = dir_names.size();
    if (newvecsize > 1) {
    } else { //no directory was specified so we are working in the cwd
        //Error checking
        //Get the size of this directory
        int dirsize = state.get_thissize();
        //Go through the directory and make sure the file is there
        //and is a file
        for (int x = 2; x < dirsize; ++x) {
            string inodename = state.get_inodename(x);
            int inodetype = state.get_inodetype(inodename);
            if (words[1] == inodename and inodetype == 0) {
                throw command_error(words[0] + ": " + words[1] +
                ": Specified file is a directory");
            } else if (words[1] == inodename and inodetype == 1)
                break;
            
            if (x == dirsize-1) {
                throw command_error(words[0] + ": " + words[1] +
                ": No such file or directory");
            }
        }
        
        //Obtain the contents
        contents = state.readfile(words[1]);
        
        //Place the contents into a string with spaces
        int consize = contents.size();
        string newwords = "";
        for (int x = 0; x < consize; ++x) {
            newwords += contents[x];
            newwords += " ";
        }
        
        //Print the string
        cout << newwords << endl;
    }
    /*
    progress through words[1] until we reach the specified directory
    if specified directory DNE
        throw command_error ("Specified directory does not exist");
    else if specified file is a directory
        throw command_error ("Specified file is a directory");
    
    access dirents map and retrieve file specified
    retrieve the file's contents and print them
    */
}

void fn_cd (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    if (words.size() == 1) {
        int inodenum = state.get_thisnum();
        while (inodenum != 1) {
            state.get_parent();
            inodenum = state.get_thisnum();
        }
    } else {
        //Split words[1] into a string of vectors that should be
        //directories
        wordvec dir_names = split(words[1], "/");
        
        //Count how many directories we're changing into
        int count = 0;
        int newvecsize = dir_names.size();
        
        while (count < newvecsize) {
            
            //Error checking for each directory
            int dirsize = state.get_thissize();
            for (int x = 2; x < dirsize; ++x) {
                string known_dir = state.get_inodename(x);
                if (known_dir == dir_names[count])
                    break;
                if (x == dirsize-1) {
                    throw command_error (words[0] + ": cannot find " +
                    words[1]);
                }
            }
            
            //advance to the next directory
            state.changedir(dir_names[count]);
            ++count;
        }
    }
}

//For comments do literally nothing
void fn_com (inode_state& state, const wordvec& words) {
    DEBUGF ('c', state);    DEBUGF ('c', words);
}

void fn_echo (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
   
    cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}

void fn_exit (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    throw ysh_exit();
}

void fn_ls (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    
    if (words.size() == 1) {
        //Print the cwd - pwd is essentially copied here, with a slight
        //change at the end
        
        //Get the num of the ogdir
        int ogdirnum = state.get_thisnum();
    
        //Initialize a new wordvector
        wordvec dirnames;
    
        //Add the root directory to the vector
        dirnames.push_back("/");
    
        //Initailize string to store name of "current" (last) directory
        string lastdir = "";
    
        int inodenum = state.get_thisnum();
    
        //While not in the root directory
        while (inodenum != 1) {
            //Go up one directory
            state.get_parent();
        
            //Get the name of the last directory from its number
            int newnum = state.get_thisnum();
            int y = 1;
            while (newnum != inodenum) {
                lastdir = state.get_inodename(y);
                newnum = state.get_inodenum(lastdir);
                ++y;
            }
        
            //Push the name of the "current" (last) directory into the
            //vector
            dirnames.push_back(lastdir);
            dirnames.push_back("/");
        
            //Get the num of the current directory
            inodenum = state.get_thisnum();
        }
    
        //Print the vector
        int dirnamessize = dirnames.size();
        if (dirnamessize > 1) {
            for (int x = dirnamessize-1; x != 0; --x)
                cout << dirnames[x];
        } else
            cout << dirnames.back();
    
        //Add in the colon and newline at the end
        cout << ":" << endl;
        
        //Get back to the original directory
        dirnames.pop_back();
        while (inodenum != ogdirnum) {
            state.changedir(dirnames.back());
            dirnames.pop_back();
            dirnames.pop_back();
            inodenum = state.get_thisnum();
        }
        
        //Print the contents of this directory
        printcontents(state);
    } else {
        //Print words[1]
        cout << words[1];
        //Add in the colon and newline at the end
        cout << ":" << endl;
        
        //Print the contents of the desired directory
        printcontents(state);
    }
}

void fn_lsr (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    /*
    if words [1] DNE
        throw command_error (words[1] + ": no such file or directory");
    
    if (words.size() == 1)
        pwd
        cout << ":" << endl;
        
        for every file/directory
            cout << "  " << inode number;
            cout << "  " << file size;
            cout << "  " << file/directory name - directories end in /;
            cout << endl;
        
        now check for any directories and go through each
        when you reach the end of a given branch of directories, go
            back and do it for each and every one
    
    else (A directory is specified)
        get to the specified directory and then "pwd"
        cout << ":" << endl;
        
        for every file/directory
            cout << "  " << inode number;
            cout << "  " << file size;
            cout << "  " << file/directory name - directories end in /;
            cout << endl;
            
        now check for any directories and go through each
        when you reach the end of a given branch of directories, go
            back and do it for each and every one
    */
}

void fn_make (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    if (words.size() == 1)
        throw command_error ("make: please specify a file name");
    
    
    
    //Initialize a new wordvec using what the user typed
    wordvec dir_names = split(words[1], "/");
    
    //If that vec is > 1, that means a directory other than the cwd was
    //specified and must then be pointed at to be written in
    int newvecsize = dir_names.size();
    if (newvecsize > 1) {
        
    } else { //no directory was specified so we are working in the cwd
        //Get the size of the cwd
        int dirsize = state.get_thissize();
        //Compare the names of all the directories in the cwd to
            //words[1]
        for (int x = 0; x < dirsize; ++x) {
            string inodename = state.get_inodename(x);
            int inodetype = state.get_inodetype(inodename);
            //If it is the name of a directory, throw an error
            if (inodename == words[1] and inodetype == 0) {
                throw command_error ("make: cannot create a file "
                "with the same name as a directory");
            } else if (inodename == words[1]) {
                //it is the name of a file, in which case delete the
                //old file and break to write in the new one
                break;
            }
        }
        
        //Make the file
        state.makefile(words[1]);
        
        //If there is more to write, write it into the file
        int wordssize = words.size();
        if (wordssize > 2) {
            wordvec newwords;
            for (int x = wordssize-1; x > 1; --x)
                newwords.push_back(words[x]);
            state.writefile(words[1], newwords);
        }
    }
    /*
    if (words[1] == a file)
        that file's contents = the rest of the wordvec
    else
        create a new file with name words[1] inside this directory
        that file's contents = the rest of the wordvec
    */
}

void fn_mkdir (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    if (words.size() == 1)
        throw command_error ("mkdir: missing operand");
    
   
    //Initialize a new wordvec using what the user typed
    wordvec dir_names = split(words[1], "/");
    
    //Initialize dirsize
    int dirsize = 0;
    
    //Count how many directories we're changing into
    int count = 0;
    int newvecsize = dir_names.size();
    
    //Get the num of the og directory
    int ogdirnum = state.get_thisnum();
    
    //Move to the last specified already made directory
    while (count < newvecsize-1) {
        
        //Error checking for each directory
        dirsize = state.get_thissize();
        for (int x = 2; x < dirsize; ++x) {
            string known_dir = state.get_inodename(x);
            if (known_dir == dir_names[count])
                break;
            if (x == dirsize-1) {
                throw command_error (words[0] + ": cannot find " +
                words[1]);
            }
        }
            
        //advance to the next directory
        state.changedir(dir_names[count]);
        ++count;
    }
    
    //Make loop based on this directory's size to test if desired
    //directory already exists
    dirsize = state.get_thissize();
    for (int x = 0; x < dirsize; ++x) {
        string known_dir = state.get_inodename(x);
        if (dir_names[count] == known_dir) {
            throw command_error (words[0] + " cannot create " +
            "directory '" + known_dir + "' : already exists");
        }
    }
    state.set_dirents(dir_names[count]);
    
    //BACK to the og directory
    int inodenum = state.get_thisnum();
    while (inodenum != ogdirnum) {
        state.get_parent();
        inodenum = state.get_thisnum();
    }
}

void fn_prompt (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);

    int wordsize = words.size();
    string newprompt = "";
    for (int x = 1; x != wordsize; ++x) {
        newprompt += words[x];
        newprompt += " ";
    }
    
    state.changeprompt(newprompt);
    
}

void fn_pwd (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    //Get the num of the ogdir
    int ogdirnum = state.get_thisnum();
    
    //Initialize a new wordvector
    wordvec dirnames;
    
    //Add the root directory to the vector
    dirnames.push_back("/");
    
    //Initailize string to store name of "current" (last) directory
    string lastdir = "";
    
    int inodenum = state.get_thisnum();
    
    //While not in the root directory
    while (inodenum != 1) {
        //Go up one directory
        state.get_parent();
        
        //Get the name of the last directory from its number
        int newnum = state.get_thisnum();
        int y = 1;
        while (newnum != inodenum) {
            lastdir = state.get_inodename(y);
            newnum = state.get_inodenum(lastdir);
            ++y;
        }
        
        //Push the name of the "current" (last) directory into the
        //vector
        dirnames.push_back(lastdir);
        dirnames.push_back("/");
        
        //Get the num of the current directory
        inodenum = state.get_thisnum();
    }
    
    //Print the vector
    int dirnamessize = dirnames.size();
    if (dirnamessize > 1) {
        for (int x = dirnamessize-1; x != 0; --x)
            cout << dirnames[x];
    } else
        cout << dirnames.back();
    
    //Add in the newline at the end
    cout << endl;
    
    //Get back to the original directory
    dirnames.pop_back();
    while (inodenum != ogdirnum) {
        state.changedir(dirnames.back());
        dirnames.pop_back();
        dirnames.pop_back();
        inodenum = state.get_thisnum();
    }
}

void fn_rm (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    /*
    if (words[1] != a file/directory)
        throw command_error (words[1] + ": cannot remove nonexistent
        file/directory");
    
    if (words[1] == a directory)
        if (words[1] != empty)
            throw command_error (words[1] + ": cannot remove a
            non-empty directory");
        
        delete the directory
    else
        delete the file
    */
}

void fn_rmr (inode_state& state, const wordvec& words){
    DEBUGF ('c', state);    DEBUGF ('c', words);
    
    /*
    //Not quite sure how this is supposed to work
    */
}
