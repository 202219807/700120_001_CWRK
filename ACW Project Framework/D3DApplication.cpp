#include "D3DApplication.h"

D3DApplication::D3DApplication(int screenWidth, int screenHeight, HWND const hwnd) : 
	m_initializationFailed(false), 
	m_d3D(nullptr), 
	m_antTweakBarStatistics(nullptr), 
	m_camera(nullptr), 
	m_lightManager(nullptr), 
	m_terrain(nullptr), 
	m_rocket(nullptr), 
	m_displacedFloor(nullptr), 
	m_skyBox(nullptr), 
	m_gameObjects(), 
	m_shaderManager(nullptr), 
	m_resourceManager(nullptr), 
	m_shadowMapManager(nullptr), 
	m_renderToggle(0), 
	m_timeScale(1), 
	m_updateCamera(false), 
	m_cameraMode(0), 
	m_dt(0.0f), 
	m_fps(0.0f), 
	m_start({0}), 
	m_end({0}), 
	m_frequency({0}) 
{
	//Create D3D object
	m_d3D = make_shared<D3DContainer>(screenWidth, screenHeight, hwnd, FULL_SCREEN, VSYNC_ENABLED, SCREEN_DEPTH, SCREEN_NEAR);

	m_windowWidth = screenWidth;
	m_windowHeight = screenHeight;

	// Initialize AntTweakBar
	if (!TwInit(TW_DIRECT3D11, m_d3D->GetDevice()))
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "AntTweak failed to Initialize", "Error", MB_OK);
		return;
	}

	TwWindowSize(screenWidth, screenHeight);

	m_antTweakBarStatistics = TwNewBar("Statistics");
	TwDefine(" Statistics label='Statistics' position='20 20' size='300 180' alpha=0 valueswidth=fit");

	TwAddVarRW(m_antTweakBarStatistics, "Video Card: ",				TW_TYPE_STDSTRING,	m_d3D->m_videoCardDescription, "");
	TwAddVarRW(m_antTweakBarStatistics, "Memory: ",					TW_TYPE_INT32,		&m_d3D->m_videoCardMemory, "");
	TwAddVarRW(m_antTweakBarStatistics, "Screen Width: ",			TW_TYPE_FLOAT,		&m_windowWidth, "");
	TwAddVarRW(m_antTweakBarStatistics, "Screen Height: ",			TW_TYPE_FLOAT,		&m_windowHeight, "");
	TwAddVarRW(m_antTweakBarStatistics, "DeltaTime: ",				TW_TYPE_FLOAT,		&m_dt, "");
	TwAddVarRW(m_antTweakBarStatistics, "FPS: ",					TW_TYPE_FLOAT,		&m_fps, "");
	TwAddVarRW(m_antTweakBarStatistics, "Render Mode: ",			TW_TYPE_INT32,		&m_renderToggle, "");
	TwAddVarRW(m_antTweakBarStatistics, "Camera Mode: ",			TW_TYPE_INT32,		&m_cameraMode, "");
	TwAddVarRW(m_antTweakBarStatistics, "Time Scale Factor: ",		TW_TYPE_INT32,		&m_timeScale, "");
	
	m_configuration = make_shared<ConfigurationManager>("Config.txt");

	// Initialize Container
	if (m_d3D->GetInitializationState()) {
		m_initializationFailed = true;
		MessageBox(hwnd, "Direct3D failed to Initialize", "Error", MB_OK);
		return;
	}

	// Initialize Managers
	m_shaderManager = make_shared<ShaderManager>(m_d3D->GetDevice(), hwnd);

	if (m_shaderManager->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "ShaderManager failed to Initialize", "Error", MB_OK);
		return;
	}

	m_resourceManager = make_shared<ResourceManager>();

	if (!m_resourceManager)
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "ResourceManager failed to Initialize", "Error", MB_OK);
		return;
	}

	m_lightManager = make_shared<LightManager>();

	if (!m_lightManager)
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "LightManager failed to Initialize", "Error", MB_OK);
		return;
	}

	// Initialize ParticleSystem Manager
	m_particleSystemManager = make_shared<ParticleSystemManager>();

	//Create camera
	m_camera = make_shared<Camera>();

	if (!m_camera)
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Camera failed to Initialize", "Error", MB_OK);
		return;
	}

	//Set camera position
	m_camera->SetPosition(m_configuration->GetCameraPosition());

	// Set scene elements and lights
	const auto terrainDimensions = m_configuration->GetTerrainDimensions();

	auto rocketPosition = m_configuration->GetRocketPosition();
	rocketPosition.x += -terrainDimensions.z;

	m_terrain = make_shared<Terrain>(m_d3D->GetDevice(), XMFLOAT3(80, 10, 40), XMFLOAT3(1, 1, 1), m_shaderManager->GetTextureDisplacementShader(), m_resourceManager);
	m_rocket = make_shared<Rocket>(m_d3D->GetDevice(), rocketPosition, m_configuration->GetRocketRotation(), m_configuration->GetRocketScale(), m_shaderManager, m_resourceManager);

	m_lightManager->AddLight(XMFLOAT3(0.0f, 0.0f, terrainDimensions.z), XMFLOAT3(0.0f, 0.0f, 0.0f), m_configuration->GetSunAmbient(), m_configuration->GetSunDiffuse(), m_configuration->GetSunSpecular(), m_configuration->GetSunSpecularPower(), terrainDimensions.x, terrainDimensions.z, 1, terrainDimensions.z, true, true);
	m_lightManager->AddLight(XMFLOAT3(terrainDimensions.x, terrainDimensions.x, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), m_configuration->GetSunAmbient(), m_configuration->GetMoonDiffuse(), m_configuration->GetMoonSpecular(), m_configuration->GetMoonSpecularPower(), terrainDimensions.z, terrainDimensions.x, 1, terrainDimensions.x, true, true);

	m_shadowMapManager = make_shared<ShadowMapManager>(hwnd, m_d3D->GetDevice(), m_shaderManager->GetDepthShader(), m_lightManager->GetLightList().size(), SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);

	vector<const WCHAR*> textureNames;

	//Launch pad
	textureNames.clear();
	textureNames.push_back(L"RoughRockColour.dds");
	textureNames.push_back(L"RoughRockNormal.dds");
	textureNames.push_back(L"RoughRockSpecular.dds");
	textureNames.push_back(L"RoughRockDisplacement.dds");

	const auto launchPadTessellationValues = m_configuration->GetLaunchPadTessellationValues();
	const auto launchPadDisplacementValues = m_configuration->GetLaunchPadDisplacementValues();

	m_displacedFloor = make_shared<GameObject>();
	m_displacedFloor->AddScaleComponent(m_configuration->GetLaunchPadScale());
	m_displacedFloor->AddPositionComponent(XMFLOAT3(-terrainDimensions.z, 0.5f, 0.0f));
	m_displacedFloor->AddRotationComponent(0.0f, 0.0f, 0.0f);
	m_displacedFloor->AddPhysicsComponent(true, 1.0f, 0.0f, 0.0f);
	m_displacedFloor->AddModelComponent(m_d3D->GetDevice(), ModelType::Plane, m_resourceManager);
	m_displacedFloor->AddTextureComponent(m_d3D->GetDevice(), textureNames, m_resourceManager);
	m_displacedFloor->AddShaderComponent(m_shaderManager->GetTextureDisplacementShader());
	m_displacedFloor->SetTessellationVariables(launchPadTessellationValues.x, launchPadTessellationValues.y, launchPadTessellationValues.z, launchPadTessellationValues.w);
	m_displacedFloor->SetDisplacementVariables(launchPadDisplacementValues.x, launchPadDisplacementValues.y, launchPadDisplacementValues.z, launchPadDisplacementValues.w);

	// Skymap
	textureNames.clear();
	textureNames.push_back(L"Skymap.dds");

	m_skyBox = make_shared<GameObject>();
	m_skyBox->AddPositionComponent(0.0f, 0.0f, 0.0f);
	m_skyBox->AddRotationComponent(0.0f, 0.0f, 0.0f);
	m_skyBox->AddScaleComponent(300.0f, 300.0f, 300.0f);
	m_skyBox->AddModelComponent(m_d3D->GetDevice(), ModelType::SphereInverted, m_resourceManager);
	m_skyBox->AddTextureComponent(m_d3D->GetDevice(), textureNames, m_resourceManager);
	m_skyBox->AddShaderComponent(m_shaderManager->GetTextureCubeShader());

	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_start);
}

