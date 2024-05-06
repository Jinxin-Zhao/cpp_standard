#ifndef __CPLUSPLUS_ALGORITHM__H__
#define __CPLUSPLUS_ALGORITHM__H__

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

inline void sort_by_value(multimap<int,int> & m) {
    vector<pair<int, int>> vec;
    for (auto it = m.begin(); it != m.end();it++) {
        vec.push_back(make_pair(it->first,it->second));
    }

    sort(vec.begin(),vec.end(), [](const pair<int,int> &x, const pair<int,int> &y) {
        return x.second < y.second;
    });

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << it->first << " " << it->second << "\n";
    }
}

// transform & execution
void test_transform() {
    //std::transform();
}



#endif
