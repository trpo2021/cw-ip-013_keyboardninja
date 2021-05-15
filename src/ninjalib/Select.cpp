#include <SFML/Graphics.hpp>

sf::Time delayTime = sf::milliseconds(170);
int Select(int select, int& ShowDiff, int& ShowRules, int& ShowScores) {
	switch (select) {
		case 1: {
			if (!ShowScores)
				ShowScores = 1;
			else 
				ShowScores = 0;
			break;
		}
		case 2: {
			if (!ShowDiff)
				ShowDiff = 1;
			else 
				ShowDiff = 0;
			break;
		}
		case 3: {
			if (!ShowRules)
				ShowRules = 1;
			else
			ShowRules = 0;
			break;
		}
		case 4: {
			return 0;
		}
	}

	if (select != 0) sf::sleep(delayTime);
	return 1;
}