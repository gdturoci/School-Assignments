import os
import argparse

# Top of C++ file with includes and namespaces
top_source_string = """
#include <iostream>
#include <assert.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

"""

# The reference function creates a loop that simply adds together all floating point constants in a loop
def reference_loop_source(chain_length):

    # function header
    function = "void reference_loop(float *b, int size) {"

    # loop header
    loop = "  for (int i = 0; i < size; i++) {"

    # read the original value from memory
    init = "    float tmp = b[i];"

    # create the dependency chain
    chain = []
    for i in range(0,chain_length):
        chain.append("    tmp += "+ str(i+1)+".0f;")

    # store the final value to memory
    close = "    b[i] = tmp;"

    # close the loop
    loop_close = "  }"

    # close the function
    function_close = "}"

    # join together all the parts to make a complete function
    return "\n".join([function, loop, init, "\n".join(chain), close, loop_close, function_close])

# First hoomework function here! Implement the reference loop unrolled
# *sequentially*, That is, create dependency chains of length
# *chain_length*. Unroll the loop by a factor of *unroll_factor*. Do
# the unrolled loop iterations sequentially: i.e. do not start the
# chain of one iteration before the previous one is finished.

# to view the reference loop for a dependency chain of N, just
# run: python3 skeleton.py N 1.
# Your code will initially fail the assertion check, but you
# should be able to view the reference loop in homework.cpp.

# The reference for this loop is slide number 75 and 76 of the
# April 8 lecture. Those slides show the example of going from
# unroll factor of 1 to 2. You need to generalize this.

# You can assume that the unroll factor evenly divides the
# array length. That is, you should be able to do this all
# in one loop without any extra clean-up loops.

# Don't forget! Floating point constants must have 'f' after them!
# that is, you would write 2 in floating point as '2.0f'
#
# You can gain confidence that implemented this correctly by executing
# skeleton.py with several power-of-two options for the unroll factor
# for example, try 1,2,4,8, etc.
def homework_loop_sequential_source(chain_length, unroll_factor):
    function = "void homework_loop_sequential(float *b, int size) {"
    
    #start a loop that goes through the array, incrementing by the unroll factor
    function_body = "   for (int x=0; x<size; x+="+str(unroll_factor)+") {\n"
    
    #for each array element that the main loop is skipping over, create a temp variable to operate on
    for y in range(unroll_factor):
        function_body +="       float tmp"+str(y)+" = b[x+"+str(y)+"];\n"
        
        #For each temp variable, perform the dependency chain
        for x in range(chain_length):
            function_body +="       tmp"+str(y)+" += "+str(x+1)+".0f;\n"
        
        #Store the results of the dependency chain in the appropriate place in the array
        function_body +="       b[x+"+str(y)+"] = tmp"+str(y)+";\n"
    function_body +="   }"
    function_close = "}"
    return "\n".join([function, function_body, function_close])

# Second homework function here! The specification for this
# function is the same as the first homework function, except
# this time you will interleave the instructions of the unrolled
# dependency chains.

# The reference slides for this loop are slide 77 - 80 on the April 8
# lecture. That example shows a dependency chain of length N with an
# unroll factor of 2. You need to generalize the unroll factor and
# place dependent instructions as far apart as possible.

# You can assume the unroll factor is a power of 2 and that the
# the dependency chain also a power of two. You can assume the unroll
# factor will always be less than or equal to the unroll factor.
def homework_loop_interleaved_source(chain_length, unroll_factor):
    function = "void homework_loop_interleaved(float *b, int size) {"
    
    #start a loop that goes through the array, incrementing by the unroll factor
    function_body = "   for (int x=0; x<size; x+="+str(unroll_factor)+") {\n"
    
    #For each array element that the main loop skips over, perform each step of the dependency 
    #   chain independent of the other elements; since operations are performed directly on each array
    #   element, temp variables are not needed
    for x in range(chain_length):
        for y in range(unroll_factor):
            function_body +="       b[x+"+str(y)+"] += "+str(x+1)+".0f;\n"
    function_body +="   }"
    function_close = "}"
    return "\n".join([function, function_body, function_close])

