#pragma once

#include <memory>

//Include all shader header files
#include "ColourShader.h"
#include "DepthShader.h"
#include "LightShader.h"
#include "ReflectionShader.h"
#include "Texture2DShader.h"
#include "TextureCubeShader.h"
#include "TextureDisplacement.h"
#include "TextureNormalMappingShader.h"
#include "TextureNormalSpecularShader.h"

class ShaderManager
{
public:

	ShaderManager(ID3D11Device* const device, HWND const hwnd);
	ShaderManager(const ShaderManager& other) = default;
	ShaderManager(ShaderManager&& other) noexcept = default;
	~ShaderManager();

	ShaderManager& operator= (const ShaderManager& other) = default;
	ShaderManager& operator= (ShaderManager&& other) noexcept = default;

	const shared_ptr<Shader>& GetColourShader() const;
	const shared_ptr<Shader>& GetDepthShader() const;
	const shared_ptr<Shader>& GetLightShader() const;
	const shared_ptr<Shader>& GetReflectionShader() const;
	const shared_ptr<Shader>& GetTexture2DShader() const;
	const shared_ptr<Shader>& GetTextureCubeShader() const;
	const shared_ptr<Shader>& GetTextureDisplacementShader() const;
	const shared_ptr<Shader>& GetTextureNormalShader() const;
	const shared_ptr<Shader>& GetTextureNormalSpecularShader() const;

	bool GetInitializationState() const;

private:
	shared_ptr<Shader> m_colourShader;
	shared_ptr<Shader> m_depthShader;
	shared_ptr<Shader> m_lightShader;
	shared_ptr<Shader> m_reflectionShader;
	shared_ptr<Shader> m_texture2DShader;
	shared_ptr<Shader> m_textureCubeShader;
	shared_ptr<Shader> m_textureDisplacementShader;
	shared_ptr<Shader> m_textureNormalShader;
	shared_ptr<Shader> m_textureNormalSpecularShader;

	bool m_initializationFailed;
};

