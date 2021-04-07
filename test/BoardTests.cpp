#include "Board.hpp"
#include "JSONFileReader.hpp"
#include "json.hpp"
#include <gtest/gtest.h>

struct BoardTests : public ::testing::Test
{
    using json = nlohmann::json;
    std::string path;
};

TEST_F(BoardTests, checkConstructorNoexception)
{
    json j;
    j["cluesCols"] = {{1, 1}, {1}};
    j["cluesRows"] = {{1}, {1}, {1}};
    j["rowSize"] = 3;
    j["colSize"] = 2;

    Board board(j["rowSize"], j["colSize"], j["cluesRows"], j["cluesCols"]);
}

TEST_F(BoardTests, checkReadingJSON)
{
    path = "../test/boards/ReadMeBoardTestFile.json";
    JSONFileReader jfr(path);
    Board board(jfr.readRowSize(),
                jfr.readColSize(),
                jfr.readCluesRows(),
                jfr.readCluesCols());

    ASSERT_EQ(board.getSizeRows(), 3);
    ASSERT_EQ(board.getSizeCols(), 3);
}

TEST_F(BoardTests, checkJSONFileReaderExceptions)
{
    path = "../test/json/JSONFileReaderWrongColSizeTestFile.json";
    JSONFileReader jfr1(path);
    ASSERT_THROW(Board board(jfr1.readRowSize(),
                             jfr1.readColSize(),
                             jfr1.readCluesRows(),
                             jfr1.readCluesCols()), InvalidDimensions);

    path = "../test/json/JSONFileReaderWrongRowSizeTestFile.json";
    JSONFileReader jfr2(path);
    ASSERT_THROW(Board board(jfr2.readRowSize(),
                             jfr2.readColSize(),
                             jfr2.readCluesRows(),
                             jfr2.readCluesCols()), InvalidDimensions);

    path = "../test/json/JSONFileReaderNumberOfLinesAndColsNoMatch.json";
    JSONFileReader jfr3(path);
    ASSERT_THROW(Board board(jfr3.readRowSize(),
                             jfr3.readColSize(),
                             jfr3.readCluesRows(),
                             jfr3.readCluesCols()), InvalidDimensions);

    path = "../test/json/JSONFileReaderNumberOfLinesAndRowsNoMatch.json";
    JSONFileReader jfr4(path);
    ASSERT_THROW(Board board(jfr4.readRowSize(),
                             jfr4.readColSize(),
                             jfr4.readCluesRows(),
                             jfr4.readCluesCols()), InvalidDimensions);
}
TEST_F(BoardTests, checkBoardArgumentBoard_WithGetBoardLinesFunction)
{
    Line vec = {1, 2};
    Lines vec2 = {vec, vec};

    Board board(3, 3, vec2, vec2);
    ASSERT_EQ(board.getBoardLines().at(1)[1], BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(1)[0], BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(0)[1], BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(0)[0], BoardFields::UNKNOWN);
}

TEST_F(BoardTests, checkBoardSetGetField)
{
    Board board(3, 2, {}, {});
    board.setField(0, 0, BoardFields::BLACK);
    board.setField(1, 0, BoardFields::WHITE);

    ASSERT_EQ(board.getBoardLines().at(0).at(0), BoardFields::BLACK);
    ASSERT_EQ(board.getBoardLines().at(1).at(1), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(2).at(0), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(0).at(1), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(1).at(0), BoardFields::WHITE);
    ASSERT_EQ(board.getBoardLines().at(2).at(1), BoardFields::UNKNOWN);

    board.setField(0, 0, BoardFields::UNKNOWN);
    board.setField(2, 0, BoardFields::BLACK);
    board.setField(1, 0, BoardFields::UNKNOWN);
    board.setField(2, 1, BoardFields::WHITE);

    ASSERT_EQ(board.getBoardLines().at(0).at(0), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(1).at(1), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(2).at(0), BoardFields::BLACK);
    ASSERT_EQ(board.getBoardLines().at(0).at(1), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(1).at(0), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getBoardLines().at(2).at(1), BoardFields::WHITE);

    ASSERT_EQ(board.getField(0, 0), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getField(1, 0), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getField(2, 0), BoardFields::BLACK);
    ASSERT_EQ(board.getField(0, 1), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getField(1, 1), BoardFields::UNKNOWN);
    ASSERT_EQ(board.getField(2, 1), BoardFields::WHITE);
}

