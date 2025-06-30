/*#include "huffman.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>
#include <vector>
#include <cstdint> // Required for uint32_t

namespace Huffman {

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Priority queue comparison
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Build frequency map
std::unordered_map<char, int> buildFrequencyMap(const std::string &data) {
    std::unordered_map<char, int> freqMap;
    for (char ch : data) freqMap[ch]++;
    return freqMap;
}

// Build Huffman tree
Node* buildTree(const std::unordered_map<char, int> &freqMap) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto &pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    return pq.empty() ? nullptr : pq.top();
}

// Build Huffman codes
void buildCodeTable(Node* node, const std::string &str, std::unordered_map<char, std::string> &code) {
    if (!node) return;
    if (!node->left && !node->right) {
        code[node->ch] = str;
        return;
    }
    buildCodeTable(node->left, str + "0", code);
    buildCodeTable(node->right, str + "1", code);
}

// Serialize tree to string
void serializeTree(Node* root, std::ostream &out) {
    if (!root) return;
    if (!root->left && !root->right) {
        out.put('1'); // Leaf marker
        out.put(root->ch);
    } else {
        out.put('0'); // Internal node
        serializeTree(root->left, out);
        serializeTree(root->right, out);
    }
}

// Deserialize tree from stream
Node* deserializeTree(std::istream &in) {
    char flag;
    if (!in.get(flag)) return nullptr;
    if (flag == '1') {
        char ch;
        in.get(ch);
        return new Node(ch, 0);
    }
    Node* node = new Node('\0', 0);
    node->left = deserializeTree(in);
    node->right = deserializeTree(in);
    return node;
}

// Free memory
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Compress file
bool compressFile(const std::string &inputPath) {
    std::ifstream in(inputPath, std::ios::binary);
    if (!in) return false;

    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    auto freqMap = buildFrequencyMap(content);
    Node* root = buildTree(freqMap);
    if (!root) return false;

    std::unordered_map<char, std::string> code;
    buildCodeTable(root, "", code);

    // Serialize tree to memory
    std::ostringstream treeBuffer;
    serializeTree(root, treeBuffer);
    std::string treeData = treeBuffer.str();
    uint32_t treeSize = static_cast<uint32_t>(treeData.size());

    // Encode data into bit string
    std::string bitString;
    for (char ch : content) {
        bitString += code[ch];
    }

    int padding = (8 - (bitString.size() % 8)) % 8;
    bitString.append(padding, '0');

    // Write to output
    std::ofstream out(inputPath + ".huff", std::ios::binary);
    out.write(reinterpret_cast<const char*>(&treeSize), sizeof(treeSize));
    out.write(treeData.c_str(), treeSize);
    out.put(static_cast<char>(padding));

    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::bitset<8> bits(bitString.substr(i, 8));
        out.put(static_cast<char>(bits.to_ulong()));
    }

    out.close();
    freeTree(root);
    return true;
}

// Decompress file
bool decompressFile(const std::string &inputPath) {
    std::ifstream in(inputPath, std::ios::binary);
    if (!in) return false;

    uint32_t treeSize;
    in.read(reinterpret_cast<char*>(&treeSize), sizeof(treeSize));

    std::string treeData(treeSize, '\0');
    in.read(&treeData[0], treeSize);
    std::istringstream treeStream(treeData);
    Node* root = deserializeTree(treeStream);

    char paddingChar;
    in.get(paddingChar);
    int padding = static_cast<unsigned char>(paddingChar); // Prevent sign issues

    std::string bitString;
    char byte;
    while (in.get(byte)) {
        std::bitset<8> bits(static_cast<unsigned char>(byte));
        bitString += bits.to_string();
    }
    in.close();

    if (padding > 0)
        bitString.erase(bitString.end() - padding, bitString.end());

    std::ofstream out(inputPath.substr(0, inputPath.size() - 5), std::ios::binary);
    Node* current = root;
    for (char bit : bitString) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            out.put(current->ch);
            current = root;
        }
    }
    out.close();
    freeTree(root);
    return true;
}

} // namespace Huffman
 */
 /*

 #include "huffman.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

namespace Huffman {

struct Node {
    std::string word;
    int freq;
    Node *left, *right;

    Node(std::string w, int f) : word(w), freq(f), left(nullptr), right(nullptr) {}
};

// Comparison for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Tokenize input into words
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

// Build frequency map for words
std::unordered_map<std::string, int> buildFrequencyMap(const std::string& data) {
    auto words = tokenize(data);
    std::unordered_map<std::string, int> freqMap;
    for (const auto& word : words) {
        freqMap[word]++;
    }
    return freqMap;
}

// Build Huffman Tree
Node* buildTree(const std::unordered_map<std::string, int>& freqMap) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node("", left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();
}

// Generate Huffman codes
void generateCodes(Node* root, const std::string& code,
                   std::unordered_map<std::string, std::string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->word] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Encode data using word Huffman codes
std::string encode(const std::string& data, std::unordered_map<std::string, std::string>& huffmanCode) {
    auto words = tokenize(data);
    std::string encoded;
    for (const auto& word : words) {
        encoded += huffmanCode[word];
    }
    return encoded;
}

// Save code map to a file
void saveCodeMap(const std::unordered_map<std::string, std::string>& huffmanCode, const std::string& path) {
    std::ofstream out(path);
    for (const auto& pair : huffmanCode) {
        out << pair.first << " " << pair.second << "\n";
    }
}

// Public interface to compress data

void compress(const std::string& inputPath, const std::string& outputPath, const std::string& codeMapPath) {
    std::ifstream inputFile(inputPath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string data = buffer.str();

    auto freqMap = buildFrequencyMap(data);
    Node* root = buildTree(freqMap);

    std::unordered_map<std::string, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    std::string encoded = encode(data, huffmanCode);

    std::ofstream outFile(outputPath, std::ios::binary);
    outFile << encoded;

    saveCodeMap(huffmanCode, codeMapPath);
}
void decompress(const std::string& compressedPath,
                const std::string& codeMapPath,
                const std::string& outputPath) {
    std::ifstream codeMapIn(codeMapPath);
    std::unordered_map<std::string, std::string> codeMap;
    std::unordered_map<std::string, std::string> reverseMap;

    std::string word, code;
    while (codeMapIn >> word >> code) {
        codeMap[word] = code;
        reverseMap[code] = word;
    }

    std::ifstream input(compressedPath);
    std::string compressedData;
    std::getline(input, compressedData);

    std::ofstream output(outputPath);
    std::string currentCode;
    for (char ch : compressedData) {
        currentCode += ch;
        if (reverseMap.find(currentCode) != reverseMap.end()) {
            output << reverseMap[currentCode] << " ";
            currentCode.clear();
        }
    }
}
} // namespace Huffman
 */
 #include "huffman.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <bitset>