D3DApplication::~D3DApplication()
{
	TwTerminate();
}

bool D3DApplication::GetInitializationState() const 
{
	return m_initializationFailed;
}

bool D3DApplication::UpdateFrame() {

	//Calculate delta
	QueryPerformanceCounter(&m_end);
	m_dt = static_cast<float>((m_end.QuadPart - m_start.QuadPart) / static_cast<double>(m_frequency.QuadPart));
	m_start = m_end;

	//Apply timescale
	m_dt *= m_timeScale;

	//Calculate fps
	m_fps = static_cast<int>(1.0 / m_dt);

	// Handle collision
	auto collisionPosition = XMFLOAT3();
	auto blastRadius = 0.0f;

	const auto rocketCollisionState = m_rocket->CheckForTerrainCollision(m_terrain, collisionPosition, blastRadius);

	if (rocketCollisionState)
	{
		m_particleSystemManager->GenerateExplosion(m_d3D->GetDevice(), collisionPosition, blastRadius, m_resourceManager);
	}

	// Update game objects, managers and camera
	if (m_gameObjects.size() > 0)
	{
		for (const auto& gameObject : m_gameObjects)
		{
			gameObject->Update();
		}
	}
	
	m_displacedFloor->Update();
	m_skyBox->Update();
	m_terrain->UpdateTerrain();
	m_rocket->UpdateRocket(m_dt);
	m_particleSystemManager->Update(m_dt);
	for (const auto& light : m_lightManager->GetLightList())
	{
		light->UpdateLightVariables(m_dt);
	}

	UpdateCameraPosition();
	
	auto const result = RenderFrame();
	return result;
}

