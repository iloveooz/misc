#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

int main() {
	const int МАХ_WRONG_ERRORS = 8;

	std::vector<std::string> words;

	words.push_back("GUESS");
	words.push_back("HANGMAN");
	words.push_back("DIFFICULT");

	srand(static_cast<unsigned int>(time(nullptr)));

	std::random_shuffle(words.begin(), words.end());

	const std::string THE_WORD = words[0]; //слово для отгадывания

	int wrong = 0; // количество ошибочных вариантов
	std::string soFar(THE_WORD.size(), '-'); // часть слова. открытая на данный момент
	std::string used = ""; // уже отгаданные буквы

	std::cout << "Welcome to Hangman. Good luck!\n";

	while ((wrong < МАХ_WRONG_ERRORS) && (soFar != THE_WORD)) {
		std::cout << "\n\nYou have " << (МАХ_WRONG_ERRORS - wrong);
		std::cout << " incorrect guesses left. \n";
		std::cout << "\nYou've used the following letters;\n" << used << std::endl;
		std::cout << "\nSo far. the word is;\n" << soFar << std::endl;

		char guess;
		std::cout << "\n\nEnter your guess; ";
		std::cin >> guess;

		guess = toupper(guess); // перевод в верхний регистр, так как загаданное слово записано в верхнем регистре.

		while (used.find(guess) != std::string::npos) {
			std::cout << "\nYou've already guessed " << guess << std::endl;
			std::cout << "Enter your guess; ";
			std::cin >> guess;
			guess = toupper(guess);
		}

		used += guess;

		if (THE_WORD.find(guess) != std::string::npos) {
			std::cout << "That's right! " << guess << " is in the word.\n";
			// обновить переменную soFar, включив в нее новую угаданную букву
			for (int i = 0; i < THE_WORD.length(); ++i) {
				if (THE_WORD[i] == guess) {
					soFar[i] = guess;
				}
			}
		}
		else {
			std::cout << "Sorry. "<< guess <<" isn't in the word.\n";
			++wrong;
		}
	}

	// конец игры
	if (wrong == МАХ_WRONG_ERRORS) {
		std::cout << "\nYou've been hanged!";
	}
	else {
		std::cout << "\nYou guessed it!";
	}

	std::cout << "\nThe word was " << THE_WORD << std::endl;
	
	system("pause");
	return 0;
}
