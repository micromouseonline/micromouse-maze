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


#ifndef MAZEDATA_H
#define MAZEDATA_H

#include <cstdint>

typedef struct {
  const char title[64];
  const uint8_t * data;
} MazeDataSource;

extern MazeDataSource mazeList[];


extern int mazeCount;





extern const uint8_t apec1996[] ;
extern const uint8_t apec1997[] ;
extern const uint8_t apec1998[];
extern const uint8_t apec2012[];
extern const uint8_t apec2013[];
extern const uint8_t emptyMaze[];
extern const uint8_t japan11[];
extern const uint8_t japan13[];
extern const uint8_t japan2011ef[];
extern const uint8_t japan2011ff[];
extern const uint8_t japan2011eq[];
extern const uint8_t japan2013ef[];
extern const uint8_t japan2014ef[];
extern const uint8_t japan2015ef[];
extern const uint8_t japan2016ef[];
extern const uint8_t japan4[];
extern const uint8_t japan5[];
extern const uint8_t japan95[];
extern const uint8_t japan97[];
extern const uint8_t japan98[] ;
extern const uint8_t japan99[] ;
extern const uint8_t japan1988[];
extern const uint8_t japan1990[];
extern const uint8_t japan1991[];
extern const uint8_t japan1993ef[];
extern const uint8_t japan1994ef[];
extern const uint8_t japan1996ef[];
extern const uint8_t japan1997eq[];
extern const uint8_t japan1998f[];
extern const uint8_t japan1999f[];
extern const uint8_t japan2000[];
extern const uint8_t japan2000ef[];
extern const uint8_t japan2001[];
extern const uint8_t japan2001ef[];
extern const uint8_t japan2002[];
extern const uint8_t japan2002ef[];
extern const uint8_t japan2002q[];
extern const uint8_t japan2003[];
extern const uint8_t japan2004[];
extern const uint8_t japan2005f[];
extern const uint8_t japan2007ef[];

extern const uint8_t japan2007eq[];
extern const uint8_t japan2009ef[];
extern const uint8_t japan2009eq[];
extern const uint8_t japan2012_ef[];
extern const uint8_t japan2012_eq[];
extern const uint8_t japan2014eq[];
extern const uint8_t kyot_89[];
extern const uint8_t minos01f[];
extern const uint8_t minos02f[];
extern const uint8_t minos03f[];

extern const uint8_t minos04f[];
extern const uint8_t minos04q[];
extern const uint8_t minos08f[];
extern const uint8_t minos09f[];
extern const uint8_t minos10f[];
extern const uint8_t minos12f[];
extern const uint8_t mj96bon[];
extern const uint8_t mont88[];
extern const uint8_t nagoya2002[];
extern const uint8_t niigata03[];
extern const uint8_t robotic2009[];
extern const uint8_t robotic2010[];
extern const uint8_t robotic2011[];
extern const uint8_t seoul2[];
extern const uint8_t sg87[];
extern const uint8_t sg88[];
extern const uint8_t sg89[];
extern const uint8_t taiwan2012[];
extern const uint8_t taiwan2014[];
extern const uint8_t taiwan2009[];
extern const uint8_t taiwan2015[];
extern const uint8_t testMazeClassic[];
extern const uint8_t tyubu200906[];
extern const uint8_t uk1987f[];
extern const uint8_t uk1988f[];
extern const uint8_t uk1989[];
extern const uint8_t uk1990f[];
extern const uint8_t uk1991f[];
extern const uint8_t uk1992f[];
extern const uint8_t uk2000f[];
extern const uint8_t uk2001f[];
extern const uint8_t uk2002f[];
extern const uint8_t uk2003f[];
extern const uint8_t uk2004f[];
extern const uint8_t uk2005f[];
extern const uint8_t uk2006f[];
extern const uint8_t uk2007f[];
extern const uint8_t uk2008f[];
extern const uint8_t uk2009f[];
extern const uint8_t uk2010f[];
extern const uint8_t uk2011f[];
extern const uint8_t uk2012f[];
extern const uint8_t uk2014f[];

// half size mazes
extern const uint8_t emptyHalfSize[];
extern const uint8_t japan2011ef_half[];  // goal 827
extern const uint8_t japan2014ef_half[];  // goal 837
extern const uint8_t japan2015ef_half[];
extern const uint8_t japan2016ef_half[];
extern const uint8_t japan2017ef_half[];


extern const uint8_t japan2010ef_halfx[];
extern const uint8_t japan2011ef_halfx[];
extern const uint8_t japan2012ef_halfx[];
extern const uint8_t japan2014ef_halfx[];
extern const uint8_t japan2016ef_halfx[];
extern const uint8_t japan2017ef_halfx[];

extern const uint8_t taiwan2014ef_halfx[];
extern const uint8_t taiwan2015ef_halfx[];
extern const uint8_t taiwan2017ef_halfx[];

#endif    /* MAZEDATA_H */

