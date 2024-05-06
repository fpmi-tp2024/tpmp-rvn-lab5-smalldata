#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "auth.h"


class AuthServiceTest : public ::testing::Test {
protected:
    std::string testFilePath = "test_passwords.txt";

    AuthService* authService;

    virtual void SetUp() {
        std::ofstream out(testFilePath);
        out << "admin adminpass";
        out.close();
        authService = new AuthService(testFilePath);
    }

    virtual void TearDown() {
        delete authService;
        std::remove(testFilePath.c_str());
    }
};


// Test case for successful authorization
TEST_F(AuthServiceTest, AuthorizesWithCorrectCredentials) {
    // Expect the authorization to succeed with the correct credentials
    EXPECT_TRUE(authService->authorize("admin", "adminpass"));
}

// Test case for failed authorization with incorrect username
TEST_F(AuthServiceTest, FailsAuthorizationWithIncorrectUsername) {
    // Expect the authorization to fail with an incorrect username
    EXPECT_FALSE(authService->authorize("user", "adminpass"));
}

// Test case for failed authorization with incorrect password
TEST_F(AuthServiceTest, FailsAuthorizationWithIncorrectPassword) {
    // Expect the authorization to fail with an incorrect password
    EXPECT_FALSE(authService->authorize("admin", "wrongpass"));
}


// Test case for failed authorization with incorrect credentials
TEST_F(AuthServiceTest, FailsAuthorizationWithIncorrectCredentials) {
    EXPECT_FALSE(authService->authorize("not_admin", "wrongpass"));
}
