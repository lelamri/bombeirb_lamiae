/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/

#include <SDL/SDL_image.h>
#include <assert.h>

#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <map.h>
#include <bonus.h>

struct player {
	int x, y;
	enum direction current_direction;
	int nb_bombs;
	int nb_life;
	int nb_key;
	int range;
};


struct player* player_init(int bomb_number, int life_number, int key_number, int range) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->current_direction = SOUTH;
	player->nb_bombs = bomb_number;
	player->nb_life = life_number;
	player->nb_key = key_number;
	player->range = range;

	return player;
}



void player_set_position(struct player *player, int x, int y) {
	assert(player);
	player->x = x;
	player->y = y;
}


void player_free(struct player* player) {
	assert(player);
	free(player);
}

int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}

void player_set_current_way(struct player* player, enum direction way) {
	assert(player);
	player->current_direction = way;
}


int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bombs;
}

void player_inc_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bombs += 1;
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bombs -= 1;
}


int player_get_nb_life(struct player* player) {
	assert(player);
	return player->nb_life;
}

void player_inc_nb_life(struct player* player) {
	assert(player);
	player->nb_life += 1;
}

void player_dec_nb_life(struct player* player) {
	assert(player);
	player->nb_life -= 1;
}



int player_get_nb_key(struct player* player) {
	assert(player);
	return player->nb_key;
}

void player_inc_nb_key(struct player* player) {
	assert(player);
	player->nb_key += 1;
}

void player_dec_nb_key(struct player* player) {
	assert(player);
	player->nb_key -= 1;
}



int player_get_range(struct player* player) {
	assert(player);
	return player->range;
}

void player_inc_range(struct player* player) {
	assert(player);
	player->range += 1;
}

void player_dec_range(struct player* player) {
	assert(player);
	player->range -= 1;
}


static int player_move_aux(struct player* player, struct map* map, int x, int y) {

	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_BOX:
		switch (player->current_direction) {

		case NORTH:
			if (map_is_inside(map, x, y-1) && map_get_cell_type(map, x, y-1)==CELL_EMPTY){
				map_set_cell_type(map, x, y-1, map_get_cell_type(map,x,y));
				map_set_cell_type(map,x,y,CELL_EMPTY);
				return 1;
			}

			else {
				return 0;

			}

			break;


		case SOUTH:
			if (map_is_inside(map,x,y+1) && map_get_cell_type(map, x, y+1)==CELL_EMPTY){
				map_set_cell_type(map,x,y+1,map_get_cell_type(map,x,y));
				map_set_cell_type(map, x, y , CELL_EMPTY);
				return 1;
			}

			else {
				return 0;
			}
			break;


		case WEST:
			if (map_is_inside(map, x-1, y) && map_get_cell_type(map, x-1, y)==CELL_EMPTY){


				map_set_cell_type(map, x-1, y, map_get_cell_type(map,x,y));
				map_set_cell_type(map,x,y,CELL_EMPTY);
				return 1;
			}
			else {
				return 0;
			}
			break;


		case EAST:
			if (map_is_inside(map, x+1, y) && map_get_cell_type(map, x+1, y)==CELL_EMPTY){

				map_set_cell_type(map, x+1, y, map_get_cell_type(map,x,y));
				map_set_cell_type(map,x,y,CELL_EMPTY);
				return 1;
			}
			else {
				return 0;
			}
			break;
		}
		break;



	case CELL_BONUS:

		switch(map_get_compose_type(map, x, y)){

		case CELL_BONUS_BOMBINC:
			player_inc_nb_bomb(player);
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
			break;

		case CELL_BONUS_BOMBDEC:
			player_dec_nb_bomb(player);
			map_set_cell_type(map, x, y, CELL_EMPTY);

			return 1;
			break;


		case CELL_BONUS_LIFE:
			player_inc_nb_life(player);
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
			break;

		case CELL_BONUS_RANGEINC:
			player_inc_range(player);
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
			break;

		case CELL_BONUS_RANGEDEC:
			player_dec_range(player);
			map_set_cell_type(map, x, y, CELL_EMPTY);
			return 1;
			break;

		default:
			break;
		}

		return 0;

		break;

	case CELL_MONSTER:
		player_dec_nb_life(player);
		return 0;
		break;

	case CELL_DOOR:
		break;


	default:
		break;
	}


	// Player has moved
	return 1;
}

int player_move(struct player* player, struct map* map) {
	int x = player->x;
	int y = player->y;
	int move = 0;

	switch (player->current_direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1)) {
			player->y--;
			move = 1;
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1)) {
			player->y++;
			move = 1;
		}
		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y)) {
			player->x--;
			move = 1;
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y)) {
			player->x++;
			move = 1;
		}
		break;
	}

	if (move) {
		map_set_cell_type(map, x, y, CELL_EMPTY);
	}
	return move;
}

void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->current_direction),
			player->x * SIZE_BLOC, player->y * SIZE_BLOC);
}
