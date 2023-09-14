#pragma once
#include "ParticleSystem.h"

class Smoke : ParticleSystem
{
public:
	Smoke(ID3D11Device* const device, HWND const hwnd, const XMFLOAT3& initialPosition, const XMFLOAT3& initialScale, const XMFLOAT3& scaleReduction, const XMFLOAT3& killScale, const float transparency, const float spawnRate, const float velocity, const shared_ptr<ResourceManager>& resourceManager);
	~Smoke() { };
	
	Smoke(const Smoke& other) = default;
	Smoke(Smoke&& other) noexcept = default;
	Smoke& operator= (const Smoke& other) = default;
	Smoke& operator= (Smoke&& other) noexcept = default;

	void Update(const float dt);
	bool Render(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMFLOAT3& cameraPosition) const;
};

