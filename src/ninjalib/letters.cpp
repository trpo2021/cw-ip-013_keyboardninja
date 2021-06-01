#include <SFML/Graphics.hpp>

#include "letters.h"

#include <iostream>
#include <list>

int Letters::Get_key()
{
    return m_code_key;
}

int Letters::Get_coordinate_x()
{
    return m_coordinate_x;
}

int Letters::Get_coordinate_y()
{
    return m_coordinate_x;
}

bool Letters::Check_code_key(int key, int& score, int& change_speed)
{
    if (m_code_key == key) {
        if (!m_bomb) {
            score += 5;
            change_speed = 1;
        }
        return true;
    }
    return false;
}

bool Letters::Isbomb()
{
    return m_bomb;
}

void Lose_health(My_Sprite*& static_spr_mas, int& hp)
{
    hp--;
    static_spr_mas->Get_sprite().setTextureRect(
            sf::IntRect(0, 0, 80, 68 * hp)); // function lose health
}

void Press_button(
        std::list<Letters*>& list_letters,
        int& hp,
        int& score,
        My_Sprite*& static_spr_mas,
        int code,
        int& change_speed)
{
    for (std::list<Letters*>::iterator it = list_letters.begin(),
                                       end = list_letters.end(),
                                       tmp = it;
         it != list_letters.end();) {
        tmp++;
        if ((tmp == end && !(*it)->Check_code_key(code, score, change_speed))
            or ((*it)->Isbomb()
                and (*it)->Check_code_key(code, score, change_speed))) {
            Lose_health(static_spr_mas, hp);
        }

        if ((*it)->Check_code_key(code, score, change_speed)) {
            delete *it;
            it = list_letters.erase(it);
            break;
        } else
            it++;
    }
}

void Letters::Update(
        sf::Sprite& sprite,
        Difficult& dif,
        int score,
        float time,
        int& change_speed)
{
    m_coordinate_y += dif.m_start_speed * time;
    if (score % 50 == 0 && score && change_speed && dif.m_start_speed <= 0.59) {
        dif.m_start_speed += dif.m_boost;
        change_speed = 0;
    }
    sprite.setPosition(m_coordinate_x, m_coordinate_y);
}

bool Letters::Delete_letter_beyond(int coordinate_y, int hp)
{
    if (m_coordinate_y >= 960)
        return true;

    return false;
}