TEST_F(BoardTests, checkBoardSetGetFieldException)
{
    Board board(2, 3, {}, {});
    ASSERT_THROW(board.setField(2, 0, BoardFields::BLACK), std::out_of_range);
    ASSERT_THROW(board.setField(0, 3, BoardFields::BLACK), std::out_of_range);
    ASSERT_THROW(board.getField(2, 0), std::out_of_range);
    ASSERT_THROW(board.getField(0, 3), std::out_of_range);
}

TEST_F(BoardTests, checkBoardSetGetRow)
{
    Board board(3, 2, {}, {});
    BLine result1 = {BoardFields::BLACK, BoardFields::UNKNOWN};
    BLine result2 = {BoardFields::WHITE, BoardFields::UNKNOWN};

    board.setField(0, 0, BoardFields::BLACK);
    board.setField(1, 0, BoardFields::WHITE);

    ASSERT_EQ(board.getRow(0), result1);
    ASSERT_EQ(board.getRow(1), result2);

    board.setRow(0, result2);
    board.setRow(1, result1);

    ASSERT_EQ(board.getRow(0), result2);
    ASSERT_EQ(board.getRow(1), result1);
}

TEST_F(BoardTests, checkBoardSetGetRowException)
{
    Board board(2, 4, {}, {});
    BLine lineTooBig = {BoardFields::UNKNOWN, BoardFields::WHITE, BoardFields::UNKNOWN};
    BLine lineTooShort = {BoardFields::UNKNOWN};
    BLine lineGood = {BoardFields::UNKNOWN, BoardFields::WHITE};

    ASSERT_THROW(board.getRow(3), std::out_of_range);
    ASSERT_THROW(board.setRow(1, lineTooBig), std::out_of_range);
    ASSERT_THROW(board.setRow(1, lineTooShort), std::out_of_range);
    ASSERT_THROW(board.setRow(3, lineGood), std::out_of_range);
}

TEST_F(BoardTests, checkBoardSetGetCol)
{
    Board board(2, 3, {}, {});
    BLine result1 = {BoardFields::BLACK, BoardFields::UNKNOWN};
    BLine result2 = {BoardFields::UNKNOWN, BoardFields::UNKNOWN};
    BLine result3 = {BoardFields::UNKNOWN, BoardFields::WHITE};

    board.setField(0, 0, BoardFields::BLACK);
    board.setField(1, 2, BoardFields::WHITE);

    ASSERT_EQ(board.getCol(0), result1);
    ASSERT_EQ(board.getCol(1), result2);
    ASSERT_EQ(board.getCol(2), result3);

    board.setCol(0, result3);
    board.setCol(1, result1);
    board.setCol(2, result2);

    ASSERT_EQ(board.getCol(0), result3);
    ASSERT_EQ(board.getCol(1), result1);
    ASSERT_EQ(board.getCol(2), result2);
}

TEST_F(BoardTests, checkBoardSetGetColException)
{
    Board board(4, 2, {}, {});
    BLine lineTooBig = {BoardFields::UNKNOWN, BoardFields::WHITE, BoardFields::UNKNOWN};
    BLine lineTooShort = {BoardFields::UNKNOWN};
    BLine lineGood = {BoardFields::UNKNOWN, BoardFields::WHITE};

    ASSERT_THROW(board.getCol(3), std::out_of_range);
    ASSERT_THROW(board.setCol(1, lineTooBig), std::out_of_range);
    ASSERT_THROW(board.setCol(1, lineTooShort), std::out_of_range);
    ASSERT_THROW(board.setCol(3, lineGood), std::out_of_range);
}

