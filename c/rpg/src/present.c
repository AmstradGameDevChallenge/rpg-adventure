#include "present.h"
#include "util.h"
#include "i18n_strings.h"

void show_presentation() {
   // int c;
   // FILE *file;
   // file = fopen("present.txt", "r");
   // if (file) {
   //    while ((c = getc(file)) != EOF)
   //       putchar(c);
   //    fclose(file);
   // }

    char *s = 
    "8888888b.  8888888b.   .d8888b. \r\n"
    "888   Y88b 888   Y88b d88P  Y88b\r\n"
    "888    888 888    888 888    888\r\n" 
    "888   d88P 888   d88P 888       \r\n" 
    "8888888P   8888888P   888  88888\r\n" 
    "888 T88b   888        888    888\r\n" 
    "888  T88b  888        Y88b  d88P\r\n" 
    "888   T88b 888         Y8888P88 \r\n"; 

    puts(s);
    puts("RPG GAME by dfreniche\r\n");

    repeat_print("_", 10);

    printf("\r\n");
    printf(i18n_PRESS_ENTER_START);
    
    // Is enter pressed?
    wait_for_enter_key();
}