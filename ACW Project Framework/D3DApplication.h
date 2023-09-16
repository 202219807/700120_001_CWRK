#pragma once

#include <Windows.h>

#include "AntTweakBar.h";
#include "ConfigurationManager.h"

#include "D3DContainer.h"

#include "Camera.h"

#include "GameObject.h"
#include "Terrain.h"
#include "Rocket.h"
#include "ResourceManager.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "ShadowMapManager.h"
#include "ParticleSystemManager.h"
#include "ParticleSystem.h"
#include "Fire.h"
#include "Smoke.h"
#include "RenderToTexture.h"

auto const FULL_SCREEN			= false;
auto const VSYNC_ENABLED		= true;
auto const SCREEN_DEPTH			= 1000.0f;
auto const SCREEN_NEAR			= 0.1f;

const int  SHADOW_MAP_WIDTH		= 1360;
const int  SHADOW_MAP_HEIGHT	= 720;

class D3DApplication
{
public:
	D3DApplication(int screenWidth, int screenHeight, HWND const hwnd);
	~D3DApplication();

	D3DApplication(const D3DApplication& other) = default;
	D3DApplication(D3DApplication&& other) noexcept = default;
	D3DApplication& operator = (const D3DApplication& other) = default;
	D3DApplication& operator = (D3DApplication&& other) noexcept = default;

	bool GetInitializationState() const;
	bool UpdateFrame();
	bool RenderFrame();
	void ResetToInitialState() const;

private:
	vector<shared_ptr<GameObject>>		m_gameObjects;

	shared_ptr<D3DContainer>			m_d3D;
	shared_ptr<GameObject>				m_displacedFloor;
	shared_ptr<GameObject>				m_skyBox;
	shared_ptr<Terrain>					m_terrain;
	shared_ptr<Rocket>					m_rocket;
	shared_ptr<Camera>					m_camera;
	shared_ptr<LightManager>			m_lightManager;
	shared_ptr<ShaderManager>			m_shaderManager;
	shared_ptr<ResourceManager>			m_resourceManager;
	shared_ptr<ParticleSystemManager>	m_particleSystemManager;
	shared_ptr<ShadowMapManager>		m_shadowMapManager;
	shared_ptr<ConfigurationManager>	m_configuration;
	
	TwBar*								m_antTweakBarStatistics;

	LARGE_INTEGER						m_start;
	LARGE_INTEGER						m_end;
	LARGE_INTEGER						m_frequency;

	float								m_windowWidth;
	float								m_windowHeight;
	float								m_dt;
	float								m_fps;

	bool								m_initializationFailed;
	bool								m_updateCamera;
	
	int									m_renderToggle;
	int									m_cameraMode;
	int									m_timeScale;

public:
	const shared_ptr<Camera>& GetCamera() const { return m_camera; }

	// Rocket controls
	void LaunchRocket() const;
	void RotateRocketLeft() const;
	void RotateRocketRight() const;
	
	// Camera
	void ChangeCameraMode(const int cameraMode);
	void UpdateCameraPosition() const;
	
	// Timescale
	void UpdateTimeScale(const int number);

	// Rendering
	void ToggleRenderOption();
};