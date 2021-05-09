#include "helper.h"
#include <SFML/Graphics.hpp>

int main_menu(
sf::RenderWindow& window, Difficult& difficulty, My_Sprite* spr_mas)

{ // Функция главного меню
using namespace sf;

int select = 0, isMenu = 1, ShowRules = 0, ShowDiff = 0, ShowScores = 0;

Time delayTime = sf::milliseconds(100);

while (isMenu) {
Event event;
while (window.pollEvent(event)) {
if (event.type == Event::Closed)
window.close();
}

spr_mas[SPR_SCORE_MENU].m_sprite.setColor(Color::White);
spr_mas[SPR_START].m_sprite.setColor(Color::White);
spr_mas[SPR_ABOUT].m_sprite.setColor(Color::White);
spr_mas[SPR_EXIT].m_sprite.setColor(Color::White);

select = 0;

if (!ShowDiff && !ShowScores) {
if (IntRect(31, 19, 490, 60).contains(Mouse::getPosition(window))) {
spr_mas[SPR_SCORE_MENU].m_sprite.setColor(Color::Red);
select = 1;
}
if (IntRect(100, 110, 350, 60)
.contains(Mouse::getPosition(window))) {
spr_mas[SPR_START].m_sprite.setColor(Color::Red);
select = 2;
}
if (IntRect(180, 217, 170, 50)
.contains(Mouse::getPosition(window))) {
spr_mas[SPR_ABOUT].m_sprite.setColor(Color::Red);
select = 3;
}
if (IntRect(200, 315, 130, 55)
.contains(Mouse::getPosition(window))) {
spr_mas[SPR_EXIT].m_sprite.setColor(Color::Red);
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

window.draw(spr_mas[SPR_BG].m_sprite);
window.draw(spr_mas[SPR_START].m_sprite);
window.draw(spr_mas[SPR_ABOUT].m_sprite);
window.draw(spr_mas[SPR_EXIT].m_sprite);
window.draw(spr_mas[SPR_SCORE_MENU].m_sprite);
if (ShowRules)
window.draw(spr_mas[SPR_RULES].m_sprite);

if (ShowScores) {
window.draw(spr_mas[SPR_SHOWSCORE].m_sprite);
if (IntRect(315, 826, 490, 50).contains(Mouse::getPosition(window))
&& Mouse::isButtonPressed(Mouse::Left))
ShowScores = 0;
}

if (ShowDiff) {
window.draw(spr_mas[SPR_DIFF].m_sprite);
if (IntRect(396, 807, 288, 80).contains(Mouse::getPosition(window))
&& Mouse::isButtonPressed(Mouse::Left))
ShowDiff = 0;
else if (
IntRect(373, 349, 217, 257)
.contains(Mouse::getPosition(window))
&& Mouse::isButtonPressed(Mouse::Left)) {
difficulty.Diff_choose(0.0005, 0.4, 5);

isMenu = false;
} else if (
IntRect(667, 355, 210, 247)
.contains(Mouse::getPosition(window))
&& Mouse::isButtonPressed(Mouse::Left)) {
difficulty.Diff_choose(0.0010, 0.5, 7);

isMenu = false;
} else if (
IntRect(954, 352, 204, 286)
.contains(Mouse::getPosition(window))
&& Mouse::isButtonPressed(Mouse::Left)) {
difficulty.Diff_choose(0.0015, 0.6, 10);
isMenu = false;
}
}
window.display();
}
return 1;
}