//Fowzi Hindi 33587
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Variable.h"

// Implements a stack according to hw
template <typename T>
class Stack {
private:
    Variable<T>* variables;  // Array of variables managed by the stack.
    int capacity;            // Maximum number of variables the stack can hold.
    int currentSize;         // Current number of variables in the stack.
    int baseAddress;         // Starting address of the memory block.
    int blockSize;           // Total size of the memory block in bytes.

public:
    // Constructor: Initializes the stack for a memory block.
    Stack(int base = 0, int size = 0)
        : variables(nullptr), capacity(0), currentSize(0), baseAddress(base), blockSize(size) {
        if (size > 0) {
            capacity = size / sizeof(T);  // Calculate how many variables fit in the block.
            variables = new Variable<T>[capacity];  // Allocate space for variables.
        }
    }

    // Destructor: Cleans up allocated memory for the stack.
    ~Stack() {
        delete[] variables;
    }

    // Push: Adds a new variable to the stack.
    Stack& operator<<(const std::pair<int, T>& varInfo) {
        Variable<T> newVar{varInfo.first, varInfo.second};

        // Ensure the variable's address fits within the memory block.
        if (newVar.address < baseAddress || newVar.address + sizeof(T) > baseAddress + blockSize) {
            std::cout << "Error: Address " << newVar.address << " is outside allocation boundaries." << std::endl;
            return *this;
        }

        // Ensure there is space in the stack.
        if (currentSize >= capacity) {
            std::cout << "Error: Stack is full." << std::endl;
            return *this;
        }

        // Enforce the LIFO property by checking address alignment.
        if (currentSize > 0) {
            int expectedAddress = variables[currentSize - 1].address + sizeof(T);
            if (newVar.address != expectedAddress) {
                std::cout << "Error: Cannot define variable. Violates LIFO property." << std::endl;
                return *this;
            }
        }

        // Add the new variable to the stack.
        variables[currentSize++] = newVar;
        std::cout << "Defined variable at address " << newVar.address
                  << ": Type " << (sizeof(T) == 4 ? "i" : (sizeof(T) == 2 ? "s" : "c"))
                  << ", Value: " << newVar.value << "." << std::endl;
        return *this;
    }

    // Pop: Removes the most recently added variable from the stack.
    bool operator>>(int addr) {
        if (currentSize == 0) {
            std::cout << "Error: Cannot undefine. Stack is empty." << std::endl;
            return false;
        }

        // Ensure the address matches the last variable in the stack.
        if (addr != variables[currentSize - 1].address) {
            std::cout << "Error: Cannot undefine. Address does not match the most recent variable." << std::endl;
            return false;
        }

        std::cout << "Undefined variable at address " << addr << "." << std::endl;
        --currentSize;  // Decrease the size to "pop" the variable.
        return true;
    }

    // Displays the contents of the stack from top to bottom.
    void display() const {
        if (currentSize == 0) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }

        for (int i = currentSize - 1; i >= 0; --i) {
            std::cout << "Variable from address " << variables[i].address
                      << " to " << variables[i].address + sizeof(T) - 1
                      << ", Type: " << (sizeof(T) == 4 ? "i" : (sizeof(T) == 2 ? "s" : "c"))
                      << ", Value: " << variables[i].value << std::endl;
        }
    }
};

#endif // STACK_H
