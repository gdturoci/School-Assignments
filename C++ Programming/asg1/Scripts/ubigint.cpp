//Galen Turoci (gturoci) and Ocean Hurd (ohurd), Assignment 1

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <vector>
using namespace std;

#include "ubigint.h"
#include "debug.h"

//Constructors --------------------------------------------------------

ubigint::ubigint (unsigned long that): ubig_value (that) {
    DEBUGF ('~', this << " -> " << this);
}

ubigint::ubigint (const string& that): ubig_value(0) {
    DEBUGF ('~', "that = \"" << that << "\"");
    
    for (auto x = that.crbegin(); x != that.crend(); ++x) {
        //Grab the current char from the string
        char c = *x;
        //Make that char an int
        int ic = c - '0';
        //Put that int into the ubig_value vector
        ubig_value.push_back(ic);
    }
    
    //take off all the high order zeros from the vector
    while (ubig_value.size() > 0 and ubig_value.back() == 0)
        ubig_value.pop_back();
}

//Operations ----------------------------------------------------------

void ubigint::trim_leading_zeroes() {
    //take off all the high order zeros from the vector
    while (ubig_value.size() > 0 and ubig_value.back() == 0)
        ubig_value.pop_back();
}

ubigint ubigint::operator+ (const ubigint& that) const {
    //Create results
    ubigint result;
    int tempres = 0;
    int carry = 0;
    
    //Initialize the values we're grabbing from the vectors
    int iubv = 0;
    int tiubv = 0;
    
    //Get the sizes of the vectors
    int thissize = ubig_value.size();
    int thatsize = that.ubig_value.size();
    
    //Take care of the possibility that either of them are empty
    if (thissize == 0) {
        //Push all the values in the non-empty vector into the result
        for (auto x = that.ubig_value.begin();
        x != that.ubig_value.end(); ++x) {
            tiubv = *x;
            result.ubig_value.push_back(tiubv);
        }
    } else if (thatsize == 0)
        return *this;
    //Bigger one first
    else if (thissize > thatsize) {
        //Proceed through both vectors from front to ass,
        //adding digits pairwise
        for (auto x = ubig_value.begin(),
        y = that.ubig_value.begin();
        x != ubig_value.end(); ++x) {
            //Get the values
            iubv = *x;
            //Only grab the value from that if we're not at the end of
            //the vector
            if (y != that.ubig_value.end())
                tiubv = *y;
            else //just supplement with 0s
                tiubv = 0;
            
            //Add the values to the tempres and reset the carry
            tempres = iubv + tiubv + carry;
            carry = 0;
            
            //If the result of the addition is < 10,
            //throw it on the result as normal and reset tempres
            if (tempres < 10) {
                result.ubig_value.push_back(tempres);
                tempres = 0;
            } else { //if the sum is >= 10
                //Add 1 to the carry
                carry = 1;
                //Subtract tempres by 10
                tempres -= 10;
                //Put the new tempres in the result vector
                result.ubig_value.push_back(tempres);
                //Reset tempres
                tempres = 0;
            }
            //Only iterate y if we haven't reached the end of the
            //Smaller vector
            if (y != that.ubig_value.end())
                ++y;
        }
    } else {
        //Proceed through both vectors from front to ass,
        //adding digits pairwise
        for (auto x = that.ubig_value.begin(),
        y = ubig_value.begin();
        x != that.ubig_value.end(); ++x) {
            //Get the values
            //Only grab the value from this if we're not at the end of
            //the vector
            if (y != ubig_value.end())
                iubv = *y;
            else //Just supplement with 0s
                iubv = 0;
            tiubv = *x;
            
            //Add the values to the tempres and reset the carry
            tempres = iubv + tiubv + carry;
            carry = 0;
            
            //If the result of the addition is < 10,
            //throw it on the result as normal and reset tempres
            if (tempres < 10) {
                result.ubig_value.push_back(tempres);
                tempres = 0;
            } else { //if the sum is >= 10
                //Add 1 to the carry
                carry = 1;
                //Subtract tempres by 10
                tempres -= 10;
                //Put the new tempres in the result vector
                result.ubig_value.push_back(tempres);
                //Reset tempres
                tempres = 0;
            }
            //Only iterate y if we haven't reached the end of the
            //smaller vector
            if (y != ubig_value.end())
                ++y;
        }
    }
    
    
    //push the final carry
    result.ubig_value.push_back(carry);
    
    //Take off leading 0s
    result.trim_leading_zeroes();
    
    return result;
    
}

