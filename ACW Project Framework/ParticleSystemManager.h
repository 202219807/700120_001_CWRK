#pragma once
#include <memory>
#include "Smoke.h"
#include "Fire.h"

using namespace std;

class ParticleSystemManager
{
public:
	ParticleSystemManager();
	ParticleSystemManager(const ParticleSystemManager& other); //Copy Constructor
	ParticleSystemManager(ParticleSystemManager&& other) noexcept; // Move Constructor
	~ParticleSystemManager();

	ParticleSystemManager& operator = (const ParticleSystemManager& other); // Copy Assignment Operator
	ParticleSystemManager& operator = (ParticleSystemManager&& other) noexcept; // Move Assignment Operator

	const bool ExplosionExists() const;
	const vector<shared_ptr<Light>>& GetLights() const;

	void ResetParticleSystems();
	void GenerateExplosion(ID3D11Device* const device, const XMFLOAT3& explosionPosition, const float blastRadius, const shared_ptr<ResourceManager>& resourceManager);
	void Update(const float dt);

	bool Render(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMFLOAT3& cameraPosition) const;

private:
	bool			          m_explosion;
	float			          m_timeSinceExplosion;

	unsigned int	          m_smokeRenderCount;
	unsigned int			  m_explosionRenderCount;

	vector<shared_ptr<Light>> m_explosionLights;
	vector<shared_ptr<Smoke>> m_smokeParticleSystems;
	vector<shared_ptr<Fire>>  m_fireJetParticleSystems;
};

