#pragma once
#include <random>
#include <functional>
#include <algorithm>

template<typename _key>
class order_statistic_tree {
private:
    std::function<bool(_key, _key)> compare;

    class tree_node {
    public:
        _key key;
        int prior, size = 1;
        tree_node* l = nullptr, * r = nullptr, * par = nullptr;

        tree_node(_key k) {
            key = k;
            prior = rand();
        }

        tree_node() {}

        // fixed sizes of current vertex and parents of adjacent vertices
        void update_node() {
            size = 1;

            par = 0;
            if (l) {
                l->par = this;
                size += l->size;
            }
            if (r) {
                r->par = this;
                size += r->size;
            }
        }
    };

    using node_pair = std::pair<tree_node*, tree_node*>;

    // -------------------------- tree_node helper functions -----------------

    static size_t size(tree_node* v) {
        return v ? v->size : 0;
    }

    // fixes priorities if priority of v->l is larger than priority of v
    tree_node* rightRotate(tree_node* v) {
        tree_node* x = v->l;

        v->l = x->r;
        x->r = v;
        v->update_node();
        x->update_node();

        return x;
    }

    // fixes priorities if priority of v->r is larger than priority of v
    tree_node* leftRotate(tree_node* v) {
        tree_node* x = v->r;

        v->r = x->l;
        x->l = v;
        v->update_node();
        x->update_node();

        return x;
    }

    // splits the tree by given key with less comparator
    node_pair split(tree_node* v, _key value) {
        if (!v) return { nullptr, nullptr };

        if (compare(v->key, value)) {
            node_pair res = split(v->r, value);
            v->r = res.first;
            v->update_node();
            return { v, res.second };
        } else {
            node_pair res = split(v->l, value);
            v->l = res.second;
            v->update_node();
            return { res.first, v };
        }
    }

    // splits the tree by given key with less or equal comparator
    node_pair spliteq(tree_node* v, _key value) {
        if (!v) return { nullptr, nullptr };

        if (!compare(value, v->key)) {
            node_pair res = spliteq(v->r, value);
            v->r = res.first;
            v->update_node();
            return { v, res.second };
        } else {
            node_pair res = spliteq(v->l, value);
            v->l = res.second;
            v->update_node();
            return { res.first, v };
        }
    }

    // merges two trees such that all keys in l are smaller than keys in r
    tree_node* merge(tree_node* l, tree_node* r) {
        if (!l) return r;
        if (!r) return l;

        if (l->prior < r->prior) {
            l->r = merge(l->r, r);
            l->update_node();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->update_node();
            return r;
        }
    }

    // Recursive implementation of insertion in Treap using rotation
    tree_node* insert(tree_node* v, _key key) {
        if (!v) return (new tree_node(key));

        if (!(compare(key, v->key) | compare(v->key, key))) return v;
        if (compare(key, v->key)) {
            v->l = insert(v->l, key);

            if (v->l->prior > v->prior) v = rightRotate(v);
        } else {
            v->r = insert(v->r, key);

            if (v->r->prior > v->prior) v = leftRotate(v);
        }

        v->update_node();
        return v;
    }

    /*
        This template function returns the pointer to the node with value in it equal to _key value if it exists.
        If such node does not exist then the function returns the pointer to node
        with the largest value which does not exceed _key value or
        to node with the smallest value which exceed _key value.
    */

    tree_node* find(tree_node* v, _key value) const {
        if (v == 0) return endnode;
        while (compare(v->key, value) | compare(value, v->key)) {
            if (compare(v->key, value)) {
                if (!v->r) break;
                v = v->r;
            } else {
                if (!v->l) break;
                v = v->l;
            }
        }
        return v;
    }

    // clears the tree
    void destruct_tree(tree_node* v) {
        if (v->l) destruct_tree(v->l);
        if (v->r) destruct_tree(v->r);

        delete v;
    }

    void upd_end() {
        endnode->l = root;
        endnode->r = root;
    }

    tree_node* root = nullptr;
    tree_node* endnode = nullptr;
public:
    explicit order_statistic_tree(std::function<bool(_key, _key)> compare_ = std::less<_key>()) : compare(compare_) {
        endnode = new tree_node();
        endnode->l = root;
        endnode->r = root;
    }

    [[nodiscard]] bool empty() const {
        return (root == nullptr);
    }

    [[nodiscard]] size_t size() const {
        return root ? root->size : 0;
    }

