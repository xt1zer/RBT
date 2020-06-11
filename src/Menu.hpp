#pragma once
#include <iostream>
#include <fstream>
#include "RBT.hpp"
#include "clearScreen.hpp"
using std::cout;

void load(RBT& tree) {
    std::ifstream inFile("tree.txt");

    int i = 0;
    while (!inFile.is_open()) {
        if (i > 2) {
            cout << "File failed to open, probably not found, idk\n";
            return;
        }
        cout << "File didn't open, give me just a bit\n";
        inFile.open("tree.txt", std::ios::in);
        ++i;
    }

    int value;
    while (inFile >> value)
        tree.add(value);
    inFile.close();
}

void saveTraversals(RBT& tree) {
    std::ofstream outFile("output.txt");

    while (!outFile.is_open()) {
        cout << "File didn't open, give me just a bit\n";
        outFile.open("output", std::ios::out);
    }
    outFile << "Pre-order (NLR): " << tree.preOrderTraversal() << "\n";
    outFile << "In-order (LNR): " << tree.inOrderTraversal() << "\n";
    outFile << "Post-order (LRN): " << tree.postOrderTraversal() << "\n";
    outFile << "Breadth-first: " << tree.breadthTraversal() << "\n";
    outFile.close();
}

void choice(const int &c, RBT &tree) {
    clearScreen();

    switch (c) {
        case 0:
        {
            if (tree.isEmpty())
                cout << "Tree is empty\n\n";
            else {
                cout << "Pre-order (NLR): " << tree.preOrderTraversal() << "\n";
                cout << "In-order (LNR): " << tree.inOrderTraversal() << "\n";
                cout << "Post-order (LRN): " << tree.postOrderTraversal() << "\n";
                cout << "Breadth-first: " << tree.breadthTraversal() << "\n\n";
            }
            break;
        }

        case 1:
        {
            int value;
            cout << "Enter value: ";
            std::cin >> value;
            tree.add(value);
            cout << "Value pushed\n\n";
            break;
        }

        case 2:
        {
            if (tree.isEmpty())
                cout << "Tree is empty\n\n";
            else {
                int value;
                cout << "Enter value: ";
                std::cin >> value;

                if (tree.remove(value) == 1)
                    cout << "Value not found\n\n";
                else
                    cout << "Value deleted\n\n";
            }
            break;
        }

        case 3:
        {
            if (tree.isEmpty())
                cout << "Tree is empty\n\n";
            else {
                int value;
                cout << "Enter value: ";
                std::cin >> value;

                if (!tree.find(value))
                    cout << "Value not found\n\n";
                else
                    cout << "Value " << value << " found\n\n";
            }
            break;
        }

        case 4:
        {
            if (tree.isEmpty())
                cout << "Tree is empty\n\n";
            else {
                cout << "Tree height = " << tree.getHeight() << "\n\n";
            }
            break;
        }

        case 5:
        {
            if (tree.isEmpty())
                cout << "Tree is empty\n\n";
            else {
                cout << "Tree black depth = " << tree.getBlackDepth() << "\n\n";
            }
            break;
        }

        case 6:
        {
            tree.clear();
            cout << "Tree cleared\n\n";
            break;
        }

        case 7:
        {
            if (tree.isEmpty())
                cout << "Tree is empty\n\n";
            else
                cout << "Tree is not empty\n\n";
            break;
        }

        case 8:
        {
            if (!tree.isEmpty())
                tree.clear();
            load(tree);
            cout << "Tree created from tree.txt\n\n";
            break;
        }

        case 9:
        {
            saveTraversals(tree);
            cout << "Traversals saved to output.txt\n\n";
            break;
        }
    }
}

void menu(RBT &tree) {
    short int c;
    while (true) {
        cout << "Options:\n\n";
        cout << "0. Print all traversals\n";
        cout << "1. Add value\n";
        cout << "2. Delete value\n";
        cout << "3. Find element by key\n";
        cout << "4. Get height of tree\n";
        cout << "5. Get black depth of tree\n";
        cout << "6. Clear tree\n";
        cout << "7. Check if empty\n";
        cout << "8. Load from tree.txt\n";
        cout << "9. Save traversals to output.txt\n";

        std::cin >> c;

        choice(c, tree);
    }
}

