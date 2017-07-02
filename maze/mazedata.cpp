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


/**
 *  \file mazedata.cpp
 *  \brief contains sample mazes for testing
 * *
 *  \version
 *  \date 15 Apr 2017
 *  \author peterharrison
 *  \bug No known bugs.
 */


#include <stdint.h>
#include "mazedata.h"

MazeDataSource mazeList[] = {
  {"apec1996", apec1996},
  {"apec1997", apec1997},
  {"apec1998", apec1998},
  {"apec2012", apec2012},
  {"apec2013", apec2013},
  {"emptyMaze", emptyMaze},
  {"japan11", japan11},
  {"japan13", japan13},
  {"japan2011ff", japan2011ff},
  {"japan2011eq", japan2011eq},
  {"japan4", japan4},
  {"japan5", japan5},
  {"japan95", japan95},
  {"japan97", japan97},
  {"japan98", japan98},
  {"japan99", japan99},
  {"japan1988", japan1988},
  {"japan1990", japan1990},
  {"japan1991", japan1991},
  {"japan1993ef", japan1993ef},
  {"japan1994ef", japan1994ef},
  {"japan1996ef", japan1996ef},
  {"japan1997eq", japan1997eq},
  {"japan1998f", japan1998f},
  {"japan1999f", japan1999f},
  {"japan2000", japan2000},
  {"japan2000ef", japan2000ef},
  {"japan2001", japan2001},
  {"japan2001ef", japan2001ef},
  {"japan2002", japan2002},
  {"japan2002ef", japan2002ef},
  {"japan2002q", japan2002q},
  {"japan2003", japan2003},
  {"japan2004", japan2004},
  {"japan2005f", japan2005f},
  {"japan2007ef", japan2007ef},
  {"japan2007eq", japan2007eq},
  {"japan2009ef", japan2009ef},
  {"japan2009eq", japan2009eq},
  {"japan2011ef", japan2011ef},
  {"japan2012ef", japan2012_ef},
  {"japan2012eq", japan2012_eq},
  {"japan2013ef", japan2013ef},
  {"japan2014ef", japan2014ef},
  {"japan2014eq", japan2014eq},
  {"japan2015ef", japan2015ef},
  {"japan2016ef", japan2016ef},
  {"kyot_89", kyot_89},
  {"minos01f", minos01f},
  {"minos02f", minos02f},
  {"minos03f", minos03f},
  {"minos04f", minos04f},
  {"minos04q", minos04q},
  {"minos08f", minos08f},
  {"minos09f", minos09f},
  {"minos10f", minos10f},
  {"minos12f", minos12f},
  {"mj96bon", mj96bon},
  {"mont88", mont88},
  {"nagoya2002", nagoya2002},
  {"niigata03", niigata03},
  {"robotic2009_final", robotic2009},
  {"robotic2010", robotic2010},
  {"robotic2011_solver_finals", robotic2011},
  {"seoul2", seoul2},
  {"sg87", sg87},
  {"sg88", sg88},
  {"sg89", sg89},
  {"taiwan_2009", taiwan2009},
  {"taiwan_2012_final", taiwan2012},
  {"taiwan_2014_final", taiwan2014},
  {"taiwan_2015_final", taiwan2015},
  {"tyubu200906", tyubu200906},
  {"uk1987f", uk1987f},
  {"uk1988f", uk1988f},
  {"uk1989", uk1989},
  {"uk1990f", uk1990f},
  {"uk1991f", uk1991f},
  {"uk1992f", uk1992f},
  {"uk2000f", uk2000f},
  {"uk2001f", uk2001f},
  {"uk2002f", uk2002f},
  {"uk2003f", uk2003f},
  {"uk2004f", uk2004f},
  {"uk2005f", uk2005f},
  {"uk2006f", uk2006f},
  {"uk2007f", uk2007f},
  {"uk2008f", uk2008f},
  {"uk2009f", uk2009f},
  {"uk2010f", uk2010f},
  {"uk2011f", uk2011f},
  {"uk2012f", uk2012f},
  {"uk2014f", uk2014f},

};

int mazeCount = sizeof(mazeList) / sizeof(mazeList[0]);

const uint8_t japan2016ef[] = {
  0x0e, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x03, 0x0c, 0x08, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x08, 0x0a, 0x0a, 0x09, 0x0c, 0x03, 0x05, 0x0c, 0x03, 0x05,
  0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x06, 0x08, 0x09, 0x05, 0x06, 0x09,
  0x05, 0x05, 0x0c, 0x01, 0x05, 0x0c, 0x0a, 0x0a, 0x0a, 0x03, 0x0c, 0x03,
  0x05, 0x06, 0x09, 0x05, 0x05, 0x05, 0x05, 0x06, 0x01, 0x06, 0x0a, 0x0a,
  0x0a, 0x09, 0x06, 0x09, 0x05, 0x0c, 0x03, 0x05, 0x05, 0x05, 0x04, 0x0b,
  0x06, 0x09, 0x0e, 0x08, 0x09, 0x05, 0x0c, 0x03, 0x05, 0x06, 0x0a, 0x01,
  0x05, 0x05, 0x06, 0x09, 0x0c, 0x03, 0x0c, 0x03, 0x06, 0x01, 0x06, 0x09,
  0x05, 0x0c, 0x09, 0x07, 0x05, 0x06, 0x09, 0x05, 0x06, 0x09, 0x05, 0x0c,
  0x09, 0x04, 0x08, 0x03, 0x06, 0x03, 0x06, 0x09, 0x04, 0x0b, 0x05, 0x05,
  0x0c, 0x03, 0x05, 0x06, 0x01, 0x07, 0x06, 0x09, 0x0e, 0x09, 0x0c, 0x03,
  0x05, 0x0c, 0x01, 0x05, 0x06, 0x09, 0x05, 0x0e, 0x00, 0x0b, 0x0c, 0x02,
  0x08, 0x02, 0x02, 0x09, 0x05, 0x05, 0x05, 0x05, 0x0c, 0x03, 0x05, 0x0e,
  0x00, 0x0b, 0x06, 0x09, 0x04, 0x0a, 0x0a, 0x03, 0x05, 0x04, 0x01, 0x05,
  0x06, 0x09, 0x05, 0x0e, 0x00, 0x0b, 0x0c, 0x03, 0x06, 0x0a, 0x0a, 0x09,
  0x05, 0x05, 0x05, 0x05, 0x0c, 0x03, 0x05, 0x0e, 0x00, 0x0b, 0x06, 0x08,
  0x0a, 0x0a, 0x09, 0x05, 0x05, 0x05, 0x06, 0x03, 0x06, 0x09, 0x05, 0x0c,
  0x00, 0x09, 0x0c, 0x02, 0x0b, 0x0d, 0x05, 0x05, 0x05, 0x06, 0x09, 0x0d,
  0x0c, 0x03, 0x04, 0x01, 0x07, 0x05, 0x06, 0x0a, 0x0a, 0x01, 0x05, 0x05,
  0x06, 0x0a, 0x02, 0x03, 0x06, 0x0a, 0x03, 0x06, 0x0a, 0x02, 0x0a, 0x0a,
  0x0a, 0x03, 0x06, 0x03
};

const uint8_t japan2015ef[] = {
  0x0e, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x02, 0x03, 0x0d, 0x0d, 0x0e, 0x08, 0x0a,
  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x05, 0x05, 0x0c, 0x0a, 0x00,
  0x02, 0x09, 0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x05, 0x05,
  0x05, 0x05, 0x0c, 0x02, 0x09, 0x06, 0x09, 0x0e, 0x08, 0x0a, 0x0a, 0x0a,
  0x0a, 0x03, 0x05, 0x05, 0x05, 0x06, 0x00, 0x0b, 0x06, 0x09, 0x06, 0x09,
  0x06, 0x08, 0x08, 0x08, 0x0a, 0x09, 0x05, 0x05, 0x06, 0x09, 0x06, 0x09,
  0x0c, 0x00, 0x0b, 0x06, 0x09, 0x07, 0x05, 0x07, 0x0c, 0x01, 0x05, 0x05,
  0x0d, 0x04, 0x0b, 0x04, 0x01, 0x07, 0x0c, 0x09, 0x06, 0x09, 0x07, 0x0c,
  0x01, 0x05, 0x05, 0x05, 0x04, 0x03, 0x0c, 0x03, 0x06, 0x08, 0x03, 0x04,
  0x09, 0x06, 0x08, 0x03, 0x05, 0x05, 0x05, 0x05, 0x04, 0x09, 0x06, 0x09,
  0x0c, 0x02, 0x09, 0x04, 0x03, 0x0c, 0x02, 0x09, 0x05, 0x05, 0x05, 0x05,
  0x07, 0x04, 0x0b, 0x04, 0x01, 0x0d, 0x06, 0x03, 0x0c, 0x03, 0x0d, 0x06,
  0x01, 0x05, 0x05, 0x05, 0x0c, 0x03, 0x0c, 0x03, 0x06, 0x00, 0x0b, 0x0c,
  0x03, 0x0c, 0x02, 0x09, 0x06, 0x01, 0x05, 0x05, 0x05, 0x0e, 0x00, 0x0b,
  0x0c, 0x03, 0x0c, 0x03, 0x0c, 0x03, 0x0c, 0x00, 0x0b, 0x05, 0x05, 0x05,
  0x06, 0x09, 0x06, 0x08, 0x03, 0x0c, 0x03, 0x0c, 0x03, 0x0e, 0x01, 0x07,
  0x0c, 0x03, 0x05, 0x05, 0x0c, 0x03, 0x0d, 0x06, 0x08, 0x03, 0x0d, 0x06,
  0x09, 0x0d, 0x06, 0x08, 0x03, 0x0c, 0x01, 0x05, 0x05, 0x0c, 0x00, 0x09,
  0x07, 0x0c, 0x00, 0x09, 0x04, 0x00, 0x0b, 0x07, 0x0c, 0x03, 0x07, 0x05,
  0x06, 0x03, 0x07, 0x06, 0x0a, 0x03, 0x07, 0x06, 0x03, 0x07, 0x0e, 0x0a,
  0x02, 0x0a, 0x0a, 0x03
};

const uint8_t japan2014ef[] = {
  0x0e, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x03, 0x04, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x08, 0x09,
  0x04, 0x09, 0x0e, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x09, 0x0d,
  0x0d, 0x0d, 0x07, 0x05, 0x07, 0x04, 0x0b, 0x04, 0x08, 0x0b, 0x0c, 0x0a,
  0x03, 0x05, 0x04, 0x00, 0x00, 0x00, 0x09, 0x05, 0x0c, 0x03, 0x0d, 0x07,
  0x04, 0x09, 0x06, 0x09, 0x0d, 0x05, 0x07, 0x07, 0x07, 0x07, 0x05, 0x05,
  0x05, 0x0c, 0x00, 0x09, 0x07, 0x04, 0x09, 0x06, 0x02, 0x00, 0x0a, 0x0a,
  0x0a, 0x09, 0x05, 0x05, 0x05, 0x05, 0x07, 0x04, 0x09, 0x07, 0x04, 0x08,
  0x09, 0x04, 0x0b, 0x0c, 0x09, 0x05, 0x05, 0x05, 0x05, 0x06, 0x09, 0x07,
  0x04, 0x09, 0x07, 0x06, 0x01, 0x06, 0x09, 0x05, 0x05, 0x05, 0x05, 0x05,
  0x05, 0x0e, 0x00, 0x09, 0x07, 0x04, 0x09, 0x0e, 0x02, 0x09, 0x06, 0x03,
  0x05, 0x05, 0x05, 0x05, 0x05, 0x0c, 0x03, 0x04, 0x09, 0x07, 0x04, 0x09,
  0x0e, 0x02, 0x09, 0x0d, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x08, 0x03,
  0x06, 0x09, 0x07, 0x04, 0x09, 0x0e, 0x02, 0x01, 0x05, 0x05, 0x05, 0x05,
  0x05, 0x0c, 0x02, 0x09, 0x0c, 0x00, 0x09, 0x07, 0x04, 0x09, 0x0e, 0x02,
  0x03, 0x05, 0x05, 0x05, 0x06, 0x02, 0x0a, 0x02, 0x03, 0x07, 0x04, 0x0b,
  0x05, 0x04, 0x08, 0x0b, 0x0c, 0x03, 0x05, 0x05, 0x0c, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x03, 0x0c, 0x00, 0x01, 0x06, 0x08, 0x03, 0x0c, 0x03, 0x05,
  0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x03, 0x07, 0x06, 0x0a, 0x02,
  0x0b, 0x06, 0x0a, 0x03
};

const uint8_t japan2013ef[] = {
  0x0e, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x08, 0x08, 0x09, 0x0c, 0x0a, 0x0a, 0x08, 0x08, 0x09, 0x0c, 0x09,
  0x0c, 0x08, 0x09, 0x0d, 0x0d, 0x07, 0x05, 0x07, 0x04, 0x0b, 0x0c, 0x03,
  0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x00, 0x00, 0x09, 0x06, 0x09,
  0x04, 0x0b, 0x06, 0x09, 0x05, 0x06, 0x03, 0x06, 0x03, 0x04, 0x03, 0x07,
  0x05, 0x06, 0x09, 0x05, 0x05, 0x0e, 0x08, 0x03, 0x06, 0x09, 0x0c, 0x0a,
  0x0a, 0x03, 0x0c, 0x09, 0x06, 0x0a, 0x01, 0x05, 0x05, 0x0c, 0x01, 0x0c,
  0x0a, 0x03, 0x04, 0x09, 0x0c, 0x0a, 0x03, 0x06, 0x0a, 0x09, 0x05, 0x05,
  0x05, 0x05, 0x07, 0x06, 0x09, 0x0c, 0x03, 0x06, 0x03, 0x0d, 0x0d, 0x0d,
  0x0d, 0x05, 0x05, 0x05, 0x05, 0x06, 0x09, 0x0c, 0x01, 0x06, 0x09, 0x0c,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x05, 0x05, 0x05, 0x0c, 0x03, 0x05,
  0x05, 0x0c, 0x03, 0x06, 0x03, 0x05, 0x07, 0x07, 0x07, 0x05, 0x05, 0x05,
  0x05, 0x05, 0x0c, 0x02, 0x03, 0x06, 0x09, 0x0c, 0x09, 0x06, 0x09, 0x0c,
  0x0a, 0x03, 0x05, 0x05, 0x05, 0x05, 0x04, 0x09, 0x0c, 0x0b, 0x06, 0x03,
  0x06, 0x0a, 0x03, 0x06, 0x09, 0x0d, 0x05, 0x05, 0x05, 0x04, 0x03, 0x06,
  0x02, 0x0a, 0x09, 0x0c, 0x0b, 0x0c, 0x0a, 0x0a, 0x03, 0x04, 0x03, 0x05,
  0x05, 0x06, 0x0a, 0x0a, 0x09, 0x0d, 0x06, 0x02, 0x0a, 0x03, 0x0c, 0x0a,
  0x08, 0x03, 0x0e, 0x01, 0x04, 0x0a, 0x08, 0x0b, 0x06, 0x02, 0x0a, 0x0a,
  0x0a, 0x0a, 0x03, 0x0d, 0x05, 0x0c, 0x0a, 0x03, 0x05, 0x0d, 0x06, 0x0a,
  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x02, 0x03, 0x06, 0x0a, 0x09,
  0x06, 0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
  0x0a, 0x0a, 0x0a, 0x03
};

const uint8_t japan2014eq[] = {
  0x0e, 0x0a, 0x08, 0x08, 0x0a, 0x0a, 0x08, 0x08, 0x0a, 0x09, 0x0c, 0x0a,
  0x08, 0x08, 0x0a, 0x09, 0x0c, 0x08, 0x03, 0x06, 0x08, 0x08, 0x03, 0x06,
  0x08, 0x01, 0x04, 0x08, 0x03, 0x06, 0x09, 0x05, 0x05, 0x06, 0x09, 0x0c,
  0x03, 0x06, 0x09, 0x0c, 0x03, 0x06, 0x03, 0x06, 0x09, 0x0c, 0x02, 0x01,
  0x04, 0x09, 0x05, 0x04, 0x09, 0x0c, 0x01, 0x04, 0x09, 0x0c, 0x09, 0x0c,
  0x01, 0x05, 0x0c, 0x01, 0x05, 0x04, 0x02, 0x03, 0x06, 0x01, 0x04, 0x03,
  0x06, 0x01, 0x06, 0x03, 0x06, 0x01, 0x05, 0x05, 0x04, 0x02, 0x08, 0x09,
  0x0c, 0x03, 0x06, 0x09, 0x0c, 0x01, 0x0c, 0x09, 0x0c, 0x03, 0x06, 0x01,
  0x05, 0x0c, 0x03, 0x06, 0x02, 0x09, 0x0c, 0x02, 0x03, 0x06, 0x03, 0x06,
  0x02, 0x09, 0x0c, 0x03, 0x05, 0x04, 0x09, 0x0c, 0x08, 0x02, 0x03, 0x0c,
  0x09, 0x0c, 0x09, 0x0c, 0x09, 0x06, 0x02, 0x09, 0x05, 0x05, 0x04, 0x03,
  0x06, 0x08, 0x09, 0x06, 0x01, 0x05, 0x04, 0x03, 0x06, 0x09, 0x0c, 0x03,
  0x04, 0x03, 0x06, 0x09, 0x0c, 0x03, 0x06, 0x09, 0x04, 0x03, 0x06, 0x09,
  0x0c, 0x01, 0x06, 0x09, 0x04, 0x09, 0x0c, 0x01, 0x04, 0x09, 0x0c, 0x01,
  0x06, 0x09, 0x0c, 0x02, 0x03, 0x06, 0x09, 0x05, 0x05, 0x04, 0x03, 0x06,
  0x01, 0x04, 0x03, 0x06, 0x09, 0x05, 0x04, 0x08, 0x09, 0x0c, 0x01, 0x05,
  0x04, 0x02, 0x09, 0x0c, 0x03, 0x06, 0x09, 0x0c, 0x03, 0x05, 0x05, 0x05,
  0x06, 0x03, 0x06, 0x01, 0x05, 0x0e, 0x01, 0x06, 0x09, 0x0c, 0x03, 0x06,
  0x09, 0x06, 0x03, 0x06, 0x08, 0x09, 0x0c, 0x01, 0x05, 0x0e, 0x01, 0x0c,
  0x01, 0x04, 0x09, 0x0c, 0x02, 0x0a, 0x09, 0x0c, 0x01, 0x06, 0x03, 0x05,
  0x06, 0x0a, 0x02, 0x03, 0x06, 0x03, 0x06, 0x02, 0x0a, 0x0a, 0x02, 0x03,
  0x06, 0x0a, 0x0a, 0x03
};

const uint8_t taiwan2014[] = {
  0x0e, 0x08, 0x0a, 0x08, 0x08, 0x0a, 0x08, 0x0a, 0x09, 0x0c, 0x08, 0x0a,
  0x08, 0x0b, 0x0c, 0x09, 0x0c, 0x02, 0x08, 0x01, 0x05, 0x0c, 0x02, 0x0a,
  0x02, 0x03, 0x06, 0x0a, 0x02, 0x0a, 0x03, 0x05, 0x05, 0x0e, 0x03, 0x06,
  0x01, 0x06, 0x08, 0x0a, 0x08, 0x08, 0x0b, 0x0c, 0x0a, 0x08, 0x09, 0x05,
  0x04, 0x09, 0x0c, 0x09, 0x06, 0x09, 0x05, 0x0d, 0x05, 0x05, 0x0e, 0x01,
  0x0d, 0x07, 0x05, 0x05, 0x05, 0x04, 0x01, 0x04, 0x09, 0x06, 0x01, 0x05,
  0x06, 0x02, 0x0b, 0x04, 0x02, 0x0a, 0x01, 0x05, 0x04, 0x01, 0x04, 0x01,
  0x04, 0x0b, 0x07, 0x04, 0x09, 0x0e, 0x0a, 0x01, 0x0e, 0x0b, 0x05, 0x05,
  0x05, 0x04, 0x01, 0x07, 0x05, 0x0e, 0x08, 0x03, 0x06, 0x09, 0x0d, 0x04,
  0x0a, 0x0a, 0x01, 0x05, 0x04, 0x03, 0x05, 0x0e, 0x03, 0x0c, 0x02, 0x08,
  0x09, 0x06, 0x01, 0x06, 0x08, 0x0a, 0x01, 0x05, 0x06, 0x08, 0x02, 0x09,
  0x0e, 0x02, 0x09, 0x06, 0x03, 0x0e, 0x02, 0x08, 0x03, 0x0e, 0x01, 0x05,
  0x0e, 0x00, 0x0a, 0x01, 0x0c, 0x09, 0x07, 0x0c, 0x0a, 0x09, 0x0c, 0x02,
  0x08, 0x0a, 0x01, 0x05, 0x0e, 0x00, 0x0a, 0x01, 0x05, 0x06, 0x09, 0x05,
  0x0c, 0x00, 0x01, 0x0d, 0x06, 0x09, 0x05, 0x05, 0x0e, 0x00, 0x0a, 0x00,
  0x00, 0x0b, 0x05, 0x04, 0x03, 0x05, 0x06, 0x01, 0x0d, 0x06, 0x01, 0x05,
  0x0e, 0x00, 0x0a, 0x01, 0x04, 0x0b, 0x05, 0x06, 0x0a, 0x03, 0x0d, 0x06,
  0x00, 0x0b, 0x05, 0x05, 0x0e, 0x00, 0x0b, 0x04, 0x03, 0x0c, 0x03, 0x0c,
  0x0a, 0x08, 0x02, 0x08, 0x02, 0x08, 0x01, 0x05, 0x0e, 0x01, 0x0c, 0x03,
  0x0c, 0x02, 0x08, 0x02, 0x08, 0x02, 0x09, 0x06, 0x09, 0x05, 0x05, 0x05,
  0x0e, 0x02, 0x02, 0x0a, 0x02, 0x0a, 0x02, 0x0a, 0x02, 0x0a, 0x02, 0x0a,
  0x02, 0x02, 0x02, 0x03
};

const uint8_t uk2014f[] = {
  0x0e, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x0a, 0x09, 0x0c,
  0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x01,
  0x05, 0x0c, 0x03, 0x05, 0x0d, 0x0d, 0x0d, 0x05, 0x05, 0x0e, 0x08, 0x0a,
  0x0a, 0x0a, 0x0a, 0x03, 0x05, 0x06, 0x09, 0x05, 0x04, 0x00, 0x00, 0x01,
  0x06, 0x09, 0x06, 0x09, 0x0d, 0x0e, 0x0a, 0x08, 0x01, 0x0e, 0x01, 0x05,
  0x05, 0x07, 0x05, 0x07, 0x0d, 0x06, 0x09, 0x06, 0x01, 0x0c, 0x0a, 0x03,
  0x05, 0x0d, 0x05, 0x05, 0x06, 0x09, 0x04, 0x09, 0x04, 0x09, 0x05, 0x0f,
  0x05, 0x06, 0x0a, 0x09, 0x05, 0x05, 0x06, 0x03, 0x0c, 0x03, 0x05, 0x05,
  0x05, 0x06, 0x03, 0x0c, 0x03, 0x0c, 0x0a, 0x03, 0x07, 0x04, 0x0a, 0x09,
  0x06, 0x09, 0x07, 0x05, 0x06, 0x0a, 0x09, 0x06, 0x0a, 0x02, 0x0b, 0x0c,
  0x09, 0x06, 0x09, 0x06, 0x0a, 0x03, 0x0e, 0x03, 0x0c, 0x0a, 0x00, 0x0a,
  0x0a, 0x0a, 0x0b, 0x06, 0x02, 0x09, 0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x09,
  0x05, 0x0e, 0x02, 0x0a, 0x09, 0x0c, 0x0b, 0x0c, 0x09, 0x06, 0x0a, 0x0a,
  0x09, 0x0e, 0x08, 0x01, 0x05, 0x0c, 0x0b, 0x0c, 0x03, 0x05, 0x0e, 0x01,
  0x05, 0x0e, 0x08, 0x08, 0x02, 0x0b, 0x07, 0x05, 0x07, 0x05, 0x0c, 0x03,
  0x0c, 0x01, 0x0c, 0x03, 0x04, 0x0b, 0x05, 0x05, 0x0d, 0x0d, 0x0d, 0x05,
  0x0c, 0x02, 0x03, 0x0c, 0x03, 0x05, 0x06, 0x09, 0x05, 0x0d, 0x05, 0x06,
  0x00, 0x00, 0x00, 0x01, 0x05, 0x0f, 0x0c, 0x03, 0x0c, 0x03, 0x0c, 0x03,
  0x04, 0x03, 0x06, 0x09, 0x07, 0x07, 0x07, 0x05, 0x05, 0x0c, 0x03, 0x0c,
  0x03, 0x0d, 0x06, 0x09, 0x06, 0x09, 0x0f, 0x07, 0x0d, 0x0c, 0x09, 0x05,
  0x06, 0x03, 0x0e, 0x02, 0x0a, 0x02, 0x0a, 0x03, 0x0e, 0x02, 0x0a, 0x0a,
  0x02, 0x03, 0x06, 0x03
};

