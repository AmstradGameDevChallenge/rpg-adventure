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