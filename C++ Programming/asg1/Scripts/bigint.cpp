//Galen Turoci (gturoci) and Ocean Hurd (ohurd), Assignment 1

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <vector>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"


//Debug Stuff ---------------------------------------------------------

bigint::bigint (long that): ubig_value (that), is_negative (that < 0) {
    DEBUGF ('~', this << " -> " << ubig_value)
}

//Constructors --------------------------------------------------------

bigint::bigint (const ubigint& ubig_value_, bool is_negative_):
                ubig_value(ubig_value_), is_negative(is_negative_) {
}

bigint::bigint (const string& that) {
    is_negative = that.size() > 0 and that[0] == '_';
    ubig_value = ubigint (that.substr (is_negative ? 1 : 0));
}

//Signs ---------------------------------------------------------------

bigint bigint::operator+ () const {
    return *this;
}

bigint bigint::operator- () const {
    return {ubig_value, not is_negative};
}

//Actual Operations ---------------------------------------------------

bigint bigint::operator+ (const bigint& that) const {
    //Create result
    bigint result;

    //If the signs are the same
    if (is_negative == that.is_negative) {
        result = ubig_value + that.ubig_value;
        if (is_negative)
            result.is_negative = true;
    } else { //If signs are different... (bigger number first)
        if (ubig_value > that.ubig_value) {
            result = ubig_value - that.ubig_value;
            if (is_negative)
                result.is_negative = true;
        } else {
            result = that.ubig_value - ubig_value;
            if (that.is_negative)
                result.is_negative = true;
        }
    }
    return result;
}

bigint bigint::operator- (const bigint& that) const {
    //Create result
    bigint result;

    //If signs are same... (bigger number first)
    if (is_negative == that.is_negative) {
        if (ubig_value > that.ubig_value) {
            result = ubig_value - that.ubig_value;
            if (is_negative)
                result.is_negative = true;
        } else {
            result = that.ubig_value - ubig_value;
            if (that.is_negative)
                result.is_negative = true;
        }
    } else {//If signs are different... 
        if (ubig_value > that.ubig_value)
            result = ubig_value + that.ubig_value;
        else
            result = that.ubig_value + ubig_value;
    }
    return result;
}

bigint bigint::operator* (const bigint& that) const {
    //Create result
    bigint result;
    
    //If signs are same...
    if (is_negative == that.is_negative) {
        result = ubig_value * that.ubig_value;
        result.is_negative = false;
    } else { //Signs are different
        result = ubig_value * that.ubig_value;
        result.is_negative = true;
    }

    return result;
}

bigint bigint::operator/ (const bigint& that) const {
    //Create result
    bigint result;
    
    //If signs are same...
    if (is_negative == that.is_negative) {
        result = ubig_value/that.ubig_value;
        result.is_negative = false;
    } else { //Signs are different
        result = ubig_value/that.ubig_value;
        result.is_negative = true;
    }

    return result;
}

bigint bigint::operator% (const bigint& that) const {
    //Create result
    bigint result;
    
    //If signs are same...
    if (is_negative == that.is_negative) {
        result = ubig_value%that.ubig_value;
        result.is_negative = false;
    } else { //Signs are different
        result = ubig_value%that.ubig_value;
        result.is_negative = true;
    }
    
    return result;
}

bool bigint::operator== (const bigint& that) const {
    //Create bool to store equality
    bool equals = false;
    
    //Return false if a difference is found
    if (is_negative == that.is_negative)
        equals = ubig_value == that.ubig_value;

    return equals;
}

bool bigint::operator< (const bigint& that) const {
    //If one is negative, that one is the lesser
    if (is_negative != that.is_negative)
        return is_negative;
    
    return (ubig_value < that.ubig_value);
}

ostream& operator<< (ostream& out, const bigint& that) {
    return out << (that.is_negative ? "-" : "")
               << that.ubig_value;
}
