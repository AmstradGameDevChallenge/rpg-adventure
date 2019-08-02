//-----------------------------------------------------------------------------
// character.h
// Type definitions for game characters (Player, Enemies, etc.)
//-----------------------------------------------------------------------------

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <cpctelera.h>
#include "weapon.h"

#define PLAYER_SPRITE 250
#define ENEMY_SPRITE 251

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

void redefine_character_sprites();

#endif