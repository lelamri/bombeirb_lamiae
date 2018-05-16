/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#ifndef BOMB_H_
#define BOMB_H_

struct bomb;

#include <player.h>
#include <game.h>
#include <map.h>
#include <constant.h>




// Creates the bomb and initializes it
void bomb_create(struct bomb* bomb, struct player* player);
struct bomb* bomb_init();

// Returns the next bomb
struct bomb* bomb_get_next_bomb(struct bomb* bomb);

// Displays the bomb
void bomb_display(struct bomb* bomb, struct map* map);

// Updates the bomb
int bomb_update(struct bomb* bomb, struct game* game, struct map* map, struct player * player);

#endif /* BOMB_H_ */
