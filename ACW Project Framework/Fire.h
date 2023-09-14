#pragma once
#include "ParticleSystem.h"

class Fire : public ParticleSystem
{
public:
	Fire(ID3D11Device* const device, HWND const hwnd, const ModelType modelType, const XMFLOAT3& initialPosition, const XMFLOAT3& initialScale, const XMFLOAT3& finalScale, const float transparency, const float lifeCycle, const float velocity, const int particleDensity, const shared_ptr<ResourceManager>& resourceManager);
	~Fire() { };

	Fire(const Fire& other) = default;
	Fire(Fire&& other) noexcept = default;
	Fire& operator= (const Fire& other) = default;
	Fire& operator= (Fire&& other) noexcept = default;

	void Update(const float dt);
	bool Render(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMFLOAT3& cameraPosition) const;
};

