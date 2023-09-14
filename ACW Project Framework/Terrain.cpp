#include "Terrain.h"

Terrain::Terrain(
	ID3D11Device* const device, 
	const XMFLOAT3& voxelArea, 
	const XMFLOAT3& cubeScale, 
	const shared_ptr<Shader>& shader, 
	const shared_ptr<ResourceManager>& resourceManager
) : 
	m_initializationFailed(false)
{
	const auto x = static_cast<int>(voxelArea.x / 2);
	const auto y = static_cast<int>(voxelArea.y);
	const auto z = static_cast<int>(voxelArea.z / 2);

	const auto cubeScaleX = static_cast<int>(cubeScale.x);
	const auto cubeScaleY = static_cast<int>(cubeScale.y);
	const auto cubeScaleZ = static_cast<int>(cubeScale.z);

	vector<const WCHAR*> textureNames;

	textureNames.clear();
	textureNames.push_back(L"Stylized_Stone_Floor_005_basecolor.dds");
	textureNames.push_back(L"Stylized_Stone_Floor_005_normal.dds");
	textureNames.push_back(L"Stylized_Stone_Floor_005_roughness.dds");
	textureNames.push_back(L"Stylized_Stone_Floor_005_height.dds");

	for (auto i = -x * cubeScaleX; i < x; i += cubeScaleX)
	{
		for (auto j = -y * cubeScaleY - cubeScaleY / 2; j < -(cubeScaleY / 2); j += cubeScaleY)
		{
			for (auto k = -z * cubeScaleZ; k < z; k += cubeScaleZ)
			{
				m_initialTerrainPositions.emplace_back(XMFLOAT3(i, j, k));
			}
		}
	}

	AddScaleComponent(cubeScale);
	AddPositionComponent(m_initialTerrainPositions);
	AddRotationComponent(0.0f, 0.0f, 0.0f);
	AddPhysicsComponent(true, 1.0f, 0.0f, 0.0f);
	AddModelComponent(device, ModelType::LowPolyCube, resourceManager);
	AddTextureComponent(device, textureNames, resourceManager);
	AddShaderComponent(shader);
	SetTessellationVariables(1.0f, 20.0f, 3.0f, 1.0f);

	if (GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(nullptr, "Could not initialize the model object.", "Error", MB_OK);
		return;
	}
}

Terrain::~Terrain()
{
}

void Terrain::Reset()
{
	const auto terrainPositions = GetPositionComponent()->GetPositions();

	for (unsigned int i = 0; i < terrainPositions.size(); i++)
	{
		if (terrainPositions[i].y < -200.0f)
		{
			GetPositionComponent()->TranslatePositionAt(XMFLOAT3(0.0f, 500.0f, 0.0f), i);
			UpdateInstanceData();
		}
	}
}

void Terrain::Update()
{
	GameObject::Update();
}

bool Terrain::Render(
	ID3D11DeviceContext* const deviceContext, 
	const XMMATRIX& viewMatrix, 
	const XMMATRIX& projectionMatrix, 
	const vector<ID3D11ShaderResourceView*>& depthTextures, 
	const vector<shared_ptr<Light>>& pointLightList,
	const XMFLOAT3& cameraPosition
) const
{
	return GameObject::Render(deviceContext, viewMatrix, projectionMatrix, depthTextures, pointLightList, cameraPosition);
}
