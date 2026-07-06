Huffman File Compressor

A C++ implementation of **Huffman Coding** for **lossless file compression and decompression**.  
This project was developed as a **Data Structures final project** and provides a simple command-line interface for compressing files into `.huff` format and restoring them back.

Overview

Huffman Coding is a classic greedy algorithm used for data compression.  
This project builds a Huffman Tree based on character frequencies, generates binary codes, and uses those codes to compress file contents efficiently.

The program supports:
- File compression
- File decompression
- Frequency-based encoding
- Custom Min-Heap implementation
- Command-line interaction

Features

- **Lossless Compression**
  - Compresses files without losing data

- **Decompression Support**
  - Restores compressed files back to their original form

- **Custom Huffman Tree**
  - Builds the encoding tree manually

- **Custom Min-Heap**
  - Uses a self-implemented heap instead of STL priority queue

- **Binary File Handling**
  - Reads and writes compressed data in binary format

- **Simple CLI Menu**
  - Easy to run and test from terminal

Technologies Used

- **Language:** C++
- **Concepts:** Data Structures, Trees, Heaps, File Handling, Greedy Algorithms
- **Compiler:** `g++` with C++17 support recommended

Project Structure
```text
.
├── main.cpp
├── huffman_code.cpp
├── huffman_code.h
├── huffman_tree.cpp
├── huffmantree.h
├── huffman_node.h
├── minheap.cpp
└── minheap.h
