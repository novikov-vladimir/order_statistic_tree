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
        for (auto it = (--st2.end()); ; it--) {
            vec1.push_back(*it);
            if (it == st2.begin()) break;
        }
        for (auto it = --st2.end(); ; --it) {
            vec4.push_back(*it);
            if (it == st2.begin()) break;
        }
        for (auto c : st2) vec2.push_back(c);

        for (auto it = --st2.rend(); ; it--) {
            vec5.push_back(*it);
            if (it == st2.rbegin()) break;
        }
        for (auto it = --st2.rend(); ; --it) {
            vec6.push_back(*it);
            if (it == st2.rbegin()) break;
        }
        reverse(vec2.begin(), vec2.end());
        reverse(vec3.begin(), vec3.end());

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

void get_index_test() {
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

        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        vector<int> vec2, vec3;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % vec.size(), q2 = ext_rand() % vec.size();
            vec2.push_back(q - q2);
            vec3.push_back(st2.find(vec[q]) - st2.find(vec[q2]));
        }

        if (vec2 != vec3) {
            failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void iterator_difference_test() {
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

        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        vector<int> vec2, vec3;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % vec.size(), q2 = ext_rand() % vec.size();
            vec2.push_back(q - q2);
            vec3.push_back(st2.find(vec[q]) - st2.find(vec[q2]));
        }

        if (vec2 != vec3) {
            failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void iterator_random_access_test() {
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

        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        vector<int> vec2, vec3;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % vec.size(), q2 = ext_rand() % vec.size();
            if (q > q2) swap(q, q2);
            vec2.push_back(vec[q2]);
            auto it = st2.find(vec[q]);
            it += (q2 - q);
            vec3.push_back(*it);
        }

        if (vec2 != vec3) {
            failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        vector<int> vec;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            vec.push_back(q);
            st2.insert(q);
        }

        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        vector<int> vec2, vec3;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % vec.size(), q2 = ext_rand() % vec.size();
            if (q > q2) swap(q, q2);
            vec2.push_back(vec[q]);
            auto it = st2.find(vec[q2]);
            it -= (q2 - q);
            vec3.push_back(*it);
        }

        if (vec2 != vec3) {
            failed.push_back({ 2, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 2, "re" });
    }

    result(__func__, failed.empty(), failed);
}

int main() {
    iterating_with_increment_test();
    iterating_with_decrement_test();
    iterator_difference_test();
    iterator_random_access_test();

    return 0;
}
