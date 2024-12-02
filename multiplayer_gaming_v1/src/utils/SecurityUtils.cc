#include "SecurityUtils.h"

std::string SecurityUtils::encrypt(const std::string& data) {
    // Simple encryption logic (placeholder)
    std::string encryptedData = "encrypted:" + data;
    return encryptedData;
}

std::string SecurityUtils::decrypt(const std::string& data) {
    // Simple decryption logic (placeholder)
    return data.substr(10); // Remove "encrypted:"
}

bool SecurityUtils::validateToken(int clientId, const std::string& token) {
    // Token validation logic (placeholder)
    return token == "validToken"; // Modify as needed
}