bool D3DApplication::RenderFrame()
{

	auto result = true;

	m_camera->Render();

	vector<shared_ptr<GameObject>> gameObjects;

	gameObjects.emplace_back(static_pointer_cast<GameObject>(m_terrain));
	gameObjects.emplace_back(m_displacedFloor);
	gameObjects.emplace_back(m_skyBox);
	gameObjects.emplace_back(m_rocket->GetRocketBody());
	gameObjects.emplace_back(m_rocket->GetRocketCone());
	gameObjects.emplace_back(m_rocket->GetRocketCap());
	gameObjects.emplace_back(m_rocket->GetRocketLauncher());

	//Generate shadow maps
	m_shadowMapManager->GenerateShadowMapResources(m_d3D->GetDeviceContext(), m_d3D->GetDepthStencilView(), m_lightManager->GetLightList(), gameObjects, m_camera->GetPosition());

	XMMATRIX viewMatrix = {};
	XMMATRIX projectionMatrix = {};

	//Clear the buffer and render the scene
	m_d3D->SetRenderTarget();
	m_d3D->BeginScene(1.0f, 0.0f, 0.0f, 1.0f);
	m_d3D->GetProjectionMatrix(projectionMatrix);
	m_camera->GetViewMatrix(viewMatrix);

	vector<shared_ptr<Light>> lightList = m_lightManager->GetLightList();

	if (m_rocket->RocketLaunched() && m_rocket->ParticleSystemActive())
	{
		lightList.emplace_back(m_rocket->GetParticleSystemLight());
	}

	const auto explosionLights = m_particleSystemManager->GetLights();

	if (!explosionLights.empty())
	{
		for (auto& light : explosionLights)
		{
			lightList.emplace_back(light);
		}
	}

	result = m_displacedFloor->Render(m_d3D->GetDeviceContext(), viewMatrix, projectionMatrix, m_shadowMapManager->GetShadowMapResources(), lightList, m_camera->GetPosition());
	if (!result) return false;

	result = m_skyBox->Render(m_d3D->GetDeviceContext(), viewMatrix, projectionMatrix, m_shadowMapManager->GetShadowMapResources(), lightList, m_camera->GetPosition());
	if (!result) return false;

	result = m_terrain->RenderTerrain(m_d3D->GetDeviceContext(), viewMatrix, projectionMatrix, m_shadowMapManager->GetShadowMapResources(), lightList, m_camera->GetPosition());
	if (!result) return false;

	result = m_rocket->RenderRocket(m_d3D, viewMatrix, projectionMatrix, m_shadowMapManager->GetShadowMapResources(), lightList, m_camera->GetPosition());
	if (!result) return false;

	m_d3D->DisableDepthStencil();
	m_d3D->EnableAlphaBlending();

	result = m_particleSystemManager->Render(m_d3D->GetDeviceContext(), viewMatrix, projectionMatrix, m_camera->GetPosition());
	if (!result) return false;

	m_d3D->EnabledDepthStencil();
	m_d3D->DisableAlphaBlending();

	TwDraw();

	m_d3D->EndScene();

	return true;
}

