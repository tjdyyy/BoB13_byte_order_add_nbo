#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <netinet/in.h>

using namespace std;

vector<uint32_t> readUint32FromFiles(const string& file1, const string& file2) {
    vector<uint32_t> numbers;
    ifstream infile1(file1, ios::binary);
    ifstream infile2(file2, ios::binary);

    if (!infile1) {
        cerr << "Error opening file: " << file1 << endl;
        return numbers;
    }
    if (!infile2) {
        cerr << "Error opening file: " << file2 << endl;
        return numbers;
    }

    uint32_t number;

    // Read from the first file
    while (infile1.read(reinterpret_cast<char*>(&number), sizeof(uint32_t))) {
        numbers.push_back(number);
    }

    // Read from the second file
    while (infile2.read(reinterpret_cast<char*>(&number), sizeof(uint32_t))) {
        numbers.push_back(number);
    }

    infile1.close();
    infile2.close();

    return numbers;
}

int main(int argc, char* argv[]) {
    // number of argumnets : 2
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file1> <file2>" << endl;
        return 1;
    }

    string file1 = argv[1];
    string file2 = argv[2];

    vector<uint32_t> numbers = readUint32FromFiles(file1, file2);
    uint32_t n[2];
    uint32_t sumNumbers = 0;

    for (int i = 0; i < numbers.size(); i++){
	n[i] = htonl(numbers[i]);
	sumNumbers += n[i];
    }
    
    printf("%d(%#x) + %d(%#x) = %d(%#x)\n", n[0],n[0], n[1],n[1], sumNumbers, sumNumbers);    

    return 0;
}


