#include "console_manager.h"


void ConsoleManager::display(const std::string& text) {
    std::cout << text << std::endl;
}

std::string ConsoleManager::promptString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int ConsoleManager::promptInt(const std::string& prompt) {
    int input;
    std::cout << prompt;
    std::cin >> input;
    std::cin.ignore();
    return input;
}

float ConsoleManager::promptFloat(const std::string& prompt) {
    float input;
    std::cout << prompt;
    std::cin >> input;
    std::cin.ignore();
    return input;
}
