#pragma once
#include <SFML/Graphics.hpp>

#include "helper.h"

int main_menu(
        sf::RenderWindow& window,
        Difficult& difficulty,
        sf::Text txt_score,
        std::vector<My_Sprite*>& _static_spr_mas);
