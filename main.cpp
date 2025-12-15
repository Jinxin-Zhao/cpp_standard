#include <iostream>
#include "c++_23.h"
#include "c++_11.h"
#include "c++_17.h"
#include "c++_algo.h"
#include "bitmap.h"

#include "c++_container.h"
#include "double_epsilon.h"

static const FinancialComparator financialCompare;

int main() {

    //bool f_isLessTh = financialCompare.equal(14999.325123797, 14999.325123792);
    std::cout << "double epsilon: " << std::numeric_limits<double>::epsilon() << std::endl;
    std::cout << "Scientific: " << std::scientific << std::numeric_limits<double>::epsilon() << std::endl;

    bool f_isLessTh = double_equal(14999.3251237979912346, 14999.3251237979912345);
    if (f_isLessTh) {
        printf("%s:%d double value is equal\n", __FUNCTION__, __LINE__);
    } else {
        printf("%s:%d double value is not equal\n", __FUNCTION__, __LINE__);
    }
    // bool isEqual = double_approx_equal(14999.32512347, 14999.32512347);
    // if (isEqual) {
    //     printf("%s:%d double value is equal\n", __FUNCTION__, __LINE__);
    // } else {
    //     printf("%s:%d double value is not equal\n", __FUNCTION__, __LINE__);
    // }
    printf("=================================\n");
    // test c++ containers
    test_unordered_map();
    return 0;
    //test_multimap();
    //foo();
    demo_constructed_binding();

    demo_fold_expr();

    std::optional<int> op = ConvertToInt("-12345");
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
