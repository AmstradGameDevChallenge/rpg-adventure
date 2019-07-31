

/**
 * SUPER ULTRA RPG GAME
 * by @hec_linares
 * July 2019
 **/

#include <cpctelera.h>
#include <stdio.h>

#include "present.h"
#include "util.h"

void game_loop();

void main(void) {
   // Let's start!
   show_presentation();

   printf("\r\n");
   printf("PRESS ENTER TO START\r\n");
   
   // Is enter pressed?
   wait_for_enter_key();

   game_loop();

   // Loop forever
   while (1);
}

void game_loop() {
   // Init variables
   u8 energy    = 100;
   u8 attack    = 30;
   u8 defense   = 15;
   u8 energyen  = 90;
   u8 attacken  = 20;
   u8 defenseen = 10;

   while (1) {

      FIRM_CLS;
      
      // Print stats
      printf("PLAYER [%d] (a%d) (d%d)\r\n", energy,   attack,   defense);
      printf("ENEMY  [%d] (a%d) (d%d)\r\n", energyen, attacken, defenseen);
      
      do {
         cpct_scanKeyboard();
      } while (!cpct_isKeyPressed(Key_A) && !cpct_isKeyPressed(Key_D));
         
      // PLAYER ATTACKS!
      if (cpct_isKeyPressed(Key_A)) {
         energyen -= attack;
      } else {
         // PLAYER DEFENDS!
         if (cpct_isKeyPressed(Key_D)) {
            energy += defense;
         }
      }
      
      // ENEMY DECIDE
      if (cpct_rand() < 64) {
         energyen += defenseen;
      } else {
         energy -= attacken;
      }
   }
}