#pragma once

#include <Windows.h>

#include "D3DContainer.h"

#include "Camera.h"
#include "GameObject.h"
#include "Terrain.h"
#include "Rocket.h"

#include "LightManager.h"
#include "ShaderManager.h"
#include "ShadowMapManager.h"
#include "ResourceManager.h"
#include "ParticleSystemManager.h"
#include "ParticleSystem.h"
#include "Fire.h"
#include "Smoke.h"
#include "RenderToTexture.h"

#include "AntTweakBar.h";

#include "ConfigurationManager.h"

auto const FULL_SCREEN = false;
auto const VSYNC_ENABLED = true;
auto const SCREEN_DEPTH = 1000.0f;
auto const SCREEN_NEAR = 0.1f;

const int SHADOW_MAP_WIDTH = 1360;
const int SHADOW_MAP_HEIGHT = 720;

class D3DApplication
{
public:
	D3DApplication(int screenWidth, int screenHeight, HWND const hwnd);
	~D3DApplication();

	D3DApplication(const D3DApplication& other) = default;
	D3DApplication(D3DApplication&& other) noexcept = default;
	D3DApplication& operator = (const D3DApplication& other) = default;
	D3DApplication& operator = (D3DApplication&& other) noexcept = default;

	const shared_ptr<Camera>& GetCamera() const;

	void ToggleRenderOption();
	void ToggleOptionalGameObjects();
	void ResetToInitialState() const;
	void AddTimeScale(const int number);
	void RotateRocketLeft() const;
	void RotateRocketRight() const;
	void LaunchRocket() const;
	void ChangeCameraMode(const int cameraMode);
	void UpdateCameraPosition() const;

	bool GetInitializationState() const;
	bool UpdateFrame();

private:
	bool RenderFrame();

	bool m_initializationFailed;

	shared_ptr<ConfigurationManager> m_configuration;

	shared_ptr<D3DContainer> m_d3D;

	TwBar* m_antTweakBarStatistics;

	shared_ptr<Camera> m_camera;
	shared_ptr<LightManager> m_lightManager;

	shared_ptr<Terrain> m_terrain;
	shared_ptr<Rocket> m_rocket;

	shared_ptr<GameObject> m_displacedFloor;
	shared_ptr<GameObject> m_skyBox;

	vector<shared_ptr<GameObject>> m_gameObjects;

	shared_ptr<ShaderManager> m_shaderManager;
	shared_ptr<ResourceManager> m_resourceManager;
	shared_ptr<ParticleSystemManager> m_particleSystemManager;
	shared_ptr<ShadowMapManager> m_shadowMapManager;

	float m_windowWidth;
	float m_windowHeight;

	int m_renderToggle;
	bool m_renderOptionalGameObjects;
	int m_timeScale;
	bool m_updateCamera;
	int m_cameraMode;

	float m_dt;
	float m_fps;
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_end;
	LARGE_INTEGER m_frequency;
};