TEST_F(BoardTests, findLongestVectorLenghtOfCluesInRows)
{
    Board board(4,
                5,
                {{1}, {1, 2}, {1, 2, 3, 4}, {1, 2, 3}},
                {{1}, {1, 2, 3, 4 ,5}, {1}, {1, 2}, {1}});
    ASSERT_EQ(board.getLongestCluesLenghtInRows(), 4);
}

TEST_F(BoardTests, findLongestVectorLenghtOfCluesInCols)
{
    Board board(4,
                5,
                {{1}, {1, 2}, {1, 2, 3, 4}, {1, 2, 3}},
                {{1}, {1, 2, 3, 4 ,5}, {1}, {1, 2}, {1}});
    ASSERT_EQ(board.getLongestCluesLenghtInCols(), 5);
}

TEST_F(BoardTests, checkSecondBoardConstructorNoexception)
{
    path = "../test/boards/ReadMeBoardTestFile.json";
    Board board(path);
}

TEST_F(BoardTests, checkSecondBoardConstructorExceptions)
{
    path = "../test/boards/ReadMeBoardTestFile.json";
    Board board(path);

    path = "../test/json/JSONFileReaderWrongColSizeTestFile.json";
    ASSERT_THROW(Board board(path), InvalidDimensions);

    path = "../test/json/JSONFileReaderWrongRowSizeTestFile.json";
    ASSERT_THROW(Board board(path), InvalidDimensions);

    path = "../test/json/JSONFileReaderNumberOfLinesAndColsNoMatch.json";
    ASSERT_THROW(Board board(path), InvalidDimensions);

    path = "../test/json/JSONFileReaderNumberOfLinesAndRowsNoMatch.json";
    ASSERT_THROW(Board board(path), InvalidDimensions);
}

TEST_F(BoardTests, checkSecondBoardConstructorSize)
{
    path = "../test/boards/ReadMeBoardTestFile.json";
    Board board(path);
    ASSERT_EQ(board.getSizeCols(), 3);
    ASSERT_EQ(board.getSizeRows(), 3);
    ASSERT_EQ(board.getCluesCols().at(0)[0], 1);
    ASSERT_EQ(board.getCluesRows().at(0)[0], 1);
}

TEST_F(BoardTests, checkBoardIsSolved)
{
    Board board(5,
                3,
                {{1, 1}, {3}, {1}, {}, {2}},
                {{2}, {2, 1}, {2, 1}});
    BLine row0 = {BoardFields::BLACK, BoardFields::WHITE, BoardFields::BLACK};
    BLine row1 = {BoardFields::BLACK, BoardFields::BLACK, BoardFields::BLACK};
    BLine row2 = {BoardFields::WHITE, BoardFields::BLACK, BoardFields::WHITE};
    BLine row3 = {BoardFields::WHITE, BoardFields::UNKNOWN, BoardFields::WHITE};
    BLine row4ok = {BoardFields::WHITE, BoardFields::BLACK, BoardFields::BLACK};
    BLine row4err = {BoardFields::BLACK, BoardFields::BLACK, BoardFields::WHITE};

    board.setRow(0, row0);
    board.setRow(1, row1);
    board.setRow(2, row2);
    board.setRow(3, row3);
    board.setRow(4, row4err);
    ASSERT_EQ(board.isSolved(), false);

    board.setField(3, 1, BoardFields::BLACK);
    ASSERT_EQ(board.isSolved(), false);

    board.setField(3, 1, BoardFields::WHITE);
    ASSERT_EQ(board.isSolved(), false);

    board.setRow(4, row4ok);
    ASSERT_EQ(board.isSolved(), true);
}
