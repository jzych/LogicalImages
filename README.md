# LogicalImages
[![Build Status](https://www.travis-ci.com/jzych/LogicalImages.svg?branch=master)](https://www.travis-ci.com/jzych/LogicalImages)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b0f9731493584d6880adfa723bf5e5d6)](https://www.codacy.com/gh/jzych/LogicalImages/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jzych/LogicalImages&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/jzych/LogicalImages/branch/master/graph/badge.svg?token=W2LJUIO7CE)](https://codecov.io/gh/jzych/LogicalImages)

## Program LogicalImagesSolver
===================
[Logical images](https://www.wydawnictwologi.pl/obrazki-logiczne)
The main goal is to come up with algorithms for solving logical images. We will use a lot of combinations of images solving techniques and with the help of certain heuristics we will try to put together a full algorithm that is not known at the beginning. 
 If we manage to the end, we will try to optimize it. Maybe we will even use a graphic library.

**Input:**
A text file in JSON format representing input data, e.g.

```jason
{
  "sizeRows": 3,
  "sizeCols": 3,
  "cluesRows": [
    [1, 1],
    [2],
    [1, 1]
  ],
  "cluesCols": [
    [1, 1],
    [1],
    [3]
  ]
}
```

Represents this board:
```jason
    +------+
    | 1    |
    | 1 1 3|
+---+------+
|1 1|??????|
|  2|??????|
|1 1|??????|
+---+------+
```

**Output:**
Text file with a solved board drawn with ASCII characters:
```jason
    +------+
    | 1    |
    | 1 1 3|
+---+------+
|1 1|■■  ■■|
|  2|  ■■■■|
|1 1|■■  ■■|
+---+------+
```

**Assumptions:**
3 field values - UNKNOWN, BLACK, WHITE with their representations in ASCII characters, values configured in the text file.
Maximum number given in row or column: 99

**Required functionalities**, that must be met in this order:

1.  Processing the input file and parsing it to a suitable data structure
2.  Display of an empty board in ASCII format on the screen
3.  Saving the board in ASCII format to a file
4.  Solving images with 3x3 board size (all possible cases tested in TDD)
5.  Solving images with 3x4 and 4x3 board size (all possible cases tested in TDD)
6.  Solving images with 4x4 board size (all possible cases tested in TDD)
7.  Solving images with 4x5 and 5x4 board size
8.  Visualization of solving pictures step by step on the screen

**Extra functionalities**, order is important. Verification at least with the help of [these samples](https://www.wydawnictwologi.pl/pliki/probkaOL.pdf):

1.  Solving examples with difficulty level 1 (according to the Logi Publishing House scale, to be verified with several examples of such pictures)
2.  Solving examples with difficulty level 2 (according to the Logi Publishing House scale, to be verified with several examples of such pictures)
3.  Solving examples with difficulty level 3 (according to the Logi Publishing House scale, to be verified with several examples of such pictures)
4.  Solving examples with difficulty level 4 (according to the Logi Publishing House scale, to be verified with several examples of such pictures - this is where the interesting algorithmic work starts)
5.  Solving examples with difficulty level 5 (according to the Logi Publishing House scale, to be verified with several examples of such pictures)

**Extra functionalities**, in any order, but after all required functionalities have been delivered:

6.  Visualization of solving pictures step by step using a graphics library (Qt or OpenCV)
7.  Loading pictures in a graphic form in addition to the text form - from a photo or from a scan and processing them to JSON format(could be in separate binary file)
8.  Optimization of algorithms in terms of time
