#include "present.h"
#include "util.h"
#include "i18n_strings.h"

void show_presentation(char *version) {
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

    pen(2);
    puts(s);
    pen(1);
    repeat_print("_", 10);
    puts(" RPG GAME by dfreniche\r\n");

    printf("\r\n");
    printf(i18n_PRESS_ENTER_START);
    
    pen(2); locate(35,24); puts(version); pen(1);

    // Is enter pressed?
    wait_for_enter_key();
}

void show_header() {
    char line[41];

    for (int i=0; i<40; i++) {
        line[i] = 233;
    }
    line[40] = 0;

    for (int i=1; i<4; i++) {
        locate(1,i);
        puts(line);
    }

    locate(12, 2);
    pen(2);
    puts(" R P G  G A M E ");
    pen(1);
    // for (int i=1; i<4; i++) {
    //     cpct_drawStringM1("========================================", cpct_getScreenPtr(CPCT_VMEM_START, 0, i));
    // }
}