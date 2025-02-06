#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

// 定义霍夫曼树节点结构体
struct Node {
    char symbol;
    int freq;
    Node* left;
    Node* right;

    Node(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
    Node(int f) : symbol('\0'), freq(f), left(nullptr), right(nullptr) {}
};

// 构建霍夫曼树
Node* buildHuffmanTree(const string& data) {
    vector<int> freq(128, 0);
    for (char c : data) {
        freq[(int)c]++;
    }

    vector<Node*> nodes;
    // 创建叶子节点并放入节点数组
    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            nodes.push_back(new Node((char)i, freq[i]));
        }
    }

    while (nodes.size() > 1) {
        // 查找频率最小的两个节点
        int minIndex1 = 0, minIndex2 = 1;
        if (nodes[minIndex2]->freq < nodes[minIndex1]->freq) {
            swap(minIndex1, minIndex2);
        }
        for (int i = 2; i < nodes.size(); ++i) {
            if (nodes[i]->freq < nodes[minIndex1]->freq) {
                minIndex2 = minIndex1;
                minIndex1 = i;
            }
            else if (nodes[i]->freq < nodes[minIndex2]->freq) {
                minIndex2 = i;
            }
        }

        Node* left = nodes[minIndex1];
        Node* right = nodes[minIndex2];

        // 创建新的父节点并加入节点数组
        Node* combined = new Node(left->freq + right->freq);
        combined->left = left;
        combined->right = right;

        if (minIndex1 < minIndex2) {
            nodes.erase(nodes.begin() + minIndex1);
            nodes.erase(nodes.begin() + minIndex2 - 1);
        }
        else {
            nodes.erase(nodes.begin() + minIndex2);
            nodes.erase(nodes.begin() + minIndex1 - 1);
        }

        nodes.push_back(combined);
    }

    return nodes.empty() ? nullptr : nodes[0];
}

// 编码结构体，用于存储字符编码相关信息
struct Encoding {
    char symbol = {};
    string code;
};

// 生成霍夫曼编码
Encoding* generateCodes(Node* root, int index = 0, Encoding* encodings = nullptr, string code = "") {
    static int size = 0;
    if (root == nullptr) {
        return encodings;
    }
    if (root->symbol != '\0') {
        if (encodings == nullptr) {
            encodings = new Encoding[128];  // 同样假设处理ASCII码常见字符范围，可按需扩展
        }
        encodings[size].symbol = root->symbol;
        encodings[size].code = code;
        size++;
    }
    encodings = generateCodes(root->left, index, encodings, code + "0");
    encodings = generateCodes(root->right, index, encodings, code + "1");
    return encodings;
}

// 编码函数
string encode(const string& data, Encoding* encodings) {
    string encodedData;
    for (char c : data) {
        for (int i = 0; i < 128; ++i) {  // 遍历查找对应编码;
            if (encodings[i].symbol == c) {
                encodedData += encodings[i].code;
                break;
            }
        }
    }
    return encodedData;
}

/*
// 计算平均压缩长度和压缩比的函数
void calculateCompressionMetrics(const string& data, const Encoding* encodings) {
    vector<int> freq(128, 0);
    for (char c : data) {
        freq[(int)c]++;
    }

    double totalLength = 0;  // 用于记录编码后所有字符编码长度的加权总和
    int totalChars = data.length();  // 原始数据的总字符数

    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            // 找到对应字符的编码
            string code;
            for (int j = 0; j < 128; ++j) {
                if (encodings[j].symbol == (char)i) {
                    code = encodings[j].code;
                    break;
                }
            }
            // 计算加权长度并累加
            totalLength += freq[i] * code.length();
        }
    }

    // 计算平均压缩长度
    double averageCompressionLength = totalLength / totalChars;

    // 计算压缩比，原始数据长度除以编码后数据长度
    double encodedLength = 0;
    for (int i = 0; i < 128; ++i) {
        if (encodings[i].code.size() > 0) {
            encodedLength += encodings[i].code.length();
        }
    }
    double compressionRatio = totalChars / encodedLength;

    cout << "平均压缩长度: " << averageCompressionLength << endl;
    cout << "压缩比: " << compressionRatio << endl;
}
*/

// 解码函数
string decode(const string& encodedData, Node* root) {
    string decodedData;
    Node* current = root;
    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->symbol != '\0') {
            decodedData += current->symbol;
            current = root;
        }
    }
    return decodedData;
}

int main() {
    string data;
    cout << "你的句子：";
    getline(cin, data);
    //cin >> data;
    Node* huffmanTree = buildHuffmanTree(data);
    Encoding* encodings = generateCodes(huffmanTree);
    string encodedResult = encode(data, encodings);
    cout << "原始数据: " << data << endl;
    cout << "编码后: " << encodedResult << endl;
    cout << "解码后: " << decode(encodedResult, huffmanTree) << endl;
    
    
    cout << endl;
    
    cout << endl;
    // 输出每个字符的霍夫曼编码
    cout << "字符对应的霍夫曼编码:" << endl;
    for (int i = 0; i < 128; ++i) {
        if (encodings[i].code != "") {  // 如果编码非空，说明字符存在
            cout << "字符: '" << encodings[i].symbol
                << "' -> 霍夫曼编码: " << encodings[i].code << endl;
        }
    }
    cout << endl;
    string num;
    cout << "编码：";
    cin >> num;
    cout << "解码：" << decode(num, huffmanTree) << endl;

    delete[] encodings;  // 释放动态分配的内存

    return 0;
}