ubigint ubigint::operator- (const ubigint& that) const {
    if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
    
    //Initialize results
    ubigint result;
    int tempres = 0;
    int carry = 0;
    
    //Initialize the values we'll be grabbing
    int iubv = 0;
    int tiubv = 0;
    
    //Get the sizes of the vectors
    int thissize = ubig_value.size();
    int thatsize = that.ubig_value.size();

    //Bigger one first
    if (thissize > thatsize or thissize == thatsize) {
        //Proceed through both vectors from front to ass,
        //subtracting digits pairwise
        for (auto x = ubig_value.begin(),
        y = that.ubig_value.begin();
        x != ubig_value.end(); ++x) {
            //get the values
            iubv = *x;
            //Only grab the value from this if we're not at the end of
            //the vector
            if (y != that.ubig_value.end())
                tiubv = *y;
            else
                tiubv = 0;
            
            //Subtract the values and reset the carry
            tempres = iubv - tiubv + carry;
            carry = 0;
            
            //If the result of the subtraction is > 0,
            //throw it on the result vector as normal
            if (tempres >= 0) {
                result.ubig_value.push_back(tempres);
                tempres = 0;
            } else { //add 10 to the tempres
                     //and add -1 next time around
                carry = -1;
                tempres += 10;
                result.ubig_value.push_back(tempres);
                tempres = 0;
            }
            //Only iterate y if we haven't reached the end of the
            //smaller vector
            if (y != that.ubig_value.end())
                ++y;
        }
    } else {
        //Proceed through both vectors ass to front,
        //subtracting digits pairwise
        for (auto x = that.ubig_value.begin(),
        y = ubig_value.begin();
        x != that.ubig_value.end(); ++x, ++y) {
            //Get the values
            //Only grab the value from this if we're not at the end of
            //the vector
            if (y != ubig_value.end())
                iubv = *y;
            else
                iubv = 0;
            tiubv = *x;
            
            //Subtract the values and reset the carry
            tempres = tiubv - iubv + carry;
            carry = 0;

            //If the result of the subtraction is > 0,
            //throw it on the result as normal
            if (tempres > 0) {
                result.ubig_value.push_back(tempres);
                tempres = 0;
            } else { //add 10 to the remainder
                     //and add -1 next time around
                carry = -1;
                tempres += 10;
                result.ubig_value.push_back(tempres);
                tempres = 0;
            }
            //Only iterate y if we haven't reached the end of the
            //smaller vector
            if (y != ubig_value.end())
                ++y;
        }
    }
    
    //Take off leading 0s
    result.trim_leading_zeroes();

    return result;
}

ubigint ubigint::operator* (const ubigint& that) const {
    //Get the sizes of the vectors
    int thissize = ubig_value.size();
    int thatsize = that.ubig_value.size();
    
    //Initialize the result vector with a size equal to
    //the sum of the other vectors' sizes
    ubigint result(thissize + thatsize);
    
    //initialize carry
    int carry = 0;
    //initialize temporary result
    int tempres = 0;
    
    //An unsigned to keep track of our place in the result vector
    unsigned i = 0;
    //Start the outer loop; the "bottom" number
    for (auto x = that.ubig_value.begin();
    x != that.ubig_value.end(); ++x, ++i) {
        //An unsigned to keep track of our place in the result vector
        unsigned j = 0;
        //Start the inner loop; the "Top" number
        for (auto y = ubig_value.begin();
        y != ubig_value.end(); ++y, ++j) {
            //Get the values
            int iubv = *y;
            int tiubv = *x;
            
            //Multiply the values
            tempres = result.ubig_value[j+i] + (iubv * tiubv);
            //Place the tempres%10 into the result
            result.ubig_value[j+i] = tempres%10;
            //the carry is the tempres/10
            carry = tempres/10;
            
            //If the carry is not 0, place it into the next spot in the
            //result vector and reset it
            if (carry != 0) {
                result.ubig_value[j+i+1] += carry;
                carry = 0;
            }
        }
    }
    
    //Take off the leading 0s
    result.trim_leading_zeroes();
    
    return result;
}

