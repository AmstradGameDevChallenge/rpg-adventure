//-----------------------------------------------------------------------------
// room.h
// Type definitions for game rooms
//-----------------------------------------------------------------------------

#ifndef __ROOM_H__
#define __ROOM_H__

#include <cpctelera.h>
#include "character.h"
#include "room.h"

// max number of rows, colums in a room
#define ROOM_X_MAX 10
#define ROOM_Y_MAX 10

#define WALL_CHAR 127
// empty tile represented by CHR$(144)
#define EMPTY_ROOM_TILE 144

// Room: a room is where all the action take place. A dungeon is divided in several rooms.
// inside rooms we have the player, monsters, weapons, doors, walls, etc.
// a Room is represented by a two-dimensional array of 'tiles'
typedef struct game_room {
   u8 room[ROOM_X_MAX][ROOM_Y_MAX]; // array containing different chars for each thing in a tile
   char name[15];                   // name of the room
   u8 adjacent_rooms[4];            // other rooms we can go to. [up, rigth, down, left]
   u8 padding_x;                    // x from origin to paint this room
   u8 padding_y;
} Room;

void clear_room_position(Room *r, u8 x, u8 y);
void move_character_in_room(Character *c, Room *r);
void update_room_tile(char sprite, Room *room, u8 x, u8 y);
void generate_room_layout(Room *room, Weapon *weapons);
void print_room(Room *room);

#endif