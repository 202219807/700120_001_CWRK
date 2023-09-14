#pragma once

#include <D3D11.h>
#include <DirectXMath.h>
#include <DDSTextureLoader.h>

#include <map>
#include <memory>
#include <fstream>
#include <vector>

using namespace std;
using namespace DirectX;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other) = default;
	ResourceManager(ResourceManager&& other) noexcept = default;
	ResourceManager& operator= (const ResourceManager& other) = default;
	ResourceManager& operator= (ResourceManager&& other) noexcept = default;

	bool GetModel(ID3D11Device* const device, const char* const modelFileName, ID3D11Buffer* &vertexBuffer, ID3D11Buffer* &indexBuffer);
	bool GetTexture(ID3D11Device* const device, const WCHAR* const textureFileName, ID3D11ShaderResourceView* &texture);
	int  GetSizeOfVertexType() const;
	int  GetIndexCount(const char* modelFileName) const;

private:
	bool LoadModel(ID3D11Device* const device, const char* const modelFileName);
	bool LoadTexture(ID3D11Device* const device, const WCHAR* textureFileName);

	struct VertexType 
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
	};

	map<const char*,  int>							m_indexCount;
	map<const char*,  int>							m_instanceCount;
	map<const char*,  ID3D11Buffer*>				m_vertexBuffers;
	map<const char*,  ID3D11Buffer*>				m_indexBuffers;
	map<const WCHAR*, ID3D11ShaderResourceView*>	m_textures;
};

