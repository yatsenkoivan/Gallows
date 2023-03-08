#include "Gallows.h"
#include <fstream>
#include<iostream>
#include <ctime>

Words::Words() {
	std::ifstream words;
	words.open("words.txt", std::ios::in);
	std::string temp;
	while (words >> temp) {
		arr.push_back(decrypt(temp));
	}
	words.close();
}
std::string Words::decrypt(std::string word) {
	std::string res = "";
	for (int i = 0; i < word.length(); i++) {
		res += ((word[i] + 22 + i) % 'Z' + 'A');
	}
	return res;
}
/*std::string Words::encrypt(std::string word) {
	std::string res = "";
	for (int i = 0; i < word.length(); i++) {
		res += ('Z' - 'A' % (word[i] - 22 - i));
	}
	return res;
}*/
void Words::show() {
	for (std::string word : arr) {
		std::cout << word << std::endl;
	}
}
int Words::amount() const {
	return arr.size();
}
std::string Words::operator[](int index) {
	return arr[index];
}

std::vector<std::string> Game::stages = {
	"   -----|\n"
	"   |    |\n"
	"        |\n"
	"        |\n"
	"        |\n"
	"________|\n",

	"   -----|\n"
	"   |    |\n"
	"   O    |\n"
	"        |\n"
	"        |\n"
	"________|\n",

	"   -----|\n"
	"   |    |\n"
	"   O    |\n"
	"   |    |\n"
	"        |\n"
	"________|\n",

	"   -----|\n"
	"   |    |\n"
	"   O    |\n"
	"  /|    |\n"
	"        |\n"
	"________|\n",

	"   -----|\n"
	"   |    |\n"
	"   O    |\n"
	"  /|\\   |\n"
	"        |\n"
	"________|\n",
	"   -----|\n"
	"   |    |\n"
	"   O    |\n"
	"  /|\\   |\n"
	"  /     |\n"
	"________|\n",

	"   -----|\n"
	"   |    |\n"
	"   O    |\n"
	"  /|\\   |\n"
	"  / \\   |\n"
	"________|\n"

};

void Game::new_game() {
	current_word = word_list[rand() % word_list.amount()];
	attempts = 0;
	missing.clear();
	exist.assign(current_word.length(), ' ');
	start_time = time(0);
	current_stage = 0;
}
void Game::guess(char letter) {
	if ('a' <= letter && letter <= 'z') {
		letter = letter - 'a' + 'A';
	}
	if (!('A' <= letter && letter <= 'Z')) {
		std::cout << "Not a letter\n";
		return;
	}
	if (find(missing.begin(), missing.end(), letter) != missing.end()
		||
		find(exist.begin(), exist.end(), letter) != exist.end()) {
		std::cout << "Already guessed\n";
		return;
	}
	bool found = false;
	for (int i = 0; i < current_word.length(); i++) {
		if (current_word[i] == letter) {
			exist[i] = letter;
			found = true;
		}
	}
	if (!found) {
		missing.push_back(letter);
		current_stage++;
	}
	attempts++;
}
void Game::show_stage() {
	std::cout << stages[current_stage] << std::endl;
}
void Game::show_word() {
	std::cout << "Word:\n";
	for (char& i : exist) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < current_word.length(); i++) std::cout << "_ ";
	std::cout << "\n\n";
}
void Game::show_missing_letters() {
	std::cout << "Missing: ";
	copy(missing.begin(), missing.end(), std::ostream_iterator<char>(std::cout, " "));
	std::cout << std::endl;
}
bool Game::check_end() {
	return (current_stage == stages.size()-1 || !count(exist.begin(), exist.end(), ' '));
}
void Game::end() {
	std::cout << "---GAME-OVER---\n";
	end_time = time(0);
	std::cout << "Word:\t" << current_word << std::endl;
	std::cout << "Time:\t" << difftime(end_time, start_time) << std::endl;
	std::cout << "Attempts:\t" << attempts << std::endl;
}