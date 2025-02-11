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
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name

Compile the program:
   ```bash
   gcc -o array_manipulation array_manipulation.c


Run the program:
   ```bash
   ./array_manipulation <array_size> <data_type>

   <array_size>: The size of the array (e.g., 10).
   <data_type>: The type of data (0 for int, 1 for float, 2 for char).
