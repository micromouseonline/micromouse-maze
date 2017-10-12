#ifndef _commands_h
#define _commands_h



#define CMD_STOP       (0x00)
#define CMD_STRAIGHT   (0x00)
#define CMD_DIAGONAL   (0x20)
#define CMD_SQUARES    (0x1F)
#define CMD_TURN       (0x40)

#define CMD_RIGHT      (0x00)
#define CMD_LEFT       (0x01)
#define CMD_BEGIN      (0x7D)
#define CMD_EXPLORE    (0x7E)
#define CMD_END        (0x7F)
#define CMD_ERROR_NOF   (0xF0)
#define CMD_ERROR_01   (0xF1)
#define CMD_ERROR_02   (0xF2)
#define CMD_ERROR_03   (0xF3)
#define CMD_ERROR_RRR  (0xF4)
#define CMD_ERROR_05   (0xF5)
#define CMD_ERROR_06   (0xF6)
#define CMD_ERROR_LLL   (0xF7)
#define CMD_ERROR_08   (0xF8)
#define CMD_ERROR_09   (0xF9)
#define CMD_ERR_BEGIN   (0xFA)
#define CMD_ERROR_END   (0xFB)
#define CMD_ERROR_12   (0xFC)
#define CMD_ERROR_13   (0xFD)
#define CMD_ERROR_14   (0xFE)
#define CMD_ERROR_15   (0xFF)
#define CMD_ERROR      (0xFF)

enum {
  FWD0 = 0,
  FWD1, FWD2, FWD3, FWD4, FWD5, FWD6, FWD7, FWD8, FWD9, FWD10, FWD11, FWD12, FWD13, FWD14, FWD15, FWD16, FWD17, FWD18, FWD19, FWD20, FWD21, FWD22, FWD23, FWD24, FWD25, FWD26, FWD27, FWD28, FWD29, FWD30, FWD31,
  DIA0 = 32,
  DIA1, DIA2, DIA3, DIA4, DIA5, DIA6, DIA7, DIA8, DIA9, DIA10, DIA11, DIA12, DIA13, DIA14, DIA15, DIA16, DIA17, DIA18, DIA19, DIA20, DIA21, DIA22, DIA23, DIA24, DIA25, DIA26, DIA27, DIA28, DIA29, DIA30, DIA31,

};

#define STOP     CMD_STOP

#define INPLACE (CMD_TURN +  0)
#define IP45R   (INPLACE +  0)     //64
#define IP45L   (INPLACE +  1)     //65
#define IP90R   (INPLACE +  2)     //66
#define IP90L   (INPLACE +  3)     //67
#define IP135R  (INPLACE +  4)     //68
#define IP135L  (INPLACE +  5)     //69
#define IP180R  (INPLACE +  6)     //70
#define IP180L  (INPLACE +  7)     //71

#define SMOOTH  (CMD_TURN +  8)
#define SS90SR  (SMOOTH +  0)     //72
#define SS90SL  (SMOOTH +  1)     //73
#define SS90FR  (SMOOTH +  2)     //74
#define SS90FL  (SMOOTH +  3)     //75
#define SS180R  (SMOOTH +  4)     //76
#define SS180L  (SMOOTH +  5)     //77
#define SD45R   (SMOOTH +  6)     //78
#define SD45L   (SMOOTH +  7)     //79
#define SD135R  (SMOOTH +  8)     //80
#define SD135L  (SMOOTH +  9)     //81
#define DS45R   (SMOOTH + 10)     //82
#define DS45L   (SMOOTH + 11)     //83
#define DS135R  (SMOOTH + 12)     //84
#define DS135L  (SMOOTH + 13)     //85
#define DD90R   (SMOOTH + 14)     //86
#define DD90L   (SMOOTH + 15)     //87
#define SS90ER  (SMOOTH + 16)     //88
#define SS90EL  (SMOOTH + 17)     //89



#endif
