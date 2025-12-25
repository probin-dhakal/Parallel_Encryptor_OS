#include "encryptor.h"
#include "config.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <mutex>

extern std::mutex coutMutex;

Encryptor::Encryptor(const std::string &key) : key_(key) {}

void Encryptor::encryptFile(const std::string &inputPath,
                            const std::string &outputPath)
{
    std::ifstream input(inputPath, std::ios::binary);
    std::ofstream output(outputPath, std::ios::binary);

    if (!input || !output)
    {
        if (verbose)
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cerr << "[Error] Cannot open file: " << inputPath << "\n";
        }
        return;
    }

    char ch;
    size_t index = 0;

    if (verbose)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "[Encrypted Hex for " << inputPath << "]: ";
    }

    while (input.get(ch))
    {
        char enc = transformChar(ch, index++);
        output.put(enc);

        if (verbose)
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << std::hex << std::setw(2)
                      << std::setfill('0')
                      << (int)(unsigned char)enc << " ";
        }
    }

    if (verbose)
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << std::dec << "\n";
    }
}

void Encryptor::decryptFile(const std::string &inputPath,
                            const std::string &outputPath)
{
    std::ifstream input(inputPath, std::ios::binary);
    std::ofstream output(outputPath, std::ios::binary);

    if (!input || !output)
        return;

    char ch;
    size_t index = 0;

    while (input.get(ch))
    {
        char dec = transformChar(ch, index++);
        output.put(dec);
    }
}

char Encryptor::transformChar(char c, size_t index)
{
    return c ^ key_[index % key_.size()];
}
