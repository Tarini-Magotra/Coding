#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cctype>

// Function to display hangman visuals based on the remaining lives
void displayHangman(int lives) {
    // Visual representations for different stages of hangman
    const std::vector<std::string> hangmanVisuals = {
        "  +---+\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========",
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========",
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "=========",
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|   |\n"
        "      |\n"
        "      |\n"
        "=========",
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        "      |\n"
        "      |\n"
        "=========",
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " /    |\n"
        "      |\n"
        "=========",
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " / \\  |\n"
        "      |\n"
        "========="
    };

    if (lives >= 0 && lives < hangmanVisuals.size()) {
        std::cout << hangmanVisuals[lives] << std::endl;
    }
}

std::string get_valid_word(const std::vector<std::string>& words) {
    std::string word;
    do {
        word = words[rand() % words.size()];
    } while (word.find('-') != std::string::npos || word.find(' ') != std::string::npos);

    for (char& c : word) {
        c = std::toupper(c);
    }

    return word;
}

void hangman() {
    srand(static_cast<unsigned int>(time(nullptr)));

    const std::vector<std::string> words = {"apple", "banana", "cherry", "orange", "grape", "kiwi"};

    std::string word = get_valid_word(words);
    std::set<char> word_letters(word.begin(), word.end());
    std::set<char> alphabet;
    for (char c = 'A'; c <= 'Z'; ++c) {
        alphabet.insert(c);
    }
    std::set<char> used_letters;

    int lives = 6; // Set initial lives to match the hangmanVisuals size

    // Getting user input
    while (!word_letters.empty() && lives > 0) {
        // Letters used
        std::cout << "You have " << lives << " lives left and you have used these letters: ";
        for (const auto& letter : used_letters) {
            std::cout << letter << " ";
        }
        std::cout << std::endl;

        // What the current word is (i.e., W - R D)
        for (const auto& letter : word) {
            if (used_letters.find(letter) != used_letters.end()) {
                std::cout << letter << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;

        // Display hangman visuals
        displayHangman(lives);

        char user_letter;
        std::cout << "Guess a letter: ";
        std::cin >> user_letter;
        user_letter = std::toupper(user_letter);

        if (alphabet.find(user_letter) != alphabet.end() && used_letters.find(user_letter) == used_letters.end()) {
            used_letters.insert(user_letter);
            if (word_letters.find(user_letter) != word_letters.end()) {
                word_letters.erase(user_letter);
            } else {
                lives--;
                std::cout << "\nYour letter, " << user_letter << ", is not in the word." << std::endl;
            }
        } else if (used_letters.find(user_letter) != used_letters.end()) {
            std::cout << "\nYou have already used that letter. Guess another letter." << std::endl;
        } else {
            std::cout << "\nThat is not a valid letter." << std::endl;
        }
    }

    // Gets here when len(word_letters) == 0 or when lives == 0
    if (lives == 0) {
        std::cout << "You died, sorry. The word was " << word << std::endl;
    } else {
        std::cout << "YAHOO! You guessed the word " << word << "!!" << std::endl;
    }
}

int main() {
    hangman();
    return 0;
}