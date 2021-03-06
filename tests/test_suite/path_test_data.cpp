/************************************************************************
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/

#include "path_test_data.h"

//TODO: Need test data for smooth and in-place turns

testPair_t testPairs[] = {
  "BS", {CMD_BEGIN, CMD_END},
  "BX", {CMD_BEGIN, CMD_EXPLORE}, // this is not an error
  "BFS", {CMD_BEGIN, FWD1, CMD_END},
  "BFX", {CMD_BEGIN, FWD1, CMD_EXPLORE},
  "BFFS", {CMD_BEGIN, FWD2, CMD_END},
  "BFFFS", {CMD_BEGIN, FWD3, CMD_END},
  "BFFFX", {CMD_BEGIN, FWD3, CMD_EXPLORE},
  "BRS", {CMD_BEGIN, CMD_ERROR_NOF, CMD_END},
  "BLS", {CMD_BEGIN, CMD_ERROR_NOF, CMD_END},
  "BFRS", {CMD_BEGIN, FWD1, SS90ER, FWD1, CMD_END},
  "BFLS", {CMD_BEGIN, FWD1, SS90EL, FWD1, CMD_END},
  "BFRFS", {CMD_BEGIN, FWD1, SS90FR, FWD2, CMD_END},
  "BFLFS", {CMD_BEGIN, FWD1, SS90FL, FWD2, CMD_END},
  "BFFRFS", {CMD_BEGIN, FWD2, SS90FR, FWD2, CMD_END},
  "BFFLFS", {CMD_BEGIN, FWD2, SS90FL, FWD2, CMD_END},
  //
  "BFFRFRS", {CMD_BEGIN, FWD2, SS90FR, FWD2, SS90ER, FWD1, CMD_END},
  "BFFLFLS", {CMD_BEGIN, FWD2, SS90FL, FWD2, SS90EL, FWD1, CMD_END},
  "BFFRFLS", {CMD_BEGIN, FWD2, SS90FR, FWD2, SS90EL, FWD1, CMD_END},
  //
  "BFFRLS", {CMD_BEGIN, FWD2, SD45R, DIA2, DS45L, FWD1, CMD_END},
  "BFFLRS", {CMD_BEGIN, FWD2, SD45L, DIA2, DS45R, FWD1, CMD_END},
  "BFFRLX", {CMD_BEGIN, FWD2, SD45R, DIA2, DS45L, FWD1, CMD_EXPLORE},
  "BFFLRX", {CMD_BEGIN, FWD2, SD45L, DIA2, DS45R, FWD1, CMD_EXPLORE},
  // sequential turns
  "BFFFFRRFFFS", {CMD_BEGIN, FWD4, SS180R, FWD4, CMD_END},
  "BFFFFLLFFFS", {CMD_BEGIN, FWD4, SS180L, FWD4, CMD_END},
  "BFFFFRRLLFFFS", {CMD_BEGIN, FWD4, SD135R, DIA2, DS135L, FWD4, CMD_END},
  "BFFFFLLRRFFFS", {CMD_BEGIN, FWD4, SD135L, DIA2, DS135R, FWD4, CMD_END},
  "BFFFFRRLRFFFS", {CMD_BEGIN, FWD4, SD135R, DIA3, DS45R, FWD4, CMD_END},
  "BFFFFLLRLFFFS", {CMD_BEGIN, FWD4, SD135L, DIA3, DS45L, FWD4, CMD_END},
  "BFFFFLLRLFFFX", {CMD_BEGIN, FWD4, SD135L, DIA3, DS45L, FWD4, CMD_EXPLORE},
  //
  "BFFRFLRFFS", {CMD_BEGIN, FWD2, SS90FR, FWD2, SD45L, DIA2, DS45R, FWD3, CMD_END},
  "BFRFFLFRLS", {CMD_BEGIN, FWD1, SS90FR, FWD3, SS90FL, FWD2, SD45R, DIA2, DS45L, FWD1, CMD_END},
  "BFRFFLFRLX", {CMD_BEGIN, FWD1, SS90FR, FWD3, SS90FL, FWD2, SD45R, DIA2, DS45L, FWD1, CMD_EXPLORE},
  "BFRFFLFLRX", {CMD_BEGIN, FWD1, SS90FR, FWD3, SS90FL, FWD2, SD45L, DIA2, DS45R, FWD1, CMD_EXPLORE},
  // a completely empty path
  "", {CMD_ERR_BEGIN, CMD_END},
  // an illegal first character
  "X", {CMD_ERR_BEGIN, CMD_END},
  "ZS", {CMD_ERR_BEGIN, CMD_END},
  // paths cannot start with a turn
  "RS", {CMD_ERR_BEGIN, CMD_END},
  "LS", {CMD_ERR_BEGIN, CMD_END},
  // basic straights
  "S", {CMD_ERR_BEGIN},
  "BFS", {CMD_BEGIN, FWD1, CMD_END},
  "BFFS", {CMD_BEGIN, FWD2, CMD_END},
  "BFFFS", {CMD_BEGIN, FWD3, CMD_END},
  // paths must have a terminating command
  "BF", {CMD_BEGIN, CMD_ERROR_END, CMD_END},
  "BFRR", {CMD_BEGIN, FWD1, CMD_ERROR_END, CMD_END},
  "BFLL", {CMD_BEGIN, FWD1, CMD_ERROR_END, CMD_END},
  "BFLR", {CMD_BEGIN, FWD1, SD45L, CMD_ERROR_END, CMD_END},
  "BFRL", {CMD_BEGIN, FWD1, SD45R, CMD_ERROR_END, CMD_END},
  "BFLRR", {CMD_BEGIN, FWD1, SD45L, CMD_ERROR_END, CMD_END},
  "BFRLL", {CMD_BEGIN, FWD1, SD45R, CMD_ERROR_END, CMD_END},
  // Can't turn back on yourself
  "BFRRR", {CMD_BEGIN, FWD1, CMD_ERROR_RRR, CMD_END},
  "BFLLL", {CMD_BEGIN, FWD1, CMD_ERROR_LLL, CMD_END},
  // simple 90 degree turns
  // paths with a turn just before the goal need a sharper turn
  "BFRS", {CMD_BEGIN, FWD1, SS90ER, FWD1, CMD_END},
  "BFLS", {CMD_BEGIN, FWD1, SS90EL, FWD1, CMD_END},
  "BFFRS", {CMD_BEGIN, FWD2, SS90ER, FWD1, CMD_END},
  "BFFLS", {CMD_BEGIN, FWD2, SS90EL, FWD1, CMD_END},
  "BFFFLFFLS", {CMD_BEGIN, FWD3, SS90FL, FWD3, SS90EL, FWD1, CMD_END},
  "BFFFLFLS", {CMD_BEGIN, FWD3, SS90FL, FWD2, SS90EL, FWD1, CMD_END},
  // This would be a tricky turn because of the outrun offset of SS180
  "BFFFLLS", {CMD_BEGIN, FWD3, SS180L, FWD1, CMD_END},
  "BFRFS", {CMD_BEGIN, FWD1, SS90FR, FWD2, CMD_END},
  "BFLFS", {CMD_BEGIN, FWD1, SS90FL, FWD2, CMD_END},
  "BFFFRFS", {CMD_BEGIN, FWD3, SS90FR, FWD2, CMD_END},
  "BFFFLFS", {CMD_BEGIN, FWD3, SS90FL, FWD2, CMD_END},
  "BFRFFS", {CMD_BEGIN, FWD1, SS90FR, FWD3, CMD_END},
  "BFLFFS", {CMD_BEGIN, FWD1, SS90FL, FWD3, CMD_END},
  "BFRFRFS", {CMD_BEGIN, FWD1, SS90FR, FWD2, SS90FR, FWD2, CMD_END},
  "BFLFLFS", {CMD_BEGIN, FWD1, SS90FL, FWD2, SS90FL, FWD2, CMD_END},
  "BFRFLFS", {CMD_BEGIN, FWD1, SS90FR, FWD2, SS90FL, FWD2, CMD_END},
  "BFLFRFS", {CMD_BEGIN, FWD1, SS90FL, FWD2, SS90FR, FWD2, CMD_END},
  // These two could have trouble stopping
  "BFRRS", {CMD_BEGIN, FWD1, SS180R, FWD1, CMD_END},
  "BFLLS", {CMD_BEGIN, FWD1, SS180L, FWD1, CMD_END},
  //
  "BFRRFS", {CMD_BEGIN, FWD1, SS180R, FWD2, CMD_END},
  "BFLLFS", {CMD_BEGIN, FWD1, SS180L, FWD2, CMD_END},
  // These two could have trouble stopping
  "BFRLS", {CMD_BEGIN, FWD1, SD45R, DIA2, DS45L, FWD1, CMD_END},
  "BFLRS", {CMD_BEGIN, FWD1, SD45L, DIA2, DS45R, FWD1, CMD_END},

  "BFRLFS", {CMD_BEGIN, FWD1, SD45R, DIA2, DS45L, FWD2, CMD_END},
  "BFLRFS", {CMD_BEGIN, FWD1, SD45L, DIA2, DS45R, FWD2, CMD_END},
  "BFRLRS", {CMD_BEGIN, FWD1, SD45R, DIA3, DS45R, FWD1, CMD_END},
  "BFLRLS", {CMD_BEGIN, FWD1, SD45L, DIA3, DS45L, FWD1, CMD_END},
  "BFRLRLS", {CMD_BEGIN, FWD1, SD45R, DIA4, DS45L, FWD1, CMD_END},
  "BFLRLRS", {CMD_BEGIN, FWD1, SD45L, DIA4, DS45R, FWD1, CMD_END},
  "BFRLRLFS", {CMD_BEGIN, FWD1, SD45R, DIA4, DS45L, FWD2, CMD_END},
  "BFLRLRFS", {CMD_BEGIN, FWD1, SD45L, DIA4, DS45R, FWD2, CMD_END},
  "BFRLLS", {CMD_BEGIN, FWD1, SD45R, DIA2, DS135L, FWD1, CMD_END},
  "BFLRRS", {CMD_BEGIN, FWD1, SD45L, DIA2, DS135R, FWD1, CMD_END},
  "BFRLRLLS", {CMD_BEGIN, FWD1, SD45R, DIA4, DS135L, FWD1, CMD_END},
  "BFLRLRRS", {CMD_BEGIN, FWD1, SD45L, DIA4, DS135R, FWD1, CMD_END},
  "BFLRRFS", {CMD_BEGIN, FWD1, SD45L, DIA2, DS135R, FWD2, CMD_END},
  "BFRLLFS", {CMD_BEGIN, FWD1, SD45R, DIA2, DS135L, FWD2, CMD_END},
  "BFLRRLFS", {CMD_BEGIN, FWD1, SD45L, DIA2, DD90R, DIA2, DS45L, FWD2, CMD_END},
  "BFRLLRFS", {CMD_BEGIN, FWD1, SD45R, DIA2, DD90L, DIA2, DS45R, FWD2, CMD_END},
  "BFRLLLRFS", {CMD_BEGIN, FWD1, SD45R, CMD_ERROR_LLL, CMD_END},
  // web post sample
  "BFRFRLFLLRFRLS",
  {
    CMD_BEGIN, FWD1, SS90FR, FWD2, SD45R, DIA2, DS45L, FWD2, SD135L, DIA2, DS45R, FWD2, SD45R, DIA2, DS45L, FWD1,
    CMD_END
  },
  // MINOS2014 test libMaze
  "BFFRRFLLFFLRLRFFFFRFFFFFFFFRFFRFFLRFFRFFRFFRLS",
  {
    CMD_BEGIN, FWD2, SS180R, FWD2, SS180L, FWD3, SD45L, DIA4, DS45R, FWD5, SS90FR, FWD9, SS90FR, FWD3, SS90FR, FWD3,
    SD45L, DIA2, DS45R, FWD3, SS90FR, FWD3, SS90FR, FWD3, SD45R, DIA2, DS45L, FWD1,
  },
  // other test mazes
  "BFFFFRFLFFLFRFRFLFLFRFFFFFFFRFRFFFFFFLFRFLFRFLFRFLFRFLFRFLFRFLFRFLFRFLFRFLFFFFLFLFFFRFRFFFLFRFLFFFFFFFLFFFRFRFFLFFFFLFLFRFRFLFFFLFS",
  {
    CMD_BEGIN, FWD4, SS90FR, FWD2, SS90FL, FWD3, SS90FL, FWD2, SS90FR, FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FL, FWD2,
    SS90FR, FWD8, SS90FR, FWD2, SS90FR, FWD7, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2,
    SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2,
    SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD5, SS90FL, FWD2, SS90FL, FWD4,
    SS90FR, FWD2, SS90FR, FWD4, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD8, SS90FL, FWD4, SS90FR, FWD2, SS90FR, FWD3,
    SS90FL, FWD5, SS90FL, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FR, FWD2, SS90FL, FWD4, SS90FL, FWD2, CMD_END
  },
  "BFFFFFFFFFFFFFFFRFFFFFFFFFFFFFFRFRFFFFFFLFLFFRFFLFFRFFFLFLFFFFLFRFRFFRFFFFFFFFFRFRFFFLFFRFLFRFLFRFLFRFLFRFFLFRFLFFFLFLFRFLFFRFFLFRFS",
  {
    CMD_BEGIN, FWD15, SS90FR, FWD15, SS90FR, FWD2, SS90FR, FWD7, SS90FL, FWD2, SS90FL, FWD3, SS90FR, FWD3, SS90FL,
    FWD3, SS90FR, FWD4, SS90FL, FWD2, SS90FL, FWD5, SS90FL, FWD2, SS90FR, FWD2, SS90FR, FWD3, SS90FR, FWD10, SS90FR,
    FWD2, SS90FR, FWD4, SS90FL, FWD3, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD2, SS90FL,
    FWD2, SS90FR, FWD2, SS90FL, FWD2, SS90FR, FWD3, SS90FL, FWD2, SS90FR, FWD2, SS90FL, FWD4, SS90FL, FWD2, SS90FL,
    FWD2, SS90FR, FWD2, SS90FL, FWD3, SS90FR, FWD3, SS90FL, FWD2, SS90FR, FWD2, CMD_END
  },
};


testPair_t smoothTestPairs[] = {
  "BS", {CMD_BEGIN, CMD_END},
  "BX", {CMD_BEGIN, CMD_EXPLORE}, // this is not an error
  "BFS", {CMD_BEGIN, FWD1, CMD_END},
  "BFX", {CMD_BEGIN, FWD1, CMD_EXPLORE},
  "BFFS", {CMD_BEGIN, FWD2, CMD_END},
  "BFFFS", {CMD_BEGIN, FWD3, CMD_END},
  "BFFFX", {CMD_BEGIN, FWD3, CMD_EXPLORE},
  "BRS", {CMD_BEGIN, CMD_ERROR_NOF, CMD_END},
  "BLS", {CMD_BEGIN, CMD_ERROR_NOF, CMD_END},
  "BFRS", {CMD_BEGIN, FWD1, SS90ER, FWD1, CMD_END},
  "BFLS", {CMD_BEGIN, FWD1, SS90EL, FWD1, CMD_END},
  "BFRFS", {CMD_BEGIN, FWD1, SS90ER, FWD2, CMD_END},
  "BFLFS", {CMD_BEGIN, FWD1, SS90EL, FWD2, CMD_END},
  "BFFRFS", {CMD_BEGIN, FWD2, SS90ER, FWD2, CMD_END},
  "BFFLFS", {CMD_BEGIN, FWD2, SS90EL, FWD2, CMD_END},
  // diagonal steps
  "BFFRLS", {CMD_BEGIN, FWD2, SS90ER, FWD1, SS90EL, FWD1, CMD_END},
  "BFFLRS", {CMD_BEGIN, FWD2, SS90EL, FWD1, SS90ER, FWD1, CMD_END},
  "BFFRLX", {CMD_BEGIN, FWD2, SS90ER, FWD1, SS90EL, FWD1, CMD_EXPLORE},
  "BFFLRX", {CMD_BEGIN, FWD2, SS90EL, FWD1, SS90ER, FWD1, CMD_EXPLORE},
};


int diagonalPairCount = sizeof(testPairs) / sizeof(testPair_t);


int smoothPairCount = sizeof(smoothTestPairs) / sizeof(testPair_t);

