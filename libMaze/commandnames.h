#ifndef _commandnames_h
#define _commandnames_h

/*
 * See docs/command-names.md for a description of these values
 */

#define CMD_END        (0x00)
#define CMD_STOP       (0xC0)
#define CMD_BEGIN      (0xC1)
#define CMD_EXPLORE    (0xC2)

// error codes  0xf0-0xff
#define CMD_ERROR_NOF   (0xF0)
#define CMD_ERROR_RRR   (0xF1)
#define CMD_ERROR_LLL   (0xF2)
#define CMD_ERR_BEGIN   (0xF3)
#define CMD_ERROR_END   (0xF4)
#define CMD_ERROR       (0xFF)

// It would be nice if there were an easier way to generate these
enum {
  FWD0 = 0,
  FWD1, FWD2, FWD3, FWD4, FWD5, FWD6, FWD7,
  FWD8, FWD9, FWD10, FWD11, FWD12, FWD13, FWD14, FWD15,
  FWD16, FWD17, FWD18, FWD19, FWD20, FWD21, FWD22, FWD23,
  FWD24, FWD25, FWD26, FWD27, FWD28, FWD29, FWD30, FWD31,

  DIA0 = 32,
  DIA1, DIA2, DIA3, DIA4, DIA5, DIA6, DIA7,
  DIA8, DIA9, DIA10, DIA11, DIA12, DIA13, DIA14, DIA15,
  DIA16, DIA17, DIA18, DIA19, DIA20, DIA21, DIA22, DIA23,
  DIA24, DIA25, DIA26, DIA27, DIA28, DIA29, DIA30, DIA31,
};

#define CMD_TURN    (0x80)
#define INPLACE     (CMD_TURN +  0)
#define IP45R       (INPLACE  +  0)
#define IP45L       (INPLACE  +  1)
#define IP90R       (INPLACE  +  2)
#define IP90L       (INPLACE  +  3)
#define IP135R      (INPLACE  +  4)
#define IP135L      (INPLACE  +  5)
#define IP180R      (INPLACE  +  6)
#define IP180L      (INPLACE  +  7)

#define SMOOTH      (CMD_TURN +  8)
#define SS90FR      (SMOOTH   +  0)
#define SS90FL      (SMOOTH   +  1)
#define SS180R      (SMOOTH   +  2)
#define SS180L      (SMOOTH   +  3)
#define SD45R       (SMOOTH   +  4)
#define SD45L       (SMOOTH   +  5)
#define SD135R      (SMOOTH   +  6)
#define SD135L      (SMOOTH   +  7)
#define DS45R       (SMOOTH   +  8)
#define DS45L       (SMOOTH   +  9)
#define DS135R      (SMOOTH   + 10)
#define DS135L      (SMOOTH   + 11)
#define DD90R       (SMOOTH   + 12)
#define DD90L       (SMOOTH   + 13)
#define SS90ER      (SMOOTH   + 14)
#define SS90EL      (SMOOTH   + 15)



#endif
