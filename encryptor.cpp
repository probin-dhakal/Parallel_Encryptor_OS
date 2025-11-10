#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// ==================================================
// Encryptor: Handles encryption & decryption
// ==================================================
class Encryptor
{
public:
    explicit Encryptor(const string &key) : key_(key) {}

    void encryptFile(const string &inputPath, const string &outputPath)
    {
        ifstream input(inputPath, ios::binary);
        ofstream output(outputPath, ios::binary);
        if (!input || !output)
        {
            cerr << "[Error] Cannot open file: " << inputPath << endl;
            return;
        }

        char buffer;
        size_t index = 0;
        cout << "[Encrypted Data for " << inputPath << "]: ";

        while (input.get(buffer))
        {
            char enc = transformChar(buffer, index++);
            output.put(enc);
            cout << hex << setw(2) << setfill('0') << (int)(unsigned char)enc << " ";
        }
        cout << dec << endl;
    }

    void decryptFile(const string &inputPath, const string &outputPath)
    {
        ifstream input(inputPath, ios::binary);
        ofstream output(outputPath, ios::binary);
        if (!input || !output)
        {
            cerr << "[Error] Cannot open encrypted file: " << inputPath << endl;
            return;
        }

        char buffer;
        size_t index = 0;
        cout << "[Decrypted Data from " << inputPath << "]: ";
        while (input.get(buffer))
        {
            char dec = transformChar(buffer, index++);
            output.put(dec);
            cout << dec;
        }
        cout << endl;
    }

private:
    string key_;
    char transformChar(char c, size_t index)
    {
        return c ^ key_[index % key_.size()];
    }
};
