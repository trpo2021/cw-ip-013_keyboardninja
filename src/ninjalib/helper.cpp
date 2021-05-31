#include "helper.h"

#include <SFML/Graphics.hpp>

#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>

My_Sprite::My_Sprite()
{
}

My_Sprite::My_Sprite(std::string fname)
{
    Add_method1(fname);
}

void My_Sprite::Add_method1(std::string fname)
{
    m_texture.loadFromFile("src/images/" + fname);
    m_sprite.setTexture(m_texture);
}

My_Sprite::My_Sprite(std::string str_info[]) : My_Sprite(str_info[0])
{
    float coordinate[2];
    std::stringstream m_str_stream;

    for (int i = 0, j = 1; i < 2; i++) {
        m_str_stream << str_info[j++];
        m_str_stream >> coordinate[i];
        m_str_stream.str(std::string());
        m_str_stream.clear();
    }
    m_coordinate_x = coordinate[0];
    m_coordinate_y = coordinate[1];
    m_sprite.setPosition(coordinate[0], coordinate[1]);
}

sf::Sprite& My_Sprite::Get_sprite()
{
    return m_sprite;
}

sf::Texture& My_Sprite::Get_Texture()
{
    return m_texture;
}

void My_Sprite::Add_Letter(
        sf::Texture& fname, float x, float y, float W, float H)
{
    m_width = W;
    m_Height = H;
    m_sprite.setTexture(fname);
    m_sprite.setTextureRect(sf::IntRect(x, y, W, H));
    m_sprite.setPosition(m_coordinate_x, m_coordinate_y);
}