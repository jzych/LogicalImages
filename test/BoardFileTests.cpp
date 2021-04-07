#include <gtest/gtest.h>
#include <string>
#include "Utilities.cpp"

struct BoardFileTests : public ::testing::Test
{
};

TEST_F(BoardFileTests, whenFileToReadPathIsGiven)
{
    std::string path = "../test/json/EmptyFile.txt";

    ASSERT_NO_THROW(openFileToRead(path));
}

TEST_F(BoardFileTests, whenWrongFileToReadPathIsGiven)
{
    std::string path = "./WrongPath.txt";

    ASSERT_ANY_THROW(openFileToRead(path));
}

TEST_F(BoardFileTests, whenWrongPathIsGiven)
{
    std::string path = "./Test/";

    ASSERT_ANY_THROW(openFileToWrite(path));
}

TEST_F(BoardFileTests, whenFileToWritePathIsGiven)
{
    std::string path = "../test/json/EmptyFile.txt";

    ASSERT_NO_THROW(openFileToWrite(path));
}
