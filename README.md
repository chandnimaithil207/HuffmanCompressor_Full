HuffmanCompressor_Full
Project Overview
HuffmanCompressor_Full is a GUI-based C++ application that demonstrates both standard character-level Huffman compression and an optimized word-level Huffman compression technique. Developed using the Qt framework, it allows users to compress text files, visualize bitstring output, perform decompression, and compare memory usage between the two methods. The project serves as a practical implementation of greedy algorithms and is suitable for educational demonstrations and research purposes.

Technologies Used
Frontend / GUI: Qt Widgets (C++ with .ui files)

Backend Logic: C++ (Huffman Tree, file handling, compression algorithms)

Compression Techniques:

Standard Huffman (character-based)

Modified Huffman (word-based)

Tools:

Qt Creator IDE

MinGW 64-bit Compiler

Getting Started
Prerequisites
Qt Creator installed (tested with Qt 6.9.0)

MinGW or compatible C++ compiler

Installation
bash
Copy code
git clone https://github.com/chandnimaithil207/HuffmanCompressor_Full.git
cd HuffmanCompressor_Full
Open HuffmanCompressor.pro in Qt Creator.

Configure the build environment (MinGW recommended).

Build and run the application.

Project Structure
bash
Copy code
HuffmanCompressor_Full/
├── huffman.cpp             # Compression & Decompression Logic
├── huffman.h
├── main.cpp                # Application Entry Point
├── mainwindow.cpp          # UI Control Logic
├── mainwindow.h
├── mainwindow.ui           # Interface Layout (Qt Designer)
├── HuffmanCompressor.pro   # Qt Project Configuration File
├── .gitignore              # Ignored Build and User Files
└── build/                  # Auto-generated build files
Features
Standard Huffman coding using character frequency

Modified Huffman coding using word frequency

File compression with bitstring output

Decompression for both character and word Huffman data

Memory usage comparison (in KB and percentage)

GUI-based interaction for file selection and operation

Clear display of input, compressed output, and stats

Testing & Validation
Verified correct bitstring generation for both methods

Ensured successful decompression matches original content

Memory saved calculated using original vs compressed file size

GUI interactions tested for both typical and edge-case inputs

Compared results across different types of text data (plain, repeated, mixed)

Sample Results
Input File	Original Size	Char Huffman	Word Huffman	Memory Saved
sample.txt	10 KB	5.2 KB	3.3 KB	Char: 48%
Word: 67%

Future Improvements

Batch compression of multiple files

Contributors
Shraddha Chaturvedi – Team Lead / Backend logic
Chandni Maithil – Frontend & Simulation UI/Algorithms
Vanshika Agarwal – Backend / Altitude Logic
Manya Saxena – Algorithms / Frontend

Developed as part of a research-focused major project in C++ demonstrating hybrid Huffman compression approaches.

