#ifndef VARIABLE_H
#define VARIABLE_H

template <typename T>
struct Variable {
    int address; // Memory address of the variable
    T value;     // Value of the variable
};

#endif // VARIABLE_H
