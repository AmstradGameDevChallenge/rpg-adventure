

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

#define PLAYER_SPRITE 250
#define ENEMY_SPRITE 251

void game_loop();
void redefine_character_sprites();

typedef struct character_weapon {
   char name[15];       // weapon name
   char sprite;         // text sprite that represents our weapon
   u8 damage;
} Weapon;

// void create_weapon(Weapon *w, char *name, char sprite, u8 damage);

typedef struct game_character {
   u16 health_points;   // life of our player and enemies. When == 0, it dies
   u8 current_weapon;   // current weapon selected
   Weapon weapons[3];   // a character can carry up to three weapons
   u16 attack;          // attack strengh modifier 
   u16 defense;         // defense modifier
   char sprite;         // text sprite that represents our character
   char name[15];       // name of our character
   u8 x_pos;
   u8 y_pos;
} Character;

void initialize_game_character (Character *c,
   u16 health_points,   
   u16 attack,           
   u16 defense,         
   char sprite,         
   char *name       
   ); 

#define ROOM_X_MAX 10
#define ROOM_Y_MAX 10

typedef struct game_room {
   u8 room[ROOM_X_MAX][ROOM_Y_MAX];
   char name[15];
   u8 adjacent_rooms[4];   // up, rigth, down, left
} Room;

void move_character_in_room(Character *c, Room *r);
void generate_room_layout(Room *room, Weapon *weapons);
void print_room(Room *room, u8 x, u8 y);

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

void redefine_character_sprites() {
   // http://www.cpctech.org.uk/docs/basic.asm
   // __asm__ ( "ld      de,$00f0; " // DE = 240
   //           "call    $f7e9;"     // symbol after 240
   //  );

   // Player
   symbol(PLAYER_SPRITE, 56,108,84,238,198,186,254,170);
   // MONSTER
   symbol(ENEMY_SPRITE, 56,59,59,18,126,18,124,68);
}


/****************************************************************************
 *                      Character Initialization
 ***************************************************************************/
void initialize_game_character (Character *c,
   u16 health_points,   
   u16 attack,           
   u16 defense,         
   char sprite,         
   char *name       
   ) {
   c->health_points = health_points;
   // struct character_weapon fists;
   // create_weapon(&fists, i18n_FISTS, 70, 5);
   c->current_weapon = 0;
   // memcpy(c->weapons, weapons[0], sizeof(Weapon));
   
   c->attack = attack;
   c->defense = defense;
   c->sprite = sprite;
   strcpy(c->name, name);
}

// void create_weapon(struct character_weapon *w, char *name, char sprite, u8 damage) {
//    strcpy(w->name, name);
//    w->sprite = sprite;
//    w->damage = damage;
// }

#define WALL_CHAR 127

void move_character_in_room(Character *c, Room *r) {
   r->room[c->x_pos][c->y_pos] = c->sprite;
}

void generate_room_layout(Room *room, Weapon *weapons) {

   for (int i=0; i< ROOM_X_MAX; i++) {
      for (int j=0; j< ROOM_Y_MAX; j++) {
         room->room[i][j] = '.';
      }
   }

   // top a bottom walls
   for (int i=0; i < ROOM_X_MAX; i++) {
      room->room[0][i] = WALL_CHAR;
      room->room[ROOM_X_MAX-1][i] = WALL_CHAR;
   }

   for (int i=1; i< ROOM_Y_MAX-1; i++) {
      room->room[i][0] = WALL_CHAR;
      room->room[i][ROOM_Y_MAX-1] = WALL_CHAR;
   }

   room->room[2][2] = weapons[0].sprite;
}

void print_room(Room *room, u8 x, u8 y) {

   for (int i=0; i < ROOM_X_MAX; i++) {
      for (int j=0; j < ROOM_Y_MAX; j++) {
         
         locate(x+i+1,y+j+1);
         putchar(room->room[i][j]);
      }
   }
   puts(NEWLINE);
   printf(room->name);
}