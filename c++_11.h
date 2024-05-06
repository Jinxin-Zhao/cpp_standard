#ifndef __CSTANDARD_11__H__
#define __CSTANDARD_11__H__

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <map>
#include <complex>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;


namespace test_c11 {
    // constexpr
    class X {
        public:
            constexpr X() : value(5) {}
            constexpr X(int i) : value(i) {}
            constexpr int get() const {return value;}
        private:
            int value;
    };

    constexpr int foo(){
        return []() {return 58;}();
    }

    void test_const_expr() {
        constexpr X x;
        char buffer[x.get()] = {0};
    }

    // call once
    once_flag of;
    void CallOnce() {
        call_once(of, [](){
            cout << "call once" << endl;
        });
    }

    void test_call_once() {
        thread t[5];
        for (auto i = 0; i < 5; ++i) {
            t[i] = thread(CallOnce);
        }
        for (auto & th : t) {
            th.join();
        }
    }
}


void little_sleep(std::chrono::microseconds us) {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do {
        std::this_thread::yield();
    }while (std::chrono::high_resolution_clock::now() < end);
}

void test_yield() {
    auto start = std::chrono::high_resolution_clock::now();
    little_sleep(std::chrono::microseconds(100));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "wait for " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << " microseconds\n";
}


// test multimap
void test_multimap() {
    multimap<string, string> pets;
    //////////////////////////////// insert, emplace //////////////////////////////////
    auto first_iter = pets.insert(std::pair<string,string>{"dog","Sun"});
    // insert dog-spot before dog-Sun
    first_iter = pets.insert(first_iter, std::make_pair("dog", "spot"));
    // insert dog-Rover after dog-Sun
    pets.insert(std::make_pair("dog", "Rover"));
    pets.insert(std::make_pair("cat", "Kittyr"));
    // insert list
    pets.insert ({{ "rat", "Roland"}, {"pig", "Pinky" }, {"pig", "Perky"}});

    auto iter = pets.emplace("rabbit", "Flopsy");
    // insert rabbit-Mopsy before rabbit-Flopsy
    iter = pets.emplace_hint(iter, "rabbit","Mopsy");

    //////////////////////////////// find, count //////////////////////////////////
    iter = pets.find("rabbit");
    if (iter != std::end(pets)) {
        cout << iter->first << " is " << iter->second << endl;
    }
    cout << "rabbits count " << pets.count("rabbit") << endl;
    // lower_bound returns the earliest cat iterator
    // upper_bound returns the next iterator of rabbit
    // distance is 8 (8 - 0)
    cout << "distance between cat-rabbit " << distance(pets.lower_bound("cat"), pets.upper_bound("rabbit")) << endl;

    for (auto item : pets) {
        cout << item.first << " " << item.second << endl;
    }


    //
    multimap<string, complex<double>> mp;
    //mp.emplace()
    mp.emplace(piecewise_construct, make_tuple("hello"), make_tuple(1,2));
    mp.emplace(piecewise_construct, forward_as_tuple("hello"), forward_as_tuple(4,2));
    for (auto item : mp) {
        cout << iter->first << " is " << iter->second << endl;
    }

    //////////////////////////////// instance test //////////////////////////////////
    cout << "==================================================" << endl;
    using PetType = string;
    using PetName = string;
    std::multimap<PetType, PetName> m_pets;
    PetType type {};
    PetName name {};
    char more {'Y'};
    while (std::toupper(more) == 'Y') {
        cout << "Enter the type of your pet and name" << endl;
        cin >> std::ws >> type >> name;

        // add element to m_pets
        auto it = m_pets.lower_bound(type);
        if (it != end(m_pets)) {
            m_pets.emplace_hint(iter, type,name);
        } else {
            m_pets.emplace(type, name);
        }
        cout << "Do you want to enter another pet (Y or N) " << endl;
        cin >> more;
    }

    // output all the pets
    auto it = begin(m_pets);
    while (it != end(pets)) {
        auto pr = m_pets.equal_range(it->first);
        cout << "\n pets of type " << it->first << " are:\n " << endl;
        for (auto p = pr.first; p != pr.second; ++p) {
            cout << " " << p->second;
        }
        cout << endl;
        it = pr.second;
    }
}

#endif