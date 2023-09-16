#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "InputManager.h"
#include "D3DApplication.h"

class D3DSystem
{
public:
	D3DSystem();
	~D3DSystem();

	D3DSystem(const D3DSystem& other) = default;
	D3DSystem(D3DSystem&& other) noexcept = default;
	D3DSystem& operator= (const D3DSystem& other) = default;
	D3DSystem& operator= (D3DSystem&& other) noexcept = default;

	LRESULT CALLBACK MessageHandler(HWND const hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	
	void Run();
	
	bool GetInitializationState() const;

private:
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();
	
	bool Frame();

	LPCSTR									m_applicationName{};
	HINSTANCE								m_hInstance{};
	HWND									m_hwnd;
	
	D3DApplication*							m_graphics{};
	
	InputManager*							m_input{};
	
	bool									m_initializationFailed;
	
};

static LRESULT CALLBACK WndProc(HWND const hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
static D3DSystem* applicationHandle = nullptr;