#ifndef __UTIL_H__
#define __UTIL_H__

#include <cpctelera.h>

#define NEWLINE "\r\n"

// wait_for_enter_key: waits reading the keyboard until we read Key_Return
void wait_for_enter_key();

// locate: moves cursor to x,y location on screen
void locate(u8 x, u8 y);

// CLS: firmware clear screen
// using FIRMWARE
void cls();

// ink: set foreground and background colors for ink
// using FIRMWARE
void ink(u8 myInk, u8 color1, u8 color2);

// border: sets border color
// using FIRMWARE
void border(u8 color1, u8 color2);

// paper: sets paper color
// using FIRMWARE
void paper(u8 color1);

// pen
// using FIRMWARE
void pen (u8 myInk);

// symbol: redefines character at position `charNumber` using 8 bytes
// using FIRMWARE
void symbol(u8 charNumber, u8 b0, u8 b1, u8 b2, u8 b3, u8 b4, u8 b5, u8 b6, u8 b7);

// repeat_print: prints s times times :-)
void repeat_print(char *s, u8 times);

// repeat_print_char: prints character times times :-)
void repeat_print_char(char c, u8 times);

#endif