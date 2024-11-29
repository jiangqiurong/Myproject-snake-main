#include "leaderboard.hpp"
#include <fstream>
#include <iostream>

void Leaderboard::addScore(int score) {
    scores.push_back(score);
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    
    if (scores.size() > MAX_ENTRIES) {
        scores.resize(MAX_ENTRIES);
    }
}

void Leaderboard::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& score : scores) {
        file << score << std::endl;
    }
}

void Leaderboard::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    int score;
    scores.clear();
    while (file >> score) {
        addScore(score);
    }
}


void Leaderboard::drawText(int x, int y, const std::string& text, const Color& color) const {
    for (char c : text) {
        if (c >= '0' && c <= '9') {
            const uint8_t* charData = font[c - '0'];
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 8; j++) {
                    if (charData[i] & (1 << (7 - j))) {
                        Screen::getInstance().drawPoint(x + j, y + i, color);
                    }
                }
            }
            x += 8; // 移动到下一个字符位置
        } else {
            x += 8; // 对于非数字字符，只移动位置
        }
    }
}



void Leaderboard::draw(int x, int y) const {
    Color textColor(255, 255, 255); // 白色文本
    drawText(x, y, "Leaderboard:", textColor);
    y += 20; // 移动到下一行

    for (size_t i = 0; i < scores.size() && i < 5; ++i) {
        std::string score_str = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
        drawText(x, y, score_str, textColor);
        y += 20; // 移动到下一行
    }
}


void Leaderboard::loadAndSortScores() {
    loadFromFile("./scores.txt");
    std::sort(scores.begin(), scores.end(), std::greater<int>());
}

