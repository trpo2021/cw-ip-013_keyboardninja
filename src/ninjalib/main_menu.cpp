#include <SFML/Graphics.hpp>

#include "helper.h"
#include "letters.h"

int main_menu(
        sf::RenderWindow& window,
        Difficult& difficult,
        sf::Text txt_score,
        std::vector<My_Sprite*>& static_spr_mas)
{ // Функция главного меню
    using namespace sf;

    int isMenu = 1, ShowRules = 0, ShowDiff = 0, ShowScores = 0;

    while (isMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (!ShowDiff && !ShowScores) {
                static_spr_mas[SPR_SCORE_MENU]->Get_sprite().setColor(
                        Color::White);
                if (IntRect(31, 19, 490, 60)
                            .contains(Mouse::getPosition(window))) {
                    static_spr_mas[SPR_SCORE_MENU]->Get_sprite().setColor(
                            Color::Red);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        if (!ShowScores)
                            ShowScores = 1;
                        else
                            ShowScores = 0;
                    }
                }

                static_spr_mas[SPR_START]->Get_sprite().setColor(Color::White);
                if (IntRect(100, 110, 350, 60)
                            .contains(Mouse::getPosition(window))) {
                    static_spr_mas[SPR_START]->Get_sprite().setColor(
                            Color::Red);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        if (!ShowDiff)
                            ShowDiff = 1;
                        else
                            ShowDiff = 0;
                    }
                }

                static_spr_mas[SPR_ABOUT]->Get_sprite().setColor(Color::White);
                if (IntRect(180, 217, 170, 50)
                            .contains(Mouse::getPosition(window))) {
                    static_spr_mas[SPR_ABOUT]->Get_sprite().setColor(
                            Color::Red);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        if (!ShowRules)
                            ShowRules = 1;
                        else
                            ShowRules = 0;
                    }
                }

                static_spr_mas[SPR_EXIT]->Get_sprite().setColor(Color::White);
                if (IntRect(200, 315, 130, 55)
                            .contains(Mouse::getPosition(window))) {
                    static_spr_mas[SPR_EXIT]->Get_sprite().setColor(Color::Red);
                    if (Mouse::isButtonPressed(Mouse::Left))
                        return 0;
                }
            }
        }

        for (int i = 0; i < 5; i++)
            window.draw(static_spr_mas[i]->Get_sprite());

        if (ShowRules)
            window.draw(static_spr_mas[SPR_RULES]->Get_sprite());

        if (ShowScores) {
            window.draw(static_spr_mas[SPR_SHOWSCORE]->Get_sprite());
            scoreInput(txt_score, window);
            if (IntRect(315, 826, 490, 50).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left))
                ShowScores = 0;
        }

        if (ShowDiff) {
            window.draw(static_spr_mas[SPR_DIFF]->Get_sprite());
            if (IntRect(396, 807, 288, 80).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left))
                ShowDiff = 0;
            else if (
                    IntRect(373, 349, 217, 257)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficult.Diff_choose(0.1, 5, 1000, 15, 200, 0);

                isMenu = false;
            } else if (
                    IntRect(667, 355, 210, 247)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficult.Diff_choose(0.2, 10, 800, 10, 300, 1);

                isMenu = false;
            } else if (
                    IntRect(954, 352, 204, 286)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficult.Diff_choose(0.25, 15, 600, 5, 10000, 2);
                isMenu = false;
            }
        }
        window.display();
    }
    return 1;
}
