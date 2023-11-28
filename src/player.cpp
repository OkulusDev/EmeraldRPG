#include <player.h>

Entity* createPlayer (Position start_pos) {
	Entity* player = new Entity();

	player->pos.y = start_pos.y;
	player->pos.x = start_pos.x;
	player->ch = '@';

	return player;
}

void inputKeyboardHandle(int input_code) {
	switch (input_code) {
		case 'w':										// Вверх
			// Постфиксный декремент позиции на оси Y
			player->pos.y--;
			break;
		case 's':										// Вниз
			// Постфиксный инкремент позиции на оси Y
			player->pos.y++;
			break;
		case 'a':										// Вправо
			// Постфиксный декремент позиции на оси X
			player->pos.x--;
			break;
		case 'd':										// Влево
			// Постфиксный инкремент позиции на оси X
			player->pos.x++;
		default:
			break;
	}
}
