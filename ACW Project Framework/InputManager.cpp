#include "InputManager.h"

InputManager::InputManager() : m_doOnce(true), m_keys{false}
{
}

InputManager::~InputManager() = default;

//Update our key array and change defined key input to pressed
void InputManager::KeyDown(unsigned int const key) 
{
	m_keys[key] = true;
}

//Update our key array and change the defined key input to released
void InputManager::KeyUp(unsigned int const key) 
{
	m_keys[key] = false;
}

//Return state of the key
bool InputManager::IsKeyDown(unsigned int const key) const 
{
	return m_keys[key];
}

bool InputManager::IsKeyUp(unsigned int const key) const
{
	return !m_keys[key];
}

bool InputManager::DoOnce() const
{
	return m_doOnce;
}

void InputManager::ToggleDoOnce(const bool toggle)
{
	m_doOnce = toggle;
}
