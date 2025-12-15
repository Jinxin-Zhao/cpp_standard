#ifndef DOUBLE_EPSILON_H
#define DOUBLE_EPSILON_H

#include <cmath>
#include <limits>

inline bool double_approx_equal(double a, double b, double rel_epsilon = 1e-10) {
    if (a == b) return true;
    double diff = std::fabs(a - b);
    double scale = std::max(std::fabs(a), std::fabs(b));
    return diff <= scale * rel_epsilon;
}

inline bool double_financial_less_equal(double a, double b, double rel_epsilon = 1e-10) {
    return a < b || double_approx_equal(a, b, rel_epsilon);
}


class FinancialComparator {
private:
    static constexpr double DEFAULT_EPSILON = 1e-12;
    double epsilon_;
    
public:
    FinancialComparator(double epsilon = DEFAULT_EPSILON) : epsilon_(epsilon) {}
    
    bool equal(double a, double b) const {
        double diff = std::fabs(a - b);
        double scale = std::max(std::max(std::fabs(a), std::fabs(b)), 
                               std::numeric_limits<double>::min());
        printf("%s:%d diff %lf scale %lf, multi %lf\n", __FUNCTION__, __LINE__, diff, scale, scale * epsilon_);
        return diff < scale * epsilon_;
    }
    
    bool less_equal(double a, double b) const {
        return a < b || equal(a, b);
    }
    
    bool greater_equal(double a, double b) const {
        return a > b || equal(a, b);
    }
};


inline bool double_equal(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) {
    return std::fabs(a - b) < epsilon;
}

inline bool double_less_equal(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) {
    return a < b || double_equal(a, b, epsilon);
}

inline bool double_greater_equal(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) {
    return a > b || double_equal(a, b, epsilon);
}

#endif