#include <iostream>
#include <set>
#include <iomanip>
#include "order_statistic_tree.h"
using namespace std;

const long long K = 1500, SQ = 1000;

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

void insert_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            st1.insert(q);
            st2.insert(q);
        }

        vector<int> vec1, vec2;
        for (auto c : st1) vec1.push_back(c);
        for (auto c : st2) vec2.push_back(c);

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 1, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        set<string> st1;
        order_statistic_tree<string> st2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 100 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            st1.insert(ins);
            st2.insert(ins);
        }

        vector<string> vec1, vec2;
        for (const auto& c : st1) vec1.push_back(c);
        for (auto c : st2) vec2.push_back(c);

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 2, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 2, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 2, "re" });
    }

    // test3
    try {
        set<string> st1;
        order_statistic_tree<string> st2;

        vector<string> vec1, vec2;
        for (const auto& c : st1) vec1.push_back(c);
        for (auto c : st2) vec2.push_back(c);

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 3, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 3, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 3, "re" });
    }

    // test4
    try {
        struct mystruct {
            int a, b;
            char t;
        };

        struct compare {
            bool operator()(const mystruct& a, const mystruct& b) const {
                return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
            }
        };

        set<mystruct, compare> st1;
        order_statistic_tree<mystruct, compare> st2;

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({ a, b, t });
            st2.insert({ a, b, t });
        }
        vector<mystruct> vec1, vec2;
        for (auto c : st1) vec1.push_back(c);
        for (auto c : st2) vec2.push_back(c);

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 4, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i].a != vec2[i].a || vec1[i].b != vec2[i].b || vec1[i].t != vec2[i].t) f = 0;
            }

            if (!f) failed.push_back({ 4, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 4, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void upper_and_lower_bound_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            st1.insert(q);
            st2.insert(q);
        }

        const int MRG = 10;
        vector<int> vec1, vec2;
        for (int i = -MRG; i < K + MRG; i++) {
            int value = -10;
            if (st1.lower_bound(i) != st1.end()) value = (*st1.lower_bound(i));
            vec1.push_back(value);
        }

        for (int i = -MRG; i < K + MRG; i++) {
            int value = -10;
            if (st2.lower_bound(i) != st2.end()) value = (*st2.lower_bound(i));
            vec2.push_back(value);
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 1, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        set<string> st1;
        order_statistic_tree<string> st2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 100 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            st1.insert(ins);
            st2.insert(ins);
        }

        vector<string> vec1, vec2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 100 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            string ans = "#";
            if (st1.lower_bound(ans) != st1.end()) ans = (*st1.lower_bound(ans));
            vec1.push_back(ans);

            ans = "#";
            if (st2.lower_bound(ans) != st2.end()) ans = (*st2.lower_bound(ans));
            vec2.push_back(ans);
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 2, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 2, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 2, "re" });
    }

    // test3
    try {
        struct mystruct {
            int a, b;
            char t;
        };

        struct compare {
            bool operator()(const mystruct& a, const mystruct& b) const {
                return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
            }
        };

        set<mystruct, compare> st1;
        order_statistic_tree<mystruct, compare> st2;

        vector<mystruct> vec1, vec2;
        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({ a, b, t });
            st2.insert({ a, b, t });
        }

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;

            mystruct str{ 1, 1, '4' };
            if (st1.lower_bound(str) != st1.end()) str = (*st1.lower_bound(str));
            vec1.push_back(str);
            mystruct str2{ 1, 1, '4' };
            if (st2.lower_bound(str2) != st2.end()) str2 = (*st2.lower_bound(str));
            vec2.push_back(str2);
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 3, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i].a != vec2[i].a || vec1[i].b != vec2[i].b || vec1[i].t != vec2[i].t) f = 0;
            }

            if (!f) failed.push_back({ 3, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 3, "re" });
    }

    // test4
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            st1.insert(q);
            st2.insert(q);
        }

        const int MRG = 10;
        vector<int> vec1, vec2;
        for (int i = -MRG; i < K + MRG; i++) {
            int value = -10;
            if (st1.upper_bound(i) != st1.end()) value = (*st1.upper_bound(i));
            vec1.push_back(value);
        }

        for (int i = -MRG; i < K + MRG; i++) {
            int value = -10;
            if (st2.upper_bound(i) != st2.end()) value = (*st2.upper_bound(i));
            vec2.push_back(value);
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 4, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 4, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 4, "re" });
    }

    // test5
    try {
        set<string> st1;
        order_statistic_tree<string> st2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 100 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            st1.insert(ins);
            st2.insert(ins);
        }

        vector<string> vec1, vec2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 100 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            string ans = "#";
            if (st1.upper_bound(ans) != st1.end()) ans = (*st1.upper_bound(ans));
            vec1.push_back(ans);

            ans = "#";
            if (st2.upper_bound(ans) != st2.end()) ans = (*st2.upper_bound(ans));
            vec2.push_back(ans);
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 5, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 5, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 5, "re" });
    }

    // test6
    try {
        struct mystruct {
            int a, b;
            char t;
        };

        struct compare {
            bool operator()(const mystruct& a, const mystruct& b) const {
                return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
            }
        };

        set<mystruct, compare> st1;
        order_statistic_tree<mystruct, compare> st2;

        vector<mystruct> vec1, vec2;
        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({ a, b, t });
            st2.insert({ a, b, t });
        }

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            mystruct ch = { a, b, t };

            mystruct str{ 1, 1, '4' };
            if (st1.upper_bound(ch) != st1.end()) str = (*st1.upper_bound(ch));
            vec1.push_back(str);
            mystruct str2{ 1, 1, '4' };
            if (st2.upper_bound(ch) != st2.end()) str2 = (*st2.upper_bound(ch));
            vec2.push_back(str2);
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 6, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i].a != vec2[i].a || vec1[i].b != vec2[i].b || vec1[i].t != vec2[i].t) f = 0;
            }

            if (!f) failed.push_back({ 6, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 6, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void contains_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            st1.insert(q);
            st2.insert(q);
        }

        const int MRG = 10;
        vector<int> vec1, vec2;
        for (int i = -MRG; i < K + MRG; i++) {
            vec1.push_back((st1.find(i) != st1.end()));
        }

        for (int i = -MRG; i < K + MRG; i++) {
            vec2.push_back(st2.contains(i));
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 1, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        set<string> st1;
        order_statistic_tree<string> st2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 7 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            st1.insert(ins);
            st2.insert(ins);
        }

        vector<bool> vec1, vec2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 7 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }

            vec1.push_back((st1.find(ins) != st1.end()));

            vec2.push_back(st2.contains(ins));
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 2, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 2, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 2, "re" });
    }

    // test3
    try {
        struct mystruct {
            int a, b;
            char t;
        };

        struct compare {
            bool operator()(const mystruct& a, const mystruct& b) const {
                return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
            }
        };

        set<mystruct, compare> st1;
        order_statistic_tree<mystruct, compare> st2;

        vector<int> vec1, vec2;
        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({ a, b, t });
            st2.insert({ a, b, t });
        }

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;

            vec1.push_back((st1.find({ a, b, t }) != st1.end()));

            vec2.push_back(st2.contains({ a, b, t }));
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 3, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 3, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 3, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void find_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            st1.insert(q);
            st2.insert(q);
        }

        const int MRG = 10;
        vector<int> vec1, vec2;
        for (int i = -MRG; i < K + MRG; i++) {
            vec1.push_back((st1.find(i) != st1.end()));
        }

        for (int i = -MRG; i < K + MRG; i++) {
            vec2.push_back(st2.find(i) != st2.end());
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 1, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        set<string> st1;
        order_statistic_tree<string> st2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 7 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            st1.insert(ins);
            st2.insert(ins);
        }

        vector<bool> vec1, vec2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 7 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }

            vec1.push_back((st1.find(ins) != st1.end()));

            vec2.push_back(st2.find(ins) != st2.end());
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 2, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 2, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 2, "re" });
    }

    // test3
    try {
        struct mystruct {
            int a, b;
            char t;
        };

        struct compare {
            bool operator()(const mystruct& a, const mystruct& b) const {
                return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
            }
        };

        set<mystruct, compare> st1;
        order_statistic_tree<mystruct, compare> st2;

        vector<int> vec1, vec2;
        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({ a, b, t });
            st2.insert({ a, b, t });
        }

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;

            vec1.push_back((st1.find({ a, b, t }) != st1.end()));

            vec2.push_back(st2.find({ a, b, t }) != st2.end());
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 3, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 3, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 3, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void statistic_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        vector<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K; i++) {
            int q = ext_rand() % K;
            st1.push_back(q);
            st2.insert(q);
        }

        sort(st1.begin(), st1.end());
        st1.erase(unique(st1.begin(), st1.end()), st1.end());
        vector<int> vec1, vec2;

        for (int i = 0; i < st1.size(); i++) {
            vec1.push_back(st1[i]);
            vec2.push_back((*st2.statistic(i)));
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 1, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 1, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        vector<string> st1;
        order_statistic_tree<string> st2;

        for (int i = 0; i < K; i++) {
            string ins;
            for (int j = 0; j < rand() % 7 + 1; j++) {
                ins.push_back(rand() % 26 + 'a');
            }
            st1.push_back(ins);
            st2.insert(ins);
        }

        sort(st1.begin(), st1.end());
        st1.erase(unique(st1.begin(), st1.end()), st1.end());
        vector<string> vec1, vec2;
        for (int i = 0; i < st1.size(); i++) {
            vec1.push_back(st1[i]);
            vec2.push_back(*st2.statistic(i));
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 2, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (vec1[i] != vec2[i]) f = 0;
            }

            if (!f) failed.push_back({ 2, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 2, "re" });
    }

    // test3
    try {
        struct mystruct {
            int a, b;
            char t;

            bool operator==(const mystruct& rhs) const {
                return rhs.a == a && rhs.b == b && rhs.t == t;
            }
        };

        struct compare {
            bool operator()(const mystruct& a, const mystruct& b) const {
                return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
            }
        };

        vector<mystruct> st1;
        order_statistic_tree<mystruct, compare> st2;

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.push_back({ a, b, t });
            st2.insert({ a, b, t });
        }

        sort(st1.begin(), st1.end(), compare());
        st1.erase(unique(st1.begin(), st1.end()), st1.end());
        vector<mystruct> vec1, vec2;
        for (int i = 0; i < st1.size(); i++) {
            vec1.push_back(st1[i]);
            vec2.push_back(*st2.statistic(i));
        }

        if (vec1.size() != vec2.size()) {
            failed.push_back({ 3, "wa" });
        } else {
            bool f = 1;
            for (int i = 0; i < vec2.size(); i++) {
                if (!(vec1[i] == vec2[i])) {
                    f = 0;
                }
            }

            if (!f) failed.push_back({ 3, "wa" });
        }
    }
    catch (int code) {
        failed.push_back({ 3, "re" });
    }

    result(__func__, failed.empty(), failed);
}

