#include "room.h"
#include <stdio.h>
#include "util.h"

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