#pragma once
#include <SFML/Graphics.hpp>

#include "helper.h"

#include <iostream>
#include <list>

class Letters : public My_Sprite {
private:
    int m_code_key;
    int m_code_letters[26] = {16, 22, 4, 17, 19, 24, 20, 8,  14, 15, 0, 18, 3,
                              5,  6,  7, 9,  10, 11, 25, 23, 2,  21, 1, 13, 12};
    bool m_bomb;
    int m_number_key;

public:
    Letters(bool isBomb, sf::Texture& fname, float x, float y)
    {
        m_bomb = isBomb;
        m_number_key = rand() % 26;
        m_code_key = m_code_letters[m_number_key];

        if (isBomb) {
            m_number_key += 26;
        }

        m_coordinate_x = x;
        m_coordinate_y = y;
        x = static_cast<float>((m_number_key) % 9) * 91;
        y = static_cast<float>((m_number_key) / 9) * 138;
        Add_Letter(fname, x, y, 86, 128);
    }

    Letters(int x = 0, int y = 950, int code = 22, bool bomb = 0)
    {
        m_coordinate_y = y;
        m_coordinate_x = x;
        m_bomb = bomb;
        m_code_key = code;
    }

    int Get_key();
    int Get_coordinate_x();
    int Get_coordinate_y();
    bool Delete_letter_beyond(int coordinate_y, int hp);
    bool Check_code_key(int key, int& score, int& change_speed);
    bool Isbomb();
    void
    Update(sf::Sprite& sprite,
           Difficult& dif,
           int score,
           float time,
           int& change_speed);
};

void Lose_health(My_Sprite*& static_spr_mas, int& hp);

void Press_button(
        std::list<Letters*>& list_letters,
        int& hp,
        int& score,
        My_Sprite*& static_spr_mas,
        int code,
        int& change_speed);
