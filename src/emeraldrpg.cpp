/* Emerald RPG - текстовый RPG рогалик.
 * -------------------------------------------------------------------------------------
 * Название файла: src/emeraldrpg.cpp
 * Автор: Okulus Dev
 * Лицензия: MIT License
 * Заголовок: Главный файл
 * -------------------------------------------------------------------------------------
 *  Описание: главный исполняемый компилируемый файл */
#include <unistd.h>
#include <ncurses.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <player.h>
#include <map.h>

std::string username = getlogin();
Entity* player;
Entity* zombie;

// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
int GetRandomNumber(int min, int max)
{
	// Установить генератор случайных чисел
	srand(time(NULL));

	// Получить случайное число - формула
	int num = min + rand() % (max - min + 1);

	return num;
}


int main() {
	/* Главная функция */
	setlocale(LC_ALL, ""); 								// Устанавливаем локаль
	
	// Размер терминала
	initscr(); 											// Инициализация экрана
	noecho();
	curs_set(0);

	int row, col;
	getmaxyx(stdscr, row, col);

	Structure *map[(col + row) * 2];

	int i = 0;
	for (int y = 0; y < col; y++) {
		map[i] = createStructure({0, y}, true, '#');
		i++;
	}
	for (int x = 0; x < row; x++) {
		map[i] = createStructure({x, 0}, true, '#');
		i++;
	}
	for (int y = 0; y < col; y++) {
		map[i] = createStructure({row - 1, y}, true, '#');
		i++;
	}
	for (int x = 0; x < row; x++) {
		map[i] = createStructure({x, col - 1}, true, '#');
		i++;
	}
	

	auto greetingUser { [](const std::string& name) 	// лямбда функция приветствия
			{printw("Привет, %s. Нажмите Enter, чтобы начать!", name.c_str());}};
	greetingUser(username);

	getch();
	clear();

	Position start_pos = {row / 2, col / 2};
	Position zombie_pos = {row / 3, col / 3};
	player = createPlayer(start_pos, '@', false);
	zombie = createPlayer(zombie_pos, 'Z', false);

	for (int i = 0; i < sizeof(map)/sizeof(*map); i++) {
		mvaddch(map[i]->pos.y, map[i]->pos.x, map[i]->ch);
	}

	mvaddch(player->pos.y, player->pos.x, player->ch | A_BOLD);
	mvaddch(zombie->pos.y, zombie->pos.x, zombie->ch);

	int ch;
	while (ch = getch()) {
		if (ch == 'q')
			break;

		bool flag = true;
		for (int i = 0; i < sizeof(map)/sizeof(*map); i++)
		    if (checkCollision(player, map[i], ch)) {
		        flag = false;
		        break;
		    }
		if (flag) {
		    inputKeyboardHandle(ch);
		}
		
		clear();

		for (int i = 0; i < sizeof(map)/sizeof(*map); i++) {
			mvaddch(map[i]->pos.y, map[i]->pos.x, map[i]->ch);
		}

		if (player->pos.y > zombie->pos.y) {
			if (GetRandomNumber(1, 5) < 4 || player->pos.y + 1 == zombie->pos.y || player->pos.x + 1 == zombie->pos.x ||
					player->pos.y - 1 == zombie->pos.y || player->pos.x - 1 == zombie->pos.x) {
				zombie->pos.y++;
			} else {
				zombie->pos.y--;
			}
		} else if (player->pos.y < zombie->pos.y) {
			if (GetRandomNumber(1, 5) < 4 || player->pos.y + 1 == zombie->pos.y || player->pos.x + 1 == zombie->pos.x ||
					player->pos.y - 1 == zombie->pos.y || player->pos.x - 1 == zombie->pos.x) {
				zombie->pos.y--;
			} else {
				zombie->pos.y++;
			}
		} else if (player->pos.x > zombie->pos.x) {
			if (GetRandomNumber(1, 5) < 4 || player->pos.y + 1 == zombie->pos.y || player->pos.x + 1 == zombie->pos.x ||
					player->pos.y - 1 == zombie->pos.y || player->pos.x - 1 == zombie->pos.x) {
				zombie->pos.x++;
			} else {
				zombie->pos.x--;
			}
		} else if (player->pos.x < zombie->pos.x) {
			if (GetRandomNumber(1, 5) < 4 || player->pos.y + 1 == zombie->pos.y || player->pos.x + 1 == zombie->pos.x ||
					player->pos.y - 1 == zombie->pos.y || player->pos.x - 1 == zombie->pos.x) {
				zombie->pos.x--;
			} else {
				zombie->pos.x++;
			}
		} else if (player->pos.x == zombie->pos.x && player->pos.y == zombie->pos.y) {
			player->died = true;
		}

		if (!player->died) {
			mvaddch(player->pos.y, player->pos.x, player->ch | A_BOLD);
		} else {
			break;
		}
		mvaddch(zombie->pos.y, zombie->pos.x, zombie->ch);
	}

	endwin();

	// Выход
	return 0;
}