void D3DApplication::ResetToInitialState() const
{
	m_rocket->ResetRocketState();
	m_terrain->ResetTerrainState();
	m_particleSystemManager->ResetParticleSystems();
}

void D3DApplication::LaunchRocket() const
{
	m_rocket->LaunchRocket();
}

void D3DApplication::RotateRocketLeft() const
{
	m_rocket->AdjustRotationLeft();
}

void D3DApplication::RotateRocketRight() const
{
	m_rocket->AdjustRotationRight();
}

void D3DApplication::ChangeCameraMode(const int cameraMode)
{
	m_cameraMode = cameraMode;

	switch (m_cameraMode)
	{
	case 0:
		const auto position = m_rocket->GetLauncherPosition();
		m_camera->SetPosition(position.x, position.y, position.z - 10.0f);
		m_camera->SetRotation(0.0f, 0.0f, 0.0f);
		m_updateCamera = false;
		break;
	case 1:
		m_camera->SetPosition(0.0f, 10.0f, -60.0f);
		m_camera->SetRotation(0.0f, 05.0f, 0.0f);
		m_updateCamera = false;
		break;
	case 2:
		m_camera->SetRotation(0.0f, 0.0f, 0.0f);
		m_updateCamera = true;
		break;
	case 3:
		m_camera->SetRotation(0.0f, 0.0f, 0.0f);
		m_updateCamera = true;
		break;
	case 4:
		m_camera->SetRotation(0.0f, 0.0f, 0.0f);
		m_updateCamera = true;
		break;
	default:
		break;
	}
}

void D3DApplication::UpdateCameraPosition() const
{
	if (m_updateCamera)
	{
		switch (m_cameraMode)
		{
		case 2:
			const auto rocketPosition = m_rocket->GetLookAtRocketPosition();
			m_camera->SetPosition(rocketPosition.x, rocketPosition.y, rocketPosition.z - 20.0f);
			break;
		case 3:
			const auto rocketConePosition = m_rocket->GetLookAtRocketConePosition();
			m_camera->SetPosition(rocketConePosition.x, rocketConePosition.y, rocketConePosition.z - 3.0f);
			break;
		case 4:
			const auto rocketBodyPosition = m_rocket->GetLookAtRocketPosition();
			m_camera->SetPosition(rocketBodyPosition.x, rocketBodyPosition.y, rocketBodyPosition.z - 3.0f);
			break;
		default:
			break;
		}
	}
}

void D3DApplication::ToggleRenderOption()
{
	m_renderToggle++;

	if (m_renderToggle == 5) m_renderToggle = 0;

	switch (m_renderToggle)
	{
		case 0:
			m_shaderManager->GetTextureDisplacementShader()->SetRenderModeStates(0, 0, 0);
			break;
		case 1:
			m_d3D->EnableWireFrame();
			break;
		case 2:
			m_shaderManager->GetTextureDisplacementShader()->SetRenderModeStates(1, 0, 1);
			m_d3D->DisableWireFrame();
			break;
		case 3:
			m_shaderManager->GetTextureDisplacementShader()->SetRenderModeStates(0, 1, 1);
			break;
		case 4:
			m_shaderManager->GetTextureDisplacementShader()->SetRenderModeStates(0, 1, 0);
			break;
		default: return;
	}
}

void D3DApplication::AddTimeScale(const int number)
{
	m_timeScale += number;
	if (m_timeScale < 1) m_timeScale = 1;
}