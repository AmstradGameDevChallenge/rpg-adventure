//-----------------------------------------------------------------------------
// Small Text Based Rogue like RPG text-based game for the AMSTRAD CPC
// by @dfreniche
// July 2019
//-----------------------------------------------------------------------------

#define VERSION "v0.0.6"

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
u8 should_game_end(Character *characters[], u8 num_relevant_chars);
Game_actions monster_moves_in_room(Character *monster, Room *main_room);
void character_attacks_character(Character *c1, Character *c2);
void print_console(char *s);

// Keys for each action
// OPQA forever, don't accept anything else
const enum cpct_e_keyID game_action_keys[GAME_ACTIONS] = {
   Key_O, 
   Key_P, 
   Key_Q, 
   Key_A, 
   Key_Return, 
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

#define NUM_RELEVANT_CHARACTERS 2

void main(void) {
   redefine_character_sprites();

   cpct_setVideoMode(1);  // Set Video Mode 1 (40x25)
   border(1,1);

   // Let's start!
   show_presentation(VERSION);

   // Loop forever
   while (1){
      game_loop();
      cls();
      wait_for_enter_key();
      show_presentation(VERSION);
      wait_for_enter_key();
   }

}

// Main game loop
void game_loop() {
   // Init variables
   u8 game_ends = 0;

   Character player;
   Character monster;
   Game_actions monster_move;
   Game_actions action = NONE;

   // Character *relevant_characters[NUM_RELEVANT_CHARACTERS] = malloc(sizeof(Character) * NUM_RELEVANT_CHARACTERS);
   Character *relevant_characters[NUM_RELEVANT_CHARACTERS] = {
      {&player},
      {&monster}
   };
   // setup room
   Room main_room;
   strcpy(main_room.name, "Main Hall");
   generate_room_layout(&main_room, world_weapons);
   main_room.padding_x = 15;
   main_room.padding_y = 5;

   initialize_game_character(&player, 100, 10, 10, 248, "Diego");
   
   initialize_game_character(&monster, 100, 10, 10, 225, "Monster");

   // Game loop starts
   cls();
   print_room(&main_room);
   locate(1,24);
   puts("Move (O/P/Q/A) - Select Weapon (1/2/3)\r");
   printf("Attack (Enter) - Defend (D) - Wait (Spc)");

   show_header();

   while (!game_ends) {      
      put_character_in_room(&player, &main_room);
      put_character_in_room(&monster, &main_room);

      // Print stats
      pen(1);
      locate(1,6); putchar(PLAYER_SPRITE); printf(" PLAYER");
      locate(1,7); printf("%c %3d", 228, player.health_points);
      locate(1,8); printf("(a%d) (d%d)\r\n   ", player.attack, player.defense);
      pen(3);
      locate(34,6); putchar(ENEMY_SPRITE);  printf(" ENEMY");
      locate(36,7); printf("%c %3d", 228, monster.health_points);
      locate(30,8); printf("(a%d) (d%d)\r\n   ", monster.attack, monster.defense);
      locate(1,10);
      pen(1);
      puts("Weapon:");
      locate(1,11); printf("%s", player.weapons[player.current_weapon]->name);
      locate(1,13); printf("damage: %d", player.weapons[player.current_weapon]->damage);

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
         character_attacks_character(&player, &monster);
         break; 
      case DEFEND:
         player.health_points = player.health_points + player.defense;
         break;
      case PICK_WEAPON:
         break; 
      case SELECT_1_WEAPON:
         player.current_weapon = 0;
         break; 
      case SELECT_2_WEAPON:
         player.current_weapon = 1;
         break; 
      case SELECT_3_WEAPON:
         player.current_weapon = 2;
         break; 
      default:
         break;
      }

      // Before moving the enemy checks to see if the player is nearby. 
      // In that case it attacks
      if (character_next_to_character_in_room(&player, &monster, &main_room) == 1) {
         pen(3);
         character_attacks_character(&monster, &player);
         monster_attack_effect();
      } else {
         // ENEMY MOVES

         monster_move = monster_moves_in_room(&monster, &main_room);
         border(1, 1);
      }
      
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

   return action_found;
}

// game ends when all characters in this array (normally the player or a final boss)
// have died
u8 should_game_end(Character *characters[], u8 num_relevant_chars) {
   int h = 0;
   for (int i = 0; i < num_relevant_chars; i++) {
      h = characters[i]->health_points;
      if (h <= 0) {
         return 1;
      }
   }
   return 0;
}


Game_actions monster_moves_in_room(Character *monster, Room *main_room) {
   Game_actions monster_move = (cpct_rand() % 4) + 1;

   clear_room_position(main_room, monster->x_pos, monster->y_pos);

   if (monster_move == MOVE_UP) {
      move_character_up(monster, main_room);
   } else if (monster_move == MOVE_DOWN) {
      move_character_down(monster, main_room);
   } else if (monster_move == MOVE_RIGHT) {
      move_character_right(monster, main_room);
   } else if (monster_move == MOVE_LEFT) {
      move_character_left(monster, main_room);
   }

   return monster_move;
}

void character_attacks_character(Character *c1, Character *c2) {
   char msg[40];
   Weapon *w = c1->weapons[c1->current_weapon];
   u8 damage = c1->attack * w->damage;
   c2->health_points = c2->health_points - damage;
   sprintf(msg, "%s attacks dealing %d damage!    ", c1->name, damage);
   print_console(msg);
}

#define CONSOLE_Y_START 18
#define CONSOLE_Y_STOP 22

void print_console(char *s) {
   static u8 y = CONSOLE_Y_START;

   if (y==0) y=CONSOLE_Y_START;
   locate(1, y);
   printf(s);
   y++;
   if (y > CONSOLE_Y_STOP) {
      y = CONSOLE_Y_START;
      for (int i=CONSOLE_Y_START; i<=CONSOLE_Y_STOP; i++) {
         locate(1, i);
         printf("                                       ");
      }
   }
}