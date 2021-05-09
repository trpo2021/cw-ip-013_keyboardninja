#include "helper.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

My_Sprite::My_Sprite()
{
}

void My_Sprite::Get_sprite(sf::Sprite& sprite)
{
    sprite = m_sprite;
}

void My_Sprite::Add_method1(std::string fname)
{
    m_filename = fname;
    m_texture.loadFromFile("src/images/" + m_filename);
    m_sprite.setTexture(m_texture);
}

void My_Sprite::Add_method(std::string str_info[])
{
    float coordinate[2];
    int j = 1;

    m_filename = str_info[0];
    for (int i = 0; i < 2; i++) {
        m_str_stream << str_info[j++];

        m_str_stream >> coordinate[i];
        m_str_stream.str(std::string());
        m_str_stream.clear();
    }
    m_coordinate_x = coordinate[0];
    m_coordinate_y = coordinate[1];
    m_texture.loadFromFile("src/images/" + m_filename);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(coordinate[0], coordinate[1]);
    /* vect.push_back(m_sprite);*/
}

void My_Sprite::Add_Letter(
        std::string fname, float x, float y, float W, float H)
{
    m_filename = fname;
    m_width = W;
    m_Height = H;
    m_texture.loadFromFile("src/images/" + m_filename);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(x, y, W, H));
    m_sprite.setPosition(m_coordinate_x, m_coordinate_y);
}
