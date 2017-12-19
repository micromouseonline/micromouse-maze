/***********************************************************************
 * Created by Peter Harrison on 15/12/2017.
 * Copyright (c) 2017 Peter Harrison
 *
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
 **************************************************************************/


#ifndef MICROMOUSE_MAZE_COMPILER_H
#define MICROMOUSE_MAZE_COMPILER_H

#include <cstdint>


/// Convert the path to a set of commands using only 90 degree in place turns
void makeInPlaceCommands(const char *src, const uint16_t maxLength, uint8_t *commands);
/// Convert the path to a set of commands using only 90 degree explore turns
void makeDiagonalCommands(const char *src, const uint16_t maxLength, uint8_t *commands);
/// Convert the path to a set of commands using the full range of turns and moves
void makeSmoothCommands(const char *src, const uint16_t maxLength, uint8_t *commands);

#endif //MICROMOUSE_MAZE_COMPILER_H
