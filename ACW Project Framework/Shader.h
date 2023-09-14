#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <fstream>
#include <atlbase.h>
#include <string>
#include <vector>
#include "Light.h"

const int MAX_LIGHTS = 16;

using namespace DirectX;
using namespace std;

class Shader
{
public:
	Shader(const string& vertexShaderFileName, const string& hullShaderFileName, const string& domainShaderFileName, const string& pixelShaderFileName, ID3D11Device* const device, HWND const hwnd);
	virtual ~Shader();

	Shader(const Shader& other) = default;
	Shader(Shader&& other) noexcept = default;
	Shader& operator= (const Shader& other) = default;
	Shader& operator= (Shader&& other) noexcept = default;

	virtual bool Render(ID3D11DeviceContext* const deviceContext, const int indexCount, const int instanceCount, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const vector<ID3D11ShaderResourceView*>& textures, const vector<ID3D11ShaderResourceView*>& depthTextures, const vector<shared_ptr<Light>>& pointLightList, const XMFLOAT3& cameraPosition) = 0;
	
	void IncrementVertexBufferResourceCount();
	void IncrementHullBufferResourceCount();
	void IncrementDomainBufferResourceCount();
	void IncrementPixelBufferResourceCount();
	
	void SetRenderModeStates(const int nonTextured, const int texturedDiffuse, const int displacementEnabled);
	const D3D11_MAPPED_SUBRESOURCE&	GetMappedSubResource() const;

	bool GetInitializationState() const;
	void SetInitializationState(const bool state);

	ID3D10Blob*	GetVertexShaderBuffer()	const;
	void SetVertexShaderBuffer(ID3D10Blob* const vertexShaderBuffer);
	
	void GetTessellationVariables(float& maxTessellationDistance, float& minTessellationDistance, float& maxTessellationFactor, float& minTessellationFactor) const;
	void GetDisplacementVariables(float& mipInterval, float& mipClampMinimum, float& mipClampMaximum, float& displacementPower) const;
	void SetTessellationVariables(const float& maxTessellationDistance, const float& minTessellationDistance, const float& maxTessellationFactor, const float& minTessellationFactor);
	void SetDisplacementVariables(const float& mipInterval, const float& mipClampMinimum, const float& mipClampMaximum, const float& displacementPower);

	ID3D11Buffer* GetMatrixBuffer() const;
	ID3D11Buffer* GetCameraBuffer() const;
		
	int	GetVertexBufferResourceCount() const;
	int	GetHullBufferResourceCount() const;
	int GetDomainBufferResourceCount() const;
	int GetPixelBufferResourceCount() const;
	

protected:
	bool SetShaderParameters(ID3D11DeviceContext* const deviceContext, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, const XMFLOAT3& cameraPosition);
	void SetShader(ID3D11DeviceContext* const deviceContext) const;
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND const hwnd, const LPCSTR& shaderFileName) const;

private:
	struct MatrixBufferType 
	{
		XMMATRIX				viewMatrix;
		XMMATRIX				projectionMatrix;
	};

	struct TessellationBufferType
	{
		float					maxTessellationDistance;
		float					minTessellationDistance;
		float					maxTessellationFactor;
		float					minTessellationFactor;
	};

	struct DisplacementBuffer
	{
		float					mipInterval;
		float					mipMinimum;
		float					mipMaximum;
		float					displacementPower;
		int						displacementEnabled;
		XMFLOAT3				padding;
	};

	struct CameraBufferType
	{
		XMFLOAT3				cameraPosition;
		float					padding;
	};

	struct RenderModeBufferType
	{
		int						nonTexture;
		int						textureDiffuse;
		XMFLOAT2				padding;
	};

	D3D11_MAPPED_SUBRESOURCE	m_mappedResource;

	ID3D11VertexShader*			m_vertexShader;
	ID3D11HullShader*			m_hullShader;
	ID3D11DomainShader*			m_domainShader;
	ID3D11PixelShader*			m_pixelShader;

	ID3D10Blob*					m_vertexShaderBuffer;
	
	ID3D11Buffer*				m_matrixBuffer;
	ID3D11Buffer*				m_tessellationBuffer;
	ID3D11Buffer*				m_displacementBuffer;
	ID3D11Buffer*				m_cameraBuffer;
	ID3D11Buffer*				m_renderModeBuffer;

	bool						m_initializationFailed;

	float						m_maxTessellationDistance;
	float						m_minTessellationDistance;
	float						m_maxTessellationFactor;
	float						m_minTessellationFactor;
	float						m_mipInterval;
	float						m_mipClampMinimum;
	float						m_mipClampMaximum;
	float						m_displacementPower;
	
	int							m_vertexBufferResourceCount;
	int							m_hullBufferResourceCount;
	int							m_domainBufferResourceCount;
	int							m_pixelBufferResourceCount;
	int							m_nonTextureRenderMode;
	int							m_textureDiffuseRenderMode;
	int							m_displacementRenderMode;
};