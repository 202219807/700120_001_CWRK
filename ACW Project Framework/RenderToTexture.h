#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Shader.h"
#include "GameObject.h"

using namespace std;
using namespace DirectX;

class RenderToTexture
{
public:
	RenderToTexture(ID3D11Device* const device, const int textureWidth, const int textureHeight);
	~RenderToTexture(); 

	RenderToTexture(const RenderToTexture& other) = default;
	RenderToTexture(RenderToTexture&& other) noexcept = default;
	RenderToTexture& operator= (const RenderToTexture& other) = default;
	RenderToTexture& operator= (RenderToTexture&& other) noexcept = default;

	ID3D11ShaderResourceView* GetShaderResourceView() const;

	bool GetInitializationState() const;
	bool RenderObjectsToTexture(ID3D11DeviceContext* const deviceContext, ID3D11DepthStencilView* const depthStencilView, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<shared_ptr<Light>>& pointLightList, const vector<shared_ptr<GameObject>>& gameObjects, const XMFLOAT3& cameraPosition) const;
	
	void SetShader(const shared_ptr<Shader>& shader);

private:
	void SetRenderTarget(ID3D11DeviceContext* const deviceContext, ID3D11DepthStencilView* const depthStencilView) const;
	void ClearRenderTarget(ID3D11DeviceContext* const deviceContext, ID3D11DepthStencilView* const depthStencilView, const XMFLOAT4& RGBA) const;

	shared_ptr<Shader> m_shader;

	ID3D11ShaderResourceView* m_shaderResourceView;
	ID3D11Texture2D* m_renderTargetTexture;
	ID3D11RenderTargetView* m_renderTargetView;

	bool m_initializationFailed;
};

