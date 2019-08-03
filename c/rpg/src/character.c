#include "character.h"
#include "util.h"
#include <string.h>

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


// initialize_game_character: initializes a game character (player, enemies, etc.)
// Args:
//    Character *c: pointer to the character to be initialized
//    u16 health_points: health points for this character. When zero, it dies   
//    u16 attack: attack points           
//    u16 defense: defense points         
//    char sprite: graphical representation         
//    char *name: name of this character       
// All characters start with three weapons   
void initialize_game_character (Character *c,
   u16 health_points,   
   u16 attack,           
   u16 defense,         
   char sprite,         
   char *name       
   ) {
   c->health_points = health_points;
   
   c->attack = attack;
   c->defense = defense;
   c->sprite = sprite;
   strcpy(c->name, name);

   // adding three weapons to this character
   c->current_weapon = 0;
   for (int i=0; i<MAX_WEAPONS; i++) {
      c->weapons[i] = &(world_weapons[i]);
   }
}