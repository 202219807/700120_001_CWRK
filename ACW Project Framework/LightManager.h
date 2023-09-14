#pragma once
#include <vector>

#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"

using namespace std;

class LightManager
{
public:
	LightManager() {};
	~LightManager() {};

	LightManager(const LightManager& other) = default;
	LightManager(LightManager&& other) noexcept = default;
	LightManager& operator= (const LightManager& other) = default;
	LightManager& operator= (LightManager&& other) noexcept = default;

	const vector<shared_ptr<Light>>& GetLightList() const;
	const vector<shared_ptr<DirectionalLight>>& GetDirectionalLightList() const;
	
	void AddLight(const XMFLOAT3& lightPosition, const XMFLOAT3& lightPointPosition, const XMFLOAT4& ambientColour, const XMFLOAT4& diffuseColour, const XMFLOAT4& specularColour, const float specularPower, const float projectionScreenWidth, const float projectionScreenHeight, const float screenNear, const float screenDepth, const bool orbit, const bool directionalLight);

private:
	vector<shared_ptr<Light>> m_lights;
};

