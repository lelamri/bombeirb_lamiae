#include <SDL/SDL_image.h>
#include <assert.h>

#include <window.h>
#include <misc.h>
#include <constant.h>
#include <player.h>
#include <game.h>




void bonus_type(struct player* player, int x, int y, unsigned char type){
	switch (bonus_type) {

		case BONUS_BOMB_RANGE_INC:
			player_inc_range(player);
			break;

		case BONUS_BOMB_NB_INC:
			player_inc_nb_bomb(player);
			break;

		case BONUS_LIFE:
			player_inc_nb_life(player);
			break;
		default:
			break;
	}
}

void bonus_box_type(struct game* game,struct map* map, int x, int y, unsigned char type){
	switch (bonus_type) {

		case BONUS_BOMB_RANGE_INC:
			map_set_cell_type(map, x, y, CELL_BONUS_RANGEINC);
			break;

		case BONUS_BOMB_NB_INC:
			map_set_cell_type(map, x, y, CELL_BONUS_BOMBINC);
			break;

		case BONUS_LIFE:
			map_set_cell_type(map, x, y, CELL_BONUS_LIFE);
			break;

		default:
			map_set_cell_type(map, x, y, CELL_EMPTY);
			break;

	}
}
