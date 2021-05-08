#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "ninjalib/helper.h"
#include "ninjalib/main_menu.h"

int main()

{
    using namespace sf;

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

    RenderWindow window(VideoMode(1536, 960), "KeyBoardNinja");

    Time delayTime = sf::milliseconds(100);
    int isPause = 0, hp = 3;
    Difficult choose;

    if (!main_menu(window, choose, spr_mas))
        return 0; // вызов главного меню

    while (window.isOpen()) { //Основное тело программы, пока что тут описана

        //только кнопка паузы и условного получения урона

        // Нужно для закрытия проги через "крестик"

        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)

                window.close();
        }

        if (!isPause) {
            spr_mas[8].m_sprite.setColor(Color::White);

            if (IntRect(0, 1, 90, 89).contains(Mouse::getPosition(window))) {
                spr_mas[8].m_sprite.setColor(Color::Red);

                if (Mouse::isButtonPressed(Mouse::Left))

                    isPause = 1;
            }

            // Generate_letter(letter);

            // Основые игровые функции вставлять сюда
        }

        // Действия в меню паузы

        while (isPause) {
            window.draw(spr_mas[13].m_sprite);

            window.display();

            if (IntRect(586, 411, 148, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left))

                isPause = 0;

            if (IntRect(788, 415, 148, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left)) {
                printf("\npressed replay\n");

                isPause = 0;
            }

            if (IntRect(649, 455, 224, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left)) {
                if (!main_menu(window, choose, spr_mas))

                    return 0;

                isPause = 0;

                hp = 3;
            }

            if (IntRect(724, 504, 75, 45).contains(Mouse::getPosition(window))

                && Mouse::isButtonPressed(Mouse::Left))

                return 0;
        }

        window.draw(spr_mas[12].m_sprite);

        window.draw(spr_mas[8].m_sprite);

        // Дальше пример получения урона, сейчас это просто правый клик мыши:

        if (Mouse::isButtonPressed(Mouse::Right)) {
            hp--;

            sleep(delayTime);
        }

        if (hp == 3) {
            window.draw(spr_mas[9].m_sprite);

            window.draw(spr_mas[10].m_sprite);

            window.draw(spr_mas[11].m_sprite);
        }

        if (hp == 2) {
            window.draw(spr_mas[9].m_sprite);

            window.draw(spr_mas[10].m_sprite);
        }

        if (hp == 1)

            window.draw(spr_mas[9].m_sprite);

        window.display();
    }

    return 0;
}