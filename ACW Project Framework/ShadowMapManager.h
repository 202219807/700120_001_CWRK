#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Shader.h"
#include "GameObject.h"
#include "RenderToTexture.h"

using namespace std;

class ShadowMapManager
{
public:
	ShadowMapManager(HWND const hwnd, ID3D11Device* const device, const shared_ptr<Shader>& depthShader, const int lightCount, const int shadowMapWidth, const int shadowMapHeight);
	~ShadowMapManager();

	ShadowMapManager(const ShadowMapManager& other) = default;
	ShadowMapManager(ShadowMapManager&& other) noexcept = default;
	ShadowMapManager& operator= (const ShadowMapManager& other) = default;
	ShadowMapManager& operator= (ShadowMapManager&& other) noexcept = default;

	void AddShadowMap(ID3D11Device* const device, const int shadowMapWidth, const int shadowMapHeight);

	bool GetInitializationState() const;
	bool GenerateShadowMapResources(ID3D11DeviceContext* const deviceContext, ID3D11DepthStencilView* const depthStencilView, const vector<shared_ptr<Light>>& pointLightList, const vector<shared_ptr<GameObject>>& gameObjects, const XMFLOAT3& cameraPosition);

	const vector<ID3D11ShaderResourceView*>& GetShadowMapResources() const;

private:
	shared_ptr<Shader>							m_depthShader;
	vector<shared_ptr<RenderToTexture>>			m_renderToTextures;
	vector<ID3D11ShaderResourceView*>			m_shadowMapShaderResources;
	bool										m_initializationFailed;
};

