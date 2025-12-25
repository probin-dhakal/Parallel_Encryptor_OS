#pragma once

#include <string>

class Encryptor
{
public:
    explicit Encryptor(const std::string &key);

    void encryptFile(const std::string &inputPath,
                     const std::string &outputPath);

    void decryptFile(const std::string &inputPath,
                     const std::string &outputPath);

private:
    std::string key_;
    char transformChar(char c, size_t index);
};
