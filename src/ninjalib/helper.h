#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

using namespace sf;

bool Select(int select, int& ShowDiff, int& ShowRules, int& ShowScores);

namespace help {
const int count_images = 13;
const int line_count = 3;
const int string_columns = 3;
}

class My_Sprite {
private:
    std::stringstream m_str_stream;

public:
    sf::Sprite m_sprite;

    My_Sprite();
    void Add_Letter(std::string fname, float x, float y, float W, float H);
    void Add_method(std::string str_info[]);
    void Add_method1(std::string fname);

    void Get_sprite(sf::Sprite& sprite);

protected:
    std::string m_filename;
    float m_coordinate_x{}, m_coordinate_y{}, m_width{}, m_Height{};
    sf::Texture m_texture;
};

struct Difficult {
    double m_boost, m_start_speed;
    int m_barrier;

    Difficult(double boost = 0.2, double speed = 0.2, int barrier = 4)
        : m_boost(boost), m_start_speed(speed), m_barrier(barrier)
    {
    }
    void Diff_choose(double boost, double speed, int barrier)
    {
        m_boost = boost;
        m_start_speed = speed;
        m_barrier = barrier;
    }
};

class Letters : public My_Sprite {
private:
    int code_key;
    int code_letters[26] = {16, 22, 4, 17, 19, 24, 20, 8,  14, 15, 0, 18, 3,
                            5,  6,  7, 9,  10, 11, 25, 23, 2,  21, 1, 13, 12};
    bool bomb;
    int number_key;

public:
    void Check_code_key(int key, int& hp, int& score, Sprite& spr_hp)
    {
        bool del = 0;
        if (!bomb) {
            if (code_key == key)
                score += 5;
            else
                del = 1;
        } else
            del = 1;

        if (del) {
            hp--;
            spr_hp.setTextureRect(IntRect(0, 0, 80, 68 * hp));
        }
    }

    void Get_Letter(bool isBomb, std::string fname, float x, float y)
    {
        bomb = isBomb;
        if (!isBomb)
            number_key = rand() % 26;
        else
            number_key = rand() % (51 - 26 + 1) + 26;
        m_coordinate_x = x;
        m_coordinate_y = y;
        std::cout << "Key number " << number_key << "\n";
        x = ((number_key) % 9) * 91;
        std::cout << x << " ";
        y = ((number_key) / 9) * 138;
        std::cout << y;
        Add_Letter(fname, x, y, 86, 128);
        if (number_key < 26)
            code_key = code_letters[number_key];
        else
            code_key = code_letters[number_key - 26];
    }

    Sprite Move_letter(sf::Sprite sprite, Difficult dif)
    {
        sprite.setPosition(m_coordinate_x, m_coordinate_y);
        m_coordinate_y += dif.m_start_speed;
        // dif.m_start_speed += dif.m_boost;
        return sprite;
    }
};

enum M_Sprite {
    SPR_START,
    SPR_ABOUT,
    SPR_SCORE_MENU,
    SPR_EXIT,
    SPR_BG,
    SPR_RULES,
    SPR_DIFF,
    SPR_SHOWSCORE,
    SPR_PAUSE,
    SPR_HP,
    SPR_GAME_BG,
    SPR_MENU_PAUSE,
    SPR_LETTERS
};