#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include "ninjalib/helper.h"
#include "ninjalib/main_menu.h"

int start_game(int& showMenu)
{
    srand(time(0)); // Избавление от псевдослучайности ГПСЧ
    using namespace sf;

    float timer = 0;
    float deley = 3;
    Clock clock;

    std::ifstream inf_images("src/ninja/images_names.txt");
    std::string str[help::line_count];
    if (!(inf_images.is_open())) {
        inf_images.close();
        std::cerr << "Ошибка: файл не открылся\n";
        exit(1);
    }

    My_Sprite spr_mas[help::count_images];
    for (int j = 0; j < help::count_images && inf_images; j++) {
        for (int i = 0; i < 3; i++) {
            inf_images >> str[i];
            if (isalpha(str[1][0])) {
                spr_mas[j].Add_method1(str[0]);
                swap(str[0], str[1]);
                i--;
                j++;
            }
        }
        spr_mas[j].Add_method(str);
    }

    Letters M;

    RenderWindow window(VideoMode(1536, 960), "KeyBoardNinja");

    int isPause = 0, hp = 3;

    Difficult difficult;

    if (showMenu == 1)
        if (!main_menu(window, difficult, spr_mas))
            return 0; // вызов главного меню

    int score = 0;

    while (window.isOpen()) { //Основное тело программы
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key Pressed " << event.key.code << "\n";
                M.Check_code_key(
                        event.key.code, hp, score, spr_mas[SPR_HP].m_sprite);
                std::cout << "Score now " << score << "\n";
            }
        }

        if (hp == 0) {
            return 0;
        } // Если хп кончилось - игра оконченна

        if (!isPause) {
            spr_mas[8].m_sprite.setColor(Color::White);

            if (IntRect(0, 1, 90, 89).contains(Mouse::getPosition(window))) {
                spr_mas[8].m_sprite.setColor(Color::Red);

                if (Mouse::isButtonPressed(Mouse::Left))

                    isPause = 1;
            }

            if (timer > deley) { // Генерирует новое место и значение для буквы
                // M каждые delay сек.
                int x = 200 + (rand() % (1338 - 150 + 1));
                M.Get_Letter(0, "letters_tex.png", x, 0);
                timer = 0;
            }
        }

        // Действия в меню паузы

        while (isPause) {
            window.draw(spr_mas[11].m_sprite);

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

        window.draw(spr_mas[SPR_GAME_BG].m_sprite);

        window.draw(spr_mas[SPR_PAUSE].m_sprite);

        window.draw(spr_mas[SPR_HP].m_sprite);

        window.draw(M.Move_letter(M.m_sprite, difficult));

        window.display();
    }
    return 0;
}
int gameRunning(int& showMenu)
{
    showMenu =

            start_game(showMenu);
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
