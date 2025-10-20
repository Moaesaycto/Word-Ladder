#include "word_ladder.h"

#include <iostream>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
    // Empty main function for submission
    return 0;
}


/* auto main(int argc, char* argv[]) -> int { // CHANGE BACK TO MAIN WHEN YOU FINISH!!!
	if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <word1> <word2>" << std::endl;
        return 1;
    }

	std::string from = argv[1];
    std::string to = argv[2];

    auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
    auto const ladders = word_ladder::generate(from, to, english_lexicon);
    for (const auto& ladder : ladders) {
        for (const auto& word : ladder) {
            std::cout << word << " -> ";
        }
        std::cout << "DONE" << std::endl;
    }

    return 0;
}
 */