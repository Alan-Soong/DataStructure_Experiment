#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

// ������������ڵ�ṹ��
struct Node {
    char symbol;
    int freq;
    Node* left;
    Node* right;

    Node(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
    Node(int f) : symbol('\0'), freq(f), left(nullptr), right(nullptr) {}
};

// ������������
Node* buildHuffmanTree(const string& data) {
    vector<int> freq(128, 0);
    for (char c : data) {
        freq[(int)c]++;
    }

    vector<Node*> nodes;
    // ����Ҷ�ӽڵ㲢����ڵ�����
    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            nodes.push_back(new Node((char)i, freq[i]));
        }
    }

    while (nodes.size() > 1) {
        // ����Ƶ����С�������ڵ�
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

        // �����µĸ��ڵ㲢����ڵ�����
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

// ����ṹ�壬���ڴ洢�ַ����������Ϣ
struct Encoding {
    char symbol = {};
    string code;
};

// ���ɻ���������
Encoding* generateCodes(Node* root, int index = 0, Encoding* encodings = nullptr, string code = "") {
    static int size = 0;
    if (root == nullptr) {
        return encodings;
    }
    if (root->symbol != '\0') {
        if (encodings == nullptr) {
            encodings = new Encoding[128];  // ͬ�����账��ASCII�볣���ַ���Χ���ɰ�����չ
        }
        encodings[size].symbol = root->symbol;
        encodings[size].code = code;
        size++;
    }
    encodings = generateCodes(root->left, index, encodings, code + "0");
    encodings = generateCodes(root->right, index, encodings, code + "1");
    return encodings;
}

// ���뺯��
string encode(const string& data, Encoding* encodings) {
    string encodedData;
    for (char c : data) {
        for (int i = 0; i < 128; ++i) {  // �������Ҷ�Ӧ����;
            if (encodings[i].symbol == c) {
                encodedData += encodings[i].code;
                break;
            }
        }
    }
    return encodedData;
}

/*
// ����ƽ��ѹ�����Ⱥ�ѹ���ȵĺ���
void calculateCompressionMetrics(const string& data, const Encoding* encodings) {
    vector<int> freq(128, 0);
    for (char c : data) {
        freq[(int)c]++;
    }

    double totalLength = 0;  // ���ڼ�¼����������ַ����볤�ȵļ�Ȩ�ܺ�
    int totalChars = data.length();  // ԭʼ���ݵ����ַ���

    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            // �ҵ���Ӧ�ַ��ı���
            string code;
            for (int j = 0; j < 128; ++j) {
                if (encodings[j].symbol == (char)i) {
                    code = encodings[j].code;
                    break;
                }
            }
            // �����Ȩ���Ȳ��ۼ�
            totalLength += freq[i] * code.length();
        }
    }

    // ����ƽ��ѹ������
    double averageCompressionLength = totalLength / totalChars;

    // ����ѹ���ȣ�ԭʼ���ݳ��ȳ��Ա�������ݳ���
    double encodedLength = 0;
    for (int i = 0; i < 128; ++i) {
        if (encodings[i].code.size() > 0) {
            encodedLength += encodings[i].code.length();
        }
    }
    double compressionRatio = totalChars / encodedLength;

    cout << "ƽ��ѹ������: " << averageCompressionLength << endl;
    cout << "ѹ����: " << compressionRatio << endl;
}
*/

// ���뺯��
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
    cout << "��ľ��ӣ�";
    getline(cin, data);
    //cin >> data;
    Node* huffmanTree = buildHuffmanTree(data);
    Encoding* encodings = generateCodes(huffmanTree);
    string encodedResult = encode(data, encodings);
    cout << "ԭʼ����: " << data << endl;
    cout << "�����: " << encodedResult << endl;
    cout << "�����: " << decode(encodedResult, huffmanTree) << endl;
    
    
    cout << endl;
    
    cout << endl;
    // ���ÿ���ַ��Ļ���������
    cout << "�ַ���Ӧ�Ļ���������:" << endl;
    for (int i = 0; i < 128; ++i) {
        if (encodings[i].code != "") {  // �������ǿգ�˵���ַ�����
            cout << "�ַ�: '" << encodings[i].symbol
                << "' -> ����������: " << encodings[i].code << endl;
        }
    }
    cout << endl;
    string num;
    cout << "���룺";
    cin >> num;
    cout << "���룺" << decode(num, huffmanTree) << endl;

    delete[] encodings;  // �ͷŶ�̬������ڴ�

    return 0;
}