#include "util.h"
#include <stdio.h>

// wait_for_enter_key: waits reading the keyboard until we read Key_Return
void wait_for_enter_key() {
    // Is enter pressed?

   while (!cpct_isKeyPressed(Key_Return)) {
      cpct_scanKeyboard();
   }
}

// locate: moves cursor to x,y location on screen
void locate(u8 x, u8 y) {
    // we check for absurd x, y values
    if (x > 80 || y > 25) {
        return;
    }

    putchar(31); // 31 is control code for firmware locate
    putchar(x);
    putchar(y);
}

// repeat_print: prints s times times :-)
void repeat_print(char *s, u8 times) {
    for (int i=0; i<times; i++) {
        printf(s);
    }
}