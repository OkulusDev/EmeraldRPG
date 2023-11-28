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
#include <player.h>

std::string username = getlogin();
Entity* player;

int main() {
	/* Главная функция */
	setlocale(LC_ALL, ""); 								// Устанавливаем локаль
	
	// Размер терминала
	initscr(); 											// Инициализация экрана
	noecho();
	curs_set(0);

	int row, col;
	getmaxyx(stdscr, row, col);

	int ch;
	Position start_pos = {row / 2, col / 2};

	auto greetingUser { [](const std::string& name) 	// лямбда функция приветствия
			{printw("Привет, %s. Нажмите Enter, чтобы начать!", name.c_str());}};
	greetingUser(username);

	getch();
	clear();

	player = createPlayer(start_pos);
	
	mvaddch(player->pos.y, player->pos.x, player->ch | A_BOLD);

	while (ch = getch()) {
		if (ch == 'q')
			break;

		inputKeyboardHandle(ch);
		clear();
		mvaddch(player->pos.y, player->pos.x, player->ch | A_BOLD);
	}

	endwin();

	// Выход
	return 0;
}
