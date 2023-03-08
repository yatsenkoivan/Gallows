#pragma once
#include <vector>;
#include <string>

class Words {
	private:
		std::vector<std::string> arr;
	public:
		Words();
		std::string decrypt(std::string word);
		//std::string encrypt(std::string word);
		void show();
		int amount() const;
		std::string operator[](int index);
};

class Game {
	private:
		Words word_list;
		std::string current_word;
		std::vector<char> missing;
		std::vector<char> exist;
		int current_stage;
		static std::vector<std::string> stages;
		time_t start_time;
		time_t end_time;
		int attempts;
	public:
		void new_game();
		void end();
		void guess(char letter);
		bool check_end();
		void show_stage();
		void show_word();
		void show_missing_letters();
};