#include <queue>
#include "RBT.hpp"

#define NIL &sentinel

Node sentinel(0, NIL, NIL, nullptr, Colour::black);

Node::Node(const int& value) : key(value), left(NIL), right(NIL), parent(nullptr),
colour(Colour::red) { }

Node* RBT::root = NIL;

void RBT::leftRotation(Node* anode) {
    Node* r = anode->right;

    anode->right = r->left;
    if (r->left != NIL)
        r->left->parent = anode;

    if (r != NIL)
        r->parent = anode->parent;
    if (/*anode && */anode->parent) {
        if (anode == anode->parent->left)
            anode->parent->left = r;
        else
            anode->parent->right = r;
    } else
        root = r;

    r->left = anode;
    if (anode != NIL)
        anode->parent = r;
}

void RBT::rightRotation(Node* anode) {
    Node* l = anode->left;

    anode->left = l->right;
    if (l->right != NIL)
        l->right->parent = anode;

    if (l != NIL)
        l->parent = anode->parent;
    if (/*anode && */anode->parent) {
        if (anode == anode->parent->right)
            anode->parent->right = l;
        else
            anode->parent->left = l;
    } else
        root = l;

    l->right = anode;
    if (anode != NIL)
        anode->parent = l;
}

int RBT::getBlackDepth(const Node* anode /* = root */) const {
    int count = 0;
    while (anode->left != NIL) {
        if (anode->colour == Colour::black)
            ++count;
        anode = anode->left;
    }
    return count + 1; // including root and leaf
}

int RBT::getHeight(const Node * anode /* = root */) const {
    if (anode == NIL)
        return -1;

    int lHeight = getHeight(anode->left);
    int rHeight = getHeight(anode->right);

    if (lHeight > rHeight)
        return lHeight + 1;
    else
        return rHeight + 1;
}

void RBT::addFixup(Node* anode) {
    while (anode != root && anode->parent->colour == Colour::red) {
        if (anode->parent == anode->parent->parent->left) {
            Node* uncle = anode->parent->parent->right;
            if (uncle->colour == Colour::red) {
                anode->parent->colour = Colour::black;
                uncle->colour = Colour::black;
                anode->parent->parent->colour = Colour::red;
                anode = anode->parent->parent;
            } else {
                if (anode == anode->parent->right) {
                    anode = anode->parent;
                    leftRotation(anode);
                }
                anode->parent->colour = Colour::black;
                anode->parent->parent->colour = Colour::red;
                rightRotation(anode->parent->parent);
            }
        } else {
            Node* uncle = anode->parent->parent->left;
            if (uncle->colour == Colour::red) {
                anode->parent->colour = Colour::black;
                uncle->colour = Colour::black;
                anode->parent->parent->colour = Colour::red;
                anode = anode->parent->parent;
            } else {
                if (anode == anode->parent->left) {
                    anode = anode->parent;
                    rightRotation(anode);
                }
                anode->parent->colour = Colour::black;
                anode->parent->parent->colour = Colour::red;
                leftRotation(anode->parent->parent);
            }
        }
    }
    root->colour = Colour::black;
}

void RBT::removeFixup(Node* anode) {
    while (anode != root && anode->colour == Colour::black) {
        if (anode == anode->parent->left) {
            Node* uncle = anode->parent->right;
            if (uncle->colour == Colour::red) {
                uncle->colour = Colour::black;
                anode->parent->colour = Colour::red;
                leftRotation(anode->parent);
                uncle = anode->parent->right;
            }
            if (uncle->left->colour == Colour::black && uncle->right->colour == Colour::black) {
                uncle->colour = Colour::red;
                anode = anode->parent;
            } else {
                if (uncle->right->colour == Colour::black) {
                    uncle->left->colour = Colour::black;
                    uncle->colour = Colour::red;
                    rightRotation(uncle);
                    uncle = anode->parent->right;
                }
                uncle->colour = anode->parent->colour;
                anode->parent->colour = Colour::black;
                uncle->right->colour = Colour::black;
                leftRotation(anode->parent);
                anode = root;
            }
        } else {
            Node* uncle = anode->parent->left;
            if (uncle->colour == Colour::red) {
                uncle->colour = Colour::black;
                anode->parent->colour = Colour::red;
                rightRotation(anode->parent);
                uncle = anode->parent->left;
            }
            if (uncle->right->colour == Colour::black && uncle->left->colour == Colour::black) {
                uncle->colour = Colour::red;
                anode = anode->parent;
            } else {
                if (uncle->left->colour == Colour::black) {
                    uncle->right->colour = Colour::black;
                    uncle->colour = Colour::red;
                    leftRotation(uncle);
                    uncle = anode->parent->left;
                }
                uncle->colour = anode->parent->colour;
                anode->parent->colour = Colour::black;
                uncle->left->colour = Colour::black;
                rightRotation(anode->parent);
                anode = root;
            }
        }
    }
    anode->colour = Colour::black;
}

