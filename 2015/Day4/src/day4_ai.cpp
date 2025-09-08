#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <openssl/evp.h>

// Compute MD5 hash using EVP API
std::string computeMD5(const std::string& input) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create EVP context" << std::endl;
        return "";
    }

    // Initialize MD5 digest
    if (EVP_DigestInit_ex(ctx, EVP_md5(), nullptr) != 1) {
        std::cerr << "Failed to initialize MD5" << std::endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    // Update with input data
    if (EVP_DigestUpdate(ctx, input.c_str(), input.length()) != 1) {
        std::cerr << "Failed to update digest" << std::endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    // Finalize hash
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;
    if (EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) {
        std::cerr << "Failed to finalize digest" << std::endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    // Convert to hexadecimal
    std::stringstream ss;
    for (unsigned int i = 0; i < digest_len; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }

    EVP_MD_CTX_free(ctx);
    return ss.str();
}

// Find the lowest positive number producing an MD5 hash starting with 'prefix'
int64_t findAdventCoin(const std::string& key, const std::string& prefix) {
    int64_t number = 1;
    while (true) {
        std::string input = key + std::to_string(number);
        std::string hash = computeMD5(input);
        if (hash.substr(0, prefix.length()) == prefix) {
            return number;
        }
        ++number;
    }
    return -1; // Should never reach here
}

int main() {
    // Provided puzzle input (replace if different)
    std::string secretKey = "ckczppom"; // Inferred from puzzle answers
    
    // Part 1: Find number producing MD5 hash with five leading zeros
    int64_t part1 = findAdventCoin(secretKey, "00000");
    std::cout << "Part 1: Lowest number for five zeros: " << part1 << std::endl;
    
    // Part 2: Find number producing MD5 hash with six leading zeros
    int64_t part2 = findAdventCoin(secretKey, "000000");
    std::cout << "Part 2: Lowest number for six zeros: " << part2 << std::endl;
    
    // Verify against provided answers
    if (part1 != 117946) {
        std::cerr << "Part 1: Expected 117946, got " << part1 << std::endl;
    }
    if (part2 != 3938038) {
        std::cerr << "Part 2: Expected 3938038, got " << part2 << std::endl;
    }
    
    return 0;
}