/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 8
 Due date - March 13th, 2024
 File name - Dictionary.cpp
*/

#include "Dictionary.h"
#include <stdexcept>
#include <iostream>
#include <string>

const int RED = -1;
const int BLACK = -2;

Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

Dictionary::Dictionary(const Dictionary& D) : Dictionary() {
    *this = D;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        clear();
        preOrderCopy(D.root, D.nil);
    }
    return *this;
}

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

void Dictionary::setValue(keyType k, valType v) {
    Node* X = root;
    Node* Y = nil;
    while (X != nil) {
        Y = X;
        if (k < X->key) {
            X = X->left;
        } else if (k > X->key) {
            X = X->right;
        } else {
            X->val = v;
            return;
        }
    }

    Node* Z = new Node(k, v);
    Z->parent = Y;
    if (Y == nil) {
        root = Z;
    } else if (Z->key < Y->key) {
        Y->left = Z;
    } else {
        Y->right = Z;
    }
    Z->left = nil;
    Z->right = nil;
    Z->color = RED;

    num_pairs++;
    insertFixUp(Z);
}


Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    while (R != nil && k != R->key) {
        if (k < R->key) {
            R = R->left;
        } else {
            R = R->right;
        }
    }
    return R;
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return N->val;
}

void Dictionary::insertFixUp(Node* Z) {
    while (Z != root && Z->parent->color == RED) {
        if (Z->parent == Z->parent->parent->left) {
            Node* Y = Z->parent->parent->right;
            if (Y->color == RED) {
                Z->parent->color = BLACK;
                Y->color = BLACK;
                Z->parent->parent->color = RED;
                Z = Z->parent->parent;
            } else {
                if (Z == Z->parent->right) {
                    Z = Z->parent;
                    leftRotate(Z);
                }
                Z->parent->color = BLACK;
                Z->parent->parent->color = RED;
                rightRotate(Z->parent->parent);
            }
        } else {
            Node* Y = Z->parent->parent->left;
            if (Y->color == RED) {
                Z->parent->color = BLACK;
                Y->color = BLACK;
                Z->parent->parent->color = RED;
                Z = Z->parent->parent;
            } else {
                if (Z == Z->parent->left) {
                    Z = Z->parent;
                    rightRotate(Z);
                }
                Z->parent->color = BLACK;
                Z->parent->parent->color = RED;
                leftRotate(Z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::leftRotate(Node* X) {
    Node* Y = X->right;
    X->right = Y->left;
    if (Y->left != nil) {
        Y->left->parent = X;
    }
    Y->parent = X->parent;
    if (X->parent == nil) {
        root = Y;
    } else if (X == X->parent->left) {
        X->parent->left = Y;
    } else {
        X->parent->right = Y;
    }
    Y->left = X;
    X->parent = Y;
}

void Dictionary::rightRotate(Node* X) {
    Node* Y = X->left;
    X->left = Y->right;
    if (Y->right != nil) {
        Y->right->parent = X;
    }
    Y->parent = X->parent;
    if (X->parent == nil) {
        root = Y;
    } else if (X == X->parent->right) {
        X->parent->right = Y;
    } else {
        X->parent->left = Y;
    }
    Y->right = X;
    X->parent = Y;
}

void Dictionary::remove(keyType k) {
    Node* Z = search(root, k);
    if (Z == nil) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    bool isCurrentAffected = (hasCurrent() && currentKey() == k);

    Node* Y = Z;
    Node* X;
    int originalColor = Y->color;

    if (Z->left == nil) {
        X = Z->right;
        RB_Transplant(Z, Z->right);
    } else if (Z->right == nil) {
        X = Z->left;
        RB_Transplant(Z, Z->left);
    } else {
        Y = findMin(Z->right);
        originalColor = Y->color;
        X = Y->right;

        if (Y->parent == Z) {
            X->parent = Y;
        } else {
            RB_Transplant(Y, Y->right);
            Y->right = Z->right;
            Y->right->parent = Y;
        }

        RB_Transplant(Z, Y);
        Y->left = Z->left;
        Y->left->parent = Y;
        Y->color = Z->color;
    }

    delete Z;
    if (originalColor == BLACK) {
        RB_DeleteFixUp(X);
    }

    num_pairs--;
    if (isCurrentAffected) {
        if (current != nil && current == X) {
        } else {
            current = (X != nil && X != root) ? X : nil;
            if (current != nil) {
                Node* successor = findNext(current);
                current = (successor != nil) ? successor : current;
            }
        }
    }
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* X) {
    while (X != root && X->color == BLACK) {
        if (X == X->parent->left) {
            Node* W = X->parent->right;
            if (W->color == RED) {
                W->color = BLACK;
                X->parent->color = RED;
                leftRotate(X->parent);
                W = X->parent->right;
            }
            if (W->left->color == BLACK && W->right->color == BLACK) {
                W->color = RED;
                X = X->parent;
            } else {
                if (W->right->color == BLACK) {
                    W->left->color = BLACK;
                    W->color = RED;
                    rightRotate(W);
                    W = X->parent->right;
                }
                W->color = X->parent->color;
                X->parent->color = BLACK;
                W->right->color = BLACK;
                leftRotate(X->parent);
                X = root;
            }
        } else {
            Node* W = X->parent->left;
            if (W->color == RED) {
                W->color = BLACK;
                X->parent->color = RED;
                rightRotate(X->parent);
                W = X->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK) {
                W->color = RED;
                X = X->parent;
            } else {
                if (W->left->color == BLACK) {
                    W->right->color = BLACK;
                    W->color = RED;
                    leftRotate(W);
                    W = X->parent->left;
                }
                W->color = X->parent->color;
                X->parent->color = BLACK;
                W->left->color = BLACK;
                rightRotate(X->parent);
                X = root;
            }
        }
    }
    X->color = BLACK;
}

void Dictionary::begin() {
    if (root != nil) {
        current = findMin(root);
    } else {
        current = nil;
    }
}

void Dictionary::end() {
    if (root != nil) {
        current = findMax(root);
    } else {
        current = nil;
    }
}

void Dictionary::next() {
    if (!hasCurrent()) throw std::logic_error("Dictionary: next(): current undefined");
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) throw std::logic_error("Dictionary: prev(): current undefined");
    current = findPrev(current);
}

Dictionary::Node* Dictionary::findMin(Node* R)  {
    while (R->left != nil) R = R->left;
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R)  {
    while (R->right != nil) R = R->right;
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) return findMin(N->right);

    Node* P = N->parent;
    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

Dictionary::Node* Dictionary::findPrev(Node* N)  {
    if (N->left != nil) return findMax(N->left);

    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (this->num_pairs != D.num_pairs) return false;
    return this->to_string() == D.to_string();
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}
bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) throw std::logic_error("Dictionary: currentKey(): current undefined");
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) throw std::logic_error("Dictionary: currentVal(): current undefined");
    return current->val;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key + (R->color == RED ? " (RED)" : "") + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}
