#include <iostream>
#include <set>
#include <iomanip>
#include "order_statistic_tree.h"
using namespace std;

const long long K = 150000, SQ = 10000;

void result(string func, bool res, vector<pair<int, string>> failed) {
    if (res) {
        cout << func << " passed all tests.";
    } else {
        cout << func << " failed tests: ";
        for (auto c : failed) {
            cout << c.first << " - " << c.second;
            if (c != failed.back()) {
                cout << ", ";
            } else {
                cout << ".";
            }
        }
    }
    cout << "\n";
}

long long ext_rand() { return rand() * RAND_MAX + rand(); }

void iterating_with_increment_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        vector<int> vec;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            vec.push_back(q);
            st2.insert(q);
        }

        vector<int> vec1, vec2, vec3, vec4, vec5, vec6;
        vec3 = vec;
        sort(vec3.begin(), vec3.end());
        vec3.erase(unique(vec3.begin(), vec3.end()), vec3.end());
        for (auto it = st2.end()--; ; it--) {
            vec1.push_back(*it);
            if (it == st2.begin()) break;
        }
        for (auto it = st2.end()--; ; --it) {
            vec1.push_back(*it);
            if (it == st2.begin()) break;
        }
        for (auto c : st2) vec2.push_back(c);

        for (auto it = st2.rend()--; ; it--) {
            vec5.push_back(*it);
            if (it == st2.rbegin()) break;
        }
        for (auto it = st2.rend()--; ; --it) {
            vec6.push_back(*it);
            if (it == st2.rbegin()) break;
        }
        reverse(vec5.begin(), vec5.end());
        reverse(vec6.begin(), vec6.end());

        if (vec1 != vec2 || vec2 != vec3 || vec3 != vec4 || vec4 != vec5 || vec5 != vec6) {
            failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void iterating_with_decrement_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        vector<int> vec;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            vec.push_back(q);
            st2.insert(q);
        }

        vector<int> vec1, vec2, vec3, vec4, vec5, vec6;
        vec3 = vec;
        sort(vec3.begin(), vec3.end());
        vec3.erase(unique(vec3.begin(), vec3.end()), vec3.end());
        for (auto it = st2.begin(); it != st2.end(); it++) vec1.push_back(*it);
        for (auto it = st2.begin(); it != st2.end(); ++it) vec4.push_back(*it);
        for (auto c : st2) vec2.push_back(c);

        for (auto it = st2.rbegin(); it != st2.rend(); it++) vec5.push_back(*it);
        for (auto it = st2.rbegin(); it != st2.rend(); ++it) vec6.push_back(*it);
        reverse(vec5.begin(), vec5.end());
        reverse(vec6.begin(), vec6.end());

        if (vec1 != vec2 || vec2 != vec3 || vec3 != vec4 || vec4 != vec5 || vec5 != vec6) {
            failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

int main() {
    iterating_with_increment_test();
    iterating_with_decrement_test();

    return 0;
}
