#include <SFML/Graphics.hpp>

#include "helper.h"
#include "letters.h"
#include "main_menu.h"

#include <cstdlib>

#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

Difficult difficult;

int start_game(int& showMenu)
{
    srand(static_cast<unsigned int>(time(0)));
    using namespace sf;

    float timer = 0;
    float deley = 1000;
    Clock clock;

    std::ifstream inf_images("src/ninja/static_images_names.txt");
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

    int isPause = 0;
    int hp = 3;

    if (showMenu == 1) {
        if (!main_menu(window, difficult, static_spr_mas))
            return 0;
    }

    int press_count = 0;
    int bomb_key = 0;
    int score = 0;
    int BG_num = 16 + rand() % 9;

    Font font;
    if (!font.loadFromFile("src/ninja/font.ttf")) {
        std::cerr << "Can't finde .ttf ";
    }

    Text txt_score("", font, 60);
    txt_score.setFillColor(Color::White);
    txt_score.setPosition(95, 25);

    std::list<Letters*> list_letters;

    clock.restart();
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;
        timer += time;

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
                        *static_spr_mas[SPR_HP],
                        event.key.code);
            }
        }

        while (!hp) {
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();
            int i, j;
            for (i = 12; i < 16; i++)
                window.draw(static_spr_mas[i]->Get_sprite());

            txt_score.setPosition(800, 380);
            window.draw(txt_score);
            window.display();
            for (i = 450, j = 13; i <= 650; i += 100, j++) {
                static_spr_mas[j]->Get_sprite().setColor(Color::White);
                if (IntRect(660, i, 210, 80)
                            .contains(Mouse::getPosition(window))) {
                    static_spr_mas[j]->Get_sprite().setColor(Color::Red);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        switch (j) {
                        case 13:
                            return -1;
                        case 14:
                            return 1;
                        case 15:
                            return 0;
                        }
                    }
                }
            }
        }

        char_score << score;
        txt_score.setString(char_score.str());

        window.draw(static_spr_mas[BG_num]->Get_sprite());
        for (int i = 8; i < 10; i++)
            window.draw(static_spr_mas[i]->Get_sprite());
        window.draw(txt_score);

        if (!isPause && hp > 0) {
            static_spr_mas[SPR_PAUSE]->Get_sprite().setColor(Color::White);

            if (IntRect(0, 1, 90, 89).contains(Mouse::getPosition(window))) {
                static_spr_mas[SPR_PAUSE]->Get_sprite().setColor(Color::Red);

                if (Mouse::isButtonPressed(Mouse::Left))
                    isPause = 1;
            }

            if (press_count
                == 5) { // Генерация бомб активируется после 5 нажатия
                bomb_key = press_count + (rand() % 5);
            }

            if (timer > deley
                && difficult.m_barrier
                        >= list_letters.size()) { // Генерирует новое место и
                                                  // значение для буквы
                // M каждые delay сек.

                int x = 200 + (rand() % (1338 - 150 + 1));
                if (press_count >= bomb_key
                    && bomb_key) { // Нажатие для генирации бомбы.
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
                if ((*it)->Delete_letter_beyond(
                            (*it), *static_spr_mas[SPR_HP], hp)) {
                    delete *it;
                    it = list_letters.erase(it);
                } else
                    ++it;

            for (std::list<Letters*>::iterator it = list_letters.begin();
                 it != list_letters.end();
                 it++) {
                (*it)->Update((*it)->Get_sprite(), difficult, time);
                window.draw((*it)->Get_sprite());
            }
        }
        window.display();

        // Действия в меню паузы
        while (isPause) {
            while (window.pollEvent(event))
                if (event.type == Event::Closed)
                    window.close();

            window.draw(static_spr_mas[SPR_MENU_PAUSE]->Get_sprite());
            window.display();

            if (IntRect(586, 411, 148, 45).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left)) {
                clock.restart();
                isPause = 0;
            }

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
