#pragma once

#include "GameObject.h"

using namespace std;
using namespace DirectX;

class Terrain : public GameObject
{
public:
	Terrain(ID3D11Device* const device, const XMFLOAT3& voxelArea, const XMFLOAT3& cubeScale, const shared_ptr<Shader>& shader, const shared_ptr<ResourceManager>& resourceManager);
	~Terrain();

	Terrain(const Terrain& other) = default;
	Terrain(Terrain&& other) noexcept = default;
	Terrain& operator = (const Terrain& other) = default;
	Terrain& operator = (Terrain&& other) noexcept = default;

	void Reset();
	void Update();
	bool Render(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) const;

private:
	vector<XMFLOAT3> m_initialTerrainPositions;
	bool m_initializationFailed;
};

