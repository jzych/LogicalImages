#include <gtest/gtest.h>
#include "json.hpp"
#include "LogicalImages.hpp"
#include "JSONFileReader.hpp"
#include "AlgorithmStub.hpp"

struct LogicalImagesTests : public ::testing::Test
{
};

TEST_F(LogicalImagesTests, assertThatJSONParsingLibraryWorks)
{
    using json = nlohmann::json;

    json j;
    j["pi"] = 3.14;

    ASSERT_EQ(j.dump(), "{\"pi\":3.14}");
}

TEST_F(LogicalImagesTests, checkFirstConstructorNoexception)
{
    std::string path = "../test/boards/ReadMeBoardTestFile.json";
    JSONFileReader jfr(path);
    auto b = std::make_shared<Board>(
        jfr.readRowSize(),
        jfr.readColSize(),
        jfr.readCluesRows(),
        jfr.readCluesCols());
        
    auto a = std::make_shared<AlgorithmStubA>();

    LogicalImages li(b, a);
}

TEST_F(LogicalImagesTests, checkSecondConstructorNoexception)
{
    std::string path = "../test/boards/ReadMeBoardTestFile.json";
    auto a = std::make_shared<AlgorithmStubA>();

    LogicalImages li(path, a);
}

TEST_F(LogicalImagesTests, checkSecondConstructorExceptions)
{
    std::string path;
    auto a = std::make_shared<AlgorithmStubA>();

    path = "../test/json/JSONFileReaderWrongColSizeTestFile.json";
    ASSERT_THROW(LogicalImages li1(path, a), InvalidDimensions);

    path = "../test/json/JSONFileReaderWrongRowSizeTestFile.json";
    ASSERT_THROW(LogicalImages li2(path, a), InvalidDimensions);

    path = "../test/json/JSONFileReaderNumberOfLinesAndColsNoMatch.json";
    ASSERT_THROW(LogicalImages li3(path, a), InvalidDimensions);

    path = "../test/json/JSONFileReaderNumberOfLinesAndRowsNoMatch.json";
    ASSERT_THROW(LogicalImages li4(path, a), InvalidDimensions);
}

TEST_F(LogicalImagesTests, checkSolveAlgorithmA)
{
    std::string path = "../test/boards/ReadMeBoardTestFile.json";
    std::string solution = "Puzzle solved!";
    auto a = std::make_shared<AlgorithmStubA>();
    testing::internal::CaptureStdout();

    LogicalImages li(path, a);
    li.solve();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find(solution), std::string::npos);
}

TEST_F(LogicalImagesTests, checkSolveFailure)
{
    std::string path = "../test/boards/ReadMeBoardTestFile.json";
    std::string solution = "Solution wasn't found";
    auto a = std::make_shared<AlgorithmStubB>();
    testing::internal::CaptureStdout();

    LogicalImages li(path, a);
    li.solve();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find(solution), std::string::npos);
}
