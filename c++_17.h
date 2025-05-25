#ifndef __CSTANDARD_17__H__
#define __CSTANDARD_17__H__

#include <iostream>
//#include <execution>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <tuple>
#include <map>
#include <optional>
#include <variant>
#include <any>


using namespace std;

__attribute__ ((weak)) void foo();

void demo_self_deduct() {
    // old version: pair<int, double> p(1, 2.4)
    pair p(1,2.4);
    vector v = {1,3,4};
}

//constructed binding
tuple<int,double> func() {
    return tuple(1, 2.2);
}
//
class Entry {
public:
    void Init() {
        m_name = "init_name";
        m_age = 19;
    }

    string GetName() const { return m_name; }
    int GetAge() const { return m_age; }
private:
    string m_name;
    int m_age;
};

template <size_t I>
auto get(const Entry & e) {
    if constexpr (I == 0) return e.GetName();
    else if constexpr (I == 1) return e.GetAge();
}

namespace  std {
        template <> struct tuple_size<Entry> : integral_constant<size_t, 2> {};
        template <> struct tuple_element<0, Entry> {
            using type = string;
        };
        template <> struct tuple_element<1, Entry> {
            using type = int;
        };
    }

void demo_constructed_binding() {
    auto tuple_value = func();
    auto & [i, d] = tuple_value;
    i = 99;
    cout << "tuple 0: " << get<0>(tuple_value) << endl;
    //
    Entry e;
    e.Init();
    auto [name , age] = e;
    cout << "name " << name << " age " << age << endl;
}


// inline keywords
struct A {
        static const int value;
    };
inline int const A::value = 10;

struct B {
    inline static const int value = 20;
};

// fold expression
template <typename ... Args>
auto sum(Args ...ts) {
    return (ts + ...);
}

void demo_fold_expr() {
    int a {sum(1,2,3,4,5)};
    std::cout << "demo fold expression " << a << endl;
}

// constexpr lambda function
// constrain: 函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，不能动态分配内存，不能有new delete等，不能虚函数。
void demo_constexpr_lamda() {
    constexpr auto lamb = [] (int n) {return n*n;};
    static_assert(lamb(3) == 9, "a");
}

// namespace nest
namespace RA::B::C {
        void test();
    }


#if defined __has_include

#if __has_include(<charconv>)
#define has_charconv 1
#include <charconv>
#endif

#endif


std::optional<int> ConvertToInt(const std::string & str) {
        int value{};
#ifdef has_charconv
    const auto last = str.data() + str.size();
    const auto res = std::from_chars(str.data(), last, value);
    cout << "func " << __FUNCTION__ << endl;
    if (res.ec == std::errc{} && res.ptr == last) return value;
#endif
      return std::nullopt;
#endif
    return std::nullopt;
    }

struct demo_struct {
        char c;
        uint64_t v1;
        uint16_t v2;
    };

struct __attribute__ ((__packed__)) demo_struct_packed {
    char c;
    uint64_t v1;
    uint16_t v2;
};

struct __attribute__ ((aligned(64))) demo_struct_aligned {
    char c;
    uint64_t v1;
    uint16_t v2;
};


void demo_struct_func() {
    cout << "sizeof struct " << sizeof(demo_struct) << endl;
    cout << "struct offset c " << offsetof(demo_struct, c) << endl;
    cout << "struct offset v1 " << offsetof(demo_struct, v1) << endl;
    cout << "struct offset v2 " << offsetof(demo_struct, v2) << endl;
    cout << "sizeof packed struct " << sizeof(demo_struct_packed) << endl;
    cout << "packed struct offset c " << offsetof(demo_struct_packed, c) << endl;
    cout << "packed struct offset v1 " << offsetof(demo_struct_packed, v1) << endl;
    cout << "packed struct offset v2 " << offsetof(demo_struct_packed, v2) << endl;
    cout << "sizeof aligned struct " << sizeof(demo_struct_aligned) << endl;
    cout << "aligned struct offset c " << offsetof(demo_struct_aligned, c) << endl;
    cout << "aligned struct offset v1 " << offsetof(demo_struct_aligned, v1) << endl;
    cout << "aligned struct offset v2 " << offsetof(demo_struct_aligned, v2) << endl;
}

