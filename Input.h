#ifndef _INPUT_H_
#define _INPUT_H_

#include <SFML\Window\Keyboard.hpp>
#include <map>
#include <vector>

enum KeyState
{
	RELEASED,
	DOWN,
	PRESSED
};

class Input
{
public:
	Input();

	void Frame();

	bool IsKeyPressed(int key);
	bool IsKeyDown(int key);

	void OnKeyDown(sf::Keyboard::Key key);
	void OnKeyUp(sf::Keyboard::Key key);

private:
	std::map<int, int> keyStateMap;
	std::vector<int> PressedKeyList;

};

#endif