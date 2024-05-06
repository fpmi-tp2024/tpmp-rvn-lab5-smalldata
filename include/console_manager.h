#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include <iostream>

class ConsoleManager {
public:
    void display(const std::string& text);
    std::string promptString(const std::string& prompt);
    int promptInt(const std::string& prompt);
    float promptFloat(const std::string& prompt);
};

#endif
