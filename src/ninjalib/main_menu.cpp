#include <SFML/Graphics.hpp>
#include "helper.h"

int main_menu(sf::RenderWindow& window, int& difficulty)

{ // Функция главного меню
    using namespace sf;
    Texture tex_start, tex_about, tex_show_score, tex_exit, tex_bg, tex_rules,
    tex_diff, tex_ShowScore;
// tex_about,
	// My_Sprite tex_about("About_menu.png", 150, 200);
    tex_start.loadFromFile("src/images/Start_menu.png");
    // tex_about.loadFromFile("src/images/About_menu.png");
    tex_show_score.loadFromFile("src/images/Hight_score_menu.png");
    tex_exit.loadFromFile("src/images/Exit_menu.png");
    tex_bg.loadFromFile("src/images/Background_menu.jpg");
    tex_rules.loadFromFile("src/images/Rules.jpg");
    tex_diff.loadFromFile("src/images/Difficulty.jpg");
    tex_ShowScore.loadFromFile("src/images/ShowScore.jpg");

	
// (tex_about),
    Sprite spr[sprite::count_main_menu], about, start(tex_start),  show_score(tex_show_score),
            exit(tex_exit), bg(tex_bg), rules(tex_rules), diff(tex_diff),
            ShowScore(tex_ShowScore);

	// tex_about.Get_sprite(about);
	// for (int i = 0; i < sprite::count_main_menu; i++){
	// 	My_Sprite sprite();
	// }

    show_score.setPosition(30, 14);
    start.setPosition(100, 105);
    about.setPosition(150, 200);
    exit.setPosition(150, 307);
    rules.setPosition(637, 0.5);
    diff.setPosition(0, 0);
    ShowScore.setPosition(0, 0);

    int select = 0, isMenu = 1, ShowRules = 0, ShowDiff = 0, ShowScores = 0;

    Time delayTime = sf::milliseconds(100);

    while (isMenu) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        show_score.setColor(Color::White);
        start.setColor(Color::White);
        about.setColor(Color::White);
        exit.setColor(Color::White);

        select = 0;

        if (!ShowDiff && !ShowScores) {
            if (IntRect(31, 19, 490, 60).contains(Mouse::getPosition(window))) {
                show_score.setColor(Color::Red);
                select = 1;
            }
            if (IntRect(100, 110, 350, 60)
                        .contains(Mouse::getPosition(window))) {
                start.setColor(Color::Red);
                select = 2;
            }
            if (IntRect(180, 217, 170, 50)
                        .contains(Mouse::getPosition(window))) {
                about.setColor(Color::Red);
                select = 3;
            }
            if (IntRect(200, 315, 130, 55)
                        .contains(Mouse::getPosition(window))) {
                exit.setColor(Color::Red);
                select = 4;
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (select == 1) {
                if (!ShowScores)
                    ShowScores = 1;
                else
                    ShowScores = 0;
                sleep(delayTime);
            }
            if (select == 2) {
                if (!ShowDiff)
                    ShowDiff = 1;
                else
                    ShowDiff = 0;
                sleep(delayTime);
            }
            if (select == 3) {
                if (!ShowRules)
                    ShowRules = 1;
                else
                    ShowRules = 0;
                sleep(delayTime);
            }
            if (select == 4) {
                return 0;
            }
        }

        window.draw(bg);
        window.draw(start);
        window.draw(about);
        window.draw(exit);
        window.draw(show_score);
        if (ShowRules)
            window.draw(rules);

        if (ShowScores) {
            window.draw(ShowScore);
            if (IntRect(315, 826, 490, 50).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left))
                ShowScores = 0;
        }

        if (ShowDiff) {
            window.draw(diff);
            if (IntRect(396, 807, 288, 80).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left))
                ShowDiff = 0;
            else if (
                    IntRect(373, 349, 217, 257)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficulty = 1;
                isMenu = false;
            } else if (
                    IntRect(667, 355, 210, 247)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficulty = 2;
                isMenu = false;
            } else if (
                    IntRect(954, 352, 204, 286)
                            .contains(Mouse::getPosition(window))
                    && Mouse::isButtonPressed(Mouse::Left)) {
                difficulty = 3;
                isMenu = false;
            }
        }
        window.display();
    }
    return 1;
}