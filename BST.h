//Fowzi Hindi 33587
#ifndef BST_H
#define BST_H

#include <iostream>
#include "Stack.h"

// Implements a binary search tree (BST) for managing memory allocations.
template <typename T>
class BST {
private:
    // Represents a node in the BST.
    struct BSTNode {
        int startByte;  // Start address of the memory block.
        int size;       // Size of the memory block in bytes.
        Stack<T> stack; // Stack to manage variables within this block.

        BSTNode* left;  // Pointer to the left child (smaller addresses).
        BSTNode* right; // Pointer to the right child (larger addresses).

        // Constructor: Initializes a node with memory block details.
        BSTNode(int start, int sz) : startByte(start), size(sz), stack(start, sz), left(nullptr), right(nullptr) {}
    };

    BSTNode* root;

    // Recursively inserts a new memory block into the BST.
    BSTNode* insert(BSTNode* node, int start, int sz) {
        if (node == nullptr) {
            std::cout << "Allocated " << sz << " bytes starting at byte " << start << "." << std::endl;
            return new BSTNode(start, sz);
        }

        // Check for memory overlap before inserting.
        if (start < node->startByte) {
            if (start + sz > node->startByte) {
                std::cout << "Error: Memory overlap detected." << std::endl;
                return node;
            }
            node->left = insert(node->left, start, sz);
        } else if (start > node->startByte) {
            if (node->startByte + node->size > start) {
                std::cout << "Error: Memory overlap detected." << std::endl;
                return node;
            }
            node->right = insert(node->right, start, sz);
        } else {
            std::cout << "Error: Memory already allocated at this address." << std::endl;
        }

        return node;
    }

    // Recursively removes a memory block from the BST.
    BSTNode* removeNode(BSTNode* node, int addr) {
        if (node == nullptr) {
            std::cout << "Error: No memory allocation containing the address " << addr << "." << std::endl;
            return nullptr;
        }

        if (addr < node->startByte) {
            node->left = removeNode(node->left, addr);
        } else if (addr >= node->startByte + node->size) {
            node->right = removeNode(node->right, addr);
        } else {
            std::cout << "Deallocated memory containing byte " << addr << "." << std::endl;

            // Handle node with only one child or no children.
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            // Handle node with two children.
            BSTNode* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            node->startByte = temp->startByte;
            node->size = temp->size;
            node->stack = std::move(temp->stack);

            node->right = removeNode(node->right, temp->startByte);
        }

        return node;
    }

    // Helper to perform an inorder traversal of the BST.
    void inorderHelper(BSTNode* node) const {
        if (node == nullptr) return;

        inorderHelper(node->left);

        std::cout << "Memory allocation starting at byte " << node->startByte
                  << " with size " << node->size << " bytes:" << std::endl;
        std::cout << "Stack starting at byte " << node->startByte << ":" << std::endl;
        node->stack.display();

        inorderHelper(node->right);
    }

    // Recursively deletes all nodes in the BST.
    void deleteTree(BSTNode* node) {
        if (!node) return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

public:
    // Constructor: Initializes an empty BST.
    BST() : root(nullptr) {}

    // Destructor: Cleans up all nodes in the BST.
    ~BST() {
        deleteTree(root);
    }

    // Inserts a new memory block into the BST.
    BST& operator+=(const std::pair<int, int>& allocation) {
        root = insert(root, allocation.first, allocation.second);
        return *this;
    }

    // Removes a memory block containing the given address.
    BST& operator-=(int addr) {
        root = removeNode(root, addr);
        return *this;
    }

    // Accesses the stack at a specific address.
    Stack<T>* operator[](int addr) const {
        BSTNode* node = root;
        while (node) {
            if (addr >= node->startByte && addr < node->startByte + node->size) {
                return &(node->stack);
            }
            node = addr < node->startByte ? node->left : node->right;
        }
        return nullptr;
    }

    // Displays all memory allocations in sorted order.
    void inorder() const {
        inorderHelper(root);
    }
};

#endif // BST_H
