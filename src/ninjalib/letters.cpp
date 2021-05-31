#include <SFML/Graphics.hpp>

#include "letters.h"

#include <iostream>
#include <list>

int Letters::Get_key()
{
    return m_code_key;
}

bool Letters::Check_code_key(int key, int& score)
{
    if (m_code_key == key) {
        if (!m_bomb)
            score += 5;

        return true;
    }

    return false;
}

bool Letters::Isbomb()
{
    return m_bomb;
}

void Lose_health(My_Sprite& static_spr_mas, int& hp)
{
    hp--;
    static_spr_mas.Get_sprite().setTextureRect(
            sf::IntRect(0, 0, 80, 68 * hp)); // function lose health
}

void Press_button(
        std::list<Letters*>& list_letters,
        int& hp,
        int& score,
        My_Sprite& static_spr_mas,
        int code)
{
    for (std::list<Letters*>::iterator it = list_letters.begin(),
                                       end = list_letters.end(),
                                       tmp = it;
         it != list_letters.end();) {
        tmp++;
        if ((tmp == end && !(*it)->Check_code_key(code, score))
            or ((*it)->Isbomb() and (*it)->Check_code_key(code, score))) {
            Lose_health(static_spr_mas, hp);
        }

        if ((*it)->Check_code_key(code, score)) {
            delete *it;
            it = list_letters.erase(it);
            break;
        } else
            it++;
    }
}

void Letters::Update(sf::Sprite& sprite, Difficult& dif, float time)
{
    m_coordinate_y += dif.m_start_speed * time;
    dif.m_start_speed += dif.m_boost;
    sprite.setPosition(m_coordinate_x, m_coordinate_y);
}

bool Letters::Delete_letter_beyond(
        Letters* letter, My_Sprite& static_spr_mas, int hp)
{
    if (letter->m_coordinate_y >= 960) {
        // if(!(letter->Isbomb()))
        //     Lose_health(static_spr_mas, hp);
        return true;
    }

    return false;
}