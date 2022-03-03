#include <iostream>
#include <set>
#include <iomanip>
#include "order_statistic_tree.h"
using namespace std;

const long long K = 150000;

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

        auto compare = [](const mystruct& a, const mystruct& b)
        {
            return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
        };

        set<mystruct, decltype(compare)> st1(compare);
        order_statistic_tree<mystruct> st2(compare);

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({a, b, t});
            st2.insert({a, b, t});
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

        auto compare = [](const mystruct& a, const mystruct& b)
        {
            return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
        };

        set<mystruct, decltype(compare)> st1(compare);
        order_statistic_tree<mystruct> st2(compare);

        vector<mystruct> vec1, vec2;
        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({a, b, t});
            st2.insert({a, b, t});
        }

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({a, b, t});
            st2.insert({a, b, t});

            mystruct str{1, 1, '4'};
            if (st1.lower_bound(str) != st1.end()) str = (*st1.lower_bound(str));
            vec1.push_back(str);
            mystruct str2{1, 1, '4'};
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

        auto compare = [](const mystruct& a, const mystruct& b)
        {
            return make_tuple(a.t, a.b, a.a) < make_tuple(b.t, b.b, b.a);
        };

        set<mystruct, decltype(compare)> st1(compare);
        order_statistic_tree<mystruct> st2(compare);

        vector<mystruct> vec1, vec2;
        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            st1.insert({a, b, t});
            st2.insert({a, b, t});
        }

        for (int i = 0; i < K; i++) {
            char t = rand() % 26 + 'a';
            int a = ext_rand() % K;
            int b = ext_rand() % K;
            mystruct ch = {a, b, t};

            mystruct str{1, 1, '4'};
            if (st1.upper_bound(ch) != st1.end()) str = (*st1.upper_bound(ch));
            vec1.push_back(str);
            mystruct str2{1, 1, '4'};
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

int main() {
    insert_test();
    upper_and_lower_bound_test();

    return 0;
}
