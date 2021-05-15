#include <SFML/Graphics.hpp>

#include "ninjalib/helper.h"
#include "ninjalib/main_menu.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

bool start_game(int& showMenu)
{
    srand(static_cast<unsigned int>(time(0)));
    using namespace sf;

    float timer = 0;
    float deley = 1;
    Clock clock;

    std::ifstream inf_images("src/ninja/images_names.txt");
    std::string str[help::line_count];
    if (!(inf_images.is_open())) {
        inf_images.close();
        std::cerr << "Ошибка: файл не открылся";
        exit(1);
    }

    std::vector<My_Sprite*> static_spr_mas;
    for (int j = 0; inf_images; j++) {
        for (int i = 0; i < 3; i++) {
            inf_images >> str[i];
            if (isalpha(str[1][0])) {
                static_spr_mas.push_back(new My_Sprite(str[0]));
                swap(str[0], str[1]);
                i--;
                j++;
            }
        }
        static_spr_mas.push_back(new My_Sprite(str));
    }
    inf_images.close();

    RenderWindow window(VideoMode(1536, 960), "KeyBoardNinja");

    int isPause = 0, hp = 3;

    Difficult difficult;

    if (!main_menu(window, difficult, static_spr_mas))
        return 0;

    int press_count = 0;
    int bomb_key = -1;
    int score = 0;

    Font font;
    if (!font.loadFromFile("src/ninja/font.ttf")) {
        std::cerr << "Can't finde .ttf ";
    }

    Text txt_score("", font, 60);
    txt_score.setFillColor(Color::White);
    txt_score.setPosition(95, 25);

    std::list<Letters*> list_letters;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        // time /= 0,8;

        std::ostringstream char_score;

        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                press_count++;

                Press_button(
                        list_letters,
                        hp,
                        score,
                        static_spr_mas,
                        event.key.code);
            }
        }

        char_score << score;
        txt_score.setString(char_score.str());

        if (!isPause) {
            static_spr_mas[8]->Get_sprite().setColor(Color::White);

            if (IntRect(0, 1, 90, 89).contains(Mouse::getPosition(window))) {
                static_spr_mas[8]->Get_sprite().setColor(Color::Red);

                if (Mouse::isButtonPressed(Mouse::Left))
                    isPause = 1;
            }

            if (press_count
                == 5) { // Генерация бомб активируется после 5 нажатия
                bomb_key = 5 + (rand() % 5);
            }

            if (timer > deley) { // Генерирует новое место и значение для буквы
                                 // M каждые delay сек.

                int x = 200 + (rand() % (1338 - 150 + 1));
                if (press_count == bomb_key) { // Нажатие для генирации бомбы.
                    list_letters.push_back(new Letters(
                            1,
                            static_spr_mas[SPR_LETTERS]->Get_Texture(),
                            static_cast<float>(x),
                            0));
                    press_count = 0;
                } else
                    list_letters.push_back(new Letters(
                            0,
                            static_spr_mas[SPR_LETTERS]->Get_Texture(),
                            static_cast<float>(x),
                            0));
                timer = 0;
            }

            for (std::list<Letters*>::iterator it = list_letters.begin();
                 it != list_letters.end();)
                if ((*it)->Delete_letter_beyond(*it)) {
                    delete *it;
                    it = list_letters.erase(it);
                } else
                    ++it;
        }

        // Действия в меню паузы

        while (isPause) {
            window.draw(static_spr_mas[SPR_MENU_PAUSE]->Get_sprite());

            window.display();

            if (IntRect(586, 411, 148, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left))

                isPause = 0;

            if (IntRect(788, 415, 148, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left)) {
                return -1;
            }

            if (IntRect(649, 455, 224, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left)) {
                return 1;
            }

            if (IntRect(724, 504, 75, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left))

                return 0;
        }

        window.draw(static_spr_mas[SPR_GAME_BG]->Get_sprite());

        window.draw(static_spr_mas[SPR_HP]->Get_sprite());

        window.draw(static_spr_mas[SPR_PAUSE]->Get_sprite());

        if (hp <= 0) {
            return 1;
        } // Если хп кончилось - игра оконченна

        for (std::list<Letters*>::iterator it = list_letters.begin();
             it != list_letters.end();
             it++)
            window.draw((*it)->Move_letter((*it)->Get_sprite(), difficult));

        window.draw(txt_score);

        window.display();
    }
    return 0;
}

int gameRunning(int& showMenu)
{
    showMenu = start_game(showMenu);
    if (showMenu)
        gameRunning(showMenu);
    else if (showMenu < 0) {
        start_game(showMenu);
        if (showMenu)
            gameRunning(showMenu);
        else
            return 0;
    }
    return 0;
}

int main()
{
    int showMenu = 1;
    gameRunning(showMenu);
    return 0;
}

// if (!main_menu(window, difficult, static_spr_mas))
//     return 0;

// isPause = 0;
// hp = 3;
// score = 0;