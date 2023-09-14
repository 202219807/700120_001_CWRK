#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>
#include "Shader.h"

using namespace DirectX;
using namespace std;

class TextureCubeShader : public Shader
{
public:
	TextureCubeShader(ID3D11Device* const device, HWND const hwnd);
	~TextureCubeShader();

	TextureCubeShader(const TextureCubeShader& other) = default;
	TextureCubeShader(TextureCubeShader&& other) noexcept = default;
	TextureCubeShader& operator= (const TextureCubeShader& other) = default;
	TextureCubeShader& operator= (TextureCubeShader&& other) noexcept = default;

	bool Render(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& textures, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) override;

private:
	bool SetTextureShaderParameters(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& textures, const XMFLOAT3& cameraPosition);
	void RenderShader(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount) const;

	ID3D11InputLayout* m_inputLayout;
	ID3D11SamplerState* m_sampleState;
};

