#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace help {
const int count_images = 15;
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
    // void Move(float time);
protected:
    std::string m_filename;
    float m_coordinate_x{}, m_coordinate_y{}, m_width{},
            m_Height{}; // x и y определяют положение спрайта
    sf::Texture m_texture;
};

struct Difficult {
    float m_boost, m_start_speed;
    int m_barrier;

    Difficult(float boost = 0.2, float speed = 0.2, int barrier = 4)
        : m_boost(boost), m_start_speed(speed), m_barrier(barrier)
    {
    }
    void Diff_choose(float boost, float speed, int barrier)
    {
        m_boost = boost;
        m_start_speed = speed;
        m_barrier = barrier;
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
    SPR_HP1,
    SPR_HP2,
    SPR_HP3,
    SPR_GAME_BG,
    SPR_MENU_PAUSE,
    SPR_LETTERS
};