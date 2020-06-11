#pragma once
#include <string>
using std::string;

enum Colour {
    black, red
};

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Colour colour;

    Node(const int& value);

    Node(const int& k, Node* l, Node* r, Node* p, const Colour& c) :
    key(k), left(l), right(r), parent(p), colour(c) {
    }
};

class RBT {
private:
    static Node* root;

    string r_PreOrderTraversal(const Node* anode, string& output) const;
    string r_InOrderTraversal(const Node* anode, string& output) const;
    string r_PostOrderTraversal(const Node* anode, string& output) const;

    void leftRotation(Node* anode);
    void rightRotation(Node* anode);
    void addFixup(Node* anode);
    void removeFixup(Node* anode);

public:
    ~RBT();

    Node* add(const int& value);

    int remove(const int& value);

    int getBlackDepth(const Node* anode = root) const;

    int getHeight(const Node* anode = root) const;

    Node* find(const int& value) const;

    // NLR
    string preOrderTraversal(const Node* anode = root) const;

    // LNR
    string inOrderTraversal(const Node* anode = root) const;

    // LRN
    string postOrderTraversal(const Node* anode = root) const;

    string breadthTraversal(Node* anode = root) const;

    void clear();

    bool isEmpty() const;
};