Node* RBT::add(const int& value) {
    Node* current = root, *par(nullptr), *anode(nullptr);

    while (current != NIL) {
        if (value == current->key)
            return current;
        par = current;
        current = value < current->key ? current->left : current->right;
    }

    anode = new Node(value);
    anode->parent = par;

    if (par) {
        if (value < par->key)
            par->left = anode;
        else
            par->right = anode;
    } else
        root = anode;

    addFixup(anode);
    return anode;
}

int RBT::remove(const int& value) {
    Node* toDel = find(value);
    if (!toDel || toDel == NIL)
        return 1;

    Node* y, *x;
    if (toDel->left == NIL || toDel->right == NIL) {
        y = toDel;
    } else {
        y = toDel->left;
        while (y->right != NIL)
            y = y->right;
    }

    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;


    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != toDel) toDel->key = y->key;

    if (y->colour == Colour::black)
        removeFixup(x);

    delete y;
    return 0;
}

Node* RBT::find(const int& value) const {
    Node* current = root;
    while (current != NIL)
        if (value == current->key)
            return current;
        else
            current = value < current->key ? current->left : current->right;
    return nullptr;
}

// NLR

string RBT::r_PreOrderTraversal(const Node* anode /* = root */,
        string& output) const {
    if (anode != NIL) {
        output += std::to_string(anode->key) + " ";
        r_PreOrderTraversal(anode->left, output);
        r_PreOrderTraversal(anode->right, output);
    }
    return output;
}

string RBT::preOrderTraversal(const Node* anode /* = root */) const {
    if (anode == NIL) return "";
    string output = "";
    return r_PreOrderTraversal(anode, output);
}

// LNR

string RBT::r_InOrderTraversal(const Node* anode /* = root */,
        string& output) const {
    if (anode != NIL) {
        r_InOrderTraversal(anode->left, output);
        output += std::to_string(anode->key) + " ";
        r_InOrderTraversal(anode->right, output);
    }

    return output;
}

string RBT::inOrderTraversal(const Node* anode /* = root */) const {
    if (anode == NIL) return "";
    string output = "";
    return r_InOrderTraversal(anode, output);
}

// LRN

string RBT::r_PostOrderTraversal(const Node* anode /* = root */,
        string& output) const {
    if (anode != NIL) {
        r_PostOrderTraversal(anode->left, output);
        r_PostOrderTraversal(anode->right, output);
        output += std::to_string(anode->key) + " ";
    }
    return output;
}

string RBT::postOrderTraversal(const Node* anode /* = root */) const {
    if (anode == NIL) return "";
    string output = "";
    return r_PostOrderTraversal(anode, output);
}

string RBT::breadthTraversal(Node * anode /* = root */) const {
    if (anode == NIL) return "";
    string output = "";
    std::queue<Node*>* nodeQueue = new std::queue<Node*>;
    nodeQueue->push(anode);

    while (!nodeQueue->empty()) {
        if (nodeQueue->front()->left != NIL)
            nodeQueue->push(nodeQueue->front()->left);
        if (nodeQueue->front()->right != NIL)
            nodeQueue->push(nodeQueue->front()->right);
        output += std::to_string(nodeQueue->front()->key) + " ";
        nodeQueue->pop();
    }
    return output;
}

void RBT::clear() {
    while (root != NIL)
        remove(root->key);
}

RBT::~RBT() {
    clear();
}

bool RBT::isEmpty() const {
    return root == NIL;
}
