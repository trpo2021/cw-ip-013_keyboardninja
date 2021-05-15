#include "Select.h"
#include "helper.h"
#include <SFML/Graphics.hpp>

int main_menu(
        sf::RenderWindow& window,
        Difficult& difficult,
        std::vector<My_Sprite*>& static_spr_mas)
{ // Функция главного меню
    using namespace sf;

    int select = 0;
    int isMenu = 1, ShowRules = 0, ShowDiff = 0, ShowScores = 0;

    while (isMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        static_spr_mas[SPR_SCORE_MENU]->Get_sprite().setColor(Color::White);
        static_spr_mas[SPR_START]->Get_sprite().setColor(Color::White);
        static_spr_mas[SPR_ABOUT]->Get_sprite().setColor(Color::White);
        static_spr_mas[SPR_EXIT]->Get_sprite().setColor(Color::White);

        select = 0;

        if (!ShowDiff && !ShowScores) {
            if (IntRect(31, 19, 490, 60).contains(Mouse::getPosition(window))) {
                static_spr_mas[SPR_SCORE_MENU]->Get_sprite().setColor(
                        Color::Red);
                select = 1;
            }
            if (IntRect(100, 110, 350, 60)
                        .contains(Mouse::getPosition(window))) {
                static_spr_mas[SPR_START]->Get_sprite().setColor(Color::Red);
                select = 2;
            }
            if (IntRect(180, 217, 170, 50)
                        .contains(Mouse::getPosition(window))) {
                static_spr_mas[SPR_ABOUT]->Get_sprite().setColor(Color::Red);
                select = 3;
            }
            if (IntRect(200, 315, 130, 55)
                        .contains(Mouse::getPosition(window))) {
                static_spr_mas[SPR_EXIT]->Get_sprite().setColor(Color::Red);
                select = 4;
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (!Select(select, ShowDiff, ShowRules, ShowScores))
                return 0;
        }

        window.draw(static_spr_mas[SPR_BG]->Get_sprite());
        window.draw(static_spr_mas[SPR_START]->Get_sprite());
        window.draw(static_spr_mas[SPR_ABOUT]->Get_sprite());
        window.draw(static_spr_mas[SPR_EXIT]->Get_sprite());
        window.draw(static_spr_mas[SPR_SCORE_MENU]->Get_sprite());

        if (ShowDiff) {
            window.draw(static_spr_mas[SPR_DIFF]->Get_sprite());
            if (IntRect(396, 807, 288, 80).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left))
                ShowDiff = 0;
            else if (
                    IntRect(373, 349, 217, 257)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficult.Diff_choose(0.0005, 0.3, 5);

                isMenu = false;
            } else if (
                    IntRect(667, 355, 210, 247)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficult.Diff_choose(0.0010, 0.4, 7);

                isMenu = false;
            } else if (
                    IntRect(954, 352, 204, 286)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficult.Diff_choose(0.0015, 0.5, 10);
                isMenu = false;
            }
        }
        window.display();
    }
    return 1;
}