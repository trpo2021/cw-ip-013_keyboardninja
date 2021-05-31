#include <SFML/Graphics.hpp>

#include "helper.h"
#include "letters.h"

#include <iostream>
#include <list>


void Create_letters(std::list<Letters*>& A, int x, int y)
{
    
    My_Sprite B("letters_tex.png");
    for (int i = 0, swing; i < 3; i++) {
        A.push_back(new Letters(swing, B.Get_Texture(), x, y));
        swing = 1 - swing;
    }

    for (std::list<Letters*>::iterator it = A.begin(); it != A.end(); ++it)
        std::cout << (*it)->Get_key();
}