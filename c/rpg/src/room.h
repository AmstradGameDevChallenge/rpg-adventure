//-----------------------------------------------------------------------------
// room.h
// Type definitions for game rooms
//-----------------------------------------------------------------------------

#ifndef __ROOM_H__
#define __ROOM_H__

#include <cpctelera.h>
#include "character.h"
#include "room.h"

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

#endif