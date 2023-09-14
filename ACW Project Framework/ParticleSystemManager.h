#pragma once
#include <memory>
#include "Smoke.h"
#include "Fire.h"

using namespace std;

class ParticleSystemManager
{
public:
	ParticleSystemManager();
	~ParticleSystemManager();

	ParticleSystemManager(const ParticleSystemManager& other) = default;
	ParticleSystemManager(ParticleSystemManager&& other) noexcept = default;
	ParticleSystemManager& operator= (const ParticleSystemManager& other) = default;
	ParticleSystemManager& operator= (ParticleSystemManager&& other) noexcept = default;

	bool Render(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMFLOAT3& cameraPosition) const;
	void Reset();
	void Update(const float dt);
	
	void GenerateExplosion(ID3D11Device* const device, const XMFLOAT3& explosionPosition, const float blastRadius, const shared_ptr<ResourceManager>& resourceManager);
	const bool ExplosionExists() const;

	const vector<shared_ptr<Light>>& GetLights() const;

private:
	vector<shared_ptr<Smoke>>	m_smokeEffect;
	vector<shared_ptr<Fire>>	m_fireEffect;
	vector<shared_ptr<Light>>	m_explosionLights;
	
	bool						m_explosion;
	float						m_timeSinceExplosion;
	unsigned int				m_explosionRenderCount;
	unsigned int				m_smokeRenderCount;
};

