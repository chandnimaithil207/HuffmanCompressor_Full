/*#pragma once
#include <string>

namespace Huffman {
    bool compressFile(const std::string &inputPath);
    bool decompressFile(const std::string &inputPath);
}
*/
/*
#pragma once
#include <string>
#include <unordered_map>

namespace Huffman {

    // Compress a text file using word-based Huffman encoding
    void compress(const std::string& inputPath,
                  const std::string& outputPath,
                  const std::string& codeMapPath);

    // (Optional) Decompress a previously compressed file (to be implemented)
    void decompress(const std::string& compressedPath,
                    const std::string& codeMapPath,
                    const std::string& outputPath);
}
*/
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <tuple>

class Huffman {
public:
    // Compress function that returns original size, compressed size, and space saved (%)
    static std::tuple<size_t, size_t, double> compress(const std::string& inputPath,
                                                       const std::string& outputPath,
                                                       const std::string& codeMapPath);

    // Decompress function
    static void decompress(const std::string& compressedPath,
                           const std::string& codeMapPath,
                           const std::string& outputPath);
    static bool decompressFile(const std::string &inputPath, const std::string &outputPath);
 };

#endif // HUFFMAN_H