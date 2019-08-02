//-----------------------------------------------------------------------------
// Small Text Based Rogue like RPG text-based game for the AMSTRAD CPC
// by @dfreniche
// July 2019
// v0.0.3
//-----------------------------------------------------------------------------

#include <cpctelera.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "present.h"
#include "util.h"
#include "i18n_strings.h"

#include "character.h"
#include "room.h"
#include "weapon.h"

// Actions

typedef enum {
   NONE = 0,
   MOVE_LEFT  = 1, 
   MOVE_RIGHT = 2, 
   MOVE_UP    = 3, 
   MOVE_DOWN  = 4, 
   ATTACK     = 5, 
   DEFEND     = 6, 
   PICK_WEAPON= 7, 
   SELECT_1_WEAPON = 8,
   SELECT_2_WEAPON = 9, 
   SELECT_3_WEAPON = 10, 
   DO_NOTHING = 11
} Game_actions;

#define GAME_ACTIONS 11

Game_actions read_keyboard(enum cpct_e_keyID game_action_keys[], Game_actions game_actions[]);
void game_loop();
u8 should_game_end(Character characters[], u8 num_relevant_chars);


// Keys for each action
// OPQA forever, don't accept anything else
const enum cpct_e_keyID game_action_keys[GAME_ACTIONS] = {
   Key_O, 
   Key_P, 
   Key_Q, 
   Key_A, 
   Key_Enter, 
   Key_D, 
   Key_W,
   Key_1, 
   Key_2,
   Key_3,
   Key_Space
};

const Game_actions game_actions[GAME_ACTIONS] = {
   MOVE_LEFT, 
   MOVE_RIGHT, 
   MOVE_UP, 
   MOVE_DOWN, 
   ATTACK, 
   DEFEND, 
   PICK_WEAPON, 
   SELECT_1_WEAPON, 
   SELECT_2_WEAPON, 
   SELECT_3_WEAPON, 
   DO_NOTHING
};

const Weapon weapons[3] = {
   {i18n_FISTS, 253, 5},
   {i18n_STICK, 254, 10},
   {i18n_SWORD, 252, 15}
};

#define NUM_RELEVANT_CHARACTERS 2

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
   // Init variables
   u8 game_ends = 0;

   u8 energy    = 100;
   u8 attack    = 30;
   u8 defense   = 15;
   u8 energyen  = 90;
   u8 attacken  = 20;
   u8 defenseen = 10;

   Character player;
   Character monster;
   Game_actions monster_move;

   Game_actions action = NONE;

   Character *relevant_characters = malloc(sizeof(Character) * NUM_RELEVANT_CHARACTERS);
      
   // setup room
   Room main_room;
   strcpy(main_room.name, "Main Hall");
   generate_room_layout(&main_room, weapons);
   main_room.padding_x = 3;
   main_room.padding_y = 3;

   initialize_game_character(&player, 100, 10, 10, 248, "Diego");
   player.x_pos = 7;
   player.y_pos = 7;

   initialize_game_character(&monster, 100, 10, 10, 225, "Monster");
   monster.x_pos = 5;
   monster.y_pos = 2;

   // Game loop starts
   cls();
   print_room(&main_room);
   locate(1,23);
   puts("Move (O/P/Q/A) - the ONLY way to move\r");
   puts("Attack (Enter) - Defend (D)");

   while (!game_ends) {      
      put_character_in_room(&player, &main_room);
      put_character_in_room(&monster, &main_room);

      // Print stats
      locate(1,20);
      putchar(PLAYER_SPRITE); printf("PLAYER [%3d] (a%d) (d%d)\r\n   ", energy,   attack,   defense);
      locate(1,21);
      putchar(ENEMY_SPRITE);  printf("ENEMY  [%3d] (a%d) (d%d)\r\n   ", energyen, attacken, defenseen);
      
      action = read_keyboard(game_action_keys, game_actions);
      clear_room_position(&main_room, player.x_pos, player.y_pos);

      switch (action)
      {
      case MOVE_UP:
         move_character_up(&player, &main_room);
         break;
      case MOVE_DOWN:
         move_character_down(&player, &main_room);
         break;
      case MOVE_LEFT:
         move_character_left(&player, &main_room);
         break;
      case MOVE_RIGHT:
         move_character_right(&player, &main_room);
         break;
      case ATTACK:
         break; 
      case DEFEND:
         break;
      case PICK_WEAPON:
         break; 
      case SELECT_1_WEAPON:
         break; 
      case SELECT_2_WEAPON:
         break; 
      case SELECT_3_WEAPON:
         break; 
      default:
         break;
      }

      // ENEMY MOVES

      monster_move = (cpct_rand() % 4) + 1;

      clear_room_position(&main_room, monster.x_pos, monster.y_pos);

      if (monster_move == MOVE_UP) {
         move_character_up(&monster, &main_room);
      } else if (monster_move == MOVE_DOWN) {
         move_character_down(&monster, &main_room);
      } else if (monster_move == MOVE_RIGHT) {
         move_character_right(&monster, &main_room);
      } else if (monster_move == MOVE_LEFT) {
         move_character_left(&monster, &main_room);
      }

      // // PLAYER ATTACKS!
      // if (cpct_isKeyPressed(Key_A)) {
      //    energyen -= attack;
      // } else {
      //    // PLAYER DEFENDS!
      //    if (cpct_isKeyPressed(Key_D)) {
      //       energy += defense;
      //    }
      // }
      
      // // ENEMY DECIDE
      // if (cpct_rand() < 64) {
      //    energyen += defenseen;
      // } else {
      //    energy -= attacken;
      // }

      // check if game should end
      game_ends = should_game_end(relevant_characters, NUM_RELEVANT_CHARACTERS);
   }
}

Game_actions read_keyboard(enum cpct_e_keyID game_action_keys[], Game_actions game_actions[]) {
   Game_actions action_found = NONE;

   do {
         for (int i=0; i<GAME_ACTIONS; i++) {
            cpct_scanKeyboard();
            if (cpct_isKeyPressed(game_action_keys[i])) {
               action_found = game_actions[i];
               break;
            }
         }
   } while (action_found == NONE);

   printf("Action %d    ", action_found);
   return action_found;
}

// game ends when all characters in this array (normally the player or a final boss)
// have died
u8 should_game_end(Character characters[], u8 num_relevant_chars) {
   for (int i = 0; i < num_relevant_chars; i++) {
      if (characters[i].health_points <= 0) {
         return 1;
      }
   }
   return 0;
}