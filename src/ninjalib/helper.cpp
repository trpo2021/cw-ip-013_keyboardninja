#include "helper.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <iterator>

My_Sprite::My_Sprite() {}

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

void My_Sprite::Get_Sprite(sf::Sprite &sprite) 
{
    sprite = m_sprite;
}

sf::Texture& My_Sprite::Get_Texture() {
	return m_texture;
}

void My_Sprite::Add_Letter(sf::Texture &fname, float x, float y, float W, float H)
{
    m_width = W;
    m_Height = H;
	m_sprite.setTexture(fname);
    m_sprite.setTextureRect(sf::IntRect(x, y, W, H));
    m_sprite.setPosition(m_coordinate_x, m_coordinate_y);
}

bool Letters::Check_code_key(int key, int& score) {

	if (m_code_key == key) {
		if (!m_bomb) {
			score += 5;
			return true;
		}
		else 
			return true;
	}
	return false;
}

bool Letters::Isbomb() {
	
	return m_bomb;
}

void Press_button(std::list <Letters*> &list_letters, int &hp, int &score, std::vector <My_Sprite*> &static_spr_mas, int code) {
	int t = 1;
	for (std::list <Letters*>::iterator it = list_letters.begin(), end = list_letters.end(), tmp = it ; it != list_letters.end();t++) {

		tmp++;
		if ((tmp == end && !(*it)->Check_code_key(code, score)) or ((*it)->Isbomb() and (*it)->Check_code_key(code, score))) {
			hp--;
			static_spr_mas[SPR_HP]->Get_sprite().setTextureRect(sf::IntRect(0, 0, 80, 68 * hp)); // Функция потери жизни	
		}

		if ((*it)->Check_code_key(code, score)) {
			delete* it;
			it = list_letters.erase(it);
			break;
		}
		else
			it++;
	}
}

sf::Sprite Letters::Move_letter(sf::Sprite sprite, Difficult dif) {
	sprite.setPosition(m_coordinate_x, m_coordinate_y);
	m_coordinate_y += dif.m_start_speed;
	dif.m_start_speed += dif.m_boost;
	return sprite;
}

bool Letters::Delete_letter_beyond(Letters* letter)
{
	if (letter->m_coordinate_y >= 960) {
		return true;
	}
	return false;
}