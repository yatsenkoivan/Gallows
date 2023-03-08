#include "Gallows.h"
#include <iostream>

int main() {
	srand(time(0));
	Game game;
	char letter;
	int menu;
	while (true) {
		std::cout << "Start new game - (1)\n";
		std::cout << "Exit - (0)\n> ";
		std::cin >> menu;
		if (menu == 1) {
			game.new_game();
			system("cls");
			while (!game.check_end()) {
				game.show_stage();
				game.show_word();
				game.show_missing_letters();
				std::cout << "> ";
				std::cin >> letter;
				system("cls");
				game.guess(letter);
			}
			game.show_stage();
			game.end();
			system("pause");
			system("cls");
		}
		else {
			break;
		}
	}
}