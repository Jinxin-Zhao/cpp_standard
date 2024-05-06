#ifndef __CSTANDARD__H__
#define __CSTANDARD__H__


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>




// old style
struct S_implicit {
    int data_;
    int & foo() & {return data_;}
    const int & foo() const& {return data_;}
};

// new style
struct S_explicit {
    int data_{0};

    void setValue(int d) {
        data_ = d;
    }

//   template <typename Self>
//   auto&& foo(this Self& self) {
//       return std::forward<Self>(self).data_;
//   }
};


#endif