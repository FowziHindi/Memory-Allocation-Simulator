# Memory-Allocation-Simulator

### Project Overview
This project is a C++ simulation of a sophisticated memory management system. It utilizes templated data structures and Binary Search Trees (BST) to manage memory spaces for different data types (int, short, and char), simulating how an operating system handles variable allocation, deallocation, and fragmentation.

### Technical Highlights
* Templated Architecture: Developed a generic framework using C++ templates to ensure the simulator handles multiple data types while maintaining type safety.
* BST-Based Memory Mapping: Engineered a Binary Search Tree to organize and track memory blocks by their starting addresses, optimizing the efficiency of allocation and deallocation operations.
* Stack-Based Variable Management: Implemented a custom Stack within each tree node to manage variables, strictly enforcing the Last-In, First-Out (LIFO) property for memory safety.
* Operator Overloading: Overloaded five major C++ operators (+=, -=, <<, >>, []) to create a clean, intuitive interface for allocating/deallocating memory and defining/undefining variables.
* Fragmentation and Boundary Protection: Designed logic to detect memory overlaps and ensure all variable definitions fall within authorized allocation boundaries.

### Implementation Details
* Language: C++
* Paradigm: Generic Programming (Templates)
* Data Structures: Binary Search Tree, Stack, Linked List logic
* Key Features: Memory fragmentation simulation, LIFO variable tracking, custom operator-driven CLI

### How to Run

1. **Compile the source**:
   ```bash
   g++ main.cpp -o MemorySim
   ```
 2. **Run the program with a sample input file**:

    Linux / macOS: ./MemorySim s1.txt

    Windows: MemorySim.exe s1.txt

  3. **Usage:**

      The program processes commands from the input file:
     ```
      allocate : Reserves a new memory block (uses operator+=).

      deallocate : Removes a memory block by its address (uses operator-=).

      define : Pushes a variable name onto a block's internal stack (uses operator<<).

      undefine : Pops a variable name from a block's internal stack (uses operator>>).

      display : Outputs the current state of the memory tree and all active variable stacks.
