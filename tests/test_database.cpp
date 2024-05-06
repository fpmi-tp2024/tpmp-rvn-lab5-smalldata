#include <gtest/gtest.h>

#include "database.h"


class DatabaseTest : public ::testing::Test {
protected:
    Database* db;

    virtual void SetUp() {
        db = new Database(":memory:");
        std::string output;
        db->execute("CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);", output);
    }

    virtual void TearDown() {
        delete db;
    }
};

// Test case for successful SQL execution
TEST_F(DatabaseTest, ExecutesSQLSuccessfully) {
    std::string output;
    bool result = db->execute("INSERT INTO test (name) VALUES ('John Doe');", output);
    EXPECT_TRUE(result);
    EXPECT_EQ(output, "");  // No output expected for INSERT
}

// Test case for SQL query
TEST_F(DatabaseTest, HandlesQuery) {
    std::string output;
    db->execute("INSERT INTO test (name) VALUES ('John Doe');", output);
    bool result = db->execute("SELECT * FROM test;", output);
    EXPECT_TRUE(result);
    EXPECT_NE(output.find("name = John Doe"), std::string::npos);
}

// Test case for handling SQL errors
TEST_F(DatabaseTest, HandlesSQLErrors) {
    std::string output;
    bool result = db->execute("INSERT INTO test (id, name) VALUES (1, 'John Doe');", output);  // OK
    result = db->execute("INSERT INTO test (id, name) VALUES (1, 'Jane Doe');", output);  // Error: duplicate key
    EXPECT_FALSE(result);
}

// Test case for output formatting
TEST_F(DatabaseTest, FormatsOutputCorrectly) {
    std::string output;
    db->execute("INSERT INTO test (name) VALUES ('John Doe');", output);
    db->execute("SELECT * FROM test;", output);
    std::string expectedOutput = "id = 1\nname = John Doe\n\n";
    EXPECT_EQ(output, expectedOutput);
}
