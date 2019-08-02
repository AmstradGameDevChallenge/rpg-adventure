//-----------------------------------------------------------------------------
// weapon.h
// Type definitions for game Weapons you'll find in rooms
//-----------------------------------------------------------------------------

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <cpctelera.h>

typedef struct character_weapon {
   char name[15];       // weapon name
   char sprite;         // text sprite that represents our weapon
   u8 damage;
} Weapon;

#endif