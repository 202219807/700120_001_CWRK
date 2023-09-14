#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>
#include "Shader.h"

using namespace DirectX;
using namespace std;

class DepthShader : public Shader
{
public:
	DepthShader(ID3D11Device* const device, HWND const hwnd);
	~DepthShader() override;

	DepthShader(const DepthShader& other) = default;
	DepthShader(DepthShader&& other) noexcept = default;
	DepthShader& operator= (const DepthShader& other) = default;
	DepthShader& operator= (DepthShader&& other) noexcept = default;

	bool Render(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& textures, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) override;

private:
	bool SetDepthShaderParameters(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& textures, const XMFLOAT3& cameraPosition);
	void RenderShader(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount) const;

	ID3D11InputLayout* m_inputLayout;
	ID3D11SamplerState* m_sampleStateWrap;

};