const int K2 = 1000;

void erase_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K2; i++) {
            int q = ext_rand() % K2;
            st1.insert(q);
            st2.insert(q);
        }

        vector<vector<int>> vec1, vec2;
        for (int i = 0; i < K2; i++) {
            for (int t = 0; t < rand() % 3; t++) {
                int q = ext_rand() % K2;
                st1.erase(q);
                st2.erase(q);
            }

            vector<int> nw1, nw2;
            for (auto c : st1) nw1.push_back(c);
            for (auto c : st2) nw2.push_back(c);

            vec1.push_back(nw1);
            vec2.push_back(nw2);
        }

        bool f = 1;
        if (vec1 != vec2) f = 0;

        if (!f) failed.push_back({ 1, "wa" });
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        set<int> st1;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K2; i++) {
            int q = ext_rand() % K2;
            st1.insert(q);
            st2.insert(q);
        }

        vector<vector<int>> vec1, vec2;
        for (int i = 0; i < K2; i++) {
            for (int t = 0; t < rand() % 3; t++) {
                int q = ext_rand() % K2;
                st1.erase(q);
                if (st2.find(q) != st2.end()) st2.erase(st2.find(q));
            }

            vector<int> nw1, nw2;
            for (auto c : st1) nw1.push_back(c);
            for (auto c : st2) nw2.push_back(c);

            vec1.push_back(nw1);
            vec2.push_back(nw2);
        }

        bool f = 1;
        if (vec1 != vec2) f = 0;

        if (!f) failed.push_back({ 1, "wa" });
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void clear_and_empty_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        order_statistic_tree<int> st2;

        for (int i = 0; i < K2; i++) {
            int q = ext_rand() % K2;
            st2.insert(q);
        }

        vector<int> vec2;
        for (int i = 0; i < K2; i++) {
            for (int t = 0; t < rand() % 3; t++) {
                int q = ext_rand() % K2;
                st2.erase(q);
            }
        }

        st2.clear();
        for (auto c : st2) vec2.push_back(c);

        if (!vec2.empty() || (!st2.empty())) failed.push_back({ 1, "wa" });
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    // test2
    try {
        vector<int> vec2;
        order_statistic_tree<int> st2;

        for (int i = 0; i < K2; i++) {
            int q = ext_rand() % K2;
            st2.insert(q);
        }

        st2.clear();
        for (auto c : st2) vec2.push_back(c);

        if (!vec2.empty() || !st2.empty()) failed.push_back({ 1, "wa" });
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

void swap_test() {
    vector<pair<int, string>> failed;
    srand(1);

    // test1
    try {
        order_statistic_tree<int> st1, st2;

        for (int i = 0; i < K2; i++) {
            int q = ext_rand() % K2;
            st2.insert(q);
        }

        for (int i = 0; i < K2; i++) {
            int q = ext_rand() % K2;
            st1.insert(q);
        }

        vector<int> vec2, vec1, vec1swap, vec2swap;

        for (auto c : st1) vec1.push_back(c);
        for (auto c : st2) vec2.push_back(c);

        st1.swap(st2);

        for (auto c : st1) vec1swap.push_back(c);
        for (auto c : st2) vec2swap.push_back(c);

        if (vec1swap != vec2 || vec1 != vec2swap) failed.push_back({ 1, "wa" });
    }
    catch (int code) {
        failed.push_back({ 1, "re" });
    }

    result(__func__, failed.empty(), failed);
}

int main() {
    insert_test();
    upper_and_lower_bound_test();
    contains_test();
    find_test();
    statistic_test();
    erase_test();
    clear_and_empty_test();
    swap_test();

    return 0;
}
