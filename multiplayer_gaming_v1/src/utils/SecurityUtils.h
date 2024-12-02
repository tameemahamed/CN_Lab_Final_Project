#ifndef __SECURITYUTILS_H
#define __SECURITYUTILS_H

#include <string>
#include <map>
#include "omnetpp.h"

class SecurityUtils {
public:
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);
    bool validateToken(int clientId, const std::string& token);

private:
    std::map<int, std::string> clientTokens;
};

#endif
