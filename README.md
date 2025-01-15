# Huffman Text File Compressor in C++

## Overview
This project is a text file compressor implemented in C++ using the Huffman coding algorithm. It compresses text files by encoding characters with variable-length binary codes, prioritizing frequent characters for shorter codes, resulting in efficient compression.

## Features
- **Huffman Encoding**: Constructs a binary tree based on character frequencies to generate unique binary codes for each character.
- **Compression**: Replaces characters in the input file with their corresponding Huffman codes to produce a compressed file.
- **Decompression**: Reconstructs the original text file from the compressed data.
- **Min-Heap Data Structure**: Used for efficient construction of the Huffman tree.

## Workflow
1. **Input**: Users select a text file for compression.
2. **Huffman Encoding**: The algorithm analyzes the file to generate frequency-based Huffman codes.
3. **Compression**: The characters in the file are replaced with Huffman codes, creating a compressed output file.
4. **Decompression**: The original file is reconstructed from the compressed data.

## Project Details
- **Language**: C++ (for efficient memory management and implementation)
- **Algorithm**: Huffman Coding
- **Data Structure**: Min-Heap

## Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/JeganT143/huffman-text-compressor.git
