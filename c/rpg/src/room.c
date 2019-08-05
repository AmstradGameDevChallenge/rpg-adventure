#include "room.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "i18n_strings.h"

void clear_room_position(Room *r, u8 x, u8 y) {
    if (x >= 0 && x < ROOM_X_MAX && y >= 0 && y < ROOM_Y_MAX) {
        r->room[x][y] = EMPTY_ROOM_TILE;              // update room model
        locate(r->padding_x + x, r->padding_y + y);   // update screen
        putchar(EMPTY_ROOM_TILE);
    }
}

void move_character_up(Character *character, Room *room) {
   move_character_in_room(character, room, character->x_pos, character->y_pos - 1);
}

void move_character_down(Character *character, Room *room) {
   move_character_in_room(character, room, character->x_pos, character->y_pos + 1);
}

void move_character_right(Character *character, Room *room) {
   move_character_in_room(character, room, character->x_pos + 1, character->y_pos);
}

void move_character_left(Character *character, Room *room) {
   move_character_in_room(character, room, character->x_pos - 1, character->y_pos);
}

void move_character_in_room(Character *character, Room *room, u8 new_x, u8 new_y) {
   // check x and y limits
   if (new_x < 0 || new_x >= ROOM_X_MAX) {
      return;
   }

   if (new_y < 0 || new_y >= ROOM_Y_MAX) {
      return;
   }

   // we can't walk on walls
   if (room->room[new_x][new_y] == WALL_CHAR) {
      return;
   }

   character->x_pos = new_x;
   character->y_pos = new_y;
}

void put_character_in_room(Character *c, Room *room) {
   room->room[c->x_pos][c->y_pos] = c->sprite;
   update_room_tile(c->sprite, room, c->x_pos, c->y_pos);
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

   locate(room->padding_x - strlen(i18n_YOU_ARE_IN)/2, room->padding_y + ROOM_Y_MAX + 1);
   printf("%s%s", i18n_YOU_ARE_IN, room->name);
}

u8 character_next_to_character_in_room(Character *c1, Character *c2, Room *room) {
   // in the same row
   if (c1->y_pos == c2->y_pos) {
      // distance of one 
      if (abs(c1->x_pos - c2->x_pos) == 1) {
         return 1;
      } 
   }

   // in the same column
   if (c1->x_pos == c2->x_pos) {
      // distance of one 
      if (abs(c1->y_pos - c2->y_pos) == 1) {
         return 1;
      } 
   }

   return 0;
}