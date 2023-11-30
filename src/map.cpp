#include <ncurses.h>
#include <iostream>

#include <map.h>
#include <player.h>

Structure* createStructure (Position pos, bool collision, char ch) {
	Structure* structure = new Structure();

	structure->pos.y = pos.y;
	structure->pos.x = pos.x;
	structure->collision = collision;
	structure->ch = ch;

	return structure;
}

bool checkCollision(Entity* player, Structure* wall, int input_code) {
	if (player->pos.y - 1 == wall->pos.y && player->pos.x == wall->pos.x && input_code == 'w') {
		return true;
	} else if (player->pos.y + 1 == wall->pos.y && player->pos.x == wall->pos.x && input_code == 's') {
		return true;
	} else if (player->pos.x - 1 == wall->pos.x && player->pos.y == wall->pos.y && input_code == 'a') {
		return true;
	} else if (player->pos.x + 1 == wall->pos.x && player->pos.y == wall->pos.y && input_code == 'd') {
		return true;
	} else {
		return false;
	}
}