const uint8_t taiwan2015[] = {
  0x0e, 0x08, 0x0a, 0x08, 0x08, 0x0a, 0x08, 0x0a, 0x09, 0x0c, 0x09, 0x0c, 0x08, 0x0b, 0x0c, 0x09,
  0x0c, 0x02, 0x08, 0x01, 0x05, 0x0c, 0x02, 0x0a, 0x02, 0x03, 0x06, 0x03, 0x06, 0x0a, 0x03, 0x05,
  0x05, 0x0e, 0x03, 0x06, 0x00, 0x02, 0x0a, 0x0a, 0x08, 0x08, 0x0b, 0x0c, 0x0a, 0x08, 0x09, 0x05,
  0x04, 0x09, 0x0c, 0x09, 0x07, 0x0c, 0x09, 0x0d, 0x05, 0x05, 0x0e, 0x01, 0x0d, 0x07, 0x05, 0x05,
  0x05, 0x04, 0x01, 0x05, 0x0c, 0x03, 0x04, 0x01, 0x06, 0x02, 0x0b, 0x04, 0x02, 0x0a, 0x01, 0x05,
  0x04, 0x01, 0x04, 0x01, 0x04, 0x09, 0x07, 0x06, 0x09, 0x0e, 0x0a, 0x01, 0x0e, 0x0b, 0x05, 0x05,
  0x05, 0x04, 0x01, 0x07, 0x05, 0x06, 0x08, 0x0b, 0x06, 0x09, 0x0d, 0x04, 0x0a, 0x0a, 0x01, 0x05,
  0x04, 0x03, 0x05, 0x0e, 0x03, 0x0c, 0x02, 0x08, 0x09, 0x04, 0x03, 0x04, 0x08, 0x0a, 0x01, 0x05,
  0x06, 0x08, 0x02, 0x0b, 0x0c, 0x02, 0x09, 0x06, 0x03, 0x06, 0x09, 0x05, 0x07, 0x0d, 0x05, 0x05,
  0x0e, 0x00, 0x0b, 0x0d, 0x05, 0x0d, 0x07, 0x0c, 0x0a, 0x08, 0x02, 0x02, 0x08, 0x02, 0x01, 0x05,
  0x0e, 0x03, 0x0c, 0x01, 0x05, 0x06, 0x09, 0x05, 0x0c, 0x00, 0x09, 0x0d, 0x06, 0x09, 0x05, 0x05,
  0x0c, 0x08, 0x01, 0x05, 0x04, 0x0b, 0x05, 0x04, 0x03, 0x05, 0x06, 0x01, 0x0d, 0x06, 0x01, 0x05,
  0x07, 0x05, 0x06, 0x00, 0x00, 0x0b, 0x05, 0x06, 0x0a, 0x03, 0x0d, 0x06, 0x00, 0x0b, 0x05, 0x05,
  0x0e, 0x00, 0x0b, 0x05, 0x07, 0x0c, 0x03, 0x0c, 0x0a, 0x08, 0x02, 0x08, 0x02, 0x08, 0x01, 0x05,
  0x0e, 0x01, 0x0e, 0x03, 0x0c, 0x02, 0x08, 0x02, 0x08, 0x02, 0x09, 0x06, 0x09, 0x05, 0x07, 0x05,
  0x0e, 0x02, 0x0a, 0x0a, 0x02, 0x0a, 0x02, 0x0a, 0x02, 0x0a, 0x02, 0x0a, 0x02, 0x02, 0x0a, 0x03
};

const uint8_t emptyMaze[] = {
  0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09,
  0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03
};


const uint8_t apec1997[] = {
  0x0e, 0x0a, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09,
  0x0c, 0x0a, 0x03, 0x0e, 0x08, 0x09, 0x0c, 0x09, 0x0c, 0x09, 0x0d, 0x0c, 0x0a, 0x0a, 0x09, 0x05,
  0x05, 0x0c, 0x0a, 0x09, 0x05, 0x06, 0x03, 0x06, 0x03, 0x06, 0x01, 0x05, 0x0c, 0x09, 0x05, 0x05,
  0x05, 0x06, 0x09, 0x05, 0x04, 0x09, 0x0c, 0x09, 0x0c, 0x09, 0x06, 0x03, 0x05, 0x06, 0x01, 0x05,
  0x05, 0x0c, 0x03, 0x05, 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x0c, 0x09, 0x06, 0x09, 0x07, 0x05,
  0x05, 0x06, 0x09, 0x06, 0x09, 0x06, 0x03, 0x06, 0x03, 0x06, 0x03, 0x06, 0x09, 0x06, 0x09, 0x05,
  0x05, 0x0e, 0x02, 0x09, 0x05, 0x0d, 0x0c, 0x0a, 0x0a, 0x09, 0x0c, 0x09, 0x06, 0x09, 0x06, 0x01,
  0x05, 0x0c, 0x0a, 0x03, 0x05, 0x05, 0x04, 0x08, 0x09, 0x05, 0x05, 0x06, 0x09, 0x06, 0x09, 0x05,
  0x05, 0x06, 0x0a, 0x09, 0x05, 0x05, 0x05, 0x06, 0x03, 0x05, 0x06, 0x09, 0x06, 0x09, 0x05, 0x05,
  0x05, 0x0c, 0x0a, 0x03, 0x05, 0x05, 0x06, 0x0a, 0x0a, 0x00, 0x0b, 0x06, 0x09, 0x06, 0x01, 0x05,
  0x05, 0x06, 0x0a, 0x09, 0x05, 0x06, 0x08, 0x0a, 0x09, 0x06, 0x0a, 0x09, 0x06, 0x09, 0x07, 0x05,
  0x05, 0x0c, 0x0a, 0x03, 0x06, 0x09, 0x06, 0x09, 0x06, 0x09, 0x0e, 0x00, 0x0b, 0x06, 0x09, 0x05,
  0x05, 0x06, 0x09, 0x0e, 0x09, 0x06, 0x09, 0x06, 0x09, 0x06, 0x09, 0x06, 0x0a, 0x09, 0x05, 0x05,
  0x05, 0x0c, 0x03, 0x0c, 0x00, 0x09, 0x06, 0x09, 0x06, 0x09, 0x06, 0x09, 0x0e, 0x00, 0x03, 0x05,
  0x05, 0x06, 0x0a, 0x03, 0x05, 0x04, 0x0b, 0x06, 0x0a, 0x02, 0x0b, 0x06, 0x0a, 0x02, 0x0b, 0x05,
  0x06, 0x0a, 0x0a, 0x0a, 0x02, 0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x03
};

const uint8_t apec1996[] = {
  0x0e, 0x0a, 0x08, 0x0a, 0x08, 0x0a, 0x0a, 0x0b, 0x0c, 0x0a, 0x0a, 0x0a, 0x09, 0x0c, 0x09, 0x0d,
  0x0c, 0x0a, 0x02, 0x08, 0x01, 0x0c, 0x0a, 0x09, 0x06, 0x09, 0x0c, 0x09, 0x06, 0x03, 0x06, 0x01,
  0x04, 0x0a, 0x0a, 0x03, 0x06, 0x00, 0x09, 0x05, 0x0d, 0x06, 0x03, 0x05, 0x0c, 0x09, 0x0d, 0x05,
  0x05, 0x0c, 0x0a, 0x0a, 0x09, 0x07, 0x06, 0x00, 0x01, 0x0d, 0x0e, 0x02, 0x01, 0x06, 0x01, 0x05,
  0x04, 0x01, 0x0e, 0x0a, 0x00, 0x0a, 0x09, 0x07, 0x06, 0x00, 0x09, 0x0d, 0x06, 0x09, 0x05, 0x05,
  0x05, 0x05, 0x0c, 0x09, 0x06, 0x0a, 0x01, 0x0c, 0x09, 0x07, 0x06, 0x00, 0x09, 0x05, 0x05, 0x05,
  0x04, 0x02, 0x01, 0x04, 0x09, 0x0d, 0x04, 0x03, 0x06, 0x0a, 0x09, 0x07, 0x06, 0x03, 0x05, 0x05,
  0x05, 0x0c, 0x02, 0x01, 0x04, 0x01, 0x05, 0x0c, 0x09, 0x0e, 0x02, 0x0a, 0x0a, 0x09, 0x05, 0x05,
  0x05, 0x06, 0x08, 0x02, 0x01, 0x05, 0x05, 0x06, 0x01, 0x0c, 0x0a, 0x08, 0x0b, 0x05, 0x05, 0x05,
  0x06, 0x09, 0x04, 0x08, 0x02, 0x01, 0x04, 0x09, 0x04, 0x03, 0x0c, 0x03, 0x0c, 0x03, 0x05, 0x05,
  0x0c, 0x03, 0x05, 0x04, 0x08, 0x02, 0x01, 0x05, 0x07, 0x0c, 0x03, 0x0c, 0x03, 0x0d, 0x05, 0x05,
  0x06, 0x09, 0x06, 0x03, 0x06, 0x0a, 0x03, 0x06, 0x0a, 0x03, 0x0c, 0x03, 0x0c, 0x01, 0x05, 0x05,
  0x0c, 0x03, 0x0d, 0x0c, 0x09, 0x0c, 0x09, 0x0c, 0x09, 0x0c, 0x02, 0x08, 0x03, 0x05, 0x05, 0x05,
  0x05, 0x0c, 0x02, 0x03, 0x06, 0x03, 0x06, 0x03, 0x05, 0x06, 0x0a, 0x03, 0x0c, 0x02, 0x01, 0x05,
  0x05, 0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x02, 0x0a, 0x0a, 0x0a, 0x02, 0x0a, 0x03, 0x05,
  0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x03
};

const uint8_t japan2000[] = {
  0x0e, 0x0a, 0x0a, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x08, 0x0a, 0x0a, 0x0a, 0x08, 0x0a, 0x0a, 0x09,
  0x0c, 0x0a, 0x0a, 0x03, 0x05, 0x0e, 0x0a, 0x0b, 0x05, 0x0e, 0x0b, 0x0c, 0x02, 0x09, 0x0d, 0x05,
  0x05, 0x0e, 0x0b, 0x0c, 0x02, 0x0a, 0x09, 0x0e, 0x02, 0x08, 0x0a, 0x03, 0x0f, 0x05, 0x07, 0x05,
  0x05, 0x0e, 0x0b, 0x05, 0x0e, 0x0b, 0x04, 0x0a, 0x0a, 0x03, 0x0e, 0x0b, 0x0d, 0x06, 0x0a, 0x01,
  0x05, 0x0e, 0x0b, 0x05, 0x0e, 0x0a, 0x01, 0x0c, 0x09, 0x0c, 0x0a, 0x0a, 0x01, 0x0c, 0x09, 0x05,
  0x05, 0x0e, 0x0b, 0x05, 0x0c, 0x09, 0x05, 0x06, 0x03, 0x05, 0x0c, 0x09, 0x05, 0x06, 0x03, 0x05,
  0x04, 0x0a, 0x0a, 0x01, 0x06, 0x03, 0x05, 0x0e, 0x0a, 0x01, 0x06, 0x03, 0x06, 0x0a, 0x0a, 0x01,
  0x05, 0x0c, 0x09, 0x04, 0x0a, 0x0a, 0x01, 0x0c, 0x08, 0x02, 0x0a, 0x0a, 0x09, 0x0c, 0x09, 0x07,
  0x05, 0x06, 0x03, 0x05, 0x0c, 0x09, 0x05, 0x06, 0x03, 0x0d, 0x0c, 0x09, 0x05, 0x06, 0x03, 0x0d,
  0x04, 0x0a, 0x0a, 0x01, 0x06, 0x03, 0x05, 0x0e, 0x0a, 0x01, 0x06, 0x03, 0x06, 0x0a, 0x0a, 0x01,
  0x05, 0x0e, 0x0b, 0x04, 0x0a, 0x0a, 0x01, 0x0c, 0x09, 0x04, 0x0a, 0x0a, 0x09, 0x0c, 0x09, 0x05,
  0x05, 0x0e, 0x0b, 0x05, 0x0e, 0x0b, 0x05, 0x06, 0x03, 0x05, 0x0c, 0x09, 0x05, 0x06, 0x03, 0x05,
  0x05, 0x0e, 0x0b, 0x04, 0x0a, 0x0a, 0x02, 0x0a, 0x08, 0x03, 0x06, 0x03, 0x04, 0x0a, 0x09, 0x05,
  0x05, 0x0e, 0x0b, 0x05, 0x0e, 0x0a, 0x0a, 0x0b, 0x05, 0x0c, 0x0a, 0x0a, 0x03, 0x0d, 0x05, 0x05,
  0x06, 0x0a, 0x0a, 0x02, 0x0a, 0x08, 0x0a, 0x0a, 0x03, 0x05, 0x0e, 0x0a, 0x0a, 0x03, 0x05, 0x05,
  0x0e, 0x0a, 0x0a, 0x0a, 0x0a, 0x02, 0x0a, 0x0a, 0x0a, 0x02, 0x0a, 0x0a, 0x0a, 0x0a, 0x02, 0x03
};

const uint8_t japan99[] = {
  0x0e, 0x09, 0x0d, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09,
  0x0c, 0x03, 0x04, 0x03, 0x0c, 0x0a, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x05,
  0x05, 0x0c, 0x03, 0x0c, 0x03, 0x0c, 0x03, 0x06, 0x0a, 0x0a, 0x09, 0x0c, 0x0a, 0x09, 0x05, 0x05,
  0x05, 0x05, 0x0c, 0x03, 0x0c, 0x03, 0x0c, 0x0a, 0x0a, 0x0a, 0x03, 0x05, 0x0c, 0x03, 0x05, 0x05,
  0x05, 0x06, 0x03, 0x0c, 0x03, 0x0d, 0x06, 0x0a, 0x0a, 0x0a, 0x09, 0x05, 0x06, 0x0a, 0x03, 0x05,
  0x05, 0x0e, 0x08, 0x03, 0x0e, 0x00, 0x08, 0x0a, 0x0a, 0x08, 0x03, 0x06, 0x0a, 0x0a, 0x09, 0x05,
  0x05, 0x0c, 0x03, 0x0c, 0x0a, 0x03, 0x06, 0x0a, 0x0a, 0x03, 0x0c, 0x0a, 0x0a, 0x0a, 0x03, 0x05,
  0x05, 0x06, 0x09, 0x06, 0x0a, 0x0a, 0x09, 0x0c, 0x08, 0x09, 0x06, 0x0a, 0x0a, 0x0a, 0x09, 0x05,
  0x04, 0x0a, 0x00, 0x0a, 0x0a, 0x0a, 0x03, 0x04, 0x03, 0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x03, 0x05,
  0x06, 0x09, 0x05, 0x0c, 0x09, 0x0c, 0x09, 0x06, 0x08, 0x0b, 0x0c, 0x09, 0x0c, 0x09, 0x0c, 0x01,
  0x0c, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x0d, 0x06, 0x09, 0x05, 0x06, 0x03, 0x06, 0x03, 0x05,
  0x06, 0x09, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x09, 0x06, 0x03, 0x0c, 0x09, 0x0c, 0x09, 0x05,
  0x0c, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x0c, 0x08, 0x03, 0x06, 0x03, 0x06, 0x01,
  0x06, 0x09, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x09, 0x0c, 0x09, 0x0c, 0x01,
  0x0c, 0x03, 0x06, 0x03, 0x06, 0x03, 0x06, 0x03, 0x06, 0x03, 0x07, 0x06, 0x03, 0x06, 0x03, 0x05,
  0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x03
};

const uint8_t japan98[] = {
  0x0e, 0x08, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x09,
  0x0c, 0x03, 0x0c, 0x0a, 0x08, 0x0b, 0x0c, 0x09, 0x0c, 0x09, 0x0c, 0x0a, 0x09, 0x0e, 0x08, 0x01,
  0x05, 0x0e, 0x00, 0x0b, 0x06, 0x09, 0x05, 0x06, 0x03, 0x06, 0x03, 0x0c, 0x03, 0x0c, 0x03, 0x07,
  0x05, 0x0e, 0x00, 0x0b, 0x0c, 0x03, 0x06, 0x0a, 0x0a, 0x0a, 0x09, 0x05, 0x0c, 0x03, 0x0c, 0x09,
  0x05, 0x0e, 0x00, 0x0b, 0x06, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x03, 0x05, 0x06, 0x09, 0x05, 0x05,
  0x05, 0x0e, 0x00, 0x0b, 0x0c, 0x03, 0x06, 0x0a, 0x0a, 0x0a, 0x09, 0x04, 0x09, 0x06, 0x03, 0x05,
  0x05, 0x0e, 0x00, 0x0b, 0x06, 0x09, 0x0c, 0x0a, 0x0a, 0x0a, 0x03, 0x07, 0x05, 0x0d, 0x0c, 0x03,
  0x05, 0x0e, 0x00, 0x0b, 0x0c, 0x03, 0x06, 0x08, 0x09, 0x0c, 0x0a, 0x09, 0x06, 0x01, 0x06, 0x09,
  0x05, 0x0e, 0x00, 0x0b, 0x06, 0x09, 0x0d, 0x04, 0x03, 0x06, 0x09, 0x06, 0x09, 0x06, 0x08, 0x03,
  0x05, 0x0c, 0x02, 0x09, 0x0c, 0x03, 0x05, 0x06, 0x0a, 0x09, 0x06, 0x09, 0x06, 0x09, 0x06, 0x09,
  0x04, 0x02, 0x08, 0x03, 0x05, 0x0c, 0x02, 0x08, 0x09, 0x06, 0x09, 0x04, 0x0b, 0x06, 0x09, 0x05,
  0x06, 0x09, 0x06, 0x09, 0x04, 0x03, 0x0c, 0x03, 0x06, 0x09, 0x06, 0x00, 0x0a, 0x09, 0x05, 0x05,
  0x0c, 0x03, 0x0c, 0x03, 0x07, 0x0c, 0x03, 0x0c, 0x09, 0x06, 0x09, 0x06, 0x09, 0x07, 0x05, 0x05,
  0x06, 0x09, 0x06, 0x09, 0x0c, 0x03, 0x0c, 0x03, 0x06, 0x09, 0x06, 0x09, 0x04, 0x09, 0x05, 0x05,
  0x0c, 0x02, 0x0a, 0x03, 0x06, 0x0a, 0x03, 0x0c, 0x09, 0x06, 0x09, 0x06, 0x03, 0x07, 0x05, 0x05,
  0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x03, 0x06, 0x0a, 0x02, 0x0b, 0x0e, 0x0a, 0x02, 0x03
};

const uint8_t apec1998[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X08, 0X03, 0X0C, 0X08, 0X0B, 0X0D, 0X0C, 0X09, 0X0D, 0X07, 0X0C, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X0C, 0X01, 0X07, 0X0C, 0X00, 0X03, 0X06, 0X00, 0X09, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X07, 0X0D, 0X05, 0X07, 0X0D, 0X0D, 0X07, 0X06, 0X08, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X04, 0X03, 0X0C, 0X00, 0X03, 0X0D, 0X04, 0X00, 0X09, 0X0D, 0X07, 0X06, 0X01, 0X05, 0X05,
  0X05, 0X07, 0X0D, 0X05, 0X07, 0X0E, 0X01, 0X05, 0X07, 0X06, 0X00, 0X09, 0X0D, 0X07, 0X05, 0X05,
  0X05, 0X0C, 0X00, 0X03, 0X0D, 0X0C, 0X00, 0X03, 0X0C, 0X09, 0X07, 0X06, 0X00, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X07, 0X0E, 0X01, 0X05, 0X07, 0X0C, 0X01, 0X05, 0X0C, 0X09, 0X07, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X0D, 0X0C, 0X00, 0X03, 0X0D, 0X06, 0X03, 0X05, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X03, 0X07, 0X0C, 0X02, 0X0A, 0X0A, 0X01, 0X06, 0X0A, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X0D, 0X06, 0X0A, 0X09, 0X0D, 0X06, 0X0A, 0X09, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X0D, 0X06, 0X00, 0X09, 0X0D, 0X06, 0X02, 0X08, 0X09, 0X05, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X09, 0X07, 0X06, 0X00, 0X09, 0X0D, 0X07, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X07, 0X06, 0X00, 0X09, 0X05, 0X0C, 0X09, 0X0C, 0X01, 0X05,
  0X05, 0X05, 0X07, 0X06, 0X03, 0X06, 0X0A, 0X09, 0X07, 0X05, 0X06, 0X03, 0X06, 0X03, 0X07, 0X05,
  0X06, 0X03, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};
const uint8_t apec2012[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X0E, 0X08, 0X0A, 0X09, 0X06, 0X00, 0X0B, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X07, 0X0C, 0X03, 0X07, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X02, 0X0B, 0X05, 0X0C, 0X02, 0X0B, 0X06, 0X0A, 0X03, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X08, 0X09, 0X06, 0X03, 0X0E, 0X08, 0X0A, 0X09, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X03, 0X07, 0X05, 0X0D, 0X0C, 0X09, 0X05, 0X0C, 0X03, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X08, 0X0A, 0X03, 0X04, 0X02, 0X03, 0X05, 0X06, 0X09, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X09, 0X0C, 0X01, 0X0C, 0X09, 0X05, 0X0C, 0X03, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0E, 0X02, 0X03, 0X07, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X06, 0X0A, 0X09, 0X0C, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X03, 0X05, 0X0C, 0X0A, 0X09, 0X06, 0X08, 0X0B, 0X06, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X0E, 0X01, 0X0E, 0X00, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0B, 0X06, 0X09, 0X07, 0X06, 0X03, 0X06, 0X03, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};
const uint8_t apec2013[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X0C, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0D, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X03, 0X05, 0X0C, 0X08, 0X0B, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X0E, 0X02, 0X03, 0X06, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X03, 0X06, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X02, 0X0A, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X01, 0X05, 0X05,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X03, 0X0D, 0X0C, 0X09, 0X0D, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X0D, 0X0D, 0X0C, 0X0A, 0X01, 0X06, 0X01, 0X04, 0X03, 0X0C, 0X03, 0X07, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X0C, 0X02, 0X0B, 0X0D, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X03, 0X0C, 0X03, 0X0C, 0X01, 0X0C, 0X03, 0X06, 0X0A, 0X09, 0X04, 0X01, 0X05,
  0X05, 0X06, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X07, 0X05, 0X0C, 0X09, 0X0D, 0X06, 0X01, 0X05, 0X05,
  0X05, 0X0D, 0X0C, 0X03, 0X0C, 0X00, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X04, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X04, 0X03, 0X0C, 0X03, 0X05, 0X0E, 0X01, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0B, 0X06, 0X03, 0X06, 0X03, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};


