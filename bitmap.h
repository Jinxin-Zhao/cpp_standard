#ifndef __CBITMAP__H__
#define __CBITMAP__H__

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
// check if the number in set_size(4000,000,000)
class BitMap {
    public:
    BitMap(size_t size = 0) : _bits(size) {}

    void set(size_t pos) {
        // 右移5位相当于除以32
        size_t idx = pos >> 5;
        //取余数，用于确定在unsigned int 中的具体位置
        size_t bit = pos & 0x1f;
        // 将指定位置的比特位设为1
        _bits[idx] |= (1 << bit);
    }

    bool test(size_t pos) const {
        size_t idx = pos >> 5;
        size_t bit = pos & 0x1f;
        return (_bits[idx] & (1 << bit)) != 0;
    }
    private:
    vector<unsigned int> _bits;
};

int test_number() {
    const size_t n = 1000000000;
    vector<unsigned int> data(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = rand();
    }
    BitMap bm(1<<30);
    for (size_t i = 0; i < n; ++i) {
        bm.set(data[i]);
    }
    unsigned int num = rand();
    if (bm.test(num)) {
        cout << num << "exists. " << endl;
    } else {
        cout << num << "does not exist. " << endl;
    }
    return 0;
}



#endif