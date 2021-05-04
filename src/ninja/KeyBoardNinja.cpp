#include <SFML/Graphics.hpp>

using namespace sf; // что бы не писать постоянно sf::

int main_menu(RenderWindow& window, int& difficulty)
{ // Функция главного меню
    Texture tex_start, tex_about, tex_show_score, tex_exit, tex_bg, tex_rules,
            tex_diff, tex_ShowScore;

    tex_start.loadFromFile("images/Start_menu.png");
    tex_about.loadFromFile("images/About_menu.png");
    tex_show_score.loadFromFile("images/Hight_score_menu.png");
    tex_exit.loadFromFile("images/Exit_menu.png");
    tex_bg.loadFromFile("images/Background_menu.jpg");
    tex_rules.loadFromFile("images/Rules.jpg");
    tex_diff.loadFromFile("images/Difficulty.jpg");
    tex_ShowScore.loadFromFile("images/ShowScore.jpg");

    Sprite start(tex_start), about(tex_about), show_score(tex_show_score),
            exit(tex_exit), bg(tex_bg), rules(tex_rules), diff(tex_diff),
            ShowScore(tex_ShowScore);

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

void Generate_letter(Sprite& letter)
{ // Выдать спрайту рандомную букву

    int Letters[26][3], kind = 0;
    int i;
    int x = 28, y = 9;
    int x_growth = 0, y_growth = 0;
    for (i = 0; i < 26; i++) {
        Letters[i][0] = i;
        Letters[i][1] = x + x_growth;
        Letters[i][2] = y + y_growth;
        x_growth += 114;
        if (i == 8 || i == 17) {
            y_growth += 154;
            x_growth = 0;
        }
    }
    kind = rand() % 27 - 3;
    letter.setTextureRect(IntRect(Letters[kind][1], Letters[kind][2], 83, 111));
}

int main()
{
    RenderWindow window(VideoMode(1536, 960), "KeyBoardNinja");
    Texture tex_pause, tex_hp, tex_game_bg, tex_menu_pause, tex_letters;
    tex_pause.loadFromFile("images/pause.png");
    tex_hp.loadFromFile("images/hp.png");
    tex_game_bg.loadFromFile("images/game_bg.jpg");
    tex_menu_pause.loadFromFile("images/menu_pause.png");
    tex_letters.loadFromFile("images/letters_tex.png");

    Sprite pause(tex_pause), game_bg(tex_game_bg), hp1(tex_hp), hp2(tex_hp),
            hp3(tex_hp), menu_pause(tex_menu_pause), letter;

    letter.setTexture(tex_letters);
    pause.setPosition(0, 0);
    hp1.setPosition(5, 124);
    hp2.setPosition(5, 209);
    hp3.setPosition(5, 294);
    menu_pause.setPosition(504, 356);
    letter.setPosition(500, 0);

    Time delayTime = sf::milliseconds(100);
    int difficult = 0, isPause = 0, hp = 3;

    if (!main_menu(window, difficult))
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
            pause.setColor(Color::White);
            if (IntRect(0, 1, 90, 89).contains(Mouse::getPosition(window))) {
                pause.setColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Left))
                    isPause = 1;
            }
            // Generate_letter(letter);
            // Основые игровые функции вставлять сюда
        }
        // Действия в меню паузы
        while (isPause) {
            window.draw(menu_pause);
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
                if (!main_menu(window, difficult))
                    return 0;
                isPause = 0;
                hp = 3;
            }
            if (IntRect(724, 504, 75, 45).contains(Mouse::getPosition(window))
                && Mouse::isButtonPressed(Mouse::Left))
                return 0;
        }
        window.draw(game_bg);
        window.draw(pause);

        // Дальше пример получения урона, сейчас это просто правый клик мыши:
        if (Mouse::isButtonPressed(Mouse::Right)) {
            hp--;
            sleep(delayTime);
        }
        if (hp == 3) {
            window.draw(hp1);
            window.draw(hp2);
            window.draw(hp3);
        }
        if (hp == 2) {
            window.draw(hp1);
            window.draw(hp2);
        }
        if (hp == 1)
            window.draw(hp1);
        // letter.move(0, 0.05);	//Пример падения буквы
        // window.draw(letter);
        window.display();
    }

    return 0;
}