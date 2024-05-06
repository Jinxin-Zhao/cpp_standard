#include <iostream>
#include "c++_23.h"
#include "c++_11.h"
#include "c++_17.h"
#include "c++_algo.h"
#include "bitmap.h"

#include "c++_container.h"

int main() {
    // test c++ containers
    test_unordered_map();
    return 0;
    //test_multimap();
    //foo();
    demo_constructed_binding();

    demo_fold_expr();

    optional<int> op = ConvertToInt("-12345");
    std::cout << op.value() << std::endl;

    demo_struct_func();
    //test_yield();
    //test_number();

    test_keywords();
    test_charconv_header();
    test_variant();
    test_optional();
    test_any();
    test_apply();
    test_make_from_tuple();
    test_str_view();
    return 0;
}
