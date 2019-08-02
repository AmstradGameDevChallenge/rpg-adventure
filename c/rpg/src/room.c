#include "room.h"
#include <stdio.h>
#include "util.h"
#include "i18n_strings.h"

void clear_room_position(Room *r, u8 x, u8 y) {
    if (x >= 0 && x < ROOM_X_MAX && y >= 0 && y < ROOM_Y_MAX) {
        r->room[x][y] = EMPTY_ROOM_TILE;              // update room model
        locate(r->padding_x + x, r->padding_y + y);   // update screen
        putchar(EMPTY_ROOM_TILE);
    }
}

void move_character_in_room(Character *c, Room *room) {
   room->room[c->x_pos][c->y_pos] = c->sprite;
   update_room_tile(c->sprite, room, c->x_pos, c->y_pos);
   // locate(room->padding_x + c->x_pos, room->padding_y + c->y_pos);
   // putchar(c->sprite);
}

void update_room_tile(char sprite, Room *room, u8 x, u8 y) {
   locate(room->padding_x + x, room->padding_y + y);
   putchar(sprite);
}

void generate_room_layout(Room *room, Weapon *weapons) {

   for (int i=0; i < ROOM_X_MAX; i++) {
      for (int j=0; j< ROOM_Y_MAX; j++) {
         room->room[i][j] = EMPTY_ROOM_TILE;
      }
   }

   // add top and bottom walls
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

void print_room(Room *room) {

   for (int i=0; i < ROOM_X_MAX; i++) {
      for (int j=0; j < ROOM_Y_MAX; j++) {
         
         locate(room->padding_x + i, room->padding_y + j);
         putchar(room->room[i][j]);
      }
   }

   locate(room->padding_x + 1, room->padding_y + ROOM_Y_MAX + 2);
   printf("%s%s", i18n_YOU_ARE_IN, room->name);
}