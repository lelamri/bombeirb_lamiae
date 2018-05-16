#ifndef BONUS_H_
#define BONUS_H_

#include <map.h>
#include <constant.h>
#include <game.h>



void bonus_type(struct player* player, int x, int y, unsigned char type);

void bonus_box_type(struct game* game,struct map* map, int x, int y, unsigned char type);

#endif /* BONUS_H_ */
