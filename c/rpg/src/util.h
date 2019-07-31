#ifndef __UTIL_H__
#define __UTIL_H__

#include <cpctelera.h>
#define NEWLINE "\r\n"

// CLS: firmware clear screen
#define FIRM_CLS putchar(12)

// wait_for_enter_key: waits reading the keyboard until we read Key_Return
void wait_for_enter_key();

// locate: moves cursor to x,y location on screen
void locate(u8 x, u8 y);

// repeat_print: prints s times times :-)
void repeat_print(char *s, u8 times);

#endif