void ubigint::multiply_by_2() {
    //Initialize the carry
    int carry = 0;
    
    //Run down the vector from front to ass, doubling each value
    for (auto x = ubig_value.begin();
    x != ubig_value.end(); ++x) {
        int iubv = *x;
        *x = (carry + (iubv * 2))%10;
        carry = (iubv*2)/10;
    }
    //If the carry is not a 0 push back 1
    if (carry != 0)
        ubig_value.push_back(1);
}

void ubigint::divide_by_2() {
    //Run down the vector from front to ass, halving each value
    for (auto x = ubig_value.begin();
    x != ubig_value.end(); ++x) {
        //Grab the value
        auto iubv = *x;
        
        //Return current val divided by 2
        *x = iubv/2;
        
        //If next char is odd and not the end, add 5
        if ((next(x) != ubig_value.end()) and (*(next(x))%2 == 1))
            *x = (iubv/2) + 5;
    }
}

struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
    // NOTE: udivide is a non-member function.
    ubigint divisor {divisor_};
    ubigint zero {0};
    if (divisor == zero) throw domain_error ("udivide by zero");
    ubigint power_of_2 {1};
    ubigint quotient {0};
    ubigint remainder {dividend}; // left operand, dividend
    while (divisor < remainder) {
        divisor.multiply_by_2();
        power_of_2.multiply_by_2();
    }
    while (power_of_2 > zero) {
        if (divisor <= remainder) {
            remainder = remainder - divisor;
            quotient = quotient + power_of_2;
        }
        divisor.divide_by_2();
        power_of_2.divide_by_2();
    }
    return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
    return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
    return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
    //Create bool to store equality
    bool equals = false;
    
    //Get the sizes of each vector
    int thissize = ubig_value.size();
    int thatsize = that.ubig_value.size();
    
    //If neither exists then they're equal
    if (thissize == 0 and thatsize == 0)
        equals = true;
    //If they're same size then compare each individual value
    else if (thissize == thatsize) {
        //Run down both vectors and return false if a diff is found
        for (auto x = ubig_value.crbegin(),
        y = that.ubig_value.crbegin();
        x != ubig_value.crend(); ++x, ++y) {
            equals = *x == *y;
            //If they're ever not equal then return
            if (!equals)
                return equals;
        }
    }
    return equals;
}

bool ubigint::operator< (const ubigint& that) const {
    
    //get the sizes of the vectors
    int thissize = ubig_value.size();
    int thatsize = that.ubig_value.size();
    
    //Compare sizes
    //Shorter one is smaller
    if (thissize < thatsize)
        return true;
    else if (thissize > thatsize)
        return false;
    else { //Sizes are the same
        //Compare each individual value
        for (auto x = ubig_value.crbegin(),
        y = that.ubig_value.crbegin();
        x != ubig_value.crend(); ++x, ++y) {
            //If this value is less than that value, return true
            if (*x < *y)
                return true;
        }
    }
    //If none of this's values are less than that's values, then
    //they are equal, and not less than
    return false;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
    
    //If that is empty, return just a +
    if (that.ubig_value.size() == 0)
        out << '+';
    
    //Initialize a count to keep track of how many chars we are printin
    int count = 0;
    
    //Run down the vector
    for (auto x = that.ubig_value.crbegin();
    x != that.ubig_value.crend(); x++, count++) {
        //Grab the char
        char c = *x;
        //Convert it from ASCII
        char ic = c + '0';
        //If we're at the 69th character, print a slash and return
        if (count != 0 and count%69 == 0)
            out << "\\" << "\n" << ic;
        else //put the de-ASCII'd char into the ostream
            out << ic;
    }
    
    return out;
}
