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
   u8 damage;           // damage dealt by this weapon
} Weapon;

// number of different weapons
#define MAX_WEAPONS 3

// array containing all weapons in this world
extern const Weapon world_weapons[MAX_WEAPONS];

#endif