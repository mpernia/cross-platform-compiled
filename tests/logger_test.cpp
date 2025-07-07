#include "../src/includes/logger.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

using namespace std;

class LoggerTest : public ::testing::Test 
{
    protected:
        void SetUp() override {
            originalCoutBuffer = cout.rdbuf();
            cout.rdbuf(testCout.rdbuf());
        }

        void TearDown() override {
            cout.rdbuf(originalCoutBuffer);
        }

        stringstream testCout;
        streambuf* originalCoutBuffer;
};

TEST_F(LoggerTest, DefaultLogLevelIsInfo) {
    EXPECT_EQ(Logger::getLevel(), INFO);
}

TEST_F(LoggerTest, CanChangeLogLevel) 
{
    Logger::setLevel(DEBUG);
    EXPECT_EQ(Logger::getLevel(), DEBUG);
    
    Logger::setLevel(ERROR_LEVEL);
    EXPECT_EQ(Logger::getLevel(), ERROR_LEVEL);
}

TEST_F(LoggerTest, MessagesAreSuppressedBelowLevel) 
{
    Logger::setLevel(WARNING);
    
    Logger::debug("Debug message");
    Logger::info("Info message");
    
    EXPECT_TRUE(testCout.str().empty());
}

TEST_F(LoggerTest, MessagesAreDisplayedAtOrAboveLevel) 
{
    Logger::setLevel(WARNING);
    
    Logger::warning("Warning message");
    string output = testCout.str();
    testCout.str("");
    
    EXPECT_TRUE(output.find("WARNING") != string::npos);
    EXPECT_TRUE(output.find("Warning message") != string::npos);
    
    Logger::error("Error message");
    output = testCout.str();
    testCout.str("");
    
    EXPECT_TRUE(output.find("ERROR") != string::npos);
    EXPECT_TRUE(output.find("Error message") != string::npos);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