// test keywords
// [[fallthrough]]

[[nodiscard]] int test_discard(){
    return 1;
}

void test_keywords() {
    int i = 0;
    switch (i) {
        case 0:
            cout << "0" << endl;
            //[[fallthrough]];
        case 1:
            cout << "1" << endl;
        default:
            cout << "default" << endl;
            break;
    }
    //warning if no res to catch rtn value of test_discard
    auto res =  test_discard();
    [[maybe_unused]] int y = 2;
}

//from_chars, to_chars
void test_charconv_header() {
    string str{"123456"};
    int value = 0;
    const auto res = from_chars(str.data(),str.data()+4, value);
    if (res.ec == std::errc()) {
        cout << value << ", distance " << res.ptr - str.data() << endl;
    } else if (res.ec == std::errc::invalid_argument) {
        cout << "invalid" << endl;
    }
}

// variant: 类似union的功能，但却比union更高级，举个例子union里面不能有string这种类型，但std::variant却可以，还可以支持更多复杂类型，如map等
// 一般情况下variant的第一个类型一般要有对应的构造函数，否则编译失败
struct struct_var{
    struct_var(int i) {}
};
void test_variant() {
    variant<int, string> var("Hello");
    cout << var.index() << endl;
    //var = 123;
    //cout << var.index() << endl;

    cout << "second " << get<1>(var) << endl;
    //如何避免这种情况呢，可以使用std::monostate来打个桩，模拟一个空状态。
    //variant<struct_var> new_variant;
    variant<monostate, struct_var> new_variant;
}

// test optional
optional<int> sub_func(const string & s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return nullopt;
    }
}

// test optional
void test_optional() {
    string s{"234"};
    auto o = sub_func(s);
    if (o.has_value()) {
        cout << o.value() << endl;
        cout << *o << endl;
    } else {
        cout << "error" << endl;
    }
    std::as_const(s);
}

// test any
void test_any() {
    any a = 4.6;
    cout << a.type().name() << " " << any_cast<double>(a) << endl;
    a = string("abc");
    if (a.has_value()) {
        printf("a type %s\n", any_cast<string>(a).c_str());
    }
}

// test apply
int add(int first, int second) {
    return first + second;
}
auto add_lambda = [](auto first, auto second) {return first + second;};
void test_apply() {
    cout << "apply add " << apply(add,pair(1,2)) << endl;
    cout << "apply lamda " << apply(add_lambda,std::tuple(2.0f, 3.0f)) << endl;
}

// test make_from_tuple
struct Foo {
    Foo(int first, float second, int third) {
        cout << first << ", " << second << ", " << third << endl;
    }
};

void test_make_from_tuple() {
    auto tuple = make_tuple(42, 3.14f, 0);
    auto f = make_from_tuple<Foo>(std::move(tuple));
}

// test string_view: 通常我们传递一个string时会触发对象的拷贝操作，大字符串的拷贝赋值操作会触发堆内存分配，很影响运行效率，有了string_view就可以避免拷贝操作，平时传递过程中传递string_view即可。
//因为string_view 只包含一个指向字符串的指针(*)和一个表示数组大小的整型数值(int)，因此总大小是4+4=8。而string是容器类型，内部结构我不太清楚，看输出整体是要比string_view大挺多的。
void str_view(string_view str) {
    cout << "string_view " << str << endl;
    str = "23wefsdf";
}

void test_str_view() {
    string str = "Hello";
    string_view stv(str.c_str(), str.size());
    str_view(stv);
}

#include <filesystem>
// file_system: C++17正式将file_system纳入标准中，提供了关于文件的大多数功能
void test_file_system() {
    namespace fs = std::filesystem;
    //string path = "./";
    //fs::create_directory(path);
    //fs::copy_file(src, dst, fs::copy_options::skip_existing);
    //fs::exists(filename);
    //fs::current_dir(error_code);
}