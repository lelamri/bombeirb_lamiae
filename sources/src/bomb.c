/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#include <SDL/SDL_image.h>

#include <assert.h>
#include <game.h>
#include <player.h>
#include <bomb.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <map.h>
#include <bonus.h>

struct bomb {
	int x;
	int y;
	int time;
	int range;
	enum bomb_state state;
	struct bomb* next_bomb;
};

struct bomb* bomb_init(){
	struct bomb* bomb = malloc(sizeof(*bomb));
	/*if (!bomb){
		error('Memory error');
	}*/
	bomb->next_bomb=NULL;
	return bomb;
}

void bomb_create(struct bomb* bomb, struct player* player){
	struct bomb* new_bomb = bomb;
	while( bomb_get_next_bomb(new_bomb) != NULL){
		new_bomb=bomb_get_next_bomb(new_bomb);
	}
	new_bomb->x = player_get_x(player);
	new_bomb->y = player_get_y(player);
	new_bomb->range = player_get_range(player);
	new_bomb->time = SDL_GetTicks();
	new_bomb->next_bomb=bomb_init();
	new_bomb->state=4;

}


struct bomb* bomb_get_next_bomb(struct bomb* bomb){
	return bomb->next_bomb;
}

void bomb_free(struct bomb* bomb){
	while(bomb_get_next_bomb(bomb) != NULL){
		free(bomb);
		bomb = bomb_get_next_bomb(bomb);
	}
}

void bomb_set_state(struct bomb* bomb, enum bomb_state state){
	assert(bomb);
	bomb->state = state;
}

void bomb_display(struct bomb* bomb, struct map* map){


	int i, xmin, xmax, ymin, ymax;

	xmin = bomb->x - bomb->range;
	xmax = bomb->x + bomb->range;

	ymin = bomb->y - bomb->range;
	ymax = bomb->y + bomb->range;

	if(bomb->state != 0){
		window_display_image(sprite_get_bomb(bomb->state), bomb->x * SIZE_BLOC, bomb->y * SIZE_BLOC );
	}
	else {
		for(i=xmin; i<=xmax; i++){
			if ((map_is_inside(map, i, bomb->y)) && (map_get_cell_type(map, i, bomb->y) == CELL_EMPTY)){
				if(i != bomb->x){
					window_display_image(sprite_get_explosion(), i * SIZE_BLOC, bomb->y * SIZE_BLOC);
				}
			}
		}
		for(i=ymin; i<=ymax; i++){
			if ((map_is_inside(map, bomb->x, i)) && (map_get_cell_type(map, bomb->x, i) == CELL_EMPTY)){
				if(i != bomb->y){
					window_display_image(sprite_get_explosion(), bomb->x * SIZE_BLOC, i * SIZE_BLOC);
				}
			}
		}
		window_display_image(sprite_get_explosion(), bomb->x * SIZE_BLOC, bomb->y * SIZE_BLOC);

	}
}

void bomb_explosion(struct game* game, struct bomb* bomb, struct map* map, struct player* player){
	int i, xmin, xmax, ymin, ymax;

	xmin = bomb->x - bomb->range;
	xmax = bomb->x + bomb->range;

	ymin = bomb->y - bomb->range;
	ymax = bomb->y + bomb->range;


	for(i=xmin; i<=xmax; i++){
		if ((map_is_inside(map, i, bomb->y)) && (map_get_cell_type(map, i, bomb->y) != CELL_EMPTY)){

			switch (map_get_cell_type(map, i, bomb->y)) {

				case CELL_PLAYER:
					//player_dec_nb_life(player);
					break;

				case CELL_SCENERY:
					break;

				case CELL_DOOR:
					break;

				case CELL_BONUS:
					map_set_cell_type(map, i, bomb->y, CELL_EMPTY);
					break;

				case CELL_BOX:
					map_set_cell_type(map, i, bomb->y, CELL_EMPTY);
					break;

				default:
					break;
			}
		}
	}


	for(i=ymin; i<=ymax; i++){
		if ((map_is_inside(map, bomb->x, i)) && (map_get_cell_type(map, bomb->x, i) != CELL_EMPTY)){

			switch (map_get_cell_type(map, bomb->x, i)) {

				case CELL_PLAYER:
					//player_dec_nb_life(player);
					break;

				case CELL_SCENERY:
					break;

				case CELL_DOOR:
					break;

				case CELL_BONUS:
					map_set_cell_type(map, bomb->x, i, CELL_EMPTY);
					break;

				case CELL_BOX:
					map_set_cell_type(map, bomb->x, i, CELL_EMPTY);
					break;

				/*case CELL_BOX_LIFE:
					bonus_box_type(game, map, bomb->x, i, map_get_compose_type(map, bomb->x, i));
					break;
				*/
				default:
					break;
			}
		}
	}


}


int bomb_update(struct bomb* bomb, struct game* game, struct map* map, struct player * player){
	int t = SDL_GetTicks(); // absolute time

	map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB);


	if(((t-bomb->time)>=4000) && (4500>(t-bomb->time))){
		map_set_cell_type(map, bomb->x, bomb->y, CELL_EXPLOSION);
		bomb_set_state(bomb, state_0);
		bomb_explosion(game, bomb, map, player);
	}

	if((4000>(t-bomb->time)) && (3000<=(t-bomb->time))){
		map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB1);
		bomb_set_state(bomb, state_1);
	}
	if((3000>(t-bomb->time)) && (2000<=(t-bomb->time))){
		map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB2);
		bomb_set_state(bomb, state_2);
	}

	if((2000>(t-bomb->time)) && (1000<=(t-bomb->time))){
		map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB3);
		bomb_set_state(bomb, state_3);
	}
	if((1000>(t-bomb->time)) && (0<=(t-bomb->time))){
		map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB4);
		bomb_set_state(bomb, state_4);
	}
	else{
		map_set_cell_type(map, bomb->x, bomb->y, CELL_EMPTY);
	}

	return 0;

}




