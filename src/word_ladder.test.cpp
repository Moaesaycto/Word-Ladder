#include "word_ladder.h"

#include "word_ladder.h"
#include <catch2/catch.hpp>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>

std::unordered_set<std::string> global_lexicon;

TEST_CASE("word_ladder::read_lexicon works as expected") {
    global_lexicon = word_ladder::read_lexicon("english.txt");

    CHECK(global_lexicon.find("spoon") != global_lexicon.end());
    CHECK(global_lexicon.find("spaghetti") != global_lexicon.end());
    CHECK(global_lexicon.find("egg") != global_lexicon.end());
}

TEST_CASE("at -> it") {
	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "it"}
	};

	auto const ladders = word_ladder::generate("at", "it", global_lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("word_ladder::generate returns empty with different length words") {

    auto const ladders = word_ladder::generate("cat", "doggy", global_lexicon);

    CHECK(ladders.empty());
}

TEST_CASE("word_ladder::generate with same words") {
    const auto expected = std::vector<std::vector<std::string>>{
        {"at"}
    };

    auto const ladders = word_ladder::generate("at", "at", global_lexicon);

    CHECK(ladders == expected);
}

TEST_CASE("word_ladder::generate - awake to sleep") {
    auto expected = std::vector<std::vector<std::string>>{
        {"awake", "aware", "sware", "share", "sharn", "shawn", "shewn", "sheen", "sheep", "sleep"},
        {"awake", "aware", "sware", "share", "shire", "shirr", "shier", "sheer", "sheep", "sleep"}
    };

    auto ladders = word_ladder::generate("awake", "sleep", global_lexicon);

    CHECK(ladders == expected);
}

TEST_CASE("word_ladder::generate - airplane to tricycle (no answer)") {
    auto ladders = word_ladder::generate("airplane", "tricycle", global_lexicon);

    CHECK(ladders.empty());
}

TEST_CASE("word_ladder::generate - work to play (multiple known paths)") {
    auto expected = std::vector<std::vector<std::string>>{
        {"work", "fork", "form", "foam", "flam", "flay", "play"},
        {"work", "pork", "perk", "peak", "pean", "plan", "play"},
        {"work", "pork", "perk", "peak", "peat", "plat", "play"},
        {"work", "pork", "perk", "pert", "peat", "plat", "play"},
        {"work", "pork", "porn", "pirn", "pian", "plan", "play"},
        {"work", "pork", "port", "pert", "peat", "plat", "play"},
        {"work", "word", "wood", "pood", "plod", "ploy", "play"},
        {"work", "worm", "form", "foam", "flam", "flay", "play"},
        {"work", "worn", "porn", "pirn", "pian", "plan", "play"},
        {"work", "wort", "bort", "boat", "blat", "plat", "play"},
        {"work", "wort", "port", "pert", "peat", "plat", "play"},
        {"work", "wort", "wert", "pert", "peat", "plat", "play"}
    };

    auto ladders = word_ladder::generate("work", "play", global_lexicon);

    CHECK(ladders == expected);
}