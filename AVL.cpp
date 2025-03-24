#include <iostream>
#include <algorithm>

#include <algorithm>
using namespace std;

template<typename T>
class AVL {
private:
    struct AvlNode {
        T element;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(const T& elem, AvlNode* lt = nullptr, AvlNode* rt = nullptr, int h = 0)
            : element(elem), left(lt), right(rt), height(h) {}
    };

    AvlNode* root;

    // Utility function to get height
    int height(AvlNode* t) const {
        return t == nullptr ? -1 : t->height;
    }

    // Utility function to update node height
    void updateHeight(AvlNode* t) {
        if (t != nullptr) {
            t->height = max(height(t->left), height(t->right)) + 1;
        }
    }

    // Balancing function
    AvlNode* balance(AvlNode* t) {
        if (t == nullptr) return t;

        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right))
                t = rotateWithLeftChild(t);
            else
                t = doubleWithLeftChild(t);
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left))
                t = rotateWithRightChild(t);
            else
                t = doubleWithRightChild(t);
        }

        updateHeight(t);
        return t;
    }

    // Single rotation with left child
    AvlNode* rotateWithLeftChild(AvlNode* k2) {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        updateHeight(k2);
        updateHeight(k1);
        return k1;
    }

    // Single rotation with right child
    AvlNode* rotateWithRightChild(AvlNode* k1) {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        updateHeight(k1);
        updateHeight(k2);
        return k2;
    }

    // Double rotation: left-right
    AvlNode* doubleWithLeftChild(AvlNode* k3) {
        k3->left = rotateWithRightChild(k3->left);
        return rotateWithLeftChild(k3);
    }

    // Double rotation: right-left
    AvlNode* doubleWithRightChild(AvlNode* k1) {
        k1->right = rotateWithLeftChild(k1->right);
        return rotateWithRightChild(k1);
    }

    // Internal insert
    AvlNode* insert(const T& x, AvlNode* t) {
        if (t == nullptr)
            return new AvlNode(x);

        if (x < t->element)
            t->left = insert(x, t->left);
        else if (x > t->element)
            t->right = insert(x, t->right);
        else
            ; // Duplicate, do nothing

        return balance(t);
    }

public:
    AVL() : root(nullptr) {}

    void insert(const T& x) {
        root = insert(x, root);
    }

    // TODO: add remove(), contains(), print(), etc. as needed
};