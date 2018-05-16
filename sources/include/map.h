/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#ifndef MAP_H_
#define MAP_H_

enum cell_type {
	CELL_EMPTY=0x00,   		//  0000 0000
	CELL_SCENERY=0x10, 		//  0001 0000
	CELL_BOX=0x20,   		//  0010 0000
	CELL_DOOR=0x30,      	//  0011 0000
	CELL_KEY=0x40,       	//  0100 0000
	CELL_BONUS=0x50, 		// 	0101 0000
	CELL_MONSTER=0x60, 		// 	0110 0000
	CELL_BOMB=0x70, 	   		// 	0111 0000
	CELL_PLAYER=0x80,


};

enum bonus_type {
	BONUS_BOMB_RANGE_DEC=1,
	BONUS_BOMB_RANGE_INC,
	BONUS_BOMB_NB_DEC,
	BONUS_BOMB_NB_INC,
	BONUS_MONSTER,
	BONUS_LIFE
};

enum scenery_type {
	SCENERY_STONE,     // 0000
	SCENERY_TREE,      // 0010
	SCENERY_PRINCESS   // 0010
};


enum bomb_type {
	BOMB_TTL1,
	BOMB_TTL2,
	BOMB_TTL3,
	BOMB_TTL4,
	EXPLOSION

};

enum compose_type {
	CELL_TREE     = CELL_SCENERY | SCENERY_TREE,
	CELL_STONE    = CELL_SCENERY | SCENERY_STONE,
	CELL_PRINCESS = CELL_SCENERY | SCENERY_PRINCESS,

    CELL_BOX_RANGEINC = CELL_BOX | BONUS_BOMB_RANGE_INC,
    CELL_BOX_RANGEDEC = CELL_BOX | BONUS_BOMB_RANGE_DEC,
	CELL_BOX_BOMBINC  = CELL_BOX | BONUS_BOMB_NB_INC,
    CELL_BOX_BOMBDEC  = CELL_BOX | BONUS_BOMB_NB_DEC,
    CELL_BOX_LIFE     = CELL_BOX | BONUS_LIFE,
    CELL_BOX_MONSTER  = CELL_BOX | BONUS_MONSTER,


		CELL_BONUS_RANGEINC = CELL_BONUS | BONUS_BOMB_RANGE_INC,
		CELL_BONUS_RANGEDEC = CELL_BONUS | BONUS_BOMB_RANGE_DEC,
		CELL_BONUS_BOMBINC  = CELL_BONUS | BONUS_BOMB_NB_INC,
		CELL_BONUS_BOMBDEC  = CELL_BONUS | BONUS_BOMB_NB_DEC,
		CELL_BONUS_LIFE     = CELL_BONUS | BONUS_LIFE,
		CELL_BONUS_MONSTER  = CELL_BONUS | BONUS_MONSTER,

	CELL_BOMB1 = CELL_BOMB | BOMB_TTL1,
	CELL_BOMB2 = CELL_BOMB | BOMB_TTL2,
	CELL_BOMB3 = CELL_BOMB | BOMB_TTL3,
	CELL_BOMB4 = CELL_BOMB | BOMB_TTL4,
	CELL_EXPLOSION = CELL_BOMB | EXPLOSION

};

struct map;

// Create a new empty map
struct map* map_new(int width, int height);
void map_free(struct map* map);


// Return the height and width of a map
int map_get_width(struct map* map);
int map_get_height(struct map* map);

// Return the type of a cell
enum cell_type map_get_cell_type(struct map* map, int x, int y);
enum compose_type map_get_compose_type(struct map* map, int x, int y);

// Set the type of a cell
void  map_set_cell_type(struct map* map, int x, int y, enum cell_type type);

// Test if (x,y) is within the map
int map_is_inside(struct map* map, int x, int y);

// Return a default static map
struct map* map_get_static();

// Display the map on the screen
void map_display(struct map* map);

#endif /* MAP_H_ */
