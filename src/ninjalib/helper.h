#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <list>
#include <sstream>
#include <string>

namespace help {
// const int count_images = 17;
const int line_count = 3;
const int string_columns = 3;
}

class My_Sprite {
private:
    sf::Texture m_texture;

public:
    My_Sprite();
    My_Sprite(std::string fname);
    My_Sprite(std::string str_info[]);
    void Add_Letter(sf::Texture& fname, float x, float y, float W, float H);
    void Add_method1(std::string fname);
    sf::Texture& Get_Texture();
    sf::Sprite& Get_sprite();

protected:
    float m_coordinate_x{}, m_coordinate_y{}, m_width{}, m_Height{};
    sf::Sprite m_sprite;
};

struct Difficult {
    float m_boost, m_start_speed /*, m_time*/;
    unsigned short m_barrier;

    Difficult(float boost = 0.2, float speed = 0.2, unsigned short barrier = 4)
        : m_boost(boost), m_start_speed(speed), m_barrier(barrier)
    {

    }
    void Diff_choose(float boost, float speed, unsigned short barrier)
    {
        m_boost = boost;
        m_start_speed = speed;
        m_barrier = barrier;
    }
};

enum M_Sprite {
    SPR_BG,
    SPR_START,
    SPR_ABOUT,
    SPR_SCORE_MENU,
    SPR_EXIT,
    SPR_RULES,
    SPR_DIFF,
    SPR_SHOWSCORE,
    SPR_PAUSE,
    SPR_HP,
    SPR_MENU_PAUSE,
    SPR_LETTERS,
    SPR_DEAD_MENU,
    SPR_DM_REPLAY,
    SPR_DM_GOTOMENU,
    SPR_DM_EXIT,
    SPR_GAME_BG_1,
    SPR_GAME_BG_2,
    SPR_GAME_BG_3,
    SPR_GAME_BG_4,
    SPR_GAME_BG_5,
    SPR_GAME_BG_6,
    SPR_GAME_BG_7,
    SPR_GAME_BG_8
};
