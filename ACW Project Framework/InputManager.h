#pragma once

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	InputManager(const InputManager& other) = default;
	InputManager(InputManager && other) noexcept = default;
	InputManager& operator= (const InputManager& other) = default;
	InputManager& operator= (InputManager&& other) noexcept = default;

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);

	bool IsKeyDown(unsigned int key) const;
	bool IsKeyUp(unsigned int key) const;

	bool DoOnce() const;
	void ToggleDoOnce(const bool toggle);

private:
	bool m_doOnce;
	bool m_keys[256];
};