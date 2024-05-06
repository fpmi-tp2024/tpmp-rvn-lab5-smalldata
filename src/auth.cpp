#include "auth.h"


bool AuthService::authorize(const std::string& username, const std::string& password) {
    std::string adminUsername, adminPassword;

    std::ifstream file(passswordsFilePath);
    if (!file.is_open()) {
        return false;
    }

    file >> adminUsername >> adminPassword;
    file.close();

    if (username == adminUsername && password == adminPassword) {
        return true;
    }
    return false;
}