#include "ShaderManager.h"

ShaderManager::ShaderManager(ID3D11Device* const device, HWND const hwnd) : 
	m_initializationFailed(false), 
	m_colourShader(nullptr), 
	m_depthShader(nullptr), 
	m_lightShader(nullptr), 
	m_reflectionShader(nullptr),
	m_texture2DShader(nullptr), 
	m_textureCubeShader(nullptr), 
	m_textureDisplacementShader(nullptr), 
	m_textureNormalShader(nullptr), 
	m_textureNormalSpecularShader(nullptr)
{
	m_colourShader = make_shared<ColourShader>(device, hwnd);

	if (m_colourShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the colour shader", "Error", MB_OK);
		return;
	}

	m_depthShader = make_shared<DepthShader>(device, hwnd);

	if (m_depthShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the depth shader", "Error", MB_OK);
		return;
	}

	m_lightShader = make_shared<LightShader>(device, hwnd);

	if (m_lightShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the light shader", "Error", MB_OK);
		return;
	}

	m_reflectionShader = make_shared<ReflectionShader>(device, hwnd);

	if (m_reflectionShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the reflection shader", "Error", MB_OK);
		return;
	}

	m_texture2DShader = make_shared<Texture2DShader>(device, hwnd);

	if (m_texture2DShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the texture 2D shader", "Error", MB_OK);
		return;
	}

	m_textureCubeShader = make_shared<TextureCubeShader>(device, hwnd);

	if (m_textureCubeShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Colour not initialize the texture cube shader", "Error", MB_OK);
		return;
	}

	m_textureDisplacementShader = make_shared<TextureDisplacement>(device, hwnd);

	if (m_textureDisplacementShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the texture displacement shader", "Error", MB_OK);
		return;
	}

	m_textureNormalShader = make_shared<TextureNormalMappingShader>(device, hwnd);

	if (m_textureNormalShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the texture normal shader", "Error", MB_OK);
		return;
	}

	m_textureNormalSpecularShader = make_shared<TextureNormalSpecularShader>(device, hwnd);

	if (m_textureNormalSpecularShader->GetInitializationState())
	{
		m_initializationFailed = true;
		MessageBox(hwnd, "Could not initialize the texture normal specular shader", "Error", MB_OK);
		return;
	}
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::GetInitializationState() const
{
	return m_initializationFailed;
}

const shared_ptr<Shader>& ShaderManager::GetColourShader() const 
{
	return m_colourShader;
}

const shared_ptr<Shader>& ShaderManager::GetDepthShader() const
{
	return m_depthShader;
}

const shared_ptr<Shader>& ShaderManager::GetLightShader() const 
{
	return m_lightShader;
}

const shared_ptr<Shader>& ShaderManager::GetReflectionShader() const
{
	return m_reflectionShader;
}

const shared_ptr<Shader>& ShaderManager::GetTexture2DShader() const 
{
	return m_texture2DShader;
}

const shared_ptr<Shader>& ShaderManager::GetTextureCubeShader() const
{
	return m_textureCubeShader;
}

const shared_ptr<Shader>& ShaderManager::GetTextureDisplacementShader() const
{
	return m_textureDisplacementShader;
}

const shared_ptr<Shader>& ShaderManager::GetTextureNormalShader() const
{
	return m_textureNormalShader;
}

const shared_ptr<Shader>& ShaderManager::GetTextureNormalSpecularShader() const
{
	return m_textureNormalSpecularShader;
}