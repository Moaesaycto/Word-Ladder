#include "word_ladder.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>

// HELPER FUNCTIONS

// Clean up lexicon based on desired length
std::unordered_set<std::string> filter_lexicon_by_length(
	std::size_t length,
	const std::unordered_set<std::string> &lexicon) {
    std::unordered_set<std::string> filtered_lexicon;
    
    for (const auto& word : lexicon) {
        if (word.length() == length) {
            filtered_lexicon.insert(word);
        }
    }
    
    return filtered_lexicon;
}

// Generate neighbouring words
std::vector<std::string> generate_neighbours(
	const std::string &word, 
	const std::unordered_set<std::string> &lexicon) {
	
	std::vector<std::string> neighbours;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	for (std::size_t i = 0; i < word.length(); ++i) {	// Change one letter at a time and see
        std::string modified_word = word;				// if it is a valid word. O(1) avg lookup

        for (char c : alphabet) {
            if (word[i] != c) {
                modified_word[i] = c;
                if (lexicon.find(modified_word) != lexicon.end()) {
                    neighbours.push_back(modified_word);
                }
            }
        }
    }
	return neighbours;
}

// Returns paths
std::vector<std::vector<std::string>> find_paths(
    const std::string &start,
    const std::string &end,
    const std::unordered_map<std::string, std::vector<std::string>> &predecessors) {
    if (start == end) {
        return {{start}};
    }
    if (predecessors.find(end) == predecessors.end()) {
        return {}; // No path found
    }
    std::vector<std::vector<std::string>> paths;
    for (const auto &pred : predecessors.at(end)) {
        auto partial_paths = find_paths(start, pred, predecessors);
        for (auto &path : partial_paths) {
            path.push_back(end);
            paths.push_back(path);
        }
    }
    return paths;
}

auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
	std::unordered_set<std::string> lexicon;
    std::ifstream file(path);

    if (!file.is_open()) {
        return lexicon;
    }

    std::string word;
    while (file >> word) {
        lexicon.insert(word);
    }

    file.close();
    return lexicon;
}

auto word_ladder::generate(
    const std::string &from,
    const std::string &to,
    const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {

    // Ensure words are of the same length
    if (from.length() != to.length()) {
        return {};
    }

    // Ensure that words are in the lexicon
    if (lexicon.find(from) == lexicon.end() || lexicon.find(to) == lexicon.end()) {
        return {};
    }

    // Case for when the words are teh same
    if (from == to) {
        return {{from}};
    }

    auto filtered_lexicon = filter_lexicon_by_length(from.length(), lexicon);
    std::queue<std::string> q;
    std::unordered_map<std::string, std::vector<std::string>> predecessors;
    std::unordered_set<std::string> visited;
    visited.insert(from);
    q.push(from);

    bool found = false;
    while (!q.empty() && !found) {
        int level_size = static_cast<int> (q.size());
        std::unordered_set<std::string> this_level_visited;

        for (int i = 0; i < level_size; ++i) {
            std::string current = q.front();
            q.pop();

            std::vector<std::string> neighbours = generate_neighbours(current, filtered_lexicon);
            for (const std::string &neighbour : neighbours) {
                if (visited.find(neighbour) == visited.end() || this_level_visited.find(neighbour) != this_level_visited.end()) {
                    if (this_level_visited.find(neighbour) == this_level_visited.end()) {
                        q.push(neighbour);
                        this_level_visited.insert(neighbour);
                    }
                    predecessors[neighbour].push_back(current);
                    if (neighbour == to) {
                        found = true;
                    }
                }
            }
        }
        if (!found) {
            visited.insert(this_level_visited.begin(), this_level_visited.end());
        }
    }

    auto paths = find_paths(from, to, predecessors);
    sort(paths.begin(), paths.end());

    return paths;
}