    std::function<bool(_key, _key)> key_comp() const {
        return compare;
    };

    tree_node* get_root() const {
        return root;
    }
    tree_node* get_end_node() const {
        return endnode;
    }

    void change_root(tree_node* rt) {
        root = rt;
    }

    void change_end_node(tree_node* nd) {
        endnode = nd;
    }

    void swap(order_statistic_tree<_key>& rt) {
        tree_node* v = root;
        tree_node* nd = endnode;

        std::swap(root, rt.root);
        std::swap(endnode, rt.endnode);
        std::swap(compare, rt.compare);
    }

    // clears the tree and used memory
    void clear() {
        if (root) destruct_tree(root);

        root = nullptr;
        upd_end();
    }

    // checks whenever value is contained in the tree
    bool contains(_key value) const {
        if (!root) return 0;

        _key k = find(root, value)->key;
        return !(compare(k, value) | compare(value, k));
    }

    void insert(_key value) {
        root = insert(root, value);

        upd_end();
    }

    template<bool isReversed>
    class BaseIterator {
    private:
        tree_node* ptr, * endnode;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = _key;
        using reference = _key&;
        using pointer = _key*;
        using difference_type = std::ptrdiff_t;

        explicit BaseIterator(tree_node* ptr, tree_node* endnode) : ptr(ptr), endnode(endnode) {}

        template<bool isReversedOther>
        explicit BaseIterator(const BaseIterator<isReversedOther>& other) : ptr(other.getPtr()), endnode(other.endnode) {}

        // returns index of value in set if value exists
        int get_index(tree_node* v) {
            if (v == endnode) return size(v->l);
            int ind = size(v->l);
            while (v->par) {
                if (v->par->r == v) {
                    ind += size(v->par->l) + 1;
                }

                v = v->par;
            }

            return ind;
        }

        tree_node* next(tree_node* v) {
            if (v->r) {
                v = v->r;
                while (v->l) v = v->l;
                return v;
            }

            tree_node* pr = v;
            while (v->l != pr) {
                if (!v->par) return 0;
                pr = v;
                v = v->par;
            }

            return v;
        }

        tree_node* prev(tree_node* v) {
            if (v->l) {
                v = v->l;
                while (v->r) v = v->r;
                return v;
            }

            tree_node* pr = v;
            while (v->r != pr) {
                if (!v->par) return 0;
                pr = v;
                v = v->par;
            }

            return v;
        }

        void descendLeft() {
            while (ptr->l) ptr = ptr->l;
        }

        void descendRight() {
            while (ptr->r) ptr = ptr->r;
        }

        BaseIterator& operator = (const BaseIterator& other) {
            ptr = other.ptr;
            endnode = other.endnode;
            return *this;
        }

        int operator - (const BaseIterator& other) {
            tree_node* root = this->endnode->l;
            int lst = root ? root->size : 0;
            if (ptr != endnode) lst = get_index(ptr);
            int fst = lst;
            tree_node* root2 = other.endnode->l;
            if (other.ptr != endnode) fst = get_index(other.ptr);

            return lst - fst;
        }

        BaseIterator& operator+=(int add) {
            if (isReversed) add = -add;
            int cur = size(endnode->r);
            if (ptr != endnode) cur = get_index(ptr);

            int nd = add + cur;
            if (nd < 0 || nd >= size(endnode->r)) nd = size(endnode->r);

            auto it = endnode->r;

            ptr = stat(nd);

            return *this;
        }

        BaseIterator& operator+(int add) {
            if (isReversed) add = -add;
            int cur = size(endnode->r);
            if (ptr != endnode) cur = get_index(ptr);

            int nd = add + cur;
            if (nd < 0 || nd >= size(endnode->r)) nd = size(endnode->r);

            auto it = endnode->r;

            return BaseIterator<isReversed>(stat(nd), endnode, compare);
        }

        BaseIterator& operator-(int add) {
            if (isReversed) add = -add;
            int cur = size(endnode->r);
            if (ptr != endnode) cur = get_index(ptr);

            int nd = add + cur;
            if (nd < 0 || nd >= size(endnode->r)) nd = size(endnode->r);

            auto it = endnode->r;

            return BaseIterator<isReversed>(stat(nd), endnode, compare);
        }

