// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
    regex comment_regex {R"(^\s*(#.*)?$)"};
    regex key_value_regex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
    regex trimmed_regex {R"(^\s*([^=]+?)\s*$)"};
    
    str_str_map map;
    str_str_pair pair;
    str_str_map::iterator itor;
    
    for (;;) {
        string line;
        getline (cin, line);
        if (cin.eof()) break;
        smatch result;
        if (regex_search (line, result, comment_regex))
            continue;
        
        if (regex_search (line, result, key_value_regex)) {
            if (result[1] == "" and result[2] == "") {
                //for (itor = map.begin(); itor != map.end(); ++itor)
                    //cout << map.find(itor->where) << endl;
                cout << "fuck if I know" << endl;
            
            } else if (result[1] == "") {
                cout << "Not sure what to do here yet" << endl;
                
            } else if (result[2] == "") {
                itor = map.find(result[1]);
                if (itor == map.end())
                    cout << "Error: key not found" << endl;
                else
                    map.erase(itor);
                
            } else {
                string key = result[1];
                string value = result[2];
                xpair<const string, string> mypair (key, value);
                itor = map.insert(mypair);
            }
        } else if (regex_search (line, result, trimmed_regex)) {
            itor = map.find(result[1]);
            if (itor == map.end())
                cout << result[1] << ": key not found" << endl;
            else
                cout << *itor << endl;
        }
   }
}

int main (int argc, char** argv) {
    sys_info::execname (argv[0]);
    scan_options (argc, argv);

    str_str_map test;
    for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
        str_str_pair pair (*argp, to_string<int> (argp - argv));
        cout << "Before insert: " << pair << endl;
        test.insert (pair);
    }

    for (str_str_map::iterator itor = test.begin();
    itor != test.end(); ++itor)
        cout << "During iteration: " << *itor << endl;

    str_str_map::iterator itor = test.begin();
    test.erase (itor);

    cout << "EXIT_SUCCESS" << endl;
    return EXIT_SUCCESS;
}
