#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include <player.h>
#include <iostream>

typedef struct {
	Position pos;
	bool collision;
	char ch;
} Structure;

Structure* createStructure(Position pos, bool collision, char ch);
bool checkCollision(Entity* player, Structure* wall, int input_code);

#endif