const uint8_t japan11[] = {
  0X0E, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X09, 0X0C, 0X08, 0X08, 0X08, 0X0A, 0X0A, 0X0B, 0X0C, 0X09,
  0X0C, 0X02, 0X01, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X0D, 0X0D, 0X05, 0X05,
  0X06, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X05, 0X07, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X0E, 0X02, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X04, 0X01, 0X05,
  0X0C, 0X0A, 0X02, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X02, 0X09, 0X06, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X07, 0X05, 0X05, 0X07, 0X06, 0X01, 0X05, 0X05,
  0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B, 0X0C, 0X08, 0X09, 0X05, 0X06, 0X08, 0X0B, 0X07, 0X07, 0X05,
  0X04, 0X0A, 0X08, 0X0A, 0X0A, 0X0B, 0X05, 0X06, 0X03, 0X05, 0X0C, 0X02, 0X08, 0X08, 0X08, 0X01,
  0X05, 0X0E, 0X02, 0X0A, 0X08, 0X0B, 0X06, 0X0A, 0X09, 0X05, 0X06, 0X08, 0X01, 0X05, 0X05, 0X05,
  0X04, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X09, 0X0D, 0X04, 0X01, 0X0C, 0X03, 0X04, 0X00, 0X01, 0X05,
  0X07, 0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X03, 0X05, 0X07, 0X05, 0X06, 0X0A, 0X01, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X09, 0X04, 0X09, 0X05, 0X0E, 0X08, 0X00, 0X02, 0X01, 0X05,
  0X04, 0X0A, 0X0A, 0X09, 0X0C, 0X03, 0X06, 0X03, 0X06, 0X02, 0X0B, 0X05, 0X05, 0X0E, 0X02, 0X01,
  0X04, 0X0A, 0X0A, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X08, 0X0B, 0X05,
  0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t japan13[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X03, 0X0D, 0X0C, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X05, 0X0D, 0X06, 0X01, 0X0E, 0X08, 0X02, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X04, 0X01, 0X0D, 0X04, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03,
  0X05, 0X06, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X09,
  0X04, 0X08, 0X02, 0X08, 0X0A, 0X0A, 0X08, 0X09, 0X0E, 0X08, 0X0A, 0X09, 0X07, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X0D, 0X06, 0X09, 0X0E, 0X01, 0X06, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X04, 0X01, 0X0D, 0X06, 0X09, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X00, 0X0B, 0X04, 0X03, 0X06, 0X01, 0X05, 0X06, 0X03, 0X0D, 0X06, 0X03, 0X05,
  0X05, 0X04, 0X01, 0X07, 0X0C, 0X03, 0X0C, 0X09, 0X05, 0X06, 0X09, 0X0C, 0X00, 0X09, 0X0D, 0X05,
  0X04, 0X01, 0X07, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X0C, 0X03, 0X05, 0X05, 0X04, 0X01, 0X05,
  0X05, 0X07, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X01, 0X05, 0X05, 0X0F, 0X05, 0X04, 0X01, 0X05, 0X05,
  0X07, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X02, 0X09, 0X05, 0X04, 0X0A, 0X09, 0X0D, 0X04, 0X01, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X02, 0X0A, 0X02, 0X03, 0X06, 0X09, 0X05, 0X04, 0X03, 0X05, 0X06, 0X01,
  0X06, 0X03, 0X0E, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X02, 0X0A, 0X03, 0X0E, 0X03
};

const uint8_t japan2011ef[] = {
  0X0E, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X0B, 0X0D, 0X0D, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X09,
  0X0C, 0X01, 0X06, 0X08, 0X09, 0X0D, 0X0C, 0X00, 0X00, 0X00, 0X00, 0X08, 0X0A, 0X0A, 0X03, 0X05,
  0X05, 0X04, 0X09, 0X07, 0X07, 0X04, 0X03, 0X07, 0X07, 0X05, 0X07, 0X07, 0X0C, 0X0A, 0X09, 0X05,
  0X05, 0X07, 0X06, 0X09, 0X0C, 0X02, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X0A, 0X01, 0X0C, 0X01, 0X05,
  0X04, 0X0A, 0X0A, 0X02, 0X02, 0X08, 0X0A, 0X0A, 0X03, 0X06, 0X03, 0X0D, 0X07, 0X05, 0X05, 0X05,
  0X04, 0X0A, 0X0B, 0X0C, 0X0A, 0X03, 0X0C, 0X0A, 0X08, 0X09, 0X0E, 0X02, 0X0A, 0X03, 0X07, 0X05,
  0X04, 0X0A, 0X08, 0X02, 0X0B, 0X0C, 0X00, 0X0A, 0X03, 0X04, 0X09, 0X0C, 0X0A, 0X08, 0X0A, 0X01,
  0X04, 0X09, 0X06, 0X0A, 0X0B, 0X05, 0X06, 0X08, 0X09, 0X05, 0X05, 0X04, 0X08, 0X02, 0X08, 0X01,
  0X05, 0X06, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X03, 0X05, 0X05, 0X05, 0X06, 0X08, 0X03, 0X05,
  0X04, 0X0A, 0X0B, 0X0C, 0X03, 0X0E, 0X02, 0X09, 0X0E, 0X02, 0X01, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X0C, 0X09, 0X06, 0X0A, 0X09, 0X0E, 0X02, 0X09, 0X0C, 0X02, 0X09, 0X06, 0X08, 0X03, 0X05,
  0X04, 0X03, 0X06, 0X08, 0X0A, 0X02, 0X09, 0X0E, 0X02, 0X00, 0X0A, 0X02, 0X08, 0X01, 0X0E, 0X01,
  0X04, 0X09, 0X0C, 0X02, 0X09, 0X0E, 0X02, 0X09, 0X0E, 0X02, 0X08, 0X0A, 0X01, 0X05, 0X0E, 0X01,
  0X05, 0X04, 0X03, 0X0E, 0X01, 0X0D, 0X0C, 0X03, 0X0D, 0X0D, 0X06, 0X09, 0X06, 0X00, 0X0A, 0X01,
  0X04, 0X01, 0X0D, 0X0D, 0X05, 0X05, 0X06, 0X09, 0X04, 0X02, 0X09, 0X06, 0X0A, 0X02, 0X0A, 0X01,
  0X07, 0X06, 0X02, 0X02, 0X02, 0X02, 0X0A, 0X02, 0X03, 0X0F, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t japan2011ff[] = {
  0X0E, 0X0A, 0X0A, 0X09, 0X0F, 0X0E, 0X09, 0X0C, 0X09, 0X0D, 0X0F, 0X0F, 0X0C, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X0B, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X0D, 0X04, 0X0A, 0X0B, 0X05,
  0X05, 0X0C, 0X0A, 0X01, 0X05, 0X05, 0X04, 0X02, 0X02, 0X01, 0X06, 0X03, 0X05, 0X0D, 0X0D, 0X05,
  0X04, 0X02, 0X0B, 0X06, 0X02, 0X02, 0X02, 0X08, 0X09, 0X06, 0X0A, 0X0A, 0X03, 0X06, 0X03, 0X05,
  0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X04, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0B, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X06, 0X09, 0X0E, 0X0A, 0X0A, 0X0B, 0X05, 0X05,
  0X05, 0X06, 0X02, 0X0A, 0X0A, 0X0A, 0X01, 0X0C, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X06, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X03, 0X06, 0X01, 0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X01,
  0X0C, 0X0A, 0X02, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X0A, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X01,
  0X05, 0X0E, 0X0B, 0X05, 0X07, 0X05, 0X0E, 0X0A, 0X0A, 0X0B, 0X05, 0X07, 0X07, 0X0E, 0X0B, 0X05,
  0X04, 0X0A, 0X08, 0X01, 0X0C, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X00, 0X09, 0X0C, 0X08, 0X0A, 0X01,
  0X05, 0X0F, 0X05, 0X07, 0X05, 0X0E, 0X0A, 0X0A, 0X08, 0X0A, 0X03, 0X07, 0X07, 0X05, 0X0F, 0X05,
  0X06, 0X09, 0X06, 0X0B, 0X04, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X08, 0X0A, 0X03, 0X0C, 0X01,
  0X0F, 0X06, 0X08, 0X0B, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X03, 0X0C, 0X0A, 0X03, 0X05,
  0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03
};

const uint8_t japan2011eq[] = {
  0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0B, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B, 0X0C, 0X0A, 0X09,
  0X0C, 0X02, 0X09, 0X06, 0X08, 0X0B, 0X0C, 0X00, 0X0B, 0X0C, 0X0A, 0X0A, 0X08, 0X02, 0X0B, 0X05,
  0X05, 0X0C, 0X02, 0X09, 0X06, 0X08, 0X03, 0X05, 0X0C, 0X02, 0X0B, 0X0C, 0X00, 0X0A, 0X0B, 0X05,
  0X04, 0X01, 0X0C, 0X02, 0X0A, 0X02, 0X09, 0X04, 0X02, 0X09, 0X0C, 0X03, 0X04, 0X09, 0X0C, 0X01,
  0X05, 0X04, 0X02, 0X08, 0X0A, 0X0A, 0X02, 0X02, 0X0B, 0X06, 0X01, 0X0D, 0X07, 0X05, 0X07, 0X05,
  0X05, 0X06, 0X0A, 0X03, 0X0D, 0X0C, 0X0A, 0X0A, 0X08, 0X09, 0X06, 0X02, 0X0A, 0X03, 0X0E, 0X01,
  0X04, 0X0A, 0X08, 0X0A, 0X03, 0X04, 0X0A, 0X0A, 0X03, 0X04, 0X09, 0X0C, 0X0A, 0X0A, 0X08, 0X01,
  0X04, 0X09, 0X06, 0X0A, 0X0B, 0X06, 0X08, 0X08, 0X09, 0X05, 0X05, 0X04, 0X0A, 0X08, 0X03, 0X05,
  0X05, 0X06, 0X08, 0X0A, 0X09, 0X0C, 0X03, 0X06, 0X03, 0X05, 0X05, 0X04, 0X0A, 0X02, 0X09, 0X05,
  0X04, 0X09, 0X06, 0X0B, 0X07, 0X06, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X06, 0X09, 0X0C, 0X03, 0X07,
  0X05, 0X04, 0X0A, 0X08, 0X0A, 0X0B, 0X06, 0X03, 0X06, 0X00, 0X02, 0X09, 0X06, 0X00, 0X0A, 0X09,
  0X04, 0X02, 0X0B, 0X06, 0X0A, 0X09, 0X0C, 0X09, 0X0D, 0X06, 0X08, 0X02, 0X09, 0X05, 0X0E, 0X01,
  0X04, 0X09, 0X0C, 0X09, 0X0D, 0X06, 0X03, 0X06, 0X02, 0X09, 0X06, 0X0A, 0X02, 0X00, 0X0B, 0X05,
  0X05, 0X06, 0X03, 0X06, 0X01, 0X0C, 0X0A, 0X08, 0X09, 0X06, 0X0A, 0X09, 0X0D, 0X06, 0X09, 0X05,
  0X04, 0X08, 0X0B, 0X0D, 0X05, 0X04, 0X0A, 0X01, 0X05, 0X0D, 0X0D, 0X05, 0X05, 0X0D, 0X06, 0X01,
  0X07, 0X06, 0X0A, 0X02, 0X02, 0X03, 0X0F, 0X06, 0X02, 0X02, 0X02, 0X02, 0X02, 0X02, 0X0A, 0X03
};

const uint8_t japan2002[] = {
  0X0E, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0D, 0X0D, 0X0D, 0X0D, 0X0D, 0X0C, 0X09, 0X0C, 0X08, 0X09,
  0X0E, 0X00, 0X01, 0X04, 0X01, 0X04, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X04, 0X01, 0X05, 0X05,
  0X0C, 0X01, 0X04, 0X01, 0X04, 0X01, 0X07, 0X07, 0X07, 0X07, 0X07, 0X06, 0X03, 0X04, 0X03, 0X05,
  0X05, 0X06, 0X03, 0X04, 0X01, 0X04, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X09, 0X0C, 0X03, 0X0D, 0X05,
  0X06, 0X08, 0X09, 0X07, 0X04, 0X01, 0X04, 0X01, 0X04, 0X01, 0X05, 0X04, 0X03, 0X0C, 0X01, 0X05,
  0X0E, 0X01, 0X04, 0X09, 0X07, 0X04, 0X03, 0X06, 0X01, 0X04, 0X03, 0X07, 0X0C, 0X03, 0X05, 0X05,
  0X0C, 0X02, 0X03, 0X06, 0X09, 0X07, 0X0C, 0X0B, 0X06, 0X02, 0X0B, 0X0C, 0X03, 0X0C, 0X01, 0X05,
  0X06, 0X08, 0X09, 0X0C, 0X03, 0X0E, 0X00, 0X08, 0X08, 0X0B, 0X0C, 0X01, 0X0C, 0X03, 0X05, 0X05,
  0X0C, 0X03, 0X04, 0X02, 0X09, 0X0E, 0X01, 0X04, 0X03, 0X0D, 0X06, 0X01, 0X06, 0X0A, 0X01, 0X05,
  0X06, 0X08, 0X02, 0X0A, 0X02, 0X09, 0X05, 0X06, 0X08, 0X02, 0X09, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X0C, 0X00, 0X09, 0X0C, 0X0A, 0X03, 0X04, 0X09, 0X07, 0X0D, 0X06, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X06, 0X00, 0X03, 0X05, 0X0D, 0X0D, 0X06, 0X00, 0X0A, 0X00, 0X08, 0X0B, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X05, 0X04, 0X02, 0X09, 0X07, 0X0D, 0X07, 0X06, 0X09, 0X04, 0X03, 0X05, 0X05,
  0X06, 0X08, 0X02, 0X03, 0X05, 0X0C, 0X03, 0X0C, 0X02, 0X09, 0X0C, 0X03, 0X07, 0X0E, 0X01, 0X05,
  0X0C, 0X02, 0X0B, 0X0C, 0X01, 0X06, 0X09, 0X06, 0X09, 0X05, 0X06, 0X09, 0X0D, 0X0E, 0X01, 0X05,
  0X06, 0X0A, 0X0A, 0X03, 0X07, 0X0E, 0X02, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X03, 0X0E, 0X02, 0X03
};

const uint8_t japan2012_ef[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X06, 0X09, 0X06, 0X09, 0X05, 0X0C, 0X0A, 0X03,
  0X06, 0X0A, 0X08, 0X03, 0X05, 0X04, 0X03, 0X04, 0X09, 0X04, 0X09, 0X05, 0X05, 0X06, 0X0A, 0X09,
  0X0C, 0X0A, 0X03, 0X0D, 0X05, 0X05, 0X0C, 0X03, 0X05, 0X05, 0X06, 0X01, 0X06, 0X0A, 0X09, 0X05,
  0X04, 0X0A, 0X08, 0X02, 0X02, 0X02, 0X02, 0X0A, 0X02, 0X02, 0X0B, 0X06, 0X0B, 0X0C, 0X03, 0X05,
  0X05, 0X0D, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X04, 0X09, 0X05,
  0X05, 0X04, 0X03, 0X04, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X05, 0X07, 0X06, 0X01,
  0X05, 0X05, 0X0C, 0X02, 0X08, 0X0A, 0X08, 0X08, 0X08, 0X02, 0X08, 0X01, 0X05, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X0E, 0X02, 0X0A, 0X03, 0X06, 0X03, 0X0E, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X08, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X09, 0X05, 0X05, 0X06, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X0A, 0X03, 0X06, 0X02, 0X09, 0X06, 0X09, 0X06, 0X03, 0X06, 0X02, 0X03, 0X06, 0X03,
  0X05, 0X06, 0X0A, 0X0A, 0X09, 0X0D, 0X04, 0X09, 0X04, 0X08, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X09,
  0X05, 0X0C, 0X08, 0X09, 0X06, 0X01, 0X07, 0X04, 0X01, 0X04, 0X09, 0X05, 0X05, 0X0C, 0X0A, 0X03,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X02, 0X09, 0X07, 0X06, 0X03, 0X06, 0X02, 0X03, 0X06, 0X0A, 0X09,
  0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t japan2012_eq[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X0C, 0X09,
  0X0C, 0X03, 0X0C, 0X09, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X0A, 0X09, 0X06, 0X0A, 0X02, 0X03, 0X05,
  0X05, 0X0C, 0X03, 0X06, 0X0A, 0X08, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X06, 0X08, 0X0A, 0X08, 0X01, 0X0C, 0X09, 0X0C, 0X03, 0X0C, 0X02, 0X09, 0X0C, 0X01, 0X05,
  0X04, 0X09, 0X04, 0X08, 0X03, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X03, 0X0C, 0X02, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X09, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X02, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X01, 0X04, 0X03, 0X06, 0X02, 0X0A, 0X08, 0X0A, 0X09, 0X05, 0X05, 0X04, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X0C, 0X01, 0X04, 0X01, 0X05, 0X05,
  0X04, 0X03, 0X05, 0X04, 0X01, 0X05, 0X05, 0X06, 0X02, 0X02, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X08, 0X02, 0X01, 0X05, 0X04, 0X01, 0X05,
  0X05, 0X06, 0X09, 0X05, 0X06, 0X01, 0X06, 0X08, 0X0A, 0X02, 0X08, 0X03, 0X05, 0X05, 0X06, 0X01,
  0X04, 0X09, 0X05, 0X06, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X0C, 0X02, 0X02, 0X09, 0X05,
  0X05, 0X05, 0X06, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X02, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0E, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X09, 0X06, 0X0A, 0X08, 0X0A, 0X02, 0X01, 0X05,
  0X05, 0X04, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X09, 0X06, 0X0A, 0X0A, 0X02, 0X08, 0X0A, 0X01, 0X05,
  0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X03
};

const uint8_t japan4[] = {
  0X0E, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X0B,
  0X0C, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X09,
  0X05, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0D, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X00, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X04, 0X01, 0X05, 0X05, 0X0D, 0X0E, 0X0A, 0X00, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X09, 0X05, 0X07, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X0D, 0X0C, 0X0A, 0X09, 0X05, 0X05, 0X0D, 0X05, 0X05, 0X05,
  0X05, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X09, 0X05, 0X07, 0X07, 0X05, 0X04, 0X01, 0X05,
  0X05, 0X0C, 0X01, 0X04, 0X01, 0X04, 0X01, 0X06, 0X03, 0X05, 0X0D, 0X0D, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X04, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X08, 0X0A, 0X0A, 0X03, 0X05, 0X04, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X08, 0X0A, 0X03, 0X05, 0X0C, 0X01, 0X05,
  0X05, 0X05, 0X07, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0B, 0X07, 0X05, 0X04, 0X01,
  0X05, 0X05, 0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X04, 0X0A, 0X0A, 0X08, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X06, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t japan5[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0B,
  0X0C, 0X0B, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X08, 0X09,
  0X04, 0X0A, 0X03, 0X05, 0X0E, 0X08, 0X09, 0X0C, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X05, 0X0C, 0X0A, 0X03, 0X0C, 0X01, 0X04, 0X01, 0X07, 0X0C, 0X08, 0X08, 0X09, 0X0C, 0X08, 0X01,
  0X05, 0X05, 0X0D, 0X0C, 0X03, 0X04, 0X01, 0X07, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X02, 0X08, 0X03, 0X07, 0X0E, 0X00, 0X02, 0X00, 0X00, 0X01, 0X04, 0X00, 0X01,
  0X04, 0X01, 0X06, 0X08, 0X02, 0X0B, 0X0E, 0X0A, 0X02, 0X09, 0X05, 0X05, 0X05, 0X05, 0X07, 0X07,
  0X05, 0X05, 0X0C, 0X02, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X04, 0X00, 0X01, 0X05, 0X0C, 0X09,
  0X05, 0X05, 0X06, 0X08, 0X03, 0X05, 0X05, 0X06, 0X02, 0X03, 0X07, 0X07, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X01, 0X0C, 0X02, 0X09, 0X04, 0X02, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X08, 0X03, 0X04, 0X0A, 0X0A, 0X00, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X00, 0X0B, 0X04, 0X0A, 0X0A, 0X00, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X03, 0X06, 0X03, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X01,
  0X06, 0X01, 0X0C, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0B, 0X04, 0X0A, 0X09, 0X06, 0X0A, 0X01,
  0X0E, 0X02, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X0B, 0X06, 0X0A, 0X0A, 0X03
};

const uint8_t japan95[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0B,
  0X0C, 0X0A, 0X03, 0X04, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X0D,
  0X05, 0X0C, 0X08, 0X03, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X01, 0X07,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0B, 0X0C, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X01, 0X0E, 0X02, 0X09, 0X06, 0X0B, 0X05, 0X05,
  0X05, 0X04, 0X03, 0X07, 0X05, 0X07, 0X0C, 0X0A, 0X02, 0X09, 0X0F, 0X06, 0X0A, 0X0A, 0X03, 0X05,
  0X05, 0X04, 0X0A, 0X0A, 0X02, 0X09, 0X04, 0X08, 0X09, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X04, 0X02, 0X0A, 0X0A, 0X08, 0X03, 0X05, 0X06, 0X03, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X01,
  0X05, 0X0C, 0X09, 0X0D, 0X05, 0X0D, 0X06, 0X0A, 0X0A, 0X03, 0X0F, 0X0C, 0X0A, 0X0A, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X09, 0X0E, 0X08, 0X03, 0X0C, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0B, 0X06, 0X0A, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X0C, 0X03,
  0X05, 0X06, 0X02, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X03, 0X0C, 0X01, 0X0D,
  0X06, 0X0A, 0X09, 0X05, 0X0F, 0X05, 0X0E, 0X0A, 0X08, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X05, 0X07,
  0X0E, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0B
};

const uint8_t japan97[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0F, 0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X0A, 0X0A, 0X0A, 0X03,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0E, 0X08, 0X02, 0X0A, 0X0A, 0X0A, 0X09,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0D, 0X07, 0X0D, 0X0F, 0X0C, 0X0A, 0X03,
  0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X09, 0X0E, 0X09, 0X04, 0X08, 0X03, 0X0C, 0X03, 0X0C, 0X09,
  0X04, 0X01, 0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X0C, 0X01, 0X05, 0X05, 0X0F, 0X05, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X06, 0X01, 0X05, 0X0C, 0X03, 0X05, 0X0C, 0X03,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X06, 0X09,
  0X05, 0X07, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X06, 0X01, 0X07, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X03,
  0X05, 0X0C, 0X01, 0X06, 0X00, 0X0A, 0X09, 0X0F, 0X06, 0X0A, 0X01, 0X06, 0X03, 0X06, 0X0A, 0X09,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X0B, 0X05, 0X0E, 0X08, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X05, 0X06, 0X09, 0X06, 0X09, 0X0C, 0X02, 0X0B, 0X06, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X05,
  0X04, 0X09, 0X06, 0X09, 0X06, 0X01, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X0F, 0X0F, 0X06, 0X03,
  0X05, 0X06, 0X09, 0X06, 0X09, 0X06, 0X03, 0X06, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X09,
  0X04, 0X0A, 0X02, 0X09, 0X06, 0X08, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X09, 0X0E, 0X01,
  0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X03, 0X06, 0X03, 0X06, 0X03, 0X06, 0X02, 0X03, 0X06, 0X0A, 0X03
};


const uint8_t japan1988[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X08, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X09, 0X05, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X09, 0X0D, 0X05,
  0X05, 0X07, 0X04, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X04, 0X01, 0X0C, 0X01, 0X05, 0X04, 0X01,
  0X04, 0X0A, 0X01, 0X0E, 0X0A, 0X00, 0X01, 0X06, 0X03, 0X07, 0X07, 0X05, 0X07, 0X05, 0X05, 0X05,
  0X05, 0X0D, 0X06, 0X0A, 0X0B, 0X05, 0X07, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X01, 0X04, 0X01,
  0X06, 0X02, 0X0A, 0X08, 0X0A, 0X03, 0X0C, 0X02, 0X0A, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X00, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X06, 0X02, 0X02, 0X01,
  0X06, 0X0A, 0X0A, 0X09, 0X0C, 0X01, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X0E, 0X0A, 0X09, 0X05,
  0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X06, 0X02, 0X01, 0X05, 0X05, 0X0C, 0X0A, 0X02, 0X03,
  0X06, 0X0A, 0X08, 0X0B, 0X05, 0X07, 0X06, 0X0A, 0X0A, 0X03, 0X04, 0X03, 0X06, 0X0A, 0X08, 0X0B,
  0X0E, 0X08, 0X02, 0X0B, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X0E, 0X08, 0X0A, 0X02, 0X0B,
  0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0D, 0X0C, 0X02, 0X0A, 0X0A, 0X0B,
  0X05, 0X0C, 0X02, 0X0B, 0X0C, 0X0A, 0X08, 0X09, 0X0C, 0X09, 0X04, 0X01, 0X0C, 0X0A, 0X0A, 0X09,
  0X05, 0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0E, 0X09, 0X05,
  0X05, 0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X01, 0X06, 0X01, 0X04, 0X01, 0X05, 0X06, 0X0A, 0X03, 0X05,
  0X06, 0X0A, 0X02, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X03, 0X07, 0X07, 0X06, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t japan1990[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X0D, 0X0E, 0X0A, 0X0B, 0X05, 0X0F, 0X05, 0X0F, 0X04, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X0F, 0X05,
  0X04, 0X0A, 0X0A, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X03, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X0C, 0X01,
  0X05, 0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0E, 0X0A, 0X0A, 0X01, 0X05, 0X05,
  0X04, 0X0A, 0X01, 0X0F, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0B, 0X06, 0X01, 0X05,
  0X07, 0X0F, 0X05, 0X0C, 0X01, 0X05, 0X0F, 0X05, 0X0C, 0X0A, 0X02, 0X0A, 0X08, 0X09, 0X05, 0X07,
  0X0C, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X05, 0X0C, 0X0A, 0X09, 0X05, 0X05, 0X06, 0X09,
  0X05, 0X0F, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X05, 0X0D, 0X05, 0X07, 0X05, 0X0F, 0X05,
  0X04, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05, 0X04, 0X03, 0X05, 0X07, 0X05, 0X0F, 0X04, 0X0A, 0X01,
  0X05, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X06, 0X0A, 0X03, 0X0D, 0X05, 0X0F, 0X05,
  0X05, 0X05, 0X0F, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X01, 0X04, 0X0A, 0X01,
  0X05, 0X04, 0X0A, 0X02, 0X03, 0X05, 0X05, 0X06, 0X08, 0X0A, 0X08, 0X0B, 0X05, 0X05, 0X0D, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X02, 0X0B, 0X05, 0X0D, 0X05, 0X0F, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X03, 0X05, 0X04, 0X0A, 0X02, 0X01, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X03, 0X04, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X0E, 0X0B, 0X05, 0X07, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t japan1991[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X09, 0X0D, 0X0D, 0X0C, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X09,
  0X0C, 0X02, 0X08, 0X09, 0X05, 0X05, 0X05, 0X05, 0X04, 0X09, 0X06, 0X09, 0X06, 0X09, 0X0E, 0X01,
  0X05, 0X0D, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X07, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X04, 0X03, 0X05, 0X04, 0X01, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X01,
  0X05, 0X04, 0X02, 0X08, 0X01, 0X05, 0X04, 0X0A, 0X09, 0X05, 0X0E, 0X02, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X0E, 0X01, 0X05, 0X05, 0X04, 0X0A, 0X03, 0X06, 0X0A, 0X09, 0X05, 0X0D, 0X06, 0X01,
  0X05, 0X04, 0X0A, 0X01, 0X06, 0X01, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X02, 0X03, 0X04, 0X0A, 0X01,
  0X05, 0X05, 0X0C, 0X00, 0X09, 0X06, 0X01, 0X04, 0X09, 0X07, 0X0D, 0X0D, 0X0D, 0X05, 0X0D, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X04, 0X09, 0X07, 0X06, 0X03, 0X0C, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X07, 0X06, 0X09, 0X0E, 0X0A, 0X01, 0X05, 0X07, 0X07, 0X07, 0X07, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X0E, 0X00, 0X02, 0X08, 0X09, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X04, 0X0A, 0X09, 0X05, 0X0E, 0X02, 0X09, 0X06, 0X0B, 0X05, 0X04, 0X01, 0X04, 0X01,
  0X05, 0X05, 0X05, 0X0D, 0X05, 0X06, 0X0A, 0X0A, 0X00, 0X0A, 0X0A, 0X01, 0X05, 0X04, 0X01, 0X05,
  0X05, 0X05, 0X06, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X09, 0X05, 0X04, 0X01, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X04, 0X03, 0X05, 0X04, 0X01,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X03, 0X07
};

const uint8_t japan1993ef[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X08, 0X0B, 0X0C, 0X0A, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X09,
  0X0C, 0X0B, 0X05, 0X0C, 0X02, 0X0A, 0X00, 0X0A, 0X01, 0X06, 0X09, 0X06, 0X08, 0X02, 0X09, 0X05,
  0X05, 0X0C, 0X02, 0X01, 0X0C, 0X0A, 0X02, 0X0A, 0X02, 0X0B, 0X06, 0X09, 0X06, 0X09, 0X04, 0X01,
  0X04, 0X03, 0X0C, 0X00, 0X01, 0X0E, 0X08, 0X08, 0X0A, 0X08, 0X0B, 0X06, 0X09, 0X06, 0X01, 0X07,
  0X05, 0X0C, 0X03, 0X05, 0X05, 0X0E, 0X01, 0X04, 0X0A, 0X00, 0X0B, 0X0D, 0X06, 0X09, 0X06, 0X09,
  0X05, 0X06, 0X09, 0X06, 0X02, 0X09, 0X05, 0X05, 0X0E, 0X00, 0X0B, 0X04, 0X09, 0X06, 0X09, 0X05,
  0X04, 0X09, 0X04, 0X09, 0X0C, 0X03, 0X05, 0X05, 0X0E, 0X00, 0X0B, 0X05, 0X05, 0X0D, 0X06, 0X01,
  0X07, 0X05, 0X07, 0X05, 0X06, 0X09, 0X05, 0X04, 0X09, 0X04, 0X09, 0X05, 0X05, 0X04, 0X09, 0X05,
  0X0D, 0X05, 0X0D, 0X05, 0X0C, 0X03, 0X05, 0X06, 0X03, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X03, 0X04, 0X02, 0X02, 0X09, 0X04, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X0A, 0X03, 0X07, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X04, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X09, 0X04, 0X01, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X07, 0X06, 0X03, 0X05, 0X05,
  0X07, 0X05, 0X05, 0X04, 0X00, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X06, 0X0A, 0X0A, 0X09, 0X06, 0X03,
  0X0D, 0X05, 0X06, 0X03, 0X05, 0X06, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X09,
  0X06, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};
const uint8_t japan1994ef[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X0D, 0X05, 0X0E, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X09, 0X04, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X05,
  0X04, 0X01, 0X0C, 0X0A, 0X02, 0X0A, 0X08, 0X0B, 0X05, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X01,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X0B, 0X06, 0X09, 0X0F, 0X05, 0X0F, 0X06, 0X09, 0X05,
  0X05, 0X06, 0X01, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X04, 0X09, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X0B, 0X06, 0X09, 0X0F, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X03, 0X05, 0X0C, 0X0A, 0X0A, 0X08, 0X09, 0X06, 0X09, 0X05, 0X06, 0X01,
  0X05, 0X05, 0X07, 0X0C, 0X09, 0X05, 0X04, 0X08, 0X09, 0X05, 0X04, 0X09, 0X04, 0X03, 0X0C, 0X01,
  0X05, 0X05, 0X0C, 0X01, 0X06, 0X01, 0X05, 0X06, 0X03, 0X05, 0X05, 0X05, 0X07, 0X0D, 0X05, 0X07,
  0X04, 0X01, 0X05, 0X06, 0X09, 0X07, 0X04, 0X0A, 0X08, 0X03, 0X05, 0X04, 0X09, 0X05, 0X05, 0X0D,
  0X05, 0X05, 0X05, 0X0F, 0X06, 0X09, 0X06, 0X08, 0X02, 0X08, 0X02, 0X01, 0X04, 0X01, 0X06, 0X01,
  0X04, 0X01, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X00, 0X08, 0X03, 0X05, 0X04, 0X09, 0X05,
  0X05, 0X06, 0X09, 0X0F, 0X05, 0X0F, 0X06, 0X0A, 0X09, 0X07, 0X06, 0X08, 0X03, 0X05, 0X05, 0X05,
  0X04, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X0A, 0X09, 0X06, 0X08, 0X0B, 0X06, 0X08, 0X03, 0X04, 0X01,
  0X05, 0X06, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X00, 0X0B, 0X06, 0X09, 0X0C, 0X02, 0X08, 0X03, 0X05,
  0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0B, 0X06, 0X02, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t japan1996ef[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X05,
  0X05, 0X0C, 0X02, 0X0B, 0X0E, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X06, 0X0A, 0X03,
  0X05, 0X05, 0X0D, 0X0C, 0X0B, 0X04, 0X0A, 0X0A, 0X0B, 0X0E, 0X02, 0X09, 0X06, 0X0B, 0X0C, 0X09,
  0X05, 0X05, 0X04, 0X03, 0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X0E, 0X01, 0X05,
  0X05, 0X04, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X02, 0X09, 0X06, 0X0A, 0X01, 0X05,
  0X05, 0X05, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X09, 0X0D, 0X06, 0X0A, 0X09, 0X07, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X01, 0X04, 0X02, 0X0A, 0X08, 0X02, 0X09, 0X05,
  0X04, 0X01, 0X05, 0X06, 0X09, 0X06, 0X09, 0X06, 0X01, 0X04, 0X08, 0X0A, 0X00, 0X08, 0X01, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X03, 0X07, 0X0C, 0X03, 0X07, 0X05, 0X05,
  0X05, 0X07, 0X0D, 0X06, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X0A, 0X08, 0X03, 0X0C, 0X09, 0X05, 0X05,
  0X05, 0X0D, 0X05, 0X0D, 0X06, 0X09, 0X06, 0X0A, 0X09, 0X0E, 0X01, 0X0C, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X04, 0X01, 0X04, 0X09, 0X06, 0X0A, 0X0A, 0X03, 0X0E, 0X02, 0X03, 0X0C, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X07, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X03, 0X05,
  0X06, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t japan1997eq[] = {
  0X0E, 0X0A, 0X09, 0X0D, 0X0F, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X09,
  0X0E, 0X0B, 0X05, 0X04, 0X0A, 0X01, 0X0F, 0X0C, 0X0A, 0X03, 0X0C, 0X0B, 0X05, 0X0C, 0X09, 0X05,
  0X0C, 0X0A, 0X03, 0X05, 0X0F, 0X04, 0X0A, 0X03, 0X0E, 0X0B, 0X05, 0X0F, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X08, 0X02, 0X0A, 0X01, 0X0E, 0X0B, 0X0C, 0X0A, 0X03, 0X0E, 0X01, 0X05, 0X04, 0X03,
  0X05, 0X05, 0X05, 0X0E, 0X09, 0X04, 0X08, 0X0A, 0X03, 0X0C, 0X0A, 0X0A, 0X02, 0X03, 0X05, 0X0D,
  0X05, 0X05, 0X05, 0X0E, 0X01, 0X07, 0X05, 0X0C, 0X0A, 0X03, 0X0C, 0X0A, 0X09, 0X0E, 0X01, 0X07,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X07, 0X07, 0X0F, 0X0C, 0X02, 0X0A, 0X02, 0X09, 0X06, 0X09,
  0X05, 0X04, 0X0A, 0X02, 0X0B, 0X06, 0X0B, 0X0C, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X0A, 0X03,
  0X04, 0X02, 0X0A, 0X08, 0X0B, 0X0C, 0X0B, 0X06, 0X02, 0X01, 0X06, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X05, 0X0C, 0X0A, 0X03, 0X0C, 0X03, 0X0D, 0X0D, 0X0F, 0X06, 0X08, 0X0A, 0X08, 0X03, 0X0C, 0X03,
  0X05, 0X05, 0X0D, 0X0E, 0X01, 0X0D, 0X05, 0X06, 0X0A, 0X09, 0X06, 0X0A, 0X03, 0X0E, 0X01, 0X0D,
  0X05, 0X05, 0X05, 0X0E, 0X03, 0X04, 0X02, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X08, 0X09, 0X05, 0X07,
  0X05, 0X06, 0X02, 0X08, 0X0A, 0X01, 0X0E, 0X0B, 0X06, 0X0A, 0X09, 0X0E, 0X01, 0X05, 0X04, 0X09,
  0X04, 0X0A, 0X09, 0X05, 0X0F, 0X04, 0X0A, 0X09, 0X0E, 0X0B, 0X05, 0X0F, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0F, 0X05, 0X04, 0X0A, 0X01, 0X0F, 0X06, 0X0A, 0X09, 0X06, 0X0B, 0X05, 0X06, 0X01, 0X05,
  0X06, 0X0A, 0X03, 0X07, 0X0F, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X03
};


const uint8_t japan1998f[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X08, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X09, 0X05, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X09, 0X0D, 0X05,
  0X05, 0X07, 0X04, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X04, 0X01, 0X0C, 0X01, 0X05, 0X04, 0X01,
  0X04, 0X0A, 0X01, 0X0E, 0X0A, 0X00, 0X01, 0X06, 0X03, 0X07, 0X07, 0X05, 0X07, 0X05, 0X05, 0X05,
  0X05, 0X0D, 0X06, 0X0A, 0X0B, 0X05, 0X07, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X01, 0X04, 0X01,
  0X06, 0X02, 0X0A, 0X08, 0X0A, 0X03, 0X0C, 0X02, 0X0A, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X00, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X04, 0X02, 0X02, 0X01,
  0X06, 0X0A, 0X0A, 0X09, 0X0C, 0X01, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X09, 0X05,
  0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X06, 0X02, 0X01, 0X05, 0X05, 0X0C, 0X0A, 0X02, 0X03,
  0X06, 0X0A, 0X08, 0X0B, 0X07, 0X07, 0X06, 0X0A, 0X0A, 0X03, 0X04, 0X03, 0X06, 0X0A, 0X08, 0X0B,
  0X0E, 0X08, 0X02, 0X0B, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X0E, 0X08, 0X0A, 0X02, 0X0B,
  0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0D, 0X0C, 0X02, 0X0A, 0X0A, 0X0B,
  0X05, 0X0C, 0X02, 0X0B, 0X0C, 0X0A, 0X08, 0X09, 0X0C, 0X09, 0X04, 0X01, 0X0C, 0X0A, 0X0A, 0X09,
  0X05, 0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0E, 0X09, 0X05,
  0X05, 0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X01, 0X06, 0X01, 0X04, 0X01, 0X05, 0X06, 0X0A, 0X03, 0X05,
  0X06, 0X0A, 0X02, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X03, 0X07, 0X07, 0X06, 0X0A, 0X0A, 0X0A, 0X03
};


const uint8_t japan1999f[] = {
  0X0E, 0X0A, 0X09, 0X0D, 0X0E, 0X08, 0X0A, 0X09, 0X0D, 0X0D, 0X0D, 0X0C, 0X08, 0X0A, 0X0A, 0X09,
  0X0D, 0X0E, 0X01, 0X04, 0X09, 0X06, 0X09, 0X06, 0X01, 0X04, 0X01, 0X05, 0X05, 0X0C, 0X09, 0X05,
  0X06, 0X0A, 0X02, 0X01, 0X06, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0E, 0X08, 0X0A, 0X00, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0D, 0X06, 0X09, 0X07, 0X04, 0X0B, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05,
  0X04, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X09, 0X06, 0X03, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X06, 0X09, 0X0E, 0X00, 0X0A, 0X0A, 0X09, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05, 0X0C, 0X09, 0X07, 0X0E, 0X0A, 0X03, 0X07, 0X05, 0X05,
  0X0E, 0X02, 0X09, 0X06, 0X0A, 0X03, 0X05, 0X06, 0X02, 0X08, 0X0A, 0X0A, 0X08, 0X0B, 0X05, 0X05,
  0X0E, 0X08, 0X02, 0X0A, 0X0A, 0X0B, 0X06, 0X0B, 0X0C, 0X01, 0X0C, 0X08, 0X02, 0X0A, 0X03, 0X05,
  0X0E, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0D, 0X05, 0X04, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X01,
  0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X08, 0X09, 0X0E, 0X01,
  0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X06, 0X01, 0X05, 0X0E, 0X01,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X07, 0X05, 0X04, 0X0B, 0X04, 0X03, 0X0E, 0X01,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X05, 0X0E, 0X03, 0X0C, 0X08, 0X03,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X06, 0X0B
};

const uint8_t japan2000ef[] = {
  0X0E, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X09, 0X0C, 0X08, 0X08, 0X08, 0X0A, 0X0A, 0X0B, 0X0C, 0X09,
  0X0C, 0X02, 0X01, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X0D, 0X0D, 0X05, 0X05,
  0X06, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X05, 0X07, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X0E, 0X02, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X04, 0X01, 0X05,
  0X0C, 0X0A, 0X02, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X02, 0X09, 0X06, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X07, 0X05, 0X05, 0X07, 0X06, 0X01, 0X05, 0X05,
  0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B, 0X0C, 0X08, 0X09, 0X05, 0X06, 0X08, 0X0B, 0X07, 0X07, 0X05,
  0X04, 0X0A, 0X08, 0X0A, 0X0A, 0X0B, 0X05, 0X06, 0X03, 0X05, 0X0C, 0X03, 0X0C, 0X08, 0X09, 0X05,
  0X05, 0X0E, 0X02, 0X0A, 0X08, 0X0B, 0X06, 0X0A, 0X09, 0X05, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0E, 0X0A, 0X0A, 0X02, 0X0A, 0X09, 0X0D, 0X04, 0X01, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X07, 0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X03, 0X05, 0X07, 0X05, 0X06, 0X0A, 0X01, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X09, 0X04, 0X09, 0X05, 0X0E, 0X08, 0X00, 0X02, 0X01, 0X05,
  0X04, 0X0A, 0X0A, 0X09, 0X0C, 0X03, 0X06, 0X03, 0X06, 0X02, 0X0B, 0X05, 0X05, 0X0E, 0X02, 0X01,
  0X04, 0X0A, 0X0A, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X08, 0X0B, 0X05,
  0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t japan2001[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X02, 0X08, 0X0B, 0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X06, 0X08, 0X02, 0X08, 0X0B, 0X06, 0X09, 0X06, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X07,
  0X0C, 0X02, 0X08, 0X02, 0X08, 0X0B, 0X06, 0X09, 0X06, 0X09, 0X0E, 0X08, 0X0A, 0X0A, 0X02, 0X09,
  0X06, 0X08, 0X02, 0X09, 0X06, 0X08, 0X0B, 0X06, 0X09, 0X06, 0X09, 0X06, 0X08, 0X0A, 0X09, 0X07,
  0X0C, 0X02, 0X08, 0X02, 0X08, 0X02, 0X09, 0X0E, 0X00, 0X0B, 0X06, 0X09, 0X05, 0X0E, 0X00, 0X0B,
  0X06, 0X08, 0X02, 0X09, 0X06, 0X08, 0X02, 0X0A, 0X02, 0X0B, 0X0E, 0X00, 0X01, 0X0C, 0X02, 0X09,
  0X0C, 0X02, 0X08, 0X02, 0X08, 0X03, 0X0C, 0X08, 0X08, 0X09, 0X0D, 0X07, 0X07, 0X06, 0X08, 0X03,
  0X05, 0X0E, 0X00, 0X0B, 0X07, 0X0C, 0X03, 0X06, 0X03, 0X06, 0X01, 0X0C, 0X09, 0X0E, 0X00, 0X0B,
  0X05, 0X0C, 0X02, 0X09, 0X0C, 0X03, 0X0C, 0X0A, 0X09, 0X0E, 0X00, 0X03, 0X05, 0X0E, 0X00, 0X0B,
  0X05, 0X06, 0X08, 0X03, 0X06, 0X08, 0X03, 0X0C, 0X02, 0X09, 0X07, 0X0C, 0X03, 0X0E, 0X00, 0X0B,
  0X05, 0X0E, 0X00, 0X0B, 0X0D, 0X06, 0X0A, 0X03, 0X0E, 0X02, 0X09, 0X06, 0X09, 0X0C, 0X02, 0X09,
  0X05, 0X0C, 0X02, 0X09, 0X04, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X0C, 0X03, 0X06, 0X08, 0X03,
  0X05, 0X05, 0X0C, 0X03, 0X05, 0X06, 0X03, 0X06, 0X03, 0X06, 0X01, 0X06, 0X09, 0X0C, 0X00, 0X09,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X0E, 0X00, 0X01, 0X05, 0X05,
  0X06, 0X02, 0X0B, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X03, 0X06, 0X02, 0X03
};

const uint8_t japan2001ef[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X09, 0X0D, 0X0D, 0X0C, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X09,
  0X0C, 0X02, 0X08, 0X09, 0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X0F, 0X05,
  0X05, 0X0D, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X0F, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X04, 0X03, 0X05, 0X04, 0X01, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X01,
  0X05, 0X04, 0X02, 0X08, 0X01, 0X05, 0X04, 0X0A, 0X09, 0X05, 0X0F, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X0F, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X03, 0X06, 0X0A, 0X09, 0X05, 0X0D, 0X06, 0X01,
  0X05, 0X04, 0X0A, 0X01, 0X06, 0X01, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X02, 0X03, 0X04, 0X0A, 0X01,
  0X05, 0X05, 0X0C, 0X00, 0X09, 0X06, 0X01, 0X04, 0X09, 0X07, 0X0D, 0X0D, 0X0D, 0X05, 0X0D, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X07, 0X06, 0X03, 0X0C, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X0F, 0X06, 0X09, 0X0E, 0X0A, 0X01, 0X05, 0X07, 0X07, 0X07, 0X07, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X0E, 0X00, 0X02, 0X08, 0X09, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X04, 0X0A, 0X09, 0X05, 0X0F, 0X06, 0X09, 0X06, 0X0B, 0X05, 0X04, 0X01, 0X04, 0X01,
  0X05, 0X05, 0X05, 0X0F, 0X05, 0X06, 0X0A, 0X0A, 0X00, 0X0A, 0X0A, 0X01, 0X05, 0X04, 0X01, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X09, 0X05, 0X04, 0X01, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X04, 0X03, 0X05, 0X04, 0X03,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X03, 0X0F
};

const uint8_t japan2002q[] = {
  0X0E, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0D, 0X0D, 0X0D, 0X0D, 0X0D, 0X0C, 0X09, 0X0C, 0X08, 0X09,
  0X0E, 0X00, 0X01, 0X04, 0X01, 0X04, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X04, 0X01, 0X05, 0X05,
  0X0C, 0X01, 0X04, 0X01, 0X04, 0X01, 0X07, 0X07, 0X07, 0X07, 0X07, 0X06, 0X03, 0X04, 0X03, 0X05,
  0X05, 0X06, 0X03, 0X04, 0X01, 0X04, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X09, 0X0C, 0X03, 0X0D, 0X05,
  0X06, 0X08, 0X09, 0X07, 0X04, 0X01, 0X04, 0X01, 0X04, 0X01, 0X05, 0X04, 0X03, 0X0C, 0X01, 0X05,
  0X0E, 0X01, 0X04, 0X09, 0X07, 0X04, 0X03, 0X06, 0X01, 0X04, 0X03, 0X07, 0X0C, 0X03, 0X05, 0X05,
  0X0C, 0X02, 0X03, 0X06, 0X09, 0X07, 0X0C, 0X0B, 0X06, 0X02, 0X0B, 0X0C, 0X03, 0X0C, 0X01, 0X05,
  0X06, 0X08, 0X09, 0X0C, 0X03, 0X0E, 0X00, 0X08, 0X08, 0X0B, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X05,
  0X0C, 0X03, 0X04, 0X02, 0X09, 0X0E, 0X01, 0X04, 0X03, 0X0D, 0X06, 0X09, 0X06, 0X0A, 0X01, 0X05,
  0X06, 0X08, 0X02, 0X0A, 0X02, 0X09, 0X05, 0X06, 0X08, 0X02, 0X09, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X0C, 0X0A, 0X03, 0X06, 0X09, 0X07, 0X0D, 0X06, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X06, 0X08, 0X03, 0X05, 0X0D, 0X0D, 0X0E, 0X00, 0X0A, 0X00, 0X08, 0X0B, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X05, 0X04, 0X02, 0X09, 0X07, 0X0D, 0X07, 0X06, 0X09, 0X04, 0X03, 0X05, 0X05,
  0X06, 0X08, 0X02, 0X03, 0X05, 0X0C, 0X03, 0X0C, 0X02, 0X09, 0X0C, 0X03, 0X07, 0X0E, 0X01, 0X05,
  0X0C, 0X02, 0X0B, 0X0C, 0X01, 0X06, 0X09, 0X06, 0X09, 0X05, 0X06, 0X09, 0X0D, 0X0E, 0X01, 0X05,
  0X06, 0X0A, 0X0A, 0X03, 0X07, 0X0E, 0X02, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X03, 0X0E, 0X02, 0X03
};

const uint8_t japan2002ef[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X03, 0X0D, 0X0C, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X01,
  0X05, 0X0D, 0X06, 0X01, 0X0E, 0X08, 0X02, 0X0A, 0X00, 0X0A, 0X0A, 0X08, 0X02, 0X0A, 0X0A, 0X01,
  0X04, 0X01, 0X0D, 0X04, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03,
  0X05, 0X06, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X09,
  0X04, 0X08, 0X02, 0X08, 0X0A, 0X0A, 0X08, 0X09, 0X0E, 0X08, 0X0A, 0X09, 0X07, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X0D, 0X06, 0X09, 0X0E, 0X01, 0X06, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X04, 0X01, 0X0D, 0X06, 0X09, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X00, 0X0B, 0X04, 0X03, 0X06, 0X01, 0X05, 0X06, 0X03, 0X0D, 0X06, 0X03, 0X05,
  0X05, 0X04, 0X01, 0X07, 0X0C, 0X03, 0X0C, 0X09, 0X05, 0X06, 0X09, 0X0C, 0X00, 0X09, 0X0D, 0X05,
  0X04, 0X01, 0X07, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X0C, 0X03, 0X05, 0X05, 0X04, 0X01, 0X05,
  0X05, 0X07, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X01, 0X05, 0X05, 0X0F, 0X05, 0X04, 0X01, 0X05, 0X05,
  0X07, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X02, 0X09, 0X05, 0X04, 0X0A, 0X09, 0X0D, 0X04, 0X01, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X02, 0X0A, 0X02, 0X03, 0X06, 0X09, 0X05, 0X04, 0X03, 0X05, 0X06, 0X01,
  0X06, 0X03, 0X0E, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X02, 0X0A, 0X03, 0X0E, 0X03
};

const uint8_t japan2003[] = {
  0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X0B, 0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X09,
  0X0E, 0X00, 0X08, 0X02, 0X09, 0X0C, 0X01, 0X04, 0X01, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X0C, 0X03, 0X06, 0X08, 0X02, 0X01, 0X04, 0X01, 0X04, 0X03, 0X0C, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X09, 0X06, 0X08, 0X02, 0X01, 0X04, 0X01, 0X0E, 0X00, 0X0B, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X08, 0X02, 0X01, 0X07, 0X0E, 0X00, 0X0B, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X04, 0X09, 0X06, 0X09, 0X04, 0X0A, 0X03, 0X0D, 0X0E, 0X00, 0X0B, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X03, 0X0E, 0X0A, 0X00, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X06, 0X0A, 0X08, 0X0B, 0X0C, 0X01, 0X06, 0X09, 0X06, 0X0A, 0X02, 0X03, 0X05,
  0X05, 0X0C, 0X02, 0X0A, 0X09, 0X04, 0X0B, 0X06, 0X01, 0X0D, 0X06, 0X09, 0X0C, 0X0A, 0X09, 0X05,
  0X05, 0X06, 0X09, 0X0D, 0X06, 0X01, 0X0C, 0X09, 0X06, 0X00, 0X09, 0X06, 0X03, 0X0C, 0X03, 0X05,
  0X05, 0X0C, 0X02, 0X00, 0X0A, 0X01, 0X05, 0X06, 0X09, 0X07, 0X06, 0X09, 0X0C, 0X02, 0X09, 0X05,
  0X05, 0X06, 0X08, 0X03, 0X0C, 0X03, 0X05, 0X0E, 0X02, 0X09, 0X0C, 0X01, 0X05, 0X0C, 0X03, 0X05,
  0X05, 0X0C, 0X02, 0X09, 0X06, 0X09, 0X05, 0X0C, 0X0A, 0X03, 0X06, 0X01, 0X04, 0X00, 0X0B, 0X05,
  0X05, 0X06, 0X08, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X03, 0X07, 0X06, 0X09, 0X05,
  0X05, 0X0C, 0X02, 0X09, 0X04, 0X09, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X09, 0X0E, 0X00, 0X01,
  0X06, 0X02, 0X0A, 0X03, 0X07, 0X06, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X03, 0X06, 0X0A, 0X03, 0X07
};

const uint8_t japan2004[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X08, 0X0A, 0X08, 0X08, 0X0A, 0X09, 0X05,
  0X05, 0X0E, 0X08, 0X09, 0X06, 0X01, 0X04, 0X03, 0X0C, 0X02, 0X08, 0X03, 0X06, 0X08, 0X03, 0X05,
  0X04, 0X09, 0X05, 0X06, 0X09, 0X06, 0X03, 0X0C, 0X01, 0X0C, 0X02, 0X0B, 0X0C, 0X02, 0X09, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X0C, 0X03, 0X07, 0X06, 0X0A, 0X09, 0X06, 0X08, 0X03, 0X05,
  0X05, 0X04, 0X09, 0X06, 0X09, 0X06, 0X03, 0X0D, 0X0D, 0X0C, 0X0A, 0X03, 0X0C, 0X02, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X02, 0X0A, 0X08, 0X00, 0X03, 0X06, 0X0A, 0X09, 0X06, 0X08, 0X03, 0X05,
  0X05, 0X05, 0X06, 0X02, 0X08, 0X08, 0X03, 0X04, 0X09, 0X0C, 0X0A, 0X03, 0X0E, 0X02, 0X09, 0X05,
  0X05, 0X06, 0X09, 0X0C, 0X03, 0X06, 0X08, 0X02, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05,
  0X04, 0X09, 0X06, 0X03, 0X0C, 0X09, 0X07, 0X0C, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X06, 0X01, 0X05,
  0X05, 0X06, 0X0A, 0X09, 0X05, 0X06, 0X09, 0X05, 0X06, 0X08, 0X02, 0X01, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X0C, 0X0A, 0X03, 0X06, 0X09, 0X05, 0X06, 0X09, 0X06, 0X08, 0X02, 0X09, 0X06, 0X03, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X0B, 0X06, 0X08, 0X02, 0X09, 0X0D, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0E, 0X02, 0X08, 0X02, 0X01, 0X05,
  0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X09, 0X06, 0X08, 0X02, 0X01,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t japan2005f[] = {
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0D, 0X0D, 0X0D, 0X0D, 0X0C, 0X09, 0X0C, 0X09,
  0X0E, 0X00, 0X08, 0X0B, 0X0D, 0X0C, 0X0A, 0X03, 0X04, 0X00, 0X00, 0X00, 0X01, 0X04, 0X01, 0X05,
  0X0C, 0X03, 0X06, 0X08, 0X03, 0X06, 0X0A, 0X0A, 0X03, 0X07, 0X07, 0X07, 0X06, 0X01, 0X05, 0X05,
  0X06, 0X08, 0X09, 0X06, 0X09, 0X0E, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X0D, 0X0C, 0X02, 0X01, 0X05,
  0X0C, 0X03, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X03, 0X06, 0X02, 0X02, 0X0A, 0X03, 0X05,
  0X04, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X04, 0X0B, 0X0D, 0X0D, 0X0C, 0X09, 0X0C, 0X09, 0X05,
  0X06, 0X08, 0X02, 0X09, 0X06, 0X08, 0X02, 0X03, 0X0E, 0X00, 0X00, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X05, 0X0C, 0X03, 0X0D, 0X0C, 0X08, 0X01, 0X05, 0X0C, 0X01, 0X05, 0X05, 0X05,
  0X06, 0X08, 0X03, 0X06, 0X02, 0X09, 0X04, 0X02, 0X03, 0X07, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X0E, 0X08, 0X03, 0X06, 0X09, 0X0D, 0X0C, 0X09, 0X07, 0X06, 0X03, 0X05, 0X05,
  0X06, 0X08, 0X03, 0X0C, 0X02, 0X09, 0X0E, 0X02, 0X02, 0X03, 0X05, 0X0C, 0X0A, 0X09, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X06, 0X08, 0X02, 0X0B, 0X0C, 0X0A, 0X0A, 0X03, 0X06, 0X09, 0X06, 0X01, 0X05,
  0X04, 0X0A, 0X03, 0X0C, 0X03, 0X0E, 0X08, 0X03, 0X0D, 0X0D, 0X0D, 0X0D, 0X06, 0X09, 0X07, 0X05,
  0X06, 0X0A, 0X08, 0X02, 0X0B, 0X0C, 0X02, 0X0B, 0X04, 0X00, 0X00, 0X00, 0X09, 0X06, 0X09, 0X05,
  0X0C, 0X0A, 0X02, 0X0A, 0X0B, 0X06, 0X0A, 0X0A, 0X03, 0X07, 0X07, 0X07, 0X06, 0X09, 0X04, 0X01,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03, 0X07
};

const uint8_t japan2007ef[] = {
  0X0E, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X0D, 0X0C, 0X0A, 0X09,
  0X0C, 0X02, 0X09, 0X06, 0X03, 0X06, 0X03, 0X06, 0X01, 0X0C, 0X0A, 0X03, 0X04, 0X02, 0X09, 0X05,
  0X06, 0X08, 0X02, 0X08, 0X0B, 0X0C, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05,
  0X0C, 0X02, 0X09, 0X06, 0X0A, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X06, 0X09, 0X05,
  0X04, 0X0A, 0X00, 0X0B, 0X0E, 0X08, 0X03, 0X0C, 0X0A, 0X09, 0X0E, 0X00, 0X0B, 0X0C, 0X03, 0X05,
  0X04, 0X0A, 0X00, 0X0B, 0X0C, 0X01, 0X0E, 0X02, 0X09, 0X05, 0X0E, 0X00, 0X0B, 0X06, 0X09, 0X05,
  0X04, 0X0A, 0X00, 0X0B, 0X05, 0X04, 0X08, 0X0A, 0X03, 0X05, 0X0C, 0X03, 0X0C, 0X09, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X07, 0X0C, 0X09, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X04, 0X02, 0X0A, 0X03, 0X0E, 0X00, 0X0B, 0X04, 0X03, 0X06, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X00, 0X0B, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X03, 0X04, 0X0B, 0X06, 0X0A, 0X0A, 0X08, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X08, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X0A, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X06, 0X03, 0X06, 0X03, 0X06, 0X03, 0X06, 0X09, 0X06, 0X0A, 0X02, 0X0B, 0X06, 0X01, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};

const uint8_t japan2007eq[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X08, 0X0A, 0X09,
  0X0C, 0X0A, 0X01, 0X0F, 0X0C, 0X03, 0X05, 0X0C, 0X0A, 0X09, 0X06, 0X0A, 0X00, 0X03, 0X0C, 0X03,
  0X05, 0X0C, 0X02, 0X09, 0X05, 0X0C, 0X01, 0X04, 0X08, 0X03, 0X0C, 0X08, 0X03, 0X0C, 0X02, 0X09,
  0X05, 0X05, 0X0F, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X05, 0X0C, 0X03, 0X0C, 0X01,
  0X04, 0X02, 0X0A, 0X02, 0X01, 0X04, 0X01, 0X05, 0X04, 0X01, 0X07, 0X06, 0X02, 0X0A, 0X03, 0X05,
  0X06, 0X0A, 0X08, 0X0A, 0X00, 0X03, 0X06, 0X03, 0X07, 0X07, 0X0C, 0X09, 0X0D, 0X0C, 0X09, 0X05,
  0X0C, 0X0A, 0X02, 0X08, 0X02, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X04, 0X03, 0X06, 0X01,
  0X05, 0X0C, 0X0A, 0X02, 0X0A, 0X03, 0X04, 0X08, 0X09, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X01,
  0X05, 0X05, 0X0C, 0X08, 0X08, 0X09, 0X05, 0X06, 0X03, 0X05, 0X06, 0X00, 0X08, 0X0A, 0X0A, 0X03,
  0X05, 0X06, 0X03, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X08, 0X02, 0X09, 0X07, 0X06, 0X0A, 0X0A, 0X09,
  0X04, 0X0A, 0X08, 0X03, 0X06, 0X03, 0X06, 0X08, 0X02, 0X08, 0X02, 0X0A, 0X09, 0X0F, 0X0C, 0X03,
  0X05, 0X0D, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X06, 0X09, 0X04, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09,
  0X05, 0X06, 0X01, 0X05, 0X04, 0X01, 0X04, 0X09, 0X06, 0X02, 0X0A, 0X02, 0X09, 0X06, 0X08, 0X01,
  0X05, 0X0C, 0X03, 0X05, 0X05, 0X06, 0X03, 0X06, 0X09, 0X0C, 0X0A, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X01, 0X05, 0X0C, 0X08, 0X09, 0X06, 0X03, 0X0C, 0X01, 0X0F, 0X04, 0X02, 0X01,
  0X06, 0X0A, 0X0A, 0X03, 0X06, 0X03, 0X07, 0X06, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t japan2009ef[] = {
  0X0E, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X09, 0X0D, 0X0D, 0X0D, 0X0D, 0X0D, 0X0C, 0X09,
  0X0C, 0X03, 0X06, 0X08, 0X02, 0X08, 0X00, 0X0A, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X05,
  0X06, 0X08, 0X09, 0X04, 0X08, 0X03, 0X05, 0X0C, 0X09, 0X07, 0X07, 0X07, 0X07, 0X07, 0X05, 0X05,
  0X0C, 0X03, 0X05, 0X05, 0X06, 0X09, 0X06, 0X03, 0X05, 0X0D, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X05,
  0X06, 0X09, 0X06, 0X00, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X04, 0X03, 0X0C, 0X09, 0X05, 0X05, 0X05,
  0X0C, 0X02, 0X09, 0X06, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0D, 0X06, 0X09, 0X0C, 0X09, 0X05, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X01, 0X06, 0X03, 0X05,
  0X05, 0X04, 0X09, 0X04, 0X03, 0X06, 0X03, 0X0C, 0X09, 0X0C, 0X0A, 0X03, 0X07, 0X0C, 0X09, 0X05,
  0X06, 0X03, 0X04, 0X03, 0X0C, 0X0A, 0X09, 0X04, 0X03, 0X06, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05,
  0X0C, 0X08, 0X01, 0X0D, 0X06, 0X0B, 0X05, 0X04, 0X08, 0X0B, 0X04, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X00, 0X0A, 0X0A, 0X03, 0X05, 0X06, 0X09, 0X06, 0X09, 0X06, 0X03, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X05, 0X0C, 0X0A, 0X09, 0X04, 0X0A, 0X02, 0X09, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X06, 0X03, 0X0C, 0X03, 0X06, 0X0A, 0X08, 0X02, 0X09, 0X0C, 0X01, 0X05, 0X05,
  0X05, 0X04, 0X09, 0X0C, 0X09, 0X05, 0X0D, 0X0C, 0X09, 0X06, 0X0A, 0X02, 0X01, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X04, 0X01, 0X04, 0X09, 0X0C, 0X09, 0X07, 0X05, 0X05, 0X05,
  0X06, 0X03, 0X06, 0X02, 0X0A, 0X0A, 0X03, 0X06, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X03, 0X06, 0X03
};

const uint8_t japan2009eq[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X0D, 0X0C, 0X0A, 0X0A, 0X08, 0X09, 0X0C, 0X0A, 0X08, 0X09,
  0X0C, 0X0A, 0X02, 0X08, 0X08, 0X00, 0X00, 0X02, 0X0A, 0X0A, 0X01, 0X05, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X0D, 0X0F, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X09, 0X05, 0X05, 0X0C, 0X01, 0X05, 0X05,
  0X05, 0X04, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X05, 0X07, 0X05,
  0X06, 0X00, 0X0A, 0X0A, 0X00, 0X03, 0X05, 0X06, 0X03, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X01,
  0X0E, 0X00, 0X0A, 0X0A, 0X03, 0X0F, 0X06, 0X0A, 0X0A, 0X03, 0X05, 0X04, 0X03, 0X0C, 0X03, 0X05,
  0X0C, 0X00, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X03, 0X07, 0X0C, 0X03, 0X0C, 0X03,
  0X05, 0X05, 0X0C, 0X0A, 0X09, 0X05, 0X05, 0X0C, 0X09, 0X0D, 0X0D, 0X0C, 0X03, 0X0C, 0X02, 0X09,
  0X05, 0X05, 0X05, 0X0E, 0X03, 0X05, 0X05, 0X06, 0X01, 0X05, 0X05, 0X06, 0X09, 0X06, 0X08, 0X03,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X03, 0X05, 0X0E, 0X02, 0X00, 0X00, 0X09, 0X06, 0X09, 0X06, 0X09,
  0X04, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0E, 0X0A, 0X01, 0X05, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X06, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X0C, 0X09, 0X06, 0X00, 0X0A, 0X00, 0X09, 0X06, 0X01,
  0X0C, 0X02, 0X08, 0X0A, 0X08, 0X03, 0X0C, 0X03, 0X06, 0X09, 0X06, 0X09, 0X05, 0X04, 0X09, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X06, 0X01,
  0X04, 0X02, 0X08, 0X03, 0X0C, 0X01, 0X0C, 0X01, 0X04, 0X09, 0X06, 0X09, 0X06, 0X02, 0X0A, 0X01,
  0X06, 0X0A, 0X02, 0X0A, 0X03, 0X06, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03
};


const uint8_t kyot_89[] = {
  0X0E, 0X0A, 0X0A, 0X09, 0X0E, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X08, 0X08, 0X09,
  0X0D, 0X0C, 0X09, 0X05, 0X0C, 0X09, 0X04, 0X01, 0X0E, 0X0A, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0E, 0X0A, 0X0A, 0X01, 0X04, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X02, 0X03, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0B, 0X05, 0X05, 0X04, 0X01, 0X05,
  0X04, 0X02, 0X08, 0X0A, 0X0A, 0X02, 0X01, 0X05, 0X0E, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X04, 0X01,
  0X05, 0X0F, 0X05, 0X0F, 0X0C, 0X0A, 0X03, 0X06, 0X0A, 0X0B, 0X0F, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X08, 0X02, 0X0A, 0X02, 0X0B, 0X0C, 0X0A, 0X0A, 0X09, 0X0D, 0X06, 0X00, 0X02, 0X02, 0X01,
  0X0C, 0X02, 0X0A, 0X08, 0X0A, 0X09, 0X05, 0X0C, 0X08, 0X01, 0X04, 0X09, 0X06, 0X08, 0X0A, 0X01,
  0X05, 0X0D, 0X0D, 0X05, 0X0D, 0X05, 0X05, 0X06, 0X03, 0X04, 0X03, 0X05, 0X0E, 0X02, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X07, 0X06, 0X0A, 0X0A, 0X01, 0X0C, 0X03, 0X0E, 0X0B, 0X05, 0X05,
  0X05, 0X07, 0X05, 0X07, 0X05, 0X0F, 0X0E, 0X08, 0X0A, 0X03, 0X06, 0X09, 0X0E, 0X0A, 0X01, 0X05,
  0X04, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X00, 0X0A, 0X0A, 0X02, 0X01,
  0X04, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X00, 0X09, 0X0C, 0X0A, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X01,
  0X04, 0X0A, 0X02, 0X08, 0X0A, 0X0A, 0X01, 0X04, 0X01, 0X0F, 0X05, 0X05, 0X05, 0X0C, 0X0B, 0X05,
  0X04, 0X0A, 0X0A, 0X02, 0X08, 0X0A, 0X01, 0X05, 0X06, 0X0A, 0X02, 0X01, 0X05, 0X07, 0X0C, 0X03,
  0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X03, 0X0F
};



const uint8_t minos01f[] = {
  0X0E, 0X08, 0X08, 0X0A, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X09, 0X0C, 0X0A, 0X09,
  0X0C, 0X01, 0X06, 0X0A, 0X03, 0X05, 0X0D, 0X05, 0X0D, 0X05, 0X0C, 0X03, 0X05, 0X04, 0X0A, 0X01,
  0X05, 0X06, 0X09, 0X0E, 0X09, 0X06, 0X01, 0X04, 0X03, 0X06, 0X00, 0X0A, 0X02, 0X03, 0X0C, 0X01,
  0X05, 0X0D, 0X04, 0X09, 0X04, 0X09, 0X05, 0X05, 0X0D, 0X0C, 0X03, 0X0E, 0X0A, 0X08, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X01, 0X05, 0X05, 0X06, 0X01, 0X04, 0X09, 0X0E, 0X08, 0X03, 0X07, 0X05,
  0X05, 0X05, 0X05, 0X0D, 0X06, 0X01, 0X06, 0X08, 0X01, 0X05, 0X05, 0X0C, 0X01, 0X0E, 0X09, 0X05,
  0X05, 0X06, 0X00, 0X02, 0X0A, 0X02, 0X0A, 0X03, 0X07, 0X07, 0X04, 0X01, 0X05, 0X0E, 0X02, 0X01,
  0X04, 0X08, 0X01, 0X0D, 0X0C, 0X0A, 0X0A, 0X08, 0X09, 0X0E, 0X03, 0X05, 0X04, 0X0A, 0X0A, 0X03,
  0X05, 0X05, 0X07, 0X06, 0X01, 0X0E, 0X09, 0X06, 0X03, 0X0E, 0X08, 0X01, 0X05, 0X0E, 0X0A, 0X09,
  0X05, 0X06, 0X08, 0X0B, 0X05, 0X0E, 0X02, 0X09, 0X0E, 0X09, 0X07, 0X04, 0X02, 0X0A, 0X0A, 0X01,
  0X04, 0X0A, 0X03, 0X0D, 0X06, 0X0A, 0X0A, 0X00, 0X0A, 0X02, 0X0A, 0X02, 0X08, 0X0A, 0X0A, 0X03,
  0X04, 0X0A, 0X08, 0X02, 0X0A, 0X0A, 0X0B, 0X07, 0X0D, 0X0C, 0X0A, 0X09, 0X05, 0X0C, 0X0A, 0X09,
  0X05, 0X0E, 0X02, 0X0A, 0X0A, 0X08, 0X0B, 0X0C, 0X01, 0X05, 0X0E, 0X01, 0X04, 0X02, 0X0A, 0X01,
  0X05, 0X0E, 0X08, 0X0A, 0X0A, 0X02, 0X0A, 0X03, 0X05, 0X04, 0X09, 0X04, 0X01, 0X0E, 0X0A, 0X01,
  0X04, 0X0B, 0X04, 0X09, 0X0E, 0X08, 0X0B, 0X0C, 0X03, 0X07, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X03,
  0X06, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X02, 0X03, 0X06, 0X0A, 0X0B
};

const uint8_t minos02f[] = {
  0X0E, 0X08, 0X08, 0X09, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X0B, 0X0D, 0X0C, 0X0B,
  0X0C, 0X01, 0X05, 0X05, 0X0D, 0X0E, 0X0A, 0X09, 0X0C, 0X09, 0X05, 0X04, 0X08, 0X02, 0X00, 0X0B,
  0X05, 0X05, 0X05, 0X04, 0X01, 0X0E, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X05, 0X0D,
  0X05, 0X05, 0X06, 0X01, 0X05, 0X0D, 0X0D, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X00, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X07, 0X07, 0X06, 0X00, 0X00, 0X01,
  0X0C, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X0D, 0X0E, 0X0A, 0X0A, 0X01, 0X05, 0X05,
  0X05, 0X07, 0X06, 0X01, 0X05, 0X04, 0X02, 0X01, 0X05, 0X05, 0X0D, 0X0C, 0X09, 0X04, 0X01, 0X05,
  0X06, 0X08, 0X0B, 0X04, 0X03, 0X04, 0X0B, 0X04, 0X01, 0X04, 0X02, 0X01, 0X05, 0X05, 0X04, 0X03,
  0X0E, 0X01, 0X0C, 0X00, 0X0A, 0X01, 0X0C, 0X00, 0X03, 0X04, 0X0B, 0X04, 0X02, 0X00, 0X02, 0X0B,
  0X0E, 0X01, 0X05, 0X05, 0X0C, 0X02, 0X03, 0X04, 0X08, 0X00, 0X08, 0X00, 0X0A, 0X02, 0X08, 0X0B,
  0X0C, 0X02, 0X00, 0X00, 0X00, 0X09, 0X0C, 0X01, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X08, 0X02, 0X0B,
  0X06, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X00, 0X02, 0X08, 0X02, 0X08, 0X0B,
  0X0C, 0X0A, 0X01, 0X06, 0X02, 0X01, 0X05, 0X06, 0X02, 0X01, 0X05, 0X0C, 0X01, 0X0C, 0X00, 0X09,
  0X05, 0X0C, 0X00, 0X0A, 0X08, 0X02, 0X01, 0X0C, 0X0A, 0X01, 0X06, 0X01, 0X04, 0X01, 0X05, 0X05,
  0X04, 0X03, 0X04, 0X09, 0X06, 0X0A, 0X01, 0X05, 0X0C, 0X00, 0X0A, 0X03, 0X05, 0X06, 0X00, 0X03,
  0X07, 0X0E, 0X03, 0X06, 0X0A, 0X0A, 0X02, 0X02, 0X03, 0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X0B
};

const uint8_t minos03f[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X08, 0X03, 0X05, 0X0C, 0X0A, 0X0A, 0X00, 0X03, 0X05, 0X0E, 0X08, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X04, 0X0B, 0X06, 0X01, 0X0D, 0X0E, 0X02, 0X0A, 0X01, 0X0C, 0X02, 0X08, 0X0A, 0X03, 0X05,
  0X05, 0X04, 0X0A, 0X0A, 0X02, 0X01, 0X0E, 0X09, 0X0C, 0X01, 0X05, 0X0C, 0X02, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X0C, 0X00, 0X0B, 0X05, 0X05, 0X05, 0X06, 0X00, 0X0A, 0X08, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X01, 0X06, 0X0A, 0X03, 0X06, 0X02, 0X09, 0X04, 0X0B, 0X06, 0X0A, 0X03,
  0X05, 0X05, 0X06, 0X08, 0X01, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X0C, 0X0A, 0X0A, 0X09,
  0X05, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X0A, 0X03, 0X06, 0X0A, 0X08, 0X01,
  0X05, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X07, 0X04, 0X01, 0X05, 0X0C, 0X09, 0X0E, 0X08, 0X01, 0X05,
  0X04, 0X02, 0X03, 0X05, 0X05, 0X05, 0X0E, 0X01, 0X06, 0X01, 0X05, 0X04, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X0D, 0X0C, 0X01, 0X05, 0X04, 0X0B, 0X04, 0X0B, 0X05, 0X07, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X06, 0X02, 0X01, 0X06, 0X02, 0X01, 0X0E, 0X01, 0X0E, 0X01, 0X0C, 0X08, 0X08, 0X01, 0X07, 0X05,
  0X0C, 0X0A, 0X02, 0X0A, 0X0A, 0X01, 0X0F, 0X05, 0X0C, 0X01, 0X05, 0X07, 0X05, 0X06, 0X08, 0X03,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X01, 0X0E, 0X01, 0X05, 0X07, 0X05, 0X0C, 0X02, 0X09, 0X06, 0X09,
  0X05, 0X05, 0X0E, 0X08, 0X09, 0X07, 0X0D, 0X05, 0X05, 0X0C, 0X03, 0X06, 0X0A, 0X03, 0X0E, 0X01,
  0X07, 0X07, 0X0E, 0X03, 0X06, 0X0A, 0X02, 0X02, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t minos04f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X09,
  0X0E, 0X0A, 0X08, 0X0A, 0X08, 0X08, 0X03, 0X05, 0X0C, 0X09, 0X05, 0X04, 0X09, 0X0C, 0X0B, 0X05,
  0X0C, 0X09, 0X05, 0X0D, 0X06, 0X00, 0X08, 0X01, 0X05, 0X05, 0X05, 0X05, 0X06, 0X02, 0X09, 0X05,
  0X05, 0X05, 0X06, 0X00, 0X09, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X00, 0X03,
  0X05, 0X07, 0X0E, 0X03, 0X05, 0X05, 0X07, 0X05, 0X06, 0X00, 0X02, 0X00, 0X03, 0X0C, 0X01, 0X0D,
  0X04, 0X0A, 0X08, 0X08, 0X03, 0X04, 0X09, 0X05, 0X0F, 0X06, 0X08, 0X02, 0X09, 0X05, 0X05, 0X07,
  0X05, 0X0E, 0X01, 0X06, 0X0A, 0X01, 0X05, 0X07, 0X0C, 0X09, 0X06, 0X08, 0X03, 0X05, 0X05, 0X0D,
  0X04, 0X0A, 0X03, 0X0C, 0X09, 0X05, 0X05, 0X0C, 0X01, 0X05, 0X0D, 0X06, 0X09, 0X04, 0X00, 0X01,
  0X04, 0X0A, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X04, 0X01, 0X0C, 0X02, 0X03, 0X05, 0X05,
  0X06, 0X08, 0X0A, 0X00, 0X02, 0X02, 0X01, 0X0D, 0X0D, 0X05, 0X05, 0X06, 0X0A, 0X08, 0X01, 0X05,
  0X0C, 0X01, 0X0E, 0X03, 0X0D, 0X0C, 0X01, 0X05, 0X07, 0X05, 0X06, 0X0A, 0X08, 0X03, 0X07, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X04, 0X03, 0X05, 0X06, 0X08, 0X02, 0X08, 0X0B, 0X05, 0X0D, 0X0D, 0X05,
  0X05, 0X04, 0X01, 0X04, 0X03, 0X0D, 0X05, 0X0C, 0X01, 0X0C, 0X01, 0X0D, 0X04, 0X01, 0X04, 0X01,
  0X05, 0X07, 0X04, 0X03, 0X0C, 0X01, 0X05, 0X07, 0X06, 0X01, 0X07, 0X04, 0X03, 0X06, 0X03, 0X05,
  0X04, 0X08, 0X03, 0X0D, 0X05, 0X05, 0X05, 0X0D, 0X0F, 0X04, 0X0B, 0X04, 0X0A, 0X0A, 0X0A, 0X01,
  0X07, 0X06, 0X0A, 0X02, 0X02, 0X02, 0X02, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t minos04q[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X0D,
  0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X03, 0X05, 0X0C, 0X09, 0X05, 0X04, 0X09, 0X0C, 0X03, 0X05,
  0X0D, 0X0C, 0X09, 0X0D, 0X06, 0X00, 0X08, 0X01, 0X05, 0X05, 0X05, 0X05, 0X06, 0X02, 0X09, 0X05,
  0X05, 0X05, 0X06, 0X00, 0X09, 0X05, 0X05, 0X04, 0X00, 0X01, 0X05, 0X05, 0X0C, 0X0A, 0X01, 0X05,
  0X05, 0X06, 0X0A, 0X03, 0X05, 0X07, 0X07, 0X05, 0X07, 0X05, 0X06, 0X00, 0X01, 0X0C, 0X03, 0X05,
  0X04, 0X0A, 0X08, 0X08, 0X03, 0X0C, 0X09, 0X05, 0X0D, 0X06, 0X08, 0X03, 0X05, 0X04, 0X0A, 0X03,
  0X05, 0X0E, 0X01, 0X06, 0X0A, 0X01, 0X07, 0X06, 0X03, 0X0E, 0X02, 0X09, 0X05, 0X05, 0X0D, 0X0D,
  0X04, 0X0A, 0X03, 0X0C, 0X09, 0X04, 0X09, 0X0C, 0X09, 0X0E, 0X09, 0X06, 0X03, 0X04, 0X00, 0X01,
  0X04, 0X09, 0X0E, 0X01, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X01, 0X0D, 0X0C, 0X03, 0X05, 0X05,
  0X07, 0X04, 0X08, 0X00, 0X02, 0X02, 0X02, 0X03, 0X0D, 0X05, 0X05, 0X04, 0X01, 0X0C, 0X01, 0X05,
  0X0C, 0X01, 0X06, 0X02, 0X09, 0X0C, 0X08, 0X09, 0X07, 0X07, 0X04, 0X01, 0X04, 0X03, 0X07, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X06, 0X01, 0X05, 0X06, 0X08, 0X0A, 0X01, 0X07, 0X05, 0X0D, 0X0D, 0X05,
  0X05, 0X04, 0X01, 0X04, 0X0A, 0X01, 0X05, 0X0C, 0X01, 0X0C, 0X00, 0X09, 0X05, 0X04, 0X00, 0X01,
  0X05, 0X07, 0X04, 0X02, 0X08, 0X02, 0X01, 0X05, 0X06, 0X01, 0X07, 0X07, 0X06, 0X03, 0X07, 0X05,
  0X05, 0X0C, 0X03, 0X0D, 0X05, 0X0C, 0X03, 0X05, 0X0F, 0X04, 0X0B, 0X0C, 0X0A, 0X0A, 0X0A, 0X01,
  0X07, 0X06, 0X0A, 0X03, 0X06, 0X02, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t minos08f[] = {
  0X0E, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X0D, 0X0D,
  0X0E, 0X08, 0X03, 0X05, 0X0D, 0X0C, 0X0B, 0X0C, 0X09, 0X0C, 0X09, 0X06, 0X0A, 0X01, 0X06, 0X01,
  0X0E, 0X02, 0X0B, 0X05, 0X05, 0X06, 0X0A, 0X01, 0X06, 0X01, 0X06, 0X09, 0X0C, 0X02, 0X08, 0X01,
  0X0C, 0X08, 0X0B, 0X05, 0X05, 0X0D, 0X0D, 0X06, 0X08, 0X02, 0X09, 0X06, 0X02, 0X08, 0X03, 0X05,
  0X05, 0X05, 0X0C, 0X00, 0X00, 0X00, 0X03, 0X0C, 0X01, 0X0C, 0X02, 0X08, 0X0B, 0X04, 0X0A, 0X01,
  0X05, 0X04, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X06, 0X01, 0X0C, 0X01, 0X0E, 0X01, 0X0C, 0X03,
  0X05, 0X07, 0X05, 0X05, 0X04, 0X03, 0X04, 0X0A, 0X08, 0X01, 0X05, 0X04, 0X09, 0X06, 0X02, 0X09,
  0X05, 0X0D, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X0C, 0X01, 0X06, 0X01, 0X05, 0X06, 0X09, 0X0C, 0X01,
  0X07, 0X05, 0X06, 0X00, 0X03, 0X04, 0X09, 0X04, 0X03, 0X0E, 0X01, 0X06, 0X09, 0X06, 0X01, 0X07,
  0X0E, 0X00, 0X08, 0X03, 0X0E, 0X01, 0X05, 0X06, 0X09, 0X0D, 0X05, 0X0D, 0X04, 0X09, 0X06, 0X09,
  0X0F, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X04, 0X0A, 0X02, 0X03, 0X05, 0X05, 0X07, 0X04, 0X0B, 0X05,
  0X0C, 0X00, 0X03, 0X05, 0X0C, 0X08, 0X03, 0X0C, 0X0A, 0X0A, 0X00, 0X02, 0X08, 0X02, 0X0B, 0X05,
  0X05, 0X05, 0X0E, 0X02, 0X01, 0X04, 0X08, 0X00, 0X0A, 0X08, 0X00, 0X09, 0X04, 0X0A, 0X09, 0X05,
  0X04, 0X02, 0X08, 0X0B, 0X05, 0X05, 0X05, 0X07, 0X0D, 0X05, 0X05, 0X04, 0X01, 0X0D, 0X05, 0X05,
  0X05, 0X0E, 0X02, 0X0A, 0X01, 0X05, 0X06, 0X08, 0X03, 0X05, 0X06, 0X03, 0X05, 0X04, 0X02, 0X03,
  0X07, 0X0E, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X0B, 0X06, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X0B
};

const uint8_t minos09f[] = {
  0X0E, 0X0A, 0X0A, 0X08, 0X08, 0X09, 0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X0B, 0X0D,
  0X0C, 0X0A, 0X0A, 0X03, 0X07, 0X04, 0X0A, 0X03, 0X0E, 0X08, 0X0B, 0X05, 0X0C, 0X03, 0X0D, 0X05,
  0X05, 0X0D, 0X0C, 0X08, 0X0B, 0X05, 0X0C, 0X09, 0X0C, 0X02, 0X09, 0X07, 0X04, 0X08, 0X03, 0X05,
  0X06, 0X02, 0X01, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X0D, 0X07, 0X06, 0X08, 0X03,
  0X0C, 0X08, 0X02, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05, 0X07, 0X0C, 0X02, 0X08, 0X08, 0X03, 0X0D,
  0X05, 0X06, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X07, 0X05, 0X0E, 0X02, 0X0B, 0X05, 0X04, 0X0B, 0X05,
  0X04, 0X08, 0X0A, 0X0A, 0X03, 0X07, 0X04, 0X0A, 0X02, 0X08, 0X0B, 0X0E, 0X01, 0X04, 0X0B, 0X05,
  0X07, 0X06, 0X09, 0X0E, 0X0A, 0X09, 0X06, 0X08, 0X09, 0X07, 0X0D, 0X0E, 0X01, 0X04, 0X0B, 0X05,
  0X0C, 0X09, 0X06, 0X09, 0X0D, 0X04, 0X0B, 0X06, 0X01, 0X0D, 0X05, 0X0D, 0X04, 0X02, 0X0A, 0X01,
  0X05, 0X06, 0X0A, 0X01, 0X06, 0X02, 0X08, 0X0A, 0X02, 0X03, 0X04, 0X02, 0X03, 0X0C, 0X0B, 0X05,
  0X05, 0X0C, 0X0A, 0X03, 0X0C, 0X0B, 0X04, 0X09, 0X0C, 0X0A, 0X03, 0X0C, 0X0A, 0X02, 0X0A, 0X01,
  0X05, 0X05, 0X0D, 0X0C, 0X00, 0X0B, 0X05, 0X05, 0X05, 0X0C, 0X0B, 0X04, 0X0B, 0X0C, 0X0B, 0X05,
  0X05, 0X04, 0X03, 0X05, 0X06, 0X09, 0X05, 0X04, 0X02, 0X02, 0X0A, 0X00, 0X09, 0X04, 0X0B, 0X05,
  0X05, 0X04, 0X0B, 0X06, 0X0A, 0X01, 0X05, 0X06, 0X0A, 0X08, 0X09, 0X05, 0X06, 0X02, 0X09, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X0A, 0X03, 0X06, 0X02, 0X0A, 0X0B, 0X06, 0X03,
  0X07, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B
};

const uint8_t minos10f[] = {
  0X0E, 0X0A, 0X08, 0X08, 0X08, 0X0A, 0X09, 0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X0B, 0X0D,
  0X0C, 0X0A, 0X03, 0X05, 0X06, 0X09, 0X04, 0X0A, 0X08, 0X08, 0X09, 0X05, 0X07, 0X0D, 0X0C, 0X03,
  0X06, 0X08, 0X09, 0X06, 0X09, 0X06, 0X01, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X04, 0X03, 0X0D,
  0X0C, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X01, 0X04, 0X03, 0X05, 0X06, 0X00, 0X00, 0X02, 0X09, 0X05,
  0X05, 0X0E, 0X0A, 0X09, 0X0C, 0X09, 0X06, 0X01, 0X0C, 0X03, 0X0D, 0X05, 0X06, 0X09, 0X06, 0X01,
  0X05, 0X0E, 0X09, 0X06, 0X03, 0X05, 0X0D, 0X05, 0X05, 0X0F, 0X04, 0X01, 0X0D, 0X06, 0X09, 0X05,
  0X04, 0X0A, 0X02, 0X0A, 0X09, 0X05, 0X06, 0X03, 0X06, 0X0A, 0X01, 0X05, 0X06, 0X0A, 0X03, 0X05,
  0X04, 0X0A, 0X08, 0X08, 0X03, 0X04, 0X08, 0X08, 0X09, 0X0E, 0X03, 0X06, 0X08, 0X08, 0X0A, 0X01,
  0X04, 0X08, 0X03, 0X05, 0X0E, 0X03, 0X05, 0X06, 0X02, 0X08, 0X0B, 0X0D, 0X05, 0X07, 0X0C, 0X03,
  0X05, 0X06, 0X0B, 0X07, 0X0E, 0X08, 0X03, 0X0E, 0X0A, 0X02, 0X09, 0X05, 0X04, 0X0B, 0X07, 0X0D,
  0X04, 0X08, 0X0B, 0X0C, 0X09, 0X06, 0X0A, 0X09, 0X0C, 0X09, 0X06, 0X01, 0X06, 0X0A, 0X08, 0X01,
  0X05, 0X07, 0X0C, 0X01, 0X06, 0X08, 0X0B, 0X04, 0X03, 0X04, 0X0B, 0X04, 0X0A, 0X0A, 0X01, 0X05,
  0X05, 0X0C, 0X03, 0X04, 0X09, 0X06, 0X09, 0X06, 0X08, 0X00, 0X0B, 0X05, 0X0C, 0X09, 0X05, 0X05,
  0X04, 0X03, 0X0C, 0X01, 0X06, 0X0B, 0X06, 0X09, 0X05, 0X05, 0X0D, 0X05, 0X06, 0X03, 0X07, 0X05,
  0X05, 0X0E, 0X03, 0X05, 0X0D, 0X0D, 0X0D, 0X05, 0X05, 0X06, 0X03, 0X04, 0X08, 0X08, 0X0A, 0X03,
  0X07, 0X0E, 0X0A, 0X02, 0X02, 0X02, 0X02, 0X02, 0X02, 0X0A, 0X0B, 0X07, 0X07, 0X06, 0X0A, 0X0B
};

const uint8_t minos12f[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X0B, 0X0C, 0X0B, 0X0E, 0X08, 0X08, 0X0A, 0X09,
  0X0C, 0X08, 0X02, 0X0A, 0X0A, 0X00, 0X0B, 0X06, 0X0A, 0X00, 0X0A, 0X0B, 0X07, 0X06, 0X09, 0X05,
  0X05, 0X04, 0X08, 0X0A, 0X0A, 0X01, 0X0C, 0X08, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X01, 0X05,
  0X05, 0X05, 0X07, 0X0C, 0X0A, 0X01, 0X04, 0X00, 0X01, 0X05, 0X04, 0X08, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X04, 0X0B, 0X05, 0X0E, 0X01, 0X06, 0X02, 0X03, 0X04, 0X01, 0X06, 0X09, 0X07, 0X06, 0X01,
  0X05, 0X04, 0X09, 0X05, 0X0D, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X07, 0X0D, 0X06, 0X09, 0X0D, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X02, 0X09, 0X06, 0X01, 0X05,
  0X05, 0X05, 0X04, 0X03, 0X07, 0X0E, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X0E, 0X02, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X0B, 0X0D, 0X04, 0X02, 0X03, 0X05, 0X07, 0X0E, 0X08, 0X03, 0X05, 0X05,
  0X05, 0X06, 0X01, 0X04, 0X09, 0X06, 0X02, 0X0A, 0X0A, 0X03, 0X0E, 0X08, 0X01, 0X0D, 0X05, 0X05,
  0X05, 0X0D, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X01, 0X06, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X08, 0X08, 0X0B, 0X0C, 0X0A, 0X01, 0X0D, 0X05, 0X0C, 0X01, 0X05, 0X05,
  0X05, 0X06, 0X01, 0X05, 0X07, 0X06, 0X08, 0X01, 0X0C, 0X01, 0X05, 0X04, 0X03, 0X04, 0X01, 0X05,
  0X04, 0X0A, 0X03, 0X04, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X04, 0X08, 0X01, 0X05, 0X05,
  0X05, 0X0C, 0X0A, 0X00, 0X09, 0X0C, 0X09, 0X07, 0X05, 0X05, 0X07, 0X05, 0X05, 0X07, 0X07, 0X05,
  0X06, 0X02, 0X0A, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X02, 0X0A, 0X0B, 0X07
};

const uint8_t mj96bon[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X09,
  0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X01, 0X0E, 0X09, 0X06, 0X08, 0X0A, 0X02, 0X08, 0X03, 0X05,
  0X06, 0X09, 0X04, 0X09, 0X0C, 0X03, 0X04, 0X0A, 0X02, 0X0A, 0X02, 0X08, 0X0A, 0X00, 0X0A, 0X01,
  0X0C, 0X02, 0X03, 0X06, 0X00, 0X0A, 0X00, 0X0A, 0X0B, 0X0E, 0X08, 0X02, 0X09, 0X07, 0X0C, 0X03,
  0X04, 0X0A, 0X08, 0X0B, 0X04, 0X0B, 0X04, 0X08, 0X0A, 0X08, 0X03, 0X0E, 0X02, 0X08, 0X03, 0X0D,
  0X06, 0X08, 0X00, 0X0B, 0X04, 0X0B, 0X07, 0X06, 0X0B, 0X06, 0X0B, 0X0C, 0X08, 0X02, 0X08, 0X03,
  0X0C, 0X01, 0X04, 0X0B, 0X04, 0X09, 0X0C, 0X0A, 0X08, 0X0B, 0X0C, 0X03, 0X06, 0X0A, 0X02, 0X09,
  0X05, 0X05, 0X05, 0X0C, 0X03, 0X07, 0X05, 0X0C, 0X01, 0X0E, 0X03, 0X0C, 0X0A, 0X09, 0X0D, 0X05,
  0X04, 0X03, 0X05, 0X06, 0X0A, 0X0B, 0X05, 0X06, 0X03, 0X0E, 0X08, 0X02, 0X0B, 0X05, 0X06, 0X01,
  0X06, 0X08, 0X02, 0X08, 0X0A, 0X0B, 0X05, 0X0D, 0X0E, 0X08, 0X02, 0X08, 0X0B, 0X05, 0X0C, 0X03,
  0X0C, 0X00, 0X0B, 0X06, 0X08, 0X0B, 0X06, 0X02, 0X0A, 0X02, 0X0A, 0X03, 0X0E, 0X01, 0X06, 0X09,
  0X07, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X0E, 0X0A, 0X09, 0X0E, 0X08, 0X0B, 0X0C, 0X03, 0X0E, 0X01,
  0X0D, 0X0C, 0X0A, 0X00, 0X08, 0X02, 0X09, 0X0C, 0X02, 0X08, 0X03, 0X0C, 0X03, 0X0D, 0X0E, 0X01,
  0X04, 0X00, 0X0B, 0X07, 0X06, 0X0B, 0X06, 0X03, 0X0E, 0X03, 0X0C, 0X02, 0X0B, 0X04, 0X08, 0X03,
  0X05, 0X06, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0B, 0X0C, 0X08, 0X03, 0X0D, 0X0D, 0X05, 0X05, 0X0D,
  0X06, 0X0A, 0X02, 0X0A, 0X03, 0X0E, 0X02, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X02, 0X02, 0X02, 0X03
};

const uint8_t mont88[] = {
  0X0E, 0X0A, 0X09, 0X0E, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X0D,
  0X0C, 0X0B, 0X05, 0X0E, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X09, 0X0C, 0X02, 0X0A, 0X03,
  0X06, 0X0A, 0X00, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X03,
  0X07, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X0C, 0X01, 0X0C, 0X0B, 0X0D, 0X04, 0X0B,
  0X0E, 0X08, 0X0B, 0X0C, 0X08, 0X08, 0X0A, 0X03, 0X0C, 0X03, 0X06, 0X00, 0X0A, 0X01, 0X06, 0X09,
  0X0C, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X0E, 0X0A, 0X01, 0X0C, 0X02, 0X0B, 0X05,
  0X05, 0X0C, 0X01, 0X0D, 0X05, 0X06, 0X03, 0X0C, 0X09, 0X0C, 0X0A, 0X03, 0X06, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X07, 0X05, 0X05, 0X0C, 0X09, 0X04, 0X03, 0X06, 0X0A, 0X09, 0X0E, 0X08, 0X03, 0X05,
  0X06, 0X00, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X0C, 0X09, 0X05, 0X0C, 0X03, 0X0D, 0X05,
  0X0E, 0X00, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X05, 0X05, 0X04, 0X02, 0X0A, 0X03, 0X05,
  0X0E, 0X00, 0X0B, 0X04, 0X02, 0X01, 0X05, 0X05, 0X0E, 0X03, 0X04, 0X01, 0X0C, 0X08, 0X09, 0X05,
  0X0E, 0X00, 0X0B, 0X06, 0X09, 0X05, 0X05, 0X04, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X07, 0X06, 0X03,
  0X0E, 0X00, 0X09, 0X0E, 0X01, 0X05, 0X05, 0X05, 0X0D, 0X06, 0X03, 0X05, 0X05, 0X0C, 0X09, 0X0D,
  0X0E, 0X01, 0X06, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X08, 0X03, 0X06, 0X03, 0X05, 0X05,
  0X0E, 0X02, 0X0A, 0X0A, 0X03, 0X07, 0X06, 0X03, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};

const uint8_t nagoya2002[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X0E, 0X0B, 0X0C, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0B,
  0X0C, 0X08, 0X0A, 0X0A, 0X02, 0X09, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X0A, 0X02, 0X0A, 0X08, 0X09,
  0X05, 0X05, 0X0C, 0X0A, 0X0B, 0X05, 0X0F, 0X0D, 0X0D, 0X0F, 0X05, 0X0E, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X0C, 0X01, 0X05, 0X0C, 0X02, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X07, 0X05, 0X0F, 0X0D, 0X05, 0X05, 0X04, 0X01, 0X0D, 0X0F, 0X05, 0X07, 0X05, 0X05,
  0X05, 0X06, 0X08, 0X01, 0X0E, 0X03, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0B, 0X05, 0X0C, 0X03, 0X05,
  0X06, 0X09, 0X05, 0X06, 0X0A, 0X0A, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X0A, 0X03, 0X05, 0X0C, 0X03,
  0X0D, 0X05, 0X06, 0X0A, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X08, 0X0A, 0X03, 0X05, 0X0D,
  0X07, 0X05, 0X0C, 0X0A, 0X02, 0X0A, 0X03, 0X04, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X09, 0X05, 0X07,
  0X0C, 0X03, 0X05, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X08, 0X0A, 0X0A, 0X09, 0X05, 0X06, 0X09,
  0X05, 0X0C, 0X02, 0X01, 0X0E, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X0B, 0X05, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X0D, 0X05, 0X0F, 0X07, 0X05, 0X05, 0X05, 0X05, 0X07, 0X0F, 0X05, 0X0D, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X08, 0X03, 0X05, 0X05, 0X06, 0X08, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X0B, 0X05, 0X0F, 0X06, 0X03, 0X0F, 0X05, 0X0E, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X08, 0X0A, 0X03, 0X0C, 0X0A, 0X0A, 0X09, 0X06, 0X08, 0X0A, 0X08, 0X03, 0X05,
  0X06, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X0E, 0X0B, 0X06, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t niigata03[] = {
  0X0E, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X0C, 0X0A, 0X08, 0X02, 0X0A, 0X0A, 0X0B, 0X05, 0X0E, 0X0B, 0X06, 0X0A, 0X09, 0X06, 0X09, 0X05,
  0X04, 0X09, 0X05, 0X0C, 0X0B, 0X0E, 0X0A, 0X02, 0X08, 0X0A, 0X0A, 0X0B, 0X04, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0B, 0X0F, 0X0D, 0X07, 0X04, 0X03, 0X0E, 0X08, 0X0A, 0X02, 0X0B, 0X07,
  0X05, 0X05, 0X06, 0X0A, 0X08, 0X0A, 0X02, 0X0A, 0X03, 0X0F, 0X0F, 0X06, 0X0A, 0X0A, 0X0A, 0X09,
  0X05, 0X06, 0X0A, 0X08, 0X02, 0X0A, 0X08, 0X0A, 0X0B, 0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X05,
  0X04, 0X0A, 0X09, 0X06, 0X0A, 0X09, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X07, 0X0D, 0X0D, 0X05, 0X05,
  0X05, 0X0D, 0X04, 0X0A, 0X09, 0X05, 0X05, 0X06, 0X02, 0X03, 0X05, 0X0D, 0X07, 0X07, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0F, 0X05, 0X05, 0X06, 0X0A, 0X09, 0X0E, 0X01, 0X06, 0X0A, 0X0A, 0X03, 0X05,
  0X05, 0X07, 0X04, 0X0A, 0X02, 0X02, 0X08, 0X0A, 0X01, 0X0F, 0X06, 0X0A, 0X09, 0X0E, 0X0A, 0X01,
  0X06, 0X09, 0X05, 0X0C, 0X0B, 0X0F, 0X07, 0X0D, 0X04, 0X09, 0X0E, 0X0A, 0X02, 0X08, 0X09, 0X05,
  0X0D, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X03, 0X07, 0X06, 0X0A, 0X0A, 0X09, 0X07, 0X05, 0X05,
  0X07, 0X05, 0X05, 0X06, 0X0B, 0X0E, 0X0A, 0X08, 0X09, 0X0E, 0X0A, 0X0B, 0X04, 0X0B, 0X05, 0X05,
  0X0C, 0X03, 0X06, 0X0A, 0X0A, 0X08, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X02, 0X01,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t robotic2009[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X09, 0X0E, 0X09, 0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X09,
  0X0C, 0X09, 0X0E, 0X09, 0X07, 0X05, 0X04, 0X08, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X05, 0X04, 0X0A, 0X01, 0X0D, 0X05, 0X05, 0X06, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X05, 0X05, 0X0E, 0X02, 0X02, 0X03, 0X04, 0X08, 0X03, 0X06, 0X08, 0X08, 0X08, 0X0A, 0X0A, 0X03,
  0X05, 0X05, 0X0C, 0X08, 0X0A, 0X09, 0X05, 0X04, 0X09, 0X0C, 0X03, 0X05, 0X05, 0X0C, 0X0A, 0X09,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X06, 0X03, 0X06, 0X03, 0X0E, 0X01, 0X05, 0X07, 0X0D, 0X05,
  0X05, 0X06, 0X01, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X06, 0X08, 0X01, 0X05,
  0X05, 0X0C, 0X03, 0X04, 0X00, 0X03, 0X0C, 0X08, 0X09, 0X0E, 0X0A, 0X03, 0X0C, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X01, 0X07, 0X0C, 0X03, 0X06, 0X03, 0X0C, 0X0A, 0X08, 0X03, 0X05, 0X05, 0X05,
  0X04, 0X02, 0X01, 0X06, 0X0B, 0X06, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X02, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X0E, 0X02, 0X08, 0X09, 0X0C, 0X0B, 0X0C, 0X03, 0X04, 0X00, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X09, 0X07, 0X06, 0X03, 0X0C, 0X01, 0X0C, 0X01, 0X05, 0X05, 0X05, 0X04, 0X03, 0X07,
  0X05, 0X07, 0X04, 0X08, 0X0B, 0X0C, 0X03, 0X04, 0X03, 0X07, 0X05, 0X07, 0X05, 0X06, 0X09, 0X0D,
  0X05, 0X0E, 0X01, 0X06, 0X09, 0X05, 0X0C, 0X03, 0X0C, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X03, 0X05,
  0X05, 0X0E, 0X02, 0X0B, 0X04, 0X02, 0X02, 0X0A, 0X03, 0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t robotic2010[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X08, 0X08, 0X08, 0X09,
  0X0C, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X07, 0X07, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X08, 0X0A, 0X02, 0X0B, 0X0E, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X02, 0X09, 0X0E, 0X02, 0X0A, 0X08, 0X08, 0X0B, 0X05, 0X05,
  0X05, 0X06, 0X03, 0X06, 0X01, 0X0E, 0X0A, 0X03, 0X0C, 0X0A, 0X09, 0X05, 0X07, 0X0E, 0X01, 0X05,
  0X04, 0X0A, 0X0B, 0X0C, 0X02, 0X0A, 0X09, 0X0C, 0X02, 0X09, 0X06, 0X03, 0X0E, 0X0A, 0X01, 0X05,
  0X05, 0X0C, 0X09, 0X06, 0X0A, 0X0A, 0X03, 0X07, 0X0E, 0X02, 0X08, 0X0A, 0X0A, 0X0B, 0X06, 0X01,
  0X05, 0X05, 0X05, 0X0E, 0X09, 0X0C, 0X0A, 0X08, 0X09, 0X0D, 0X04, 0X0B, 0X0C, 0X0B, 0X0D, 0X05,
  0X05, 0X05, 0X05, 0X0D, 0X05, 0X05, 0X0D, 0X06, 0X03, 0X04, 0X02, 0X08, 0X03, 0X0E, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X00, 0X0A, 0X0A, 0X02, 0X0B, 0X06, 0X0B, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X04, 0X01, 0X05, 0X0C, 0X02, 0X0A, 0X0A, 0X09, 0X0D, 0X0C, 0X0A, 0X01, 0X0E, 0X01,
  0X05, 0X05, 0X05, 0X06, 0X00, 0X03, 0X0C, 0X0A, 0X09, 0X04, 0X03, 0X05, 0X0C, 0X02, 0X0B, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X03, 0X0C, 0X03, 0X0D, 0X06, 0X00, 0X0A, 0X01, 0X06, 0X08, 0X0B, 0X05,
  0X05, 0X05, 0X0E, 0X09, 0X0C, 0X03, 0X0C, 0X02, 0X08, 0X03, 0X0C, 0X02, 0X0B, 0X05, 0X0E, 0X01,
  0X04, 0X02, 0X0A, 0X03, 0X05, 0X0C, 0X03, 0X0D, 0X06, 0X09, 0X04, 0X08, 0X0B, 0X04, 0X0A, 0X03,
  0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X0B
};

const uint8_t robotic2011[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X09, 0X0C, 0X0A, 0X0B,
  0X0E, 0X0A, 0X00, 0X03, 0X05, 0X05, 0X0C, 0X0A, 0X08, 0X09, 0X05, 0X05, 0X06, 0X00, 0X0A, 0X0B,
  0X0E, 0X08, 0X02, 0X0A, 0X03, 0X05, 0X04, 0X09, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X02, 0X08, 0X0B,
  0X0C, 0X02, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X09,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X08, 0X0A, 0X08, 0X09, 0X0D, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X08, 0X0B, 0X0E, 0X00, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X07, 0X04, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X02, 0X09, 0X07, 0X04, 0X00, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X08, 0X08, 0X03, 0X0E, 0X03, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X00, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X03, 0X04, 0X02, 0X02, 0X01, 0X0E, 0X0A, 0X0A, 0X0A, 0X02, 0X03, 0X05, 0X05,
  0X06, 0X03, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};

const uint8_t seoul2[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0B,
  0X0E, 0X08, 0X08, 0X0A, 0X02, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X02, 0X08, 0X08, 0X0B,
  0X0C, 0X03, 0X06, 0X0A, 0X0B, 0X0C, 0X0A, 0X01, 0X04, 0X0A, 0X09, 0X0E, 0X0A, 0X03, 0X06, 0X09,
  0X06, 0X09, 0X0C, 0X08, 0X08, 0X00, 0X0A, 0X00, 0X00, 0X0A, 0X00, 0X08, 0X08, 0X09, 0X0C, 0X03,
  0X0C, 0X03, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X01, 0X04, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X06, 0X09,
  0X06, 0X09, 0X05, 0X05, 0X06, 0X0A, 0X0B, 0X06, 0X03, 0X0E, 0X0A, 0X03, 0X05, 0X05, 0X0C, 0X03,
  0X0C, 0X02, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X02, 0X09,
  0X04, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0B, 0X0C, 0X09, 0X0D, 0X0D, 0X0D, 0X0D, 0X0D, 0X0D, 0X05,
  0X05, 0X0D, 0X0D, 0X04, 0X0A, 0X0A, 0X0B, 0X04, 0X03, 0X04, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X04, 0X00, 0X00, 0X00, 0X0A, 0X0A, 0X0B, 0X05, 0X0D, 0X05, 0X07, 0X07, 0X07, 0X07, 0X07, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0B, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X05,
  0X05, 0X06, 0X00, 0X03, 0X0C, 0X0A, 0X0A, 0X02, 0X01, 0X0E, 0X0A, 0X09, 0X0E, 0X00, 0X0B, 0X05,
  0X05, 0X0E, 0X00, 0X0B, 0X06, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X0E, 0X01, 0X0E, 0X00, 0X0B, 0X05,
  0X05, 0X0E, 0X00, 0X0B, 0X0C, 0X0A, 0X0A, 0X03, 0X0D, 0X06, 0X09, 0X05, 0X0E, 0X00, 0X0B, 0X05,
  0X05, 0X0E, 0X00, 0X0B, 0X06, 0X0A, 0X0A, 0X09, 0X05, 0X0D, 0X06, 0X01, 0X0E, 0X00, 0X0B, 0X05,
  0X07, 0X0E, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0B, 0X07
};

const uint8_t sg87[] = {
  0X0E, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0B,
  0X0C, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X09,
  0X05, 0X0C, 0X08, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X09, 0X05, 0X0D, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X05, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X01, 0X04, 0X01, 0X05, 0X05, 0X05, 0X06, 0X01, 0X05, 0X06, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0E, 0X02, 0X02, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X01, 0X04, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X07, 0X07, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X0B, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X02, 0X00, 0X0A, 0X0A, 0X0A, 0X0A, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X03, 0X0C, 0X0A, 0X08, 0X00, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X05,
  0X05, 0X06, 0X02, 0X0A, 0X0A, 0X02, 0X0B, 0X07, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X07, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t sg88[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X09,
  0X0C, 0X0A, 0X02, 0X02, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X02, 0X01, 0X05,
  0X05, 0X0C, 0X0A, 0X08, 0X03, 0X0C, 0X0A, 0X09, 0X0C, 0X03, 0X05, 0X0E, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X01, 0X06, 0X0A, 0X02, 0X0A, 0X08, 0X02, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X03, 0X0C, 0X01, 0X06, 0X0A, 0X0B, 0X0D, 0X0C, 0X00, 0X08, 0X0A, 0X03,
  0X05, 0X05, 0X06, 0X03, 0X0C, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X09,
  0X05, 0X05, 0X0C, 0X08, 0X02, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X04, 0X00, 0X00, 0X00, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0D, 0X05, 0X05, 0X0C, 0X08, 0X01, 0X07, 0X05, 0X05, 0X05, 0X07, 0X05,
  0X04, 0X03, 0X05, 0X06, 0X02, 0X03, 0X05, 0X06, 0X03, 0X05, 0X0E, 0X00, 0X00, 0X00, 0X09, 0X05,
  0X06, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0B, 0X05, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X01, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X06, 0X02, 0X00, 0X02, 0X02, 0X01,
  0X05, 0X05, 0X05, 0X0D, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X0E, 0X0A, 0X02, 0X0A, 0X08, 0X03,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X09,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t sg89[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X0E, 0X0A, 0X08, 0X08, 0X09, 0X0C, 0X08, 0X09, 0X0C, 0X09, 0X0C, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X01, 0X0D, 0X05, 0X05,
  0X05, 0X05, 0X07, 0X0E, 0X08, 0X01, 0X06, 0X01, 0X07, 0X07, 0X05, 0X0E, 0X02, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X0E, 0X08, 0X03, 0X06, 0X08, 0X03, 0X0C, 0X0A, 0X01, 0X0E, 0X0A, 0X01, 0X04, 0X01,
  0X07, 0X05, 0X0C, 0X00, 0X08, 0X0B, 0X04, 0X0A, 0X02, 0X0A, 0X01, 0X0C, 0X0A, 0X03, 0X05, 0X05,
  0X0D, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X07, 0X0C, 0X08, 0X09, 0X07, 0X06, 0X0A, 0X09, 0X05, 0X05,
  0X04, 0X03, 0X05, 0X07, 0X05, 0X04, 0X09, 0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X01, 0X05, 0X05,
  0X05, 0X0D, 0X06, 0X09, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X0D, 0X05, 0X06, 0X03, 0X0C, 0X0B, 0X0C, 0X00, 0X0A, 0X03, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0E, 0X08, 0X02, 0X09, 0X07, 0X04, 0X0A, 0X0A, 0X0B, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X01, 0X0C, 0X03, 0X0C, 0X02, 0X0B, 0X06, 0X0A, 0X09, 0X0E, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X02, 0X08, 0X02, 0X0A, 0X0A, 0X0B, 0X0E, 0X02, 0X0A, 0X03, 0X05, 0X07,
  0X07, 0X05, 0X06, 0X0A, 0X0A, 0X02, 0X09, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X09,
  0X0E, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t taiwan2009[] = {
  0X0E, 0X08, 0X0A, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X08, 0X08, 0X08, 0X09,
  0X0C, 0X02, 0X08, 0X01, 0X06, 0X0A, 0X02, 0X0A, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X09, 0X07, 0X04, 0X09, 0X0D, 0X0C, 0X09, 0X06, 0X08, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01,
  0X0E, 0X02, 0X0A, 0X03, 0X07, 0X04, 0X03, 0X06, 0X09, 0X07, 0X05, 0X07, 0X05, 0X07, 0X07, 0X05,
  0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X0E, 0X09, 0X06, 0X09, 0X04, 0X0A, 0X00, 0X0A, 0X09, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X02, 0X08, 0X03, 0X06, 0X09, 0X06, 0X08, 0X03, 0X05,
  0X0D, 0X0E, 0X08, 0X08, 0X01, 0X07, 0X06, 0X08, 0X03, 0X0C, 0X08, 0X02, 0X0A, 0X03, 0X0D, 0X05,
  0X06, 0X08, 0X03, 0X05, 0X07, 0X0E, 0X09, 0X04, 0X09, 0X05, 0X06, 0X0A, 0X09, 0X0C, 0X01, 0X05,
  0X0E, 0X01, 0X0C, 0X02, 0X08, 0X0A, 0X01, 0X06, 0X03, 0X06, 0X08, 0X09, 0X05, 0X07, 0X04, 0X01,
  0X0C, 0X01, 0X06, 0X08, 0X02, 0X08, 0X02, 0X0B, 0X0E, 0X09, 0X07, 0X06, 0X03, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X0C, 0X02, 0X0A, 0X02, 0X0B, 0X0E, 0X08, 0X02, 0X08, 0X08, 0X08, 0X03, 0X0D, 0X05,
  0X04, 0X01, 0X06, 0X09, 0X0D, 0X0C, 0X0B, 0X0D, 0X06, 0X0A, 0X01, 0X05, 0X04, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X00, 0X00, 0X00, 0X0A, 0X00, 0X0A, 0X09, 0X06, 0X02, 0X00, 0X0B, 0X04, 0X01,
  0X06, 0X00, 0X01, 0X07, 0X07, 0X07, 0X0D, 0X07, 0X0C, 0X00, 0X0B, 0X0C, 0X03, 0X0E, 0X03, 0X05,
  0X0D, 0X07, 0X07, 0X0C, 0X0A, 0X09, 0X05, 0X0C, 0X03, 0X07, 0X0C, 0X00, 0X0A, 0X08, 0X08, 0X01,
  0X06, 0X0A, 0X0A, 0X03, 0X0E, 0X02, 0X02, 0X02, 0X0A, 0X0A, 0X03, 0X06, 0X0B, 0X07, 0X07, 0X07
};

const uint8_t taiwan2012[] = {
  0X0E, 0X08, 0X09, 0X0D, 0X0C, 0X08, 0X09, 0X0D, 0X0C, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X01, 0X06, 0X02, 0X03, 0X07, 0X06, 0X02, 0X03, 0X07, 0X07, 0X0E, 0X08, 0X09, 0X0D, 0X05,
  0X05, 0X04, 0X08, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X09, 0X0E, 0X09, 0X0C, 0X01, 0X04, 0X01, 0X05,
  0X04, 0X01, 0X05, 0X0D, 0X0C, 0X0A, 0X03, 0X05, 0X06, 0X08, 0X02, 0X03, 0X04, 0X01, 0X05, 0X05,
  0X07, 0X04, 0X00, 0X01, 0X06, 0X0A, 0X09, 0X06, 0X08, 0X02, 0X09, 0X0C, 0X01, 0X05, 0X05, 0X05,
  0X0C, 0X01, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X0E, 0X00, 0X0B, 0X04, 0X03, 0X04, 0X03, 0X05, 0X05,
  0X05, 0X04, 0X02, 0X00, 0X02, 0X09, 0X0C, 0X0A, 0X02, 0X09, 0X07, 0X0C, 0X03, 0X0D, 0X05, 0X05,
  0X04, 0X01, 0X0C, 0X01, 0X0C, 0X03, 0X05, 0X0C, 0X09, 0X07, 0X0E, 0X00, 0X09, 0X05, 0X05, 0X05,
  0X07, 0X04, 0X01, 0X07, 0X06, 0X09, 0X06, 0X02, 0X03, 0X0C, 0X0A, 0X03, 0X06, 0X02, 0X01, 0X05,
  0X0C, 0X01, 0X04, 0X0B, 0X0E, 0X00, 0X09, 0X0E, 0X08, 0X02, 0X08, 0X0A, 0X0A, 0X08, 0X03, 0X05,
  0X05, 0X04, 0X00, 0X0B, 0X0C, 0X03, 0X06, 0X09, 0X06, 0X09, 0X07, 0X0D, 0X0C, 0X02, 0X09, 0X05,
  0X04, 0X01, 0X07, 0X0C, 0X03, 0X0C, 0X08, 0X02, 0X09, 0X06, 0X0A, 0X02, 0X03, 0X0C, 0X01, 0X05,
  0X07, 0X04, 0X0A, 0X03, 0X0C, 0X03, 0X06, 0X09, 0X06, 0X09, 0X0C, 0X0A, 0X08, 0X03, 0X05, 0X05,
  0X0C, 0X00, 0X0A, 0X08, 0X03, 0X0D, 0X0E, 0X00, 0X09, 0X04, 0X01, 0X0C, 0X02, 0X09, 0X04, 0X01,
  0X05, 0X06, 0X08, 0X02, 0X08, 0X02, 0X0B, 0X07, 0X06, 0X03, 0X06, 0X02, 0X0B, 0X06, 0X01, 0X05,
  0X06, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};

const uint8_t tyubu200906[] = {
  0X0E, 0X0A, 0X0A, 0X08, 0X0B, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X09,
  0X0E, 0X0A, 0X0B, 0X04, 0X0B, 0X0C, 0X0B, 0X0C, 0X08, 0X0A, 0X0A, 0X0B, 0X0F, 0X04, 0X03, 0X05,
  0X0E, 0X08, 0X0A, 0X01, 0X0D, 0X06, 0X08, 0X03, 0X06, 0X0B, 0X0C, 0X08, 0X0B, 0X04, 0X0B, 0X05,
  0X0C, 0X03, 0X0D, 0X05, 0X06, 0X0B, 0X05, 0X0C, 0X0A, 0X08, 0X02, 0X00, 0X09, 0X05, 0X0C, 0X01,
  0X04, 0X0B, 0X06, 0X02, 0X0A, 0X08, 0X01, 0X05, 0X0D, 0X05, 0X0D, 0X05, 0X05, 0X04, 0X03, 0X05,
  0X05, 0X0E, 0X09, 0X0D, 0X0C, 0X03, 0X05, 0X04, 0X01, 0X05, 0X05, 0X06, 0X02, 0X03, 0X0D, 0X05,
  0X04, 0X09, 0X06, 0X01, 0X05, 0X0D, 0X07, 0X05, 0X07, 0X05, 0X07, 0X0C, 0X0A, 0X09, 0X05, 0X05,
  0X07, 0X06, 0X0A, 0X01, 0X05, 0X06, 0X09, 0X04, 0X09, 0X04, 0X08, 0X03, 0X0C, 0X02, 0X00, 0X03,
  0X0C, 0X09, 0X0E, 0X01, 0X04, 0X0B, 0X05, 0X06, 0X03, 0X05, 0X05, 0X0D, 0X04, 0X09, 0X06, 0X09,
  0X05, 0X05, 0X0F, 0X05, 0X07, 0X0C, 0X03, 0X0D, 0X0D, 0X05, 0X07, 0X06, 0X03, 0X06, 0X09, 0X07,
  0X05, 0X06, 0X0A, 0X02, 0X08, 0X02, 0X0A, 0X01, 0X05, 0X05, 0X0D, 0X0D, 0X0C, 0X0A, 0X01, 0X0D,
  0X04, 0X0A, 0X0A, 0X0B, 0X06, 0X0A, 0X08, 0X03, 0X06, 0X03, 0X05, 0X06, 0X01, 0X0D, 0X04, 0X03,
  0X04, 0X08, 0X0A, 0X0A, 0X08, 0X0B, 0X04, 0X0B, 0X0C, 0X0B, 0X04, 0X0B, 0X04, 0X03, 0X04, 0X0B,
  0X05, 0X05, 0X0E, 0X09, 0X06, 0X0A, 0X03, 0X0D, 0X05, 0X0D, 0X05, 0X0F, 0X06, 0X09, 0X04, 0X09,
  0X05, 0X04, 0X0A, 0X02, 0X0A, 0X0A, 0X08, 0X03, 0X05, 0X07, 0X06, 0X0A, 0X0A, 0X02, 0X03, 0X05,
  0X06, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk1987f[] = {
  0X0E, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X02, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05,
  0X04, 0X0B, 0X0C, 0X03, 0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X01, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X02, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X04, 0X0A, 0X03, 0X0C, 0X03, 0X0C, 0X0A, 0X0A, 0X08, 0X02, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X08, 0X02, 0X08, 0X03, 0X0C, 0X0A, 0X02, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X0C, 0X02, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X0C, 0X08, 0X03, 0X05, 0X05, 0X05, 0X05, 0X04, 0X03,
  0X0C, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X04, 0X09,
  0X05, 0X05, 0X05, 0X05, 0X04, 0X01, 0X06, 0X0A, 0X08, 0X02, 0X08, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X01, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X04, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X07, 0X04, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X01, 0X0C, 0X03, 0X05, 0X05,
  0X05, 0X0C, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X04, 0X03, 0X0C, 0X02, 0X01,
  0X04, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X09, 0X05, 0X0C, 0X03, 0X0C, 0X01,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X01, 0X04, 0X03, 0X0C, 0X03, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X02, 0X02, 0X0A, 0X03, 0X0E, 0X03
};

const uint8_t uk1988f[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X02, 0X02, 0X09, 0X0C, 0X0A, 0X09, 0X05, 0X0C, 0X08, 0X0B, 0X0C, 0X0A, 0X09, 0X05,
  0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X0C, 0X03, 0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X0C, 0X03, 0X05, 0X0C, 0X03, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X03, 0X0C, 0X01, 0X05, 0X0C, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X07, 0X06, 0X03, 0X06, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X01, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X01, 0X04, 0X09, 0X06, 0X03, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X03, 0X05, 0X06, 0X0A, 0X0A, 0X08, 0X02, 0X03, 0X06, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X03, 0X0C, 0X08, 0X0B, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk1989[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X09, 0X05, 0X06, 0X08, 0X02, 0X09, 0X04, 0X08, 0X03,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X0C, 0X02, 0X08, 0X02, 0X01, 0X06, 0X09,
  0X05, 0X06, 0X08, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X07, 0X0C, 0X02, 0X08, 0X02, 0X08, 0X03,
  0X06, 0X09, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X01, 0X0C, 0X02, 0X09, 0X04, 0X09,
  0X0C, 0X01, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X06, 0X01, 0X05, 0X07, 0X0C, 0X02, 0X01, 0X07,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X09, 0X0E, 0X0A, 0X03, 0X06, 0X08, 0X01, 0X0C, 0X02, 0X09,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X08, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X0E, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X0D, 0X05, 0X05, 0X05, 0X06, 0X08, 0X01,
  0X05, 0X06, 0X03, 0X05, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X04, 0X09, 0X05, 0X05,
  0X04, 0X0A, 0X0A, 0X03, 0X04, 0X03, 0X05, 0X0C, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X09, 0X0C, 0X09, 0X05, 0X0C, 0X01, 0X05, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X03, 0X04, 0X03, 0X06, 0X0A, 0X0A, 0X02, 0X09, 0X05, 0X06, 0X03, 0X06, 0X03, 0X05,
  0X07, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk1990f[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0E, 0X08, 0X0A, 0X08, 0X09,
  0X0C, 0X0A, 0X02, 0X09, 0X06, 0X03, 0X0C, 0X0A, 0X09, 0X0E, 0X02, 0X08, 0X02, 0X09, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X0A, 0X03, 0X0C, 0X02, 0X09, 0X0E, 0X02, 0X09, 0X06, 0X03, 0X05,
  0X0D, 0X0C, 0X0A, 0X0A, 0X03, 0X0C, 0X0A, 0X02, 0X09, 0X06, 0X09, 0X0E, 0X02, 0X08, 0X0B, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X0C, 0X08, 0X02, 0X0B, 0X04, 0X09, 0X0E, 0X02, 0X08, 0X01,
  0X04, 0X01, 0X05, 0X0E, 0X0A, 0X0A, 0X01, 0X06, 0X0A, 0X0A, 0X03, 0X06, 0X09, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X09, 0X07, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X03, 0X06, 0X0B, 0X05,
  0X05, 0X06, 0X0A, 0X08, 0X09, 0X06, 0X09, 0X04, 0X09, 0X0C, 0X09, 0X05, 0X0C, 0X0A, 0X0A, 0X01,
  0X05, 0X0C, 0X09, 0X05, 0X06, 0X0A, 0X03, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X01, 0X04, 0X03, 0X06, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X07, 0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X05,
  0X04, 0X02, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X03, 0X05, 0X0C, 0X0A, 0X08, 0X01,
  0X05, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X0C, 0X03, 0X0C, 0X08, 0X09, 0X05, 0X05, 0X0C, 0X03, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X05, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X07,
  0X05, 0X05, 0X05, 0X07, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X06, 0X09, 0X06, 0X09,
  0X06, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t uk1991f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X09,
  0X0D, 0X0C, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X0B, 0X0E, 0X01, 0X06, 0X09, 0X07,
  0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X02, 0X08, 0X02, 0X0A, 0X02, 0X01,
  0X05, 0X05, 0X05, 0X04, 0X01, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X0D, 0X06, 0X09, 0X0C, 0X08, 0X01,
  0X05, 0X05, 0X05, 0X05, 0X04, 0X01, 0X0C, 0X09, 0X06, 0X03, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05,
  0X06, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X09, 0X0C, 0X09, 0X05, 0X0D, 0X05, 0X04, 0X03,
  0X0C, 0X01, 0X05, 0X05, 0X05, 0X07, 0X05, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X09,
  0X05, 0X05, 0X04, 0X01, 0X06, 0X09, 0X06, 0X08, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X09, 0X04, 0X09, 0X06, 0X0A, 0X08, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X09, 0X06, 0X03, 0X06, 0X0A, 0X0B, 0X06, 0X08, 0X03, 0X05, 0X06, 0X03, 0X05,
  0X05, 0X06, 0X09, 0X06, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X08, 0X03, 0X0C, 0X09, 0X05,
  0X06, 0X09, 0X06, 0X09, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X08, 0X03, 0X05, 0X05,
  0X0C, 0X01, 0X0D, 0X06, 0X02, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X0B, 0X06, 0X08, 0X03, 0X05,
  0X07, 0X06, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X03
};

const uint8_t uk1992f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X09,
  0X0D, 0X0C, 0X08, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X0B, 0X06, 0X03, 0X0E, 0X0A, 0X01,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X05, 0X0E, 0X08, 0X08, 0X0A, 0X09, 0X05,
  0X06, 0X01, 0X05, 0X05, 0X0C, 0X03, 0X0C, 0X09, 0X06, 0X02, 0X08, 0X03, 0X05, 0X0D, 0X05, 0X05,
  0X0C, 0X01, 0X05, 0X04, 0X03, 0X0D, 0X05, 0X07, 0X0E, 0X09, 0X04, 0X0A, 0X01, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X0A, 0X00, 0X03, 0X0C, 0X09, 0X06, 0X01, 0X0D, 0X05, 0X05, 0X07, 0X05,
  0X05, 0X04, 0X03, 0X07, 0X0D, 0X05, 0X0C, 0X03, 0X06, 0X09, 0X05, 0X06, 0X00, 0X02, 0X0A, 0X01,
  0X05, 0X06, 0X0A, 0X09, 0X05, 0X06, 0X01, 0X0C, 0X08, 0X03, 0X05, 0X0C, 0X01, 0X0C, 0X0A, 0X01,
  0X04, 0X0A, 0X09, 0X05, 0X06, 0X09, 0X05, 0X06, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X0D, 0X05,
  0X05, 0X0D, 0X05, 0X06, 0X09, 0X05, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05, 0X04, 0X01, 0X05,
  0X04, 0X03, 0X04, 0X0A, 0X03, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X01, 0X05, 0X04, 0X01,
  0X05, 0X0C, 0X00, 0X08, 0X09, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X08, 0X0B, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X07, 0X06, 0X08, 0X02, 0X08, 0X00, 0X0B, 0X05, 0X04, 0X03, 0X05,
  0X06, 0X01, 0X07, 0X06, 0X00, 0X0A, 0X0A, 0X00, 0X09, 0X05, 0X05, 0X0E, 0X00, 0X00, 0X0A, 0X03,
  0X0E, 0X02, 0X0A, 0X08, 0X00, 0X0A, 0X0A, 0X03, 0X04, 0X01, 0X06, 0X0A, 0X03, 0X06, 0X0A, 0X09,
  0X0E, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2000f[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X03, 0X0E, 0X00, 0X0A, 0X0A, 0X0A, 0X01, 0X05, 0X05, 0X04, 0X00, 0X0A, 0X09, 0X05,
  0X06, 0X0B, 0X0C, 0X0A, 0X00, 0X0A, 0X08, 0X0A, 0X00, 0X03, 0X06, 0X01, 0X04, 0X0A, 0X01, 0X05,
  0X0C, 0X09, 0X04, 0X08, 0X02, 0X08, 0X02, 0X09, 0X04, 0X08, 0X0B, 0X04, 0X02, 0X0A, 0X03, 0X05,
  0X05, 0X04, 0X01, 0X04, 0X0A, 0X00, 0X0A, 0X01, 0X07, 0X06, 0X0B, 0X06, 0X0A, 0X0A, 0X09, 0X05,
  0X06, 0X01, 0X04, 0X00, 0X0A, 0X00, 0X0B, 0X07, 0X0C, 0X0A, 0X08, 0X09, 0X0D, 0X0D, 0X05, 0X05,
  0X0C, 0X02, 0X01, 0X04, 0X0A, 0X00, 0X09, 0X0E, 0X02, 0X09, 0X05, 0X04, 0X00, 0X00, 0X01, 0X05,
  0X06, 0X08, 0X02, 0X00, 0X0A, 0X01, 0X05, 0X0C, 0X08, 0X03, 0X06, 0X03, 0X07, 0X07, 0X07, 0X05,
  0X0C, 0X02, 0X09, 0X06, 0X08, 0X03, 0X05, 0X06, 0X03, 0X0C, 0X0A, 0X0A, 0X08, 0X0B, 0X0D, 0X05,
  0X06, 0X09, 0X06, 0X09, 0X06, 0X08, 0X02, 0X08, 0X09, 0X05, 0X0C, 0X09, 0X04, 0X0B, 0X05, 0X05,
  0X0D, 0X06, 0X09, 0X06, 0X08, 0X02, 0X0A, 0X03, 0X04, 0X03, 0X05, 0X05, 0X06, 0X0A, 0X01, 0X05,
  0X04, 0X09, 0X06, 0X09, 0X06, 0X08, 0X0A, 0X09, 0X05, 0X0D, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X05,
  0X05, 0X06, 0X09, 0X06, 0X08, 0X02, 0X08, 0X03, 0X05, 0X05, 0X06, 0X02, 0X02, 0X08, 0X0A, 0X01,
  0X06, 0X09, 0X04, 0X08, 0X02, 0X0B, 0X06, 0X09, 0X05, 0X06, 0X08, 0X09, 0X0D, 0X06, 0X09, 0X05,
  0X0E, 0X00, 0X00, 0X00, 0X0A, 0X08, 0X0A, 0X01, 0X06, 0X0B, 0X05, 0X06, 0X00, 0X09, 0X07, 0X05,
  0X0E, 0X03, 0X07, 0X07, 0X0E, 0X03, 0X0E, 0X03, 0X0E, 0X0A, 0X02, 0X0B, 0X07, 0X06, 0X0A, 0X03
};

const uint8_t uk2001f[] = {
  0X0E, 0X09, 0X0E, 0X08, 0X0A, 0X08, 0X08, 0X08, 0X08, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X09,
  0X0D, 0X06, 0X09, 0X04, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X05, 0X04, 0X0A, 0X09, 0X0E, 0X01,
  0X04, 0X08, 0X02, 0X03, 0X07, 0X04, 0X03, 0X07, 0X05, 0X04, 0X01, 0X05, 0X0D, 0X07, 0X0C, 0X01,
  0X05, 0X05, 0X0D, 0X0C, 0X09, 0X06, 0X08, 0X09, 0X06, 0X01, 0X06, 0X02, 0X00, 0X0A, 0X01, 0X05,
  0X05, 0X04, 0X03, 0X07, 0X06, 0X09, 0X07, 0X04, 0X0B, 0X05, 0X0D, 0X0C, 0X02, 0X09, 0X06, 0X01,
  0X05, 0X06, 0X0A, 0X0A, 0X0B, 0X06, 0X0B, 0X05, 0X0C, 0X02, 0X01, 0X05, 0X0E, 0X02, 0X09, 0X05,
  0X05, 0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X09, 0X07, 0X07, 0X0D, 0X07, 0X07, 0X0D, 0X0C, 0X02, 0X03,
  0X05, 0X0D, 0X0D, 0X0E, 0X08, 0X03, 0X06, 0X08, 0X09, 0X05, 0X0D, 0X0E, 0X01, 0X04, 0X0A, 0X09,
  0X05, 0X06, 0X02, 0X08, 0X02, 0X0A, 0X09, 0X06, 0X03, 0X04, 0X02, 0X0A, 0X03, 0X06, 0X09, 0X07,
  0X05, 0X0E, 0X08, 0X02, 0X0A, 0X0A, 0X02, 0X08, 0X09, 0X04, 0X0A, 0X0A, 0X0A, 0X0B, 0X04, 0X0B,
  0X05, 0X0E, 0X01, 0X0C, 0X0A, 0X0A, 0X08, 0X01, 0X07, 0X04, 0X08, 0X08, 0X0A, 0X0A, 0X03, 0X0D,
  0X04, 0X0B, 0X05, 0X04, 0X08, 0X08, 0X01, 0X04, 0X09, 0X05, 0X05, 0X04, 0X0A, 0X0A, 0X0B, 0X05,
  0X05, 0X0C, 0X01, 0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X03, 0X05, 0X07, 0X0C, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X04, 0X09, 0X0D, 0X05, 0X0D, 0X05, 0X0E, 0X03, 0X05,
  0X06, 0X02, 0X01, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05, 0X05, 0X07, 0X05, 0X06, 0X0A, 0X0A, 0X01,
  0X0E, 0X0A, 0X02, 0X02, 0X03, 0X06, 0X02, 0X02, 0X03, 0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2002f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0B, 0X0C, 0X0A, 0X0B, 0X0C, 0X09, 0X0C, 0X08, 0X0B,
  0X0C, 0X0B, 0X0C, 0X08, 0X0B, 0X04, 0X08, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X07, 0X0D,
  0X04, 0X0A, 0X01, 0X06, 0X09, 0X05, 0X04, 0X0A, 0X08, 0X0B, 0X0C, 0X0B, 0X05, 0X04, 0X0A, 0X01,
  0X04, 0X0B, 0X07, 0X0E, 0X02, 0X03, 0X06, 0X0A, 0X02, 0X08, 0X02, 0X0A, 0X02, 0X01, 0X0C, 0X03,
  0X04, 0X08, 0X0B, 0X0D, 0X0C, 0X0B, 0X0C, 0X08, 0X09, 0X07, 0X0C, 0X0A, 0X0B, 0X07, 0X04, 0X0B,
  0X05, 0X04, 0X0A, 0X02, 0X03, 0X0E, 0X03, 0X05, 0X06, 0X0A, 0X01, 0X0D, 0X0E, 0X09, 0X04, 0X09,
  0X04, 0X03, 0X0C, 0X08, 0X0A, 0X09, 0X0C, 0X02, 0X0A, 0X09, 0X04, 0X02, 0X0A, 0X02, 0X03, 0X05,
  0X04, 0X0A, 0X03, 0X04, 0X0A, 0X03, 0X05, 0X0C, 0X09, 0X07, 0X05, 0X0D, 0X0C, 0X0A, 0X08, 0X03,
  0X05, 0X0C, 0X09, 0X07, 0X0C, 0X0A, 0X00, 0X02, 0X01, 0X0D, 0X06, 0X01, 0X06, 0X0B, 0X05, 0X0D,
  0X04, 0X01, 0X05, 0X0C, 0X03, 0X0E, 0X02, 0X08, 0X01, 0X06, 0X09, 0X06, 0X08, 0X09, 0X04, 0X01,
  0X05, 0X04, 0X03, 0X04, 0X0A, 0X08, 0X0A, 0X01, 0X06, 0X09, 0X04, 0X0B, 0X05, 0X06, 0X03, 0X05,
  0X04, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X02, 0X08, 0X01, 0X06, 0X09, 0X06, 0X0A, 0X09, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X01, 0X0E, 0X01, 0X0E, 0X01, 0X04, 0X08, 0X02, 0X09, 0X0C, 0X03, 0X05,
  0X07, 0X05, 0X0C, 0X01, 0X04, 0X0A, 0X01, 0X0D, 0X06, 0X01, 0X05, 0X0C, 0X01, 0X06, 0X0A, 0X01,
  0X0C, 0X02, 0X01, 0X04, 0X02, 0X08, 0X02, 0X02, 0X09, 0X06, 0X01, 0X05, 0X07, 0X0C, 0X09, 0X05,
  0X06, 0X0A, 0X02, 0X02, 0X0A, 0X02, 0X0B, 0X0E, 0X02, 0X0B, 0X06, 0X03, 0X0E, 0X02, 0X03, 0X07
};

const uint8_t uk2003f[] = {
  0X0E, 0X0A, 0X08, 0X09, 0X0D, 0X0E, 0X0B, 0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X0C, 0X0A, 0X01, 0X04, 0X02, 0X08, 0X0A, 0X0A, 0X0A, 0X00, 0X08, 0X0A, 0X0A, 0X03, 0X0C, 0X01,
  0X04, 0X09, 0X04, 0X03, 0X0E, 0X02, 0X08, 0X0A, 0X08, 0X03, 0X05, 0X0D, 0X0C, 0X0B, 0X05, 0X05,
  0X05, 0X04, 0X02, 0X09, 0X0D, 0X0C, 0X01, 0X0D, 0X05, 0X0E, 0X02, 0X02, 0X02, 0X08, 0X02, 0X03,
  0X05, 0X04, 0X09, 0X06, 0X02, 0X03, 0X06, 0X01, 0X05, 0X0E, 0X0A, 0X08, 0X09, 0X05, 0X0C, 0X09,
  0X05, 0X05, 0X06, 0X09, 0X0C, 0X08, 0X09, 0X07, 0X05, 0X0E, 0X0A, 0X03, 0X05, 0X04, 0X03, 0X05,
  0X04, 0X02, 0X09, 0X05, 0X05, 0X05, 0X05, 0X0D, 0X06, 0X0A, 0X0A, 0X0A, 0X02, 0X03, 0X0C, 0X01,
  0X05, 0X0F, 0X07, 0X05, 0X05, 0X05, 0X07, 0X04, 0X08, 0X0A, 0X0A, 0X09, 0X0E, 0X0A, 0X03, 0X05,
  0X04, 0X09, 0X0C, 0X02, 0X01, 0X04, 0X08, 0X02, 0X01, 0X0D, 0X0D, 0X06, 0X08, 0X0A, 0X09, 0X05,
  0X05, 0X04, 0X03, 0X0D, 0X05, 0X05, 0X04, 0X09, 0X05, 0X05, 0X04, 0X09, 0X06, 0X0B, 0X04, 0X03,
  0X05, 0X05, 0X0C, 0X01, 0X05, 0X04, 0X01, 0X05, 0X05, 0X07, 0X07, 0X05, 0X0C, 0X0A, 0X02, 0X0B,
  0X05, 0X04, 0X03, 0X04, 0X02, 0X01, 0X06, 0X01, 0X04, 0X0A, 0X08, 0X03, 0X06, 0X0A, 0X09, 0X0D,
  0X04, 0X02, 0X09, 0X05, 0X0D, 0X04, 0X09, 0X05, 0X07, 0X0D, 0X06, 0X0A, 0X09, 0X0D, 0X06, 0X03,
  0X05, 0X0D, 0X06, 0X01, 0X04, 0X01, 0X05, 0X04, 0X08, 0X03, 0X0C, 0X09, 0X06, 0X01, 0X0C, 0X09,
  0X04, 0X02, 0X09, 0X05, 0X05, 0X07, 0X04, 0X03, 0X06, 0X09, 0X07, 0X06, 0X09, 0X06, 0X01, 0X05,
  0X06, 0X0B, 0X07, 0X06, 0X03, 0X0E, 0X03, 0X0E, 0X0A, 0X02, 0X0A, 0X0A, 0X02, 0X0B, 0X06, 0X03
};

const uint8_t uk2004f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0B, 0X05, 0X0D, 0X05,
  0X05, 0X0C, 0X09, 0X0E, 0X00, 0X08, 0X09, 0X05, 0X05, 0X0C, 0X0B, 0X0C, 0X0A, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X04, 0X09, 0X05, 0X05, 0X05, 0X05, 0X04, 0X03, 0X0C, 0X03, 0X0D, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X07, 0X05, 0X07, 0X05, 0X07, 0X05, 0X05, 0X0E, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X04, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X01, 0X0E, 0X01, 0X05, 0X05,
  0X05, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X01, 0X0D, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X03, 0X04, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05,
  0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X06, 0X09, 0X06, 0X09, 0X07, 0X05,
  0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X03, 0X04, 0X09, 0X06, 0X09, 0X04, 0X09, 0X05,
  0X04, 0X03, 0X0D, 0X07, 0X0D, 0X07, 0X0D, 0X07, 0X0C, 0X03, 0X04, 0X0B, 0X06, 0X01, 0X05, 0X05,
  0X04, 0X08, 0X02, 0X08, 0X02, 0X08, 0X02, 0X08, 0X02, 0X09, 0X06, 0X08, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X0D, 0X07, 0X0D, 0X07, 0X0D, 0X07, 0X0D, 0X06, 0X09, 0X07, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X0A, 0X02, 0X02, 0X03, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2005f[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X08, 0X08, 0X09,
  0X0C, 0X0A, 0X01, 0X0E, 0X0B, 0X0E, 0X0A, 0X08, 0X0A, 0X09, 0X07, 0X0E, 0X01, 0X07, 0X07, 0X05,
  0X06, 0X0B, 0X06, 0X09, 0X0C, 0X0A, 0X09, 0X05, 0X0D, 0X06, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X01,
  0X0D, 0X0E, 0X09, 0X06, 0X02, 0X0A, 0X02, 0X03, 0X04, 0X0A, 0X0B, 0X06, 0X09, 0X0E, 0X09, 0X05,
  0X04, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X08, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X0E, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X01, 0X06, 0X09, 0X05, 0X05, 0X05,
  0X04, 0X08, 0X0A, 0X09, 0X0E, 0X02, 0X09, 0X0E, 0X01, 0X0D, 0X07, 0X0C, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X06, 0X09, 0X0E, 0X03, 0X0C, 0X01, 0X04, 0X0B, 0X05, 0X0C, 0X03, 0X05, 0X05,
  0X04, 0X09, 0X06, 0X09, 0X06, 0X0A, 0X0B, 0X06, 0X02, 0X02, 0X0B, 0X07, 0X04, 0X0B, 0X05, 0X05,
  0X05, 0X07, 0X0D, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05,
  0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X08, 0X09, 0X0D, 0X0E, 0X0A, 0X0A, 0X0A, 0X00, 0X09, 0X05,
  0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X01, 0X04, 0X02, 0X0A, 0X0A, 0X08, 0X0A, 0X01, 0X05, 0X05,
  0X0D, 0X05, 0X0E, 0X0A, 0X0A, 0X0A, 0X02, 0X03, 0X0D, 0X0E, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05,
  0X06, 0X02, 0X0A, 0X0A, 0X0A, 0X09, 0X0F, 0X0C, 0X02, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05, 0X05,
  0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0E, 0X03, 0X0D, 0X06, 0X0A, 0X02, 0X09, 0X05, 0X07, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X02, 0X0A, 0X03
};

const uint8_t uk2006f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X08, 0X00, 0X08, 0X08, 0X0B, 0X0C, 0X0A, 0X09, 0X05,
  0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X01, 0X0C, 0X03, 0X05, 0X05, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X08, 0X03, 0X06, 0X09, 0X05, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0E, 0X03, 0X0C, 0X09, 0X05, 0X04, 0X09, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X03, 0X06, 0X03, 0X07, 0X06, 0X0A, 0X03, 0X04, 0X01, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X03, 0X0C, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X01, 0X06, 0X09, 0X06, 0X01, 0X07, 0X05, 0X05, 0X07, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X02, 0X09, 0X06, 0X09, 0X05, 0X0E, 0X02, 0X02, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0B, 0X06, 0X0A, 0X02, 0X02, 0X08, 0X0A, 0X0A, 0X0A, 0X0B, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X0C, 0X09, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X01,
  0X05, 0X04, 0X01, 0X06, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X01,
  0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2007f[] = {
  0X0E, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X03, 0X0E, 0X0A, 0X0A, 0X0A, 0X09, 0X0E, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X05,
  0X05, 0X0C, 0X0A, 0X08, 0X08, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X01, 0X0C, 0X02, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X0E, 0X01, 0X06, 0X0A, 0X0A, 0X0A, 0X0B, 0X0C, 0X03, 0X06, 0X08, 0X0A, 0X03, 0X05,
  0X05, 0X06, 0X09, 0X06, 0X09, 0X0C, 0X0A, 0X08, 0X08, 0X03, 0X0E, 0X08, 0X02, 0X0A, 0X09, 0X05,
  0X06, 0X09, 0X04, 0X09, 0X06, 0X00, 0X0B, 0X05, 0X07, 0X0C, 0X09, 0X06, 0X09, 0X0E, 0X01, 0X05,
  0X0E, 0X01, 0X05, 0X05, 0X0C, 0X01, 0X0C, 0X03, 0X0E, 0X01, 0X06, 0X09, 0X05, 0X0C, 0X03, 0X05,
  0X0D, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X04, 0X09, 0X05, 0X05, 0X05, 0X0C, 0X03,
  0X04, 0X03, 0X05, 0X07, 0X04, 0X03, 0X05, 0X04, 0X03, 0X05, 0X05, 0X04, 0X03, 0X05, 0X06, 0X09,
  0X06, 0X09, 0X05, 0X0C, 0X03, 0X0C, 0X03, 0X04, 0X0A, 0X03, 0X05, 0X05, 0X0D, 0X06, 0X09, 0X05,
  0X0D, 0X05, 0X05, 0X07, 0X0C, 0X03, 0X0C, 0X02, 0X0A, 0X08, 0X03, 0X05, 0X05, 0X0C, 0X03, 0X05,
  0X04, 0X01, 0X05, 0X0E, 0X02, 0X08, 0X02, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05, 0X04, 0X09, 0X05,
  0X05, 0X07, 0X04, 0X0A, 0X09, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0D, 0X04, 0X0A, 0X0A, 0X0B, 0X0C, 0X08, 0X0A, 0X02, 0X09, 0X07, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X04, 0X02, 0X0A, 0X0A, 0X0A, 0X03, 0X07, 0X0C, 0X09, 0X06, 0X0A, 0X03, 0X05,
  0X06, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2008f[] = {
  0X0E, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X08, 0X00, 0X02, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X01, 0X0C, 0X0A, 0X09, 0X0C, 0X0A, 0X03,
  0X05, 0X05, 0X05, 0X0C, 0X08, 0X0A, 0X0A, 0X02, 0X03, 0X06, 0X03, 0X0C, 0X02, 0X01, 0X0C, 0X09,
  0X05, 0X05, 0X05, 0X07, 0X05, 0X0D, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X00, 0X09, 0X06, 0X03, 0X05,
  0X05, 0X06, 0X02, 0X0A, 0X03, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05, 0X0C, 0X09, 0X05,
  0X04, 0X0B, 0X0C, 0X0A, 0X09, 0X04, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X0C, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X0C, 0X09, 0X06, 0X01, 0X05, 0X05, 0X05, 0X07, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X03, 0X0C, 0X03, 0X06, 0X02, 0X09, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X01,
  0X05, 0X05, 0X0C, 0X01, 0X0C, 0X03, 0X0C, 0X09, 0X0C, 0X03, 0X05, 0X05, 0X04, 0X0A, 0X08, 0X01,
  0X05, 0X05, 0X05, 0X04, 0X02, 0X08, 0X03, 0X06, 0X03, 0X0C, 0X03, 0X05, 0X05, 0X0D, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X04, 0X09, 0X06, 0X09, 0X0C, 0X0A, 0X02, 0X0A, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X09, 0X06, 0X03, 0X0C, 0X08, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X05, 0X0C, 0X09, 0X06, 0X02, 0X03, 0X05,
  0X05, 0X06, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X01,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2009f[] = {
  0X0E, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X08, 0X0A, 0X08, 0X0A, 0X08, 0X0A, 0X0A, 0X08, 0X0A, 0X09,
  0X0C, 0X0A, 0X01, 0X0C, 0X0A, 0X01, 0X06, 0X09, 0X06, 0X09, 0X05, 0X0E, 0X0B, 0X04, 0X0A, 0X01,
  0X04, 0X09, 0X05, 0X04, 0X09, 0X04, 0X09, 0X04, 0X09, 0X05, 0X04, 0X08, 0X0B, 0X05, 0X0D, 0X05,
  0X05, 0X04, 0X02, 0X01, 0X05, 0X05, 0X04, 0X01, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X02, 0X01, 0X05,
  0X05, 0X07, 0X0E, 0X02, 0X01, 0X05, 0X05, 0X07, 0X06, 0X01, 0X05, 0X0D, 0X0D, 0X0D, 0X05, 0X05,
  0X05, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X06, 0X08, 0X0A, 0X03, 0X05, 0X05, 0X05, 0X06, 0X01, 0X05,
  0X05, 0X05, 0X0E, 0X0A, 0X0A, 0X01, 0X0C, 0X02, 0X0A, 0X08, 0X03, 0X04, 0X01, 0X0E, 0X01, 0X05,
  0X05, 0X05, 0X0C, 0X08, 0X08, 0X01, 0X05, 0X0C, 0X09, 0X07, 0X0C, 0X01, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X05, 0X06, 0X01, 0X06, 0X02, 0X0A, 0X03, 0X05, 0X0E, 0X01, 0X05, 0X05,
  0X05, 0X06, 0X02, 0X01, 0X04, 0X08, 0X02, 0X0A, 0X0B, 0X0C, 0X0B, 0X05, 0X0E, 0X02, 0X03, 0X05,
  0X05, 0X0C, 0X08, 0X01, 0X05, 0X07, 0X0C, 0X08, 0X0A, 0X01, 0X0C, 0X02, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X05, 0X07, 0X04, 0X0B, 0X05, 0X06, 0X09, 0X06, 0X01, 0X0C, 0X0A, 0X0B, 0X05, 0X05,
  0X04, 0X01, 0X06, 0X08, 0X02, 0X09, 0X05, 0X0D, 0X04, 0X09, 0X05, 0X04, 0X08, 0X0B, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X02, 0X09, 0X07, 0X05, 0X04, 0X03, 0X05, 0X06, 0X03, 0X06, 0X0B, 0X05, 0X05,
  0X05, 0X0E, 0X0A, 0X0A, 0X02, 0X0B, 0X06, 0X00, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X05,
  0X07, 0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};


const uint8_t uk2010f[] = {
  0X0E, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X0E, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X0A, 0X0A, 0X0A, 0X09, 0X04, 0X0A, 0X0A, 0X01, 0X04, 0X0A, 0X0A, 0X0A, 0X08, 0X09, 0X05,
  0X04, 0X0A, 0X0B, 0X0C, 0X02, 0X00, 0X0A, 0X09, 0X05, 0X04, 0X0A, 0X09, 0X0D, 0X05, 0X05, 0X05,
  0X04, 0X0B, 0X0C, 0X00, 0X0B, 0X04, 0X0B, 0X05, 0X06, 0X01, 0X0F, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X08, 0X03, 0X04, 0X09, 0X05, 0X0C, 0X02, 0X08, 0X01, 0X0C, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X03, 0X0D, 0X07, 0X07, 0X06, 0X02, 0X08, 0X03, 0X04, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X08, 0X02, 0X08, 0X08, 0X08, 0X09, 0X06, 0X0A, 0X01, 0X0D, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X06, 0X09, 0X07, 0X07, 0X07, 0X05, 0X0C, 0X09, 0X07, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X06, 0X0B, 0X04, 0X09, 0X0E, 0X08, 0X03, 0X06, 0X02, 0X0A, 0X01, 0X07, 0X05, 0X05, 0X05, 0X05,
  0X0C, 0X0A, 0X03, 0X06, 0X0A, 0X01, 0X0C, 0X0A, 0X0A, 0X0B, 0X06, 0X09, 0X05, 0X05, 0X05, 0X05,
  0X04, 0X08, 0X0A, 0X08, 0X09, 0X06, 0X00, 0X0B, 0X0C, 0X0A, 0X08, 0X01, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X07, 0X0D, 0X07, 0X06, 0X09, 0X04, 0X0B, 0X07, 0X0C, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X07, 0X0E, 0X02, 0X08, 0X0A, 0X01, 0X04, 0X0B, 0X0C, 0X03, 0X0F, 0X05, 0X05, 0X04, 0X01, 0X05,
  0X0C, 0X09, 0X0F, 0X04, 0X08, 0X01, 0X05, 0X0C, 0X03, 0X0E, 0X0B, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X07, 0X07, 0X0C, 0X03, 0X05, 0X06, 0X02, 0X02, 0X0A, 0X0A, 0X0A, 0X02, 0X03, 0X07, 0X07, 0X05,
  0X0E, 0X0A, 0X02, 0X0B, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03
};

const uint8_t uk2011f[] = {
  0X0E, 0X08, 0X0A, 0X09, 0X0C, 0X09, 0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X09, 0X0D, 0X0C, 0X0A, 0X09,
  0X0C, 0X02, 0X09, 0X06, 0X03, 0X06, 0X03, 0X06, 0X01, 0X0C, 0X0A, 0X03, 0X04, 0X02, 0X09, 0X05,
  0X06, 0X08, 0X02, 0X08, 0X0B, 0X0C, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X03, 0X0C, 0X03, 0X05,
  0X0C, 0X02, 0X09, 0X06, 0X0A, 0X03, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X08, 0X0B, 0X06, 0X09, 0X05,
  0X04, 0X0A, 0X00, 0X0B, 0X0E, 0X08, 0X03, 0X0C, 0X0A, 0X09, 0X0E, 0X00, 0X0B, 0X0C, 0X03, 0X05,
  0X04, 0X0A, 0X00, 0X0B, 0X0C, 0X01, 0X0E, 0X02, 0X09, 0X05, 0X0E, 0X00, 0X0B, 0X06, 0X09, 0X05,
  0X04, 0X0A, 0X00, 0X0B, 0X05, 0X04, 0X08, 0X0A, 0X03, 0X05, 0X0C, 0X03, 0X0C, 0X09, 0X05, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X03, 0X05, 0X07, 0X0C, 0X09, 0X05, 0X06, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X04, 0X02, 0X0A, 0X03, 0X0E, 0X00, 0X0B, 0X04, 0X03, 0X06, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X0C, 0X00, 0X0B, 0X0C, 0X0A, 0X0A, 0X03, 0X05, 0X05, 0X05,
  0X0C, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X03, 0X04, 0X0B, 0X06, 0X0A, 0X0A, 0X08, 0X03, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X08, 0X0A, 0X0A, 0X02, 0X0B, 0X0C, 0X0A, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X01, 0X05,
  0X05, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X06, 0X09, 0X06, 0X09, 0X06, 0X09, 0X05, 0X05,
  0X05, 0X06, 0X03, 0X06, 0X03, 0X06, 0X03, 0X06, 0X09, 0X06, 0X0A, 0X02, 0X0B, 0X06, 0X01, 0X05,
  0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X02, 0X03
};

const uint8_t uk2012f[] = {
  0X0E, 0X0A, 0X09, 0X0E, 0X08, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X09,
  0X0C, 0X08, 0X02, 0X0A, 0X02, 0X08, 0X0A, 0X0A, 0X09, 0X05, 0X05, 0X0C, 0X09, 0X0C, 0X09, 0X05,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X02, 0X0A, 0X0A, 0X03, 0X07, 0X05, 0X05, 0X06, 0X03, 0X06, 0X03,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X0A, 0X03, 0X06, 0X0A, 0X0A, 0X0A, 0X09,
  0X05, 0X05, 0X0C, 0X0A, 0X0A, 0X0A, 0X0A, 0X09, 0X0C, 0X09, 0X0E, 0X0A, 0X0A, 0X08, 0X09, 0X05,
  0X05, 0X05, 0X06, 0X0A, 0X0A, 0X0A, 0X09, 0X04, 0X01, 0X06, 0X0A, 0X0A, 0X09, 0X05, 0X06, 0X03,
  0X05, 0X05, 0X0E, 0X0A, 0X0A, 0X09, 0X07, 0X05, 0X07, 0X0E, 0X0A, 0X09, 0X05, 0X04, 0X08, 0X09,
  0X04, 0X02, 0X0A, 0X08, 0X09, 0X06, 0X09, 0X04, 0X09, 0X0C, 0X09, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X0C, 0X09, 0X05, 0X06, 0X0A, 0X03, 0X06, 0X03, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05, 0X05,
  0X05, 0X05, 0X05, 0X06, 0X0A, 0X0B, 0X0C, 0X09, 0X0D, 0X05, 0X04, 0X02, 0X03, 0X06, 0X03, 0X05,
  0X05, 0X05, 0X05, 0X0C, 0X0A, 0X09, 0X05, 0X05, 0X04, 0X03, 0X05, 0X0C, 0X0A, 0X0A, 0X09, 0X05,
  0X05, 0X05, 0X06, 0X03, 0X0C, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X02, 0X03, 0X0C, 0X0B, 0X05, 0X05,
  0X05, 0X06, 0X0A, 0X08, 0X03, 0X04, 0X01, 0X05, 0X05, 0X05, 0X0C, 0X09, 0X04, 0X08, 0X03, 0X05,
  0X05, 0X0E, 0X08, 0X02, 0X0B, 0X07, 0X04, 0X01, 0X06, 0X03, 0X05, 0X05, 0X05, 0X06, 0X09, 0X05,
  0X05, 0X0C, 0X03, 0X0C, 0X09, 0X0C, 0X01, 0X06, 0X09, 0X0C, 0X01, 0X05, 0X06, 0X09, 0X06, 0X01,
  0X06, 0X02, 0X0A, 0X03, 0X06, 0X03, 0X06, 0X0A, 0X02, 0X03, 0X06, 0X02, 0X0A, 0X02, 0X0A, 0X03
};
