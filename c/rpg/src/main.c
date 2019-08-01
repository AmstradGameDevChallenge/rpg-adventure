

/**
 * Small Text Based Rogue like RPG text-based game for the AMSTRAD CPC
 * by @dfreniche
 * July 2019
 **/

#include <cpctelera.h>
#include <stdio.h>
#include <string.h>

#include "present.h"
#include "util.h"
#include "i18n_strings.h"

#include "character.h"
#include "room.h"
#include "weapon.h"

// Actions

typedef enum {
   MOVE_LEFT, 
   MOVE_RIGHT, 
   MOVE_UP, 
   MOVE_DOWN, 
   ATTACK, 
   DEFEND, 
   PICK_WEAPON, 
   SELECT_WEAPON, 
   DO_NOTHING
} Game_actions;

Game_actions game_actions[9] = {
   MOVE_LEFT, 
   MOVE_RIGHT, 
   MOVE_UP, 
   MOVE_DOWN, 
   ATTACK, 
   DEFEND, 
   PICK_WEAPON, 
   SELECT_WEAPON, 
   DO_NOTHING
};

// Keys for each action
// OPQA forever, don't accept anything else
u8 game_action_keys[9] = {
   Key_O, 
   Key_P, 
   Key_Q, 
   Key_A, 
   Key_A, 
   Key_D, 
   Key_I, 
   Key_W, 
   Key_Space
};


void game_loop();


void main(void) {
   redefine_character_sprites();

   cpct_setVideoMode(1);  // Set Video Mode 1 (40x25)

   // Let's start!
   // show_presentation();

   game_loop();

   // Loop forever
   while (1);
}

// Main game loop
void game_loop() {
   u8 game_ends = 0;

   // Init variables
   u8 energy    = 100;
   u8 attack    = 30;
   u8 defense   = 15;
   u8 energyen  = 90;
   u8 attacken  = 20;
   u8 defenseen = 10;

   Weapon weapons[3] = {
      {i18n_FISTS, 253, 5},
      {i18n_STICK, 254, 10},
      {i18n_SWORD, 252, 15}
   };

   Character player;
   Character monster;

   Room main_room;
   strcpy(main_room.name, "Room");
   generate_room_layout(&main_room, weapons);

   initialize_game_character(&player, 100, 10, 10, 248, "Diego");

   while (!game_ends) {

      cls();
      player.x_pos = 7;
      player.y_pos = 7;
      move_character_in_room(&player, &main_room);
      print_room(&main_room, 3, 3);

      // Print stats
      locate(1,20);
      putchar(PLAYER_SPRITE); printf("PLAYER [%d] (a%d) (d%d)\r\n", energy,   attack,   defense);
      locate(1,21);
      putchar(ENEMY_SPRITE);  printf("ENEMY  [%d] (a%d) (d%d)\r\n", energyen, attacken, defenseen);
      
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

      // check if game should end
   }
}

// void create_weapon(struct character_weapon *w, char *name, char sprite, u8 damage) {
//    strcpy(w->name, name);
//    w->sprite = sprite;
//    w->damage = damage;
// }