#include <iostream>

// Huffman tree node
struct Node {
    std::string word;
    int freq;
    Node* left;
    Node* right;

    Node(const std::string& w, int f) : word(w), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Recursively build Huffman codes
void buildCodes(Node* root, const std::string& str, std::unordered_map<std::string, std::string>& codeMap) {
    if (!root) return;

    if (!root->left && !root->right) {
        codeMap[root->word] = str;
    }

    buildCodes(root->left, str + "0", codeMap);
    buildCodes(root->right, str + "1", codeMap);
}

std::tuple<size_t, size_t, double> Huffman::compress(const std::string& inputPath,
                                                     const std::string& outputPath,
                                                     const std::string& codeMapPath) {
   // std::ifstream input(inputPath);
    std::ifstream input(inputPath, std::ios::binary);
    std::string word;
    std::unordered_map<std::string, int> freqMap;

    // Count word frequencies
    while (input >> word) {
        freqMap[word]++;
    }

    // Build priority queue
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node("", left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();
    std::unordered_map<std::string, std::string> codeMap;
    buildCodes(root, "", codeMap);

    // Re-read input to encode
    input.clear();
    input.seekg(0);

    //std::ofstream output(outputPath);
    std::ofstream output(outputPath, std::ios::binary);
    std::ostringstream compressedData;
    while (input >> word) {
        compressedData << codeMap[word];
    }

    output << compressedData.str();

    // Save the code map
    //std::ofstream codeMapFile(codeMapPath);
    std::ofstream codeMapFile(codeMapPath, std::ios::binary);
    for (const auto& pair : codeMap) {
        codeMapFile << pair.first << " " << pair.second << "\n";
    }

    // Compute sizes
    std::ifstream originalFile(inputPath, std::ios::binary | std::ios::ate);
    std::ifstream compressedFile(outputPath, std::ios::binary | std::ios::ate);
    size_t originalSize = originalFile.tellg();
    size_t compressedSize = compressedFile.tellg();
    double spaceSaved = originalSize == 0 ? 0.0 : 100.0 * (originalSize - compressedSize) / originalSize;

    return {originalSize, compressedSize, spaceSaved};
}

void Huffman::decompress(const std::string& compressedPath,
                         const std::string& codeMapPath,
                         const std::string& outputPath) {
    //std::ifstream codeMapIn(codeMapPath);
    std::ifstream codeMapIn(codeMapPath, std::ios::binary);
    std::unordered_map<std::string, std::string> reverseMap;
    std::string word, code;

    while (codeMapIn >> word >> code) {
        reverseMap[code] = word;
    }

    // std::ifstream input(compressedPath);
    //std::string compressedData;
    //std::getline(input, compressedData);
    std::ifstream input(compressedPath, std::ios::binary);
    std::ostringstream buffer;
    buffer << input.rdbuf();
    std::string compressedData = buffer.str();

    //std::ofstream output(outputPath);
    std::ofstream output(outputPath, std::ios::binary);
    std::string currentCode;

    for (char ch : compressedData) {
        currentCode += ch;
        if (reverseMap.find(currentCode) != reverseMap.end()) {
            output << reverseMap[currentCode] << " ";
            currentCode.clear();
        }
    }
    output.close();
}                        
    bool Huffman::decompressFile(const std::string &inputPath, const std::string &outputPath) {
    // Try to automatically locate the .map file (assuming same base name)
    std::string base = inputPath;
    if (base.size() >= 5 && base.substr(base.size() - 5) == ".huff") {
        base = base.substr(0, base.size() - 5);  // remove ".huff"
    }
    std::string codeMapPath = inputPath + ".map";

    std::ifstream mapCheck(codeMapPath);
    if (!mapCheck.is_open()) {
        std::cerr << "Code map file not found: " << codeMapPath << std::endl;
        return false;
    }

    decompress(inputPath, codeMapPath, outputPath);
    return true;
}




