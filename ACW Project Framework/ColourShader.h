#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
#include "Shader.h"

using namespace std;
using namespace DirectX;

class ColourShader : public Shader
{
public:

	ColourShader(ID3D11Device* const device, HWND const hwnd);
	~ColourShader() override;

	ColourShader(const ColourShader& other) = default;
	ColourShader(ColourShader && other) noexcept = default;
	ColourShader& operator= (const ColourShader& other) = default;
	ColourShader& operator= (ColourShader && other) noexcept = default;

	bool Render(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& textures, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) override;

private:
	bool SetColourShaderParameters(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMFLOAT3& cameraPosition);
	void RenderShader(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount) const;

	ID3D11InputLayout* m_inputLayout;
};