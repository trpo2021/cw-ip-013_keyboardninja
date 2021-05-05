#include <SFML/Graphics.hpp>
#include "helper.h"
#include <iostream>
#include <string>

My_Sprite::My_Sprite(std::string fname, int x, int y)
{
    m_filename = fname;
    m_coordinate_x = x;
    m_coordinate_y = y;
    m_texture.loadFromFile("src/images/" + m_filename);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(x, y);
}


My_Sprite::My_Sprite(std::string fname, int x, int y, float W, float H)
{
    m_filename = fname;
    m_coordinate_x = x;
    m_coordinate_y = y;
    m_width = W;
    m_Height = H;
    m_texture.loadFromFile("src/images/" + m_filename);
    m_sprite.setTextureRect(sf::IntRect(m_width, m_Height, m_width, m_Height));
}

void My_Sprite::Get_sprite(sf::Sprite& sprite)
{
    sprite = m_sprite;
}

// void My_Sprite::Move(float time){

// }
