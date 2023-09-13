#pragma once

#include "D3DContainer.h"
#include "ShaderManager.h"
#include "Terrain.h"
#include "Fire.h"

using namespace std;
using namespace DirectX;

class Rocket
{
public:
	Rocket(ID3D11Device* const device, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale, const shared_ptr<ShaderManager>& shaderManager, const shared_ptr<ResourceManager>& resourceManager);
	~Rocket() { };

	Rocket(const Rocket& other) = default;
	Rocket(Rocket&& other) noexcept = default;
	Rocket& operator = (const Rocket& other) = default;
	Rocket& operator = (Rocket&& other) noexcept = default;

	void AdjustRotationLeft() const;
	void AdjustRotationRight() const;
	void LaunchRocket();

	const bool RocketLaunched() const;
	const bool ParticleSystemActive() const;

	const XMFLOAT3& GetLauncherPosition() const;
	const XMFLOAT3& GetLookAtRocketPosition();
	const XMFLOAT3& GetLookAtRocketConePosition();

	const shared_ptr<GameObject> GetRocketBody() const;
	const shared_ptr<GameObject> GetRocketCone() const;
	const shared_ptr<GameObject> GetRocketCap() const;
	const shared_ptr<GameObject> GetRocketLauncher() const;
	const shared_ptr<Light>& GetParticleSystemLight() const;

	bool CheckForTerrainCollision(const shared_ptr<Terrain>& terrain, XMFLOAT3& outCollisionPosition, float& outBlastRadius);	
	bool RenderRocket(const shared_ptr<D3DContainer>& d3dContainer, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) const;
	void ResetRocketState();
	void UpdateRocket(const float dt);
	void UpdateLightPosition() const;

private:
	shared_ptr<GameObject>	m_rocketCone;
	shared_ptr<GameObject>	m_rocketBody;
	shared_ptr<GameObject>	m_rocketCap;
	shared_ptr<GameObject>	m_rocketLauncher;
	shared_ptr<Light>		m_rocketLight;
	shared_ptr<Fire>		m_rocketEngine;

	bool m_initializationFailed;
	bool m_rocketLaunched;
	bool m_changedParticleSystem;
	bool m_particleSystemActive;

	float m_blastRadius;
	float m_initialVelocity;
	float m_gravity;
	
	XMFLOAT2 m_velocity;
	XMFLOAT2 m_angularVelocity;

	XMFLOAT3 m_initialLauncherPosition;
	XMFLOAT3 m_initialLauncherRotation;
	XMFLOAT3 m_lookAtRocketPosition;
	XMFLOAT3 m_lookAtRocketConePosition;
};