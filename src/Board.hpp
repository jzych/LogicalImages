#pragma once
#include "BoardFields.hpp"
#include "json.hpp"
#include <vector>

using Line = std::vector<int>;
using Lines = std::vector<Line>;
using BLine = std::vector<BoardFields>;
using BLines = std::vector<BLine>;

class Board
{
    unsigned int sizeRows_;
    unsigned int sizeCols_;
    Lines cluesRows_;
    Lines cluesCols_;
    BLines board_;

public:
    Board(const unsigned int sizeRows,
          const unsigned int sizeCols,
          const Lines& rows,
          const Lines& cols) noexcept;
    Board(std::string filename);
    ~Board();

    unsigned int getSizeRows() const;
    unsigned int getSizeCols() const;
    BLines getBoardLines() const;

    unsigned int getLongestLineLenght(const Lines& v) const;
    unsigned int getLongestCluesLenghtInRows() const;
    unsigned int getLongestCluesLenghtInCols() const;

    Lines getCluesCols() const;
    Lines getCluesRows() const;

    void display() const;
};
