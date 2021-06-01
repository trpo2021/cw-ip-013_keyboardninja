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

struct Player {
    int m_score;
    int m_hp;
    Player(int score = 0, int hp = 3) : m_score(score), m_hp(hp)
    {
    }
    void update_hp(sf::Sprite& SPR_hp, int hp)
    {
        SPR_hp.setTextureRect(sf::IntRect(0, 0, 80, 68 * hp));
    }
};

struct Difficult {
    float m_boost = 0.01, m_start_speed, m_start_speed_inf, m_letter_ger;
    int m_bomb_ger, m_regen;
    unsigned short m_choice, m_barrier;

    Difficult(
            float speed = 0.2,
            unsigned short barrier = 10,
            float letter_ger = 1000,
            int bomb_ger = 5,
            int regen = 200,
            unsigned short choise = 0)
        : m_start_speed(speed),
          m_start_speed_inf(speed),
          m_letter_ger(letter_ger),
          m_bomb_ger(bomb_ger),
          m_regen(regen),
          m_choice(choise),
          m_barrier(barrier)
    {
    }
    void Diff_choose(
            float speed,
            int barrier,
            float letter_ger,
            int bomb_ger,
            int regen,
            unsigned short choise)
    {
        m_letter_ger = letter_ger;
        m_bomb_ger = bomb_ger;
        m_regen = regen;
        m_start_speed = speed;
        m_start_speed_inf = speed;
        m_barrier = barrier;
        m_choice = choise;
    }

    void Reset_speed()
    {
        m_start_speed = m_start_speed_inf;
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

void scoreInput(sf::Text txt_score, sf::RenderWindow& window);
void scoreOutput(int score, int choice);
