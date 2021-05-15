#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <list>

using namespace sf;

namespace help {
	//const int count_images = 13;
	const int line_count = 3;
	const int string_columns = 3;
}

class My_Sprite {
private:
	std::stringstream m_str_stream;
public:
	My_Sprite();
	My_Sprite(std::string fname);
	My_Sprite(std::string str_info[]);
	void Add_Letter(sf::Texture &fname, float x, float y, float W, float H);
	void Add_method1(std::string fname);
	void Get_Sprite(sf::Sprite& sprite);
	sf::Texture& Get_Texture();
	sf::Sprite& Get_sprite();
protected:
	float m_coordinate_x{}, m_coordinate_y{}, m_width{},
		m_Height{}; // x и y определяют положение спрайта
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


struct Difficult {
	float m_boost, m_start_speed/*, m_time*/;
	int m_barrier;
	 
	Difficult(float boost = 0.2, float speed = 0.2, int barrier = 4) : m_boost(boost), m_start_speed(speed), m_barrier(barrier) {}
	void Diff_choose(float boost, float speed, int barrier) {
		m_boost = boost;
		m_start_speed = speed;
		m_barrier = barrier;
	}

        void Diff_choose(double boost, double speed, int barrier)
    {
        m_boost = boost;
        m_start_speed = speed;
        m_barrier = barrier;
    }

};


class Letters : public My_Sprite {
private:
	int m_code_key;
	int m_code_letters[26] = { 16,22,4,17,19,24,20,8,14,15,0,18,3,5,6,7,9,10,11,25,23,2,21,1,13,12 };
	bool m_bomb;
	int m_number_key;

public:

	Letters(bool isBomb, sf::Texture &fname, float x, float y) {
		m_bomb = isBomb;
		m_number_key = rand() % 26;
		m_code_key = m_code_letters[m_number_key];

		if (isBomb) {
			m_number_key += 26;
		}

		m_coordinate_x = x;
		m_coordinate_y = y;
		std::cout << "Key number " << m_number_key << "\n";
		x = static_cast<float>((m_number_key) % 9) * 91;
		/*	std::cout << x << " ";*/
		y = static_cast<float>((m_number_key) / 9) * 138;
		//std::cout << y;

		Add_Letter(fname, x, y, 86, 128);
	}

	bool Delete_letter_beyond(Letters* letter);
	bool Check_code_key(int key, int& score);
	bool Isbomb();
	sf::Sprite Move_letter(sf::Sprite sprite, Difficult dif);
};

void Press_button(std::list <Letters*> &list_letters, int &hp, int &score, std::vector <My_Sprite*> &static_spr_mas, int code);


enum M_Sprite {
	SPR_START,
	SPR_ABOUT,
	SPR_SCORE_MENU,
	SPR_EXIT,
	SPR_BG,
	SPR_RULES,
	SPR_DIFF,
	SPR_SHOWSCORE,
	SPR_PAUSE,
	SPR_HP,
	SPR_GAME_BG,
	SPR_MENU_PAUSE,
	SPR_LETTERS
};

