
# RBT-FrequencyForge

This project implements a Dictionary Abstract Data Type (ADT) using a **Red-Black Tree** (RBT) to efficiently manage key-value pairs. The ADT can be used for a variety of tasks, such as tracking word frequencies in large text files and maintaining the order of elements, making it ideal for applications requiring fast lookups and balanced data structures.

### Key Features:
- **Red-Black Tree-based Dictionary:** The underlying data structure is a Red-Black Tree, ensuring that the dictionary remains balanced, providing efficient insertions, deletions, and lookups.
- **Word Frequency Tracking:** The `WordFrequency.cpp` client reads in text files, parses them into words, and counts the frequency of each word.
- **Order Preservation:** Using the `Order.cpp` client, the project maintains key-value pairs in a sorted order, allowing for efficient pre-order traversal and order-sensitive operations.

## Files Included

- **`README.md`:** This document, providing an overview and instructions for the project.
- **`Makefile`:** A script for compiling the project, including any dependencies.
- **`Dictionary.h`:** Header file defining the Dictionary ADT and the Red-Black Tree structure.
- **`Dictionary.cpp`:** Implementation of the Dictionary ADT using a Red-Black Tree.
- **`DictionaryTest.cpp`:** A test client to verify the functionality of the Dictionary ADT.
- **`Order.cpp`:** A client for maintaining and displaying dictionary elements in order, with support for pre-order traversal.
- **`WordFrequency.cpp`:** A client for reading text files, parsing words, and counting word frequencies.

## Red-Black Tree Implementation

The Red-Black Tree used in this project ensures that the dictionary remains balanced at all times. It achieves this through a set of operations that preserve tree balance, ensuring logarithmic time complexity for insertion, deletion, and search operations. This structure is ideal for handling large datasets where performance is critical.

### RBT Properties:
1. Every node is either red or black.
2. The root node is always black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. Every path from a node to its descendant NIL nodes has the same number of black nodes.

## Clients Overview

### 1. `WordFrequency.cpp`
This client reads large text files (e.g., complete works of Shakespeare) and:
- Parses the file, ignoring punctuation and special characters.
- Converts words to lowercase and stores them as keys in the Dictionary.
- Tracks the frequency of each word as the value associated with the key.

#### Usage:
- Input: A text file (e.g., `Shakespeare.txt`).
- Output: A text file with words and their frequencies in pre-order traversal format.

### 2. `Order.cpp`
This client displays the elements of the dictionary in pre-order traversal. It also highlights the color of the nodes (red or black), demonstrating the internal balancing of the Red-Black Tree.

#### Usage:
- Input: Key-value pairs from the Dictionary.
- Output: Pre-order traversal of keys, indicating the color of each node.

## How to Run

1. Clone the repository:
   ```bash
   git clone git@github.com:vaishi01/RBT-FrequencyForge.git
   cd RBT-FrequencyForge
   ```

2. Compile the project using the provided `Makefile`:
   ```bash
   make
   ```

3. Run the clients:

   - **Word Frequency Client:**
     ```bash
     ./WordFrequency inputfile.txt
     ```

   - **Order Client:**
     ```bash
     ./Order
     ```

4. Test the dictionary functionality using the test client:
   ```bash
   ./DictionaryTest
   ```

## Example

### Word Frequency Example:
For the input file `Shakespeare.txt`, the `WordFrequency.cpp` client will output a file like this:

```
to: 1203
be: 748
or: 650
not: 490
...
```

### Order Example:
The `Order.cpp` client will traverse and display the dictionary in pre-order, indicating the color of each node:

```
Root (black): to
Left (red): be
Right (black): or
...
```
## License

This project is licensed under the MIT License



