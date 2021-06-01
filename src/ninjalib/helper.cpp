#include "helper.h"
#include "letters.h"

#include <SFML/Graphics.hpp>

#include <ctime>
#include <fstream>
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

void scoreInput(sf::Text txt_score, sf::RenderWindow& window)
{
    std::string mass;

    txt_score.setCharacterSize(90);

    std::ifstream fs("src/ninja/score.txt", std::ios::in | std::ios::binary);

    if (!fs)
        std::cout << "File open error!" << std::endl;

    for (int r = 0; r < help::line_count; r++) {
        fs >> mass;
        std::ostringstream char_score;
        char_score << mass;
        txt_score.setString(char_score.str());
        txt_score.setPosition(750, 340 + (r * 135));
        window.draw(txt_score);
    }
    fs.close();
}

void scoreOutput(int score, int choice)
{
    int sc[3];
    std::stringstream m_str_stream;
    std::string mass;

    std::ifstream fs("src/ninja/score.txt", std::ios::in);

    if (!fs)
        std::cout << "File open error!" << std::endl;
    for (int i = 0; i < help::line_count; i++) {
        fs >> mass;
        m_str_stream << mass;
        m_str_stream >> sc[i];
        m_str_stream.str("");
        m_str_stream.clear();
    }
    fs.close();

    std::ofstream fc("src/ninja/score.txt", std::ios::out | std::ios::trunc);

    if (sc[choice] < score)
        sc[choice] = score;
    for (int i = 0; i < help::line_count; i++)
        fc << sc[i] << " ";
    fc.close();
}