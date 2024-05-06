#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <fstream>

#include "console_manager.h"


class AuthService {
private:
    std::string passswordsFilePath;
public:
    AuthService(const std::string& passswordsFilePath) : passswordsFilePath(passswordsFilePath) {};

    bool authorize(const std::string& username, const std::string& password);
};


#endif
