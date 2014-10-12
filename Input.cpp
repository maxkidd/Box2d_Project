#include "Input.h"

Input::Input()
{
	for (int key{ 0 }; key < sf::Keyboard::KeyCount; ++key)
		keyStateMap[key] = KeyState::RELEASED;
}

void Input::Frame()
{
	for (int key{ 0 }; key < sf::Keyboard::KeyCount; ++key)
	{
		if (keyStateMap[key] == KeyState::PRESSED)
			keyStateMap[key] = KeyState::DOWN;
	}
}
void Input::OnKeyDown(sf::Keyboard::Key key)
{
	if (keyStateMap[key] != KeyState::DOWN)
		keyStateMap[key] = KeyState::PRESSED;
}

void Input::OnKeyUp(sf::Keyboard::Key key)
{
	keyStateMap[key] = KeyState::RELEASED;
}


bool Input::IsKeyPressed(int key)
{
	return keyStateMap[key] == KeyState::PRESSED;
}
bool Input::IsKeyDown(int key)
{
	return keyStateMap[key] == KeyState::DOWN;
}