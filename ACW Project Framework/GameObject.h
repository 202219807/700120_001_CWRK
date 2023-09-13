#pragma once

#include "Model.h"
#include "Texture.h"
#include "Position.h"
#include "Rotation.h"
#include "Scale.h"
#include "Shader.h"
#include "Light.h"
#include "Physics.h"

using namespace std;
using namespace DirectX;

enum class ModelType {
	Sphere,
	SphereInverted,
	HighPolyCube,
	LowPolyCube,
	Plane,
	HighPolyCylinder,
	LowPolyCylinder,
	Cone,
	Quad
};

class GameObject
{
public:

	GameObject();
	//GameObject(ID3D11Device* device, const ModelType modelType, ResourceManager* resourceManager); //GameObject with model
	//GameObject(ID3D11Device* device, const ModelType modelType, const WCHAR* textureFileName, ResourceManager* resourceManager); //GameObject with model/ texture
	virtual ~GameObject();

	GameObject(const GameObject& other) = default;
	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator= (const GameObject& other) = default;
	GameObject& operator= (GameObject&& other) noexcept = default;

	void AddParentGameObject(const shared_ptr<GameObject>& parentObject);
	void AddModelComponent(ID3D11Device* const device, const ModelType modelType, const shared_ptr<ResourceManager>& resourceManager);
	void AddTextureComponent(ID3D11Device* const device, const vector<const WCHAR*>& textureFileNames, const shared_ptr<ResourceManager>& resourceManager);
	void AddShaderComponent(const shared_ptr<Shader>& shader);
	void AddPhysicsComponent(const bool useGravity, const float mass, const float drag, const float angularDrag);

	void AddPositionComponent();
	void AddPositionComponent(const XMFLOAT3& position);
	void AddPositionComponent(const float x, const float y, const float z);
	void AddPositionComponent(const vector<XMFLOAT3>& positions);

	void SetPosition(const XMFLOAT3& position);
	void SetPosition(const float x, const float y, const float z);
	void SetPosition(const vector<XMFLOAT3>& positions);

	void AddRotationComponent();
	void AddRotationComponent(const XMFLOAT3& rotation);
	void AddRotationComponent(const float x, const float y, const float z);
	void AddRotationComponent(const vector<XMFLOAT3>& rotations);

	void SetRotation(const XMFLOAT3& rotation);
	void SetRotation(const float x, const float y, const float z);
	void SetRotation(const vector<XMFLOAT3>& rotations);

	void AddScaleComponent();
	void AddScaleComponent(const XMFLOAT3& scale);
	void AddScaleComponent(const float x, const float y, const float z);
	void AddScaleComponent(const vector<XMFLOAT3>& scales);

	void SetScale(const XMFLOAT3& scale);
	void SetScale(const float x, const float y, const float z);
	void SetScale(const vector<XMFLOAT3>& scales);

	void SetTessellationVariables(const float& maxTessellationDistance, const float& minTessellationDistance, const float& maxTessellationFactor, const float& minTessellationFactor);
	void SetDisplacementVariables(const float &mipInterval, const float &mipClampMinimum, const float &mipClampMaximum, const float &displacementPower);
	
	//const XMFLOAT3&								GetPosition()				const;
	//const XMFLOAT4&								GetRotation()				const;
	//const XMFLOAT3&								GetScale()					const;

	const shared_ptr<Model>&					GetModelComponent()			const;
	const shared_ptr<Position>&					GetPositionComponent()		const;
	const shared_ptr<Rotation>&					GetRotationComponent()		const;
	const shared_ptr<Scale>&					GetScaleComponent()			const;
	const shared_ptr<Shader>&					GetShaderComponent()		const;
	const shared_ptr<Physics>&					GetPhysicsComponent()		const;

	const vector<ID3D11ShaderResourceView*>&	GetTextureList()			const;

	void UpdateInstanceData();
	bool GetInitializationState() const;
	bool Update();
	bool Render(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) const;	
	int  GetIndexCount() const;

private:

	shared_ptr<GameObject>	m_parentObject;
	shared_ptr<Model>		m_model;
	shared_ptr<Position>	m_position;
	shared_ptr<Rotation>	m_rotation;
	shared_ptr<Scale>		m_scale;
	shared_ptr<Shader>		m_shader;
	shared_ptr<Texture>		m_texture;
	shared_ptr<Physics>		m_physics;

	bool					m_initializationFailed;
	bool					m_updateInstanceData;

	//Tessellation variables
	float					m_maxTessellationDistance;
	float					m_minTessellationDistance;
	float					m_maxTessellationFactor;
	float					m_minTessellationFactor;

	//Displacement variables
	float					m_mipInterval;
	float					m_mipClampMinimum;
	float					m_mipClampMaximum;
	float					m_displacementPower;
};

