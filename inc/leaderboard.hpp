#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <vector>
#include <algorithm>
#include "screen.hpp"
#include "color.hpp"
#include "font.hpp"

class Leaderboard {
private:
    std::vector<int> scores;
    const int MAX_ENTRIES = 10;

public:
    void addScore(int score);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::vector<int> getTopScores() const;
    void display() const;
    void drawText(int x, int y, const std::string& text, const Color& color) const;
    void draw(int x, int y) const;
    void loadAndSortScores();
    int getRank(int score) const;
};

#endif 