# String for the main function, including timings and
# reference checks.
main_source_string = """
#define SIZE 1024 * 1024 * 8

int main() {
  float *a;
  a = (float *) malloc(SIZE * sizeof(float));

  float *b;
  b = (float *) malloc(SIZE * sizeof(float));

  float *c;
  c = (float *) malloc(SIZE * sizeof(float));

  for (int i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = i;
    c[i] = i;
  }

  auto sequential_start = high_resolution_clock::now();
  homework_loop_sequential(a,SIZE);
  auto sequential_end = high_resolution_clock::now();
  auto sequential_duration = duration_cast<nanoseconds>(sequential_end - sequential_start);
  double sequential_seconds = sequential_duration.count()/1000000000.0;

  auto interleaved_start = high_resolution_clock::now();
  homework_loop_interleaved(c,SIZE);
  auto interleaved_end = high_resolution_clock::now();
  auto interleaved_duration = duration_cast<nanoseconds>(interleaved_end - interleaved_start);
  double interleaved_seconds = interleaved_duration.count()/1000000000.0;


  auto ref_start = high_resolution_clock::now();
  reference_loop(b,SIZE);
  auto ref_stop = high_resolution_clock::now();
  auto ref_duration = duration_cast<nanoseconds>(ref_stop - ref_start);
  double ref_seconds = ref_duration.count()/1000000000.0;

  cout << "sequential loop time: " << sequential_seconds << endl; 
  cout << "interleaved loop time: " << interleaved_seconds << endl; 
  cout << "reference loop time: " << ref_seconds << endl;
  cout << "----" << endl;
  cout << "speedups:" << endl;
  cout << "sequential speedup over reference: " << ref_seconds / sequential_seconds << endl << endl;
  cout << "interleaved speedup over reference: " << ref_seconds / interleaved_seconds << endl << endl;

  return 0;
}
"""

# Create the program source code
def pp_program(chain_length, unroll_factor):

    # Your two functions are called here
    homework_source_string_sequential = homework_loop_sequential_source(chain_length, unroll_factor)
    homework_source_string_interleaved = homework_loop_interleaved_source(chain_length, unroll_factor)

    # join together all the other parts to make a complete C++ program
    return "\n".join([top_source_string, reference_loop_source(chain_length), homework_source_string_sequential, homework_source_string_interleaved, main_source_string])

# Write a string to a file (helper function)
def write_str_to_file(st, fname):
    f = open(fname, 'w')
    f.write(st)
    f.close()

# Compile the program. Don't change the options here for the official
# assignment submission. Feel free to change them for your own curiosity.
# Some notes:
#
# I am using a recent version of C++ to use the chrono library.
#
# I am disabling the compiler's loop unrolling so we can ensure the
# reference loop and the homework loops are not unrolled "behind our backs"
#
# I am using the lowest optimization level here (-O0) to disable most
# optimizations. The compiler does some really ticky things even at
# (-O1) here. 
def compile_program():
    cmd = "clang++ -std=c++14 -fno-unroll-loops -O0 -o homework homework.cpp"
    print("running: " + cmd)
    assert(os.system(cmd) == 0)

# Execute the program
def run_program():
    cmd = "./homework"
    print("running: " + cmd)
    print("")
    assert(os.system(cmd) == 0)

# The high-level function: generate the C code, compile it, and execute it.
def generate_and_run(chain_length, unroll_factor):
    print("")
    print("----------")
    print("generating and running for:")
    print("chain length = " + str(chain_length))
    print("unroll factor = " + str(unroll_factor))
    print("-----")
    print("")
    
    program_str = pp_program(chain_length, unroll_factor)
    write_str_to_file(program_str, "homework.cpp")
    compile_program()
    run_program()

# gets two command line args, chain length (CL) and unroll factor (UF)
def main():
    parser = argparse.ArgumentParser(description='Part 1 of Homework 1: exploiting ILP by unrolling independent loops.')
    parser.add_argument('chain_length', metavar='CL', type=int,
                   help='the length of dependent instructions per loop iteration to generate')
    parser.add_argument('unroll_factor', metavar='UF', type=int,
                   help='how many loop iterations to unroll')
    args = parser.parse_args()
    CL = args.chain_length
    UF = args.unroll_factor
    generate_and_run(CL, UF)

if __name__ == "__main__":
    main()
