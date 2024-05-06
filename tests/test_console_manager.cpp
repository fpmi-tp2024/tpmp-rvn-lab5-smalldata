#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "console_manager.h"


class ConsoleManagerTest : public ::testing::Test {
protected:
    std::streambuf* oldCoutStream;
    std::streambuf* oldCinStream;
    std::ostringstream strCout;
    std::istringstream strCin;

    virtual void SetUp() {
        oldCoutStream = std::cout.rdbuf(); // Save old buf
        std::cout.rdbuf(strCout.rdbuf()); // Redirect std::cout to strCout

        oldCinStream = std::cin.rdbuf(); // Save old cin buf
    }

    virtual void TearDown() {
        std::cout.rdbuf(oldCoutStream); // Reset to standard output again
        std::cin.rdbuf(oldCinStream); // Reset to standard input again
    }

    void setInput(const std::string& input) {
        strCin.str(input);
        std::cin.rdbuf(strCin.rdbuf()); // Redirect std::cin to strCin
    }
};


TEST_F(ConsoleManagerTest, DisplayTest) {
    ConsoleManager consoleManager;
    consoleManager.display("Hello, world!");
    ASSERT_EQ("Hello, world!\n", strCout.str());
}


TEST_F(ConsoleManagerTest, PromptStringTest) {
    setInput("example input\n");
    ConsoleManager consoleManager;
    ASSERT_EQ("example input", consoleManager.promptString("Enter input: "));
    ASSERT_EQ("Enter input: ", strCout.str());
}


TEST_F(ConsoleManagerTest, PromptIntTest) {
    setInput("123\n");
    ConsoleManager consoleManager;
    ASSERT_EQ(123, consoleManager.promptInt("Enter number: "));
    ASSERT_EQ("Enter number: ", strCout.str());
}


TEST_F(ConsoleManagerTest, PromptFloatTest) {
    setInput("123.45\n");
    ConsoleManager consoleManager;
    ASSERT_FLOAT_EQ(123.45f, consoleManager.promptFloat("Enter float: "));
    ASSERT_EQ("Enter float: ", strCout.str());
}


TEST_F(ConsoleManagerTest, PromptStringEmptyInputTest) {
    setInput("\n");  // simulate empty input followed by a newline
    ConsoleManager consoleManager;
    ASSERT_EQ("", consoleManager.promptString("Enter input: "));
    ASSERT_EQ("Enter input: ", strCout.str());
}
