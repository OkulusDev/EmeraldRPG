#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include <iostream>

typedef struct {
	int y;
	int x;
} Position;

typedef struct {
	Position pos;
	char ch;
	bool died;
} Entity;

Entity* createPlayer(Position start_pos, char ch, bool died);
void inputKeyboardHandle(int input);

extern Entity* player;
extern Entity* zombie;

#endif
