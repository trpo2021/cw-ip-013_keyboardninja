#pragma once
#include <string>


namespace sprite{
    const int count_main_menu = 8;
}



class My_Sprite {
    
private:
    float m_coordinate_x, m_coordinate_y, m_width,
    m_Height; // x и y определяют положение спрайта
    std::string m_filename;
    sf::Image m_image;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

public:
    My_Sprite(std::string fname, int x, int y);
    My_Sprite(std::string fname, int x, int y, float W, float H);

    void Get_sprite(sf::Sprite& sprite);
    // void Move(float time);
};

class Letters {

};