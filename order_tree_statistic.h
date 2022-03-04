#pragma once
#include <random>
#include <functional>
#include <algorithm>

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
            prior = rand(); // fix random
        }

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

    static int size(tree_node* v) {
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
    tree_node* insert(tree_node* root, _key key) {
        if (!root) return (new tree_node(key));

        if (!(compare(key, root->key) | compare(root->key, key))) return root;
        if (compare(key, root->key)) {
            root->l = insert(root->l, key);

            if (root->l->prior > root->prior) root = rightRotate(root);
        } else {
            root->r = insert(root->r, key);

            if (root->r->prior > root->prior) root = leftRotate(root);
        }

        root->update_node();
        return root;
    }

    /* Recursive implementation of Delete() */
    tree_node* deleteNode(tree_node* root, _key key) {
        if (!root) return root;

        // IF KEYS IS NOT AT ROOT
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

            // IF KEY IS AT ROOT

            // If left is NULL
        else if (root->left == NULL)
        {
            tree_node *temp = root->right;
            delete(root);
            root = temp; // Make right child as root
        }

            // If Right is NULL
        else if (root->right == NULL)
        {
            tree_node *temp = root->left;
            delete(root);
            root = temp; // Make left child as root
        }

            // If key is at root and both left and right are not NULL
        else if (root->left->priority < root->right->priority)
        {
            root = leftRotate(root);
            root->left = deleteNode(root->left, key);
        }
        else
        {
            root = rightRotate(root);
            root->right = deleteNode(root->right, key);
        }

        return root;
    }


    /*
        This template function returns the pointer to the node with value in it equal to _key value if it exists.
        If such node does not exist then the function returns the pointer to node
        with the largest value which does not exceed _key value or
        to node with the smallest value which exceed _key value.
    */

    tree_node* find(tree_node* v, _key value) const {
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

    // returns index of value in set if value exists
    static int get_index(tree_node* v, _key value, std::function<bool(_key, _key)> compare) {
        int ind = 0;
        while (v->key != value) {
            if (compare(v->key, value)) {
                if (!v->r) break;
                ind += size(v->l) + 1;
                v = v->r;
            } else {
                if (!v->l) break;
                v = v->l;
            }
        }

        return ind;
    }

    // returns pointer to previous element in set
    static tree_node* prev(tree_node* v, std::function<bool(_key, _key)> compare) {
        if (v->l) {
            v = v->l;
            while (v->r) v = v->r;
            return v;
        }

        _key value = v->key;
        while (!compare(v->key, value)) {
            if (!v->par) return 0;
            v = v->par;
        }

        return v;
    }

    // returns pointer to next element in set
    static tree_node* next(tree_node* v, std::function<bool(_key, _key)> compare) {
        if (v->r) {
            v = v->r;
            while (v->l) v = v->l;
            return v;
        }

        _key value = v->key;
        while (!compare(value, v->key)) {
            if (!v->par) return 0;
            v = v->par;
        }

        return v;
    }

    // returns pointer to the smallest element in set
    static tree_node* first(tree_node* v) {
        if (!v) return 0;
        while (v->l) v = v->l;
        return v;
    }

    // returns pointer to the largest element in set
    static tree_node* last(tree_node* v) {
        if (!v) return 0;
        while (v->r) v = v->r;
        return v;
    }

    // clears the tree
    void destruct_tree(tree_node* v) {
        if (v->l) destruct_tree(v->l);
        if (v->r) destruct_tree(v->r);

        delete v;
    }

    tree_node* root = nullptr;
public:
    explicit order_statistic_tree(std::function<bool(_key, _key)> compare_ = std::less<_key>()) : compare(compare_) { }

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

    void swap(order_statistic_tree<_key> rt) {
        throw std::exception();
    }

    void clear() {
        if (root) destruct_tree(root);

        root = nullptr;
    }

    bool contains(_key value) const {
        if (!root) return 0;

        return !(compare(find(root, value)->key, value) | compare(value, find(root, value)->key));
    }

    void insert(_key value) {
        root = insert(root, value);
    }

    template<bool isReversed>
    class BaseIterator {
    private:
        //using curT = std::conditional_t<isConst, const T, T>;
        //using curTRef = std::conditional_t<isConst, const T&, T&>;
        //using curTPtr = std::conditional_t<isConst, const T*, T*>;

        tree_node* ptr;
        const std::function<bool(_key, _key)> compare;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = _key;
        using reference = _key&;
        using pointer = _key*;
        using difference_type = std::ptrdiff_t;

        explicit BaseIterator(tree_node* ptr, std::function<bool(_key, _key)> compare) : ptr(ptr), compare(compare) {}

        template<bool isReversedOther>
        explicit BaseIterator(const BaseIterator<isReversedOther>& other) : ptr(other.getPtr()), compare(other.compare()) {}

        BaseIterator& operator = (const BaseIterator& other) {
            ptr = other.ptr;
            return *this;
        }

        BaseIterator& operator - (const BaseIterator& other) {
            int lst = size();
            if (ptr != 0) lst = get_index(this->tree->root, ptr->key, compare);
            int fst = size();
            if (other.ptr != 0) fst = get_index(other.tree->root, other.ptr->key, other.compare);

            return lst - fst;
        }

        /*BaseIterator& operator+=(int add) {
            int cur = size();
            if (ptr != 0) cur = get_index(tree->root, ptr->key, tree->compare);
            if (!isReversed)
                ptr = next(ptr, tree->compare);
            else
                ptr = prev(ptr, tree->compare);

            return *this;
        }*/

        BaseIterator& operator++() {
            if (!isReversed)
                ptr = next(ptr, compare);
            else
                ptr = prev(ptr, compare);

            return *this;
        }

        BaseIterator& operator--() {
            if (ptr == 0) {
                if (!isReversed)
                    ptr = last()
            }
            if (!isReversed)
                ptr = prev(ptr, compare);
            else
                ptr = next(ptr, compare);

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

    const_iterator begin() const {
        return BaseIterator<0>(first(root), compare);
    }

    const_reverse_iterator rbegin() const {
        return BaseIterator<1>(last(root), compare);
    }

    const_iterator end() const {
        return BaseIterator<0>(nullptr, compare);
    }

    const_reverse_iterator rend() const {
        return BaseIterator<1>(nullptr, compare);
    }

    bool operator==(const order_statistic_tree& rhs) {
        return rhs.root = root;
    }

    const_iterator find(_key value) {
        if (root == 0) return BaseIterator<0>(nullptr, compare);
        tree_node* v = find(root, value);
        if (!(compare(v->key, value) | compare(value, v->key))) return BaseIterator<0>(v, compare);
        return BaseIterator<0>(nullptr, compare);
    }

    void erase(_key a) {
        node_pair q = split(root, a);
        node_pair q2 = spliteq(q.second, a);
        root = merge(q.first, q2.second);
    }

    void erase(const const_iterator& a) {
        if (a.getPtr() == 0) {
            const std::string err = __func__;
            throw std::invalid_argument(err +  + " received iterator to an empty node.");
        }
        erase(a.getPtr()->key);
    }

    const_iterator lower_bound(_key a) {
        const_iterator v = BaseIterator<0>(find(root, a), compare);
        if (v != end() && compare((*v), a)) {
            v++;
        }
        return v;
    }

    const_iterator upper_bound(_key a) {
        const_iterator v = BaseIterator<0>(find(root, a), compare);
        if (v != end() && (!compare(a, *v))) {
            v++;
        }
        return v;
    }

    const_iterator statistic(int k) {
        if (k >= size()) return BaseIterator<0>(nullptr, compare);
        ++k;

        tree_node* v = root;
        while (k != 0) {
            if (size(v->l) + 1 < k) {
                k -= size(v->l) + 1;
                v = v->r;
            } else if (size(v->l) + 1 == k) {
                k = 0;
            } else {
                v = v->l;
            }
        }

        return BaseIterator<0>(v, compare);
    }
};