        BaseIterator& operator-=(int add) {
            if (isReversed) add = -add;
            int cur = size(endnode->r);
            if (ptr != endnode) cur = get_index(ptr);

            int nd = cur - add;
            if (nd < 0 || nd >= size(endnode->r)) nd = size(endnode->r);

            auto it = endnode->r;

            ptr = stat(nd);

            return *this;
        }

        void changePtr(tree_node* t) {
            ptr = t;
        }

        // ordered statistic implementation
        tree_node* stat(int nd) {
            if (nd >= size(endnode->r)) return endnode;
            ++nd;

            tree_node* v = endnode->r;
            while (nd != 0) {
                if (size(v->l) + 1 < nd) {
                    nd -= size(v->l) + 1;
                    v = v->r;
                } else if (size(v->l) + 1 == nd) {
                    nd = 0;
                } else {
                    v = v->l;
                }
            }

            return v;
        }

        BaseIterator& operator++() {
            if (ptr == endnode) {
                if (!isReversed) {
                    descendLeft();
                } else {
                    descendRight();
                }

                if (ptr == 0) ptr = endnode;
                return *this;
            }
            if (!isReversed)
                ptr = next(ptr);
            else
                ptr = prev(ptr);

            if (ptr == 0) ptr = endnode;

            return *this;
        }

        BaseIterator& operator--() {
            if (ptr == endnode) {
                if (isReversed) {
                    descendLeft();
                } else {
                    descendRight();
                }

                if (ptr == 0) ptr = endnode;
                return *this;
            }

            if (!isReversed)
                ptr = prev(ptr);
            else
                ptr = next(ptr);

            if (ptr == 0) ptr = endnode;

            return *this;
        }

        BaseIterator operator++(int) {
            BaseIterator ans = *this;
            ++(*this);
            return ans;
        }

        BaseIterator operator--(int) {
            BaseIterator ans = *this;
            --(*this);
            return ans;
        }

        bool operator == (const BaseIterator<isReversed>& other) {
            return ptr == other.getPtr();
        }

        bool operator != (const BaseIterator<isReversed>& other) {
            return ptr != other.getPtr();
        }

        _key operator* () const {
            return ptr->key;
        }

        tree_node* getPtr() const {
            return ptr;
        }
    };

    using const_iterator = BaseIterator<false>;
    using const_reverse_iterator = BaseIterator<true>;
    using iterator = BaseIterator<0>;
    using reverse_iterator = BaseIterator<1>;

    // returns pointer to the smallest element in set
    tree_node* first(tree_node* v) const {
        if (!v) return 0;
        while (v->l) v = v->l;
        return v;
    }

    // returns pointer to the largest element in set
    tree_node* last(tree_node* v) const {
        if (!v) return 0;
        while (v->r) v = v->r;
        return v;
    }

    const_iterator begin() const {
        return iterator((root ? first(root) : endnode), endnode);
    }

    const_reverse_iterator rbegin() const {
        return reverse_iterator((root ? last(root) : endnode), endnode);
    }

    const_iterator end() const {
        return iterator(endnode, endnode);
    }

    const_reverse_iterator rend() const {
        return reverse_iterator(endnode, endnode);
    }

    bool operator==(const order_statistic_tree& rhs) {
        return rhs.root = root;
    }

    const_iterator find(_key value) {
        if (root == 0) return end();
        tree_node* v = find(root, value);
        if (!(compare(v->key, value) | compare(value, v->key))) return iterator(v, endnode);
        return end();
    }

    void erase(_key a) {
        node_pair q = split(root, a);
        node_pair q2 = spliteq(q.second, a);
        root = merge(q.first, q2.second);

        upd_end();
    }

    void erase(const const_iterator& a) {
        if (a.getPtr() == 0) {
            const std::string err = __func__;
            throw std::invalid_argument(err + +" received iterator to an empty node.");
        }
        erase(a.getPtr()->key);
    }

    const_iterator lower_bound(_key a) const {
        const_iterator v = iterator(find(root, a), endnode);
        if (v != end() && compare((*v), a)) {
            v++;
        }
        return v;
    }

    const_iterator upper_bound(_key a) const {
        const_iterator v = iterator(find(root, a), endnode);
        if (v != end() && (!compare(a, *v))) {
            v++;
        }
        return v;
    }

    // ordered statistic implementation
    const_iterator statistic(int k) {
        if (k >= size()) return end();

        const_iterator v = const_iterator(endnode, endnode);
        v.changePtr(v.stat(k));
        return v;
    }
};
