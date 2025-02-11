# C Program: Array Manipulation with Recursive and Binary Search

This C program demonstrates how to work with arrays of different data types (`int`, `float`, `char`). It includes functions to fill an array with random values, perform a recursive search, sort the array, and perform a binary search. The program also allows the user to choose the size of array the data type via command-line arguments.

---

## Table of Contents
1. [Description](#description)
2. [How to Compile and Run](#how-to-compile-and-run)
3. [Usage](#usage)
4. [Functions](#functions)
5. [Example](#example)
6. [License](#license)

---

## Description

The program provides the following functionality:
1. **Fill an array** with random values based on the chosen data type (`int`, `float`, or `char`).
2. **Recursive search**: Search for a value in the array using recursion.
3. **Binary search**: Sort the array and perform a binary search for a value.
4. **Command-line arguments**: The user can specify the size of the array and the data type when running the program.

---

## How to Compile and Run

1. **Clone the repository** (if applicable):
   ```bash
   git clone https://github.com/wolfymmm/system-software-architecture.git
   cd system-software-architecture

2. **Compile the program:**
   ```bash
   gcc -Wall task12.c -o task12


3. **Run the program:**
   ```bash
   ./task12 <array_size> <data_type>

## Usage

**Command-Line Arguments
<array_size>: The number of elements in the array.

<data_type>:
*0 for int (integers).
*1 for float (floating-point numbers).
*2 for char (characters).

**Example
To create an array of 10 random integers:
   ```bash
   ./task12 10 0
```

To create an array of 5 random floating-point numbers:
   ```bash 
   ./task12 10 0
```
To create an array of 8 random characters:
   ```bash
   ./task12 8 2
```
## Functions

'fill_array':
Fills the array with random values based on the chosen data type.

'recursive_search':
Searches for a value in the array using recursion.

'binary_search':
Performs a binary search on a sorted array.

'print_array':
Prints the elements of the array.

'main':
Handles command-line arguments, allocates memory, and calls the appropriate functions.

## Example
**Input** 
```bash
./task12 10 0
```
**Output**
```bash
Array: 42 67 23 89 12 45 78 34 56 90 
Enter the value to search: 45
Value found at index 5 (recursive search).
Sorted array: 12 23 34 42 45 56 67 78 89 90 
Value found at index 4 (binary search).
```
## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contact
If you have any questions or suggestions, feel free to reach out:

*GitHub Issues: Open an issue in this repository.
