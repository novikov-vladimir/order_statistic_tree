#pragma once
#include <random>
#include <functional>

template<typename _key>
class order_statistic_tree {
private:
    const std::function<bool(_key, _key)> compare;

    class tree_node {
    public:
        _key key;
        int prior, size = 1;
        tree_node* l = nullptr, * r = nullptr, * par = nullptr;

        tree_node(_key k) {
            key = k;
            prior = rand();
        }

        void update_node() {
            size = 1 + ((l) ? l->size : 0) + ((r) ? r->size : 0);

            if (l) l->par = this;
            if (r) r->par = this;
        }
    };

    typedef std::pair<tree_node*, tree_node*> node_pair;

    // -------------------------- tree_node helper functions -----------------

    tree_node* rightRotate(tree_node* y)
    {
        tree_node* x = y->l, * T2 = x->r;

        x->r = y;
        y->l = T2;

        return x;
    }

    tree_node* leftRotate(tree_node* x)
    {
        tree_node* y = x->r, * T2 = y->l;

        y->l = x;
        x->r = T2;

        return y;
    }

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

    node_pair spliteq(tree_node* v, _key value) {
        if (!v) return { nullptr, nullptr };

        if (!compare(value, v->key)) {
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

    /* Recursive implementation of insertion in Treap */
    tree_node* insert(tree_node* root, _key key)
    {
        // If root is NULL, create a new node and return it
        if (!root)
            return (new tree_node(key));

        // If key is smaller than root
        if (key == root->key) return root;

        if (compare(key, root->key))
        {
            // Insert in left subtree
            root->l = insert(root->l, key);

            // Fix Heap property if it is violated
            if (root->l->prior > root->prior)
                root = rightRotate(root);
        } else // If key is greater
        {
            // Insert in right subtree
            root->r = insert(root->r, key);

            // Fix Heap property if it is violated
            if (root->r->prior > root->prior)
                root = leftRotate(root);
        }
        return root;
    }


    /*
        This template function returns the pointer to the node with value in it equal to _key value if it exists.
        If such node does not exist then the function returns the pointer to node
        with the largest value which does not exceed _key value or
        to node with the smallest value which exceed _key value.
    */

    tree_node* find(tree_node* v, _key value) const { // the function
        while (v->key != value) {
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

    static tree_node* prev(tree_node* v) {
        if (v->l) {
            v = v->l;
            while (v->r) v = v->r;
            return v;
        }

        _key value = v->key;
        while (!(v->key < value)) { // fix this shit
            if (!v->par) return 0;
            v = v->par;
        }

        return v;
    }

    static tree_node* next(tree_node* v) {
        if (v->r) {
            v = v->r;
            while (v->l) v = v->l;
            return v;
        }

        _key value = v->key;
        while (!(value < v->key)) { // fix this shit
            if (!v->par) return 0;
            v = v->par;
        }

        return v;
    }

    static tree_node* first(tree_node* v) {
        while (v->l) v = v->l;
        return v;
    }

    static tree_node* last(tree_node* v) {
        while (v->r) v = v->r;
        return v;
    }

    void destruct_tree(tree_node* v) { // clears the tree
        if (v->l) destruct_tree(v->l);
        if (v->r) destruct_tree(v->r);

        delete v;
    }

    tree_node* root = nullptr;
public:
    order_statistic_tree(std::function<bool(_key, _key)> compare_ = std::less<_key>()) : compare(compare_) { }

    bool empty() const {
        return (root == nullptr);
    }

    int size() const {
        return root ? root->get_size() : 0;
    }

    std::function<bool(_key, _key)> key_comp() const {
        return compare;
    };

    void swap(order_statistic_tree<_key> rt) { // probably this function should be rewritten
        swap(root, rt->root);
        swap(compare, rt->compare); //check if it works in O(1)
    }

    void clear() {
        if (root) destruct_tree(root);

        root = nullptr;
    }

    bool contains(_key value) const {
        if (!root) return 0;

        return find(root, value)->key == value;
    }

    void insert(_key value) {
        root = insert(root, value);
    }

    /*
     void insert(_key value) {
        if (contains(value)) return;

        node_pair p = split(root, value);
        tree_node* to_insert = new tree_node(value);
        root = merge(merge(p.first, to_insert), p.second);
    }
     */

    template<bool isReversed>
    class BaseIterator {
    private:
        tree_node* ptr;

    public:
        BaseIterator(tree_node* ptr = nullptr) : ptr(ptr) {}

        template<bool isReversedOther>
        BaseIterator(const BaseIterator<isReversedOther>& other) : ptr(other.getPtr()) {}

        BaseIterator& operator = (const BaseIterator& other) {
            ptr = other.ptr;
            return *this;
        }

        BaseIterator& operator++() {
            if (!isReversed)
                ptr = next(ptr);
            else
                ptr = prev(ptr);

            return *this;
        }

        BaseIterator& operator--() {
            if (!isReversed)
                ptr = prev(ptr);
            else
                ptr = next(ptr);

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

        template<bool isReversedOther>
        bool operator == (const BaseIterator<isReversedOther>& other) {
            return ptr == other.getPtr();
        }

        template<bool isReversedOther>
        bool operator != (const BaseIterator<isReversedOther>& other) {
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

    const_iterator begin() const {
        return first(root);
    }

    const_reverse_iterator rbegin() const {
        return last(root);
    }

    const_reverse_iterator rend() const {
        return 0;
    }

    const_iterator end() const {
        return 0;
    }

    bool operator==(const order_statistic_tree& rhs) {
        return rhs.root = root;
    }

    const_iterator find(_key value) {
        if (root == 0) return 0;
        tree_node* v = find(root, value);
        if (v->key == value) return v;
        return 0;
    }

    void erase(_key a) {
        node_pair q = split(root, a);
        node_pair q2 = spliteq(q.second, a);
        root = merge(q.first, q2.second);
    }

    void erase(const_iterator a) {
        erase(a->ptr->key);
    }

    const_iterator lower_bound(_key a) {
        const_iterator v = find(root, a);
        if (v != end() && compare((*v), a)) {
            v++;
        }
        return v;
    }

    const_iterator upper_bound(_key a) {
        const_iterator v = find(root, a);
        if (v != end() && (compare((*v), a) || (*v) == a)) {
            v++;
        }
        return v;
    }
};
