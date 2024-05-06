#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

void test_unordered_map() {
    unordered_map<string, string> umap {
            {"key1", "value1"},
            {"key2", "value2"},
            {"key3", "value3"},
    };
    unordered_map<string, string> umap_2(umap);
    unordered_map<string, string> umap_3(++umap.begin(), umap.end());

    auto result = umap.emplace("zjx", "excellent");
    cout << "emplace pair "<< result.first->first << " " << result.first->second << endl;
    auto iter = umap.emplace_hint(result.first, "zjxx", "top");
    cout << "emplace_hint pair "<< iter->first << " " << iter->second << endl;
    iter = umap.find("zjx");
    cout << "found pair "<< iter->first << " " << iter->second << endl;
    cout << "list all elements : " << endl;
    for (auto i = umap.begin(); i != umap.end(); i++) {
        cout << i->first << " " << i->second << endl;
    }
    result = umap.emplace("zjx", "happy");
    if (result.second) {
        cout << "emplace pair "<< result.first->first << " " << result.first->second << endl;
    } else {
        cout << "emplace back failed" << endl;
    }
    result = umap.insert({"zjx" , "aha"});
    if (result.second) {
        cout << "emplace pair "<< result.first->first << " " << result.first->second << endl;
    } else {
        cout << "insert back failed" << endl;
    }
    cout << "bucekt count " << umap.bucket_count() << " max bucket count " << umap.max_bucket_count() << endl;
    cout << "load factor " << umap.load_factor() << endl;
    cout << "max load factor " << umap.max_load_factor() << endl;
    // rehash(n), set bucket count
    umap.rehash(200);
    cout << "after setting bucket count " << umap.bucket_count() << " max " << umap.max_bucket_count() << endl;
    umap.reserve(600);
    cout << "after reserving bucket count " << umap.bucket_count() << " max " << umap.max_bucket_count() << endl;
    umap.hash_function();
}


#endif