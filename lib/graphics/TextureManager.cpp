#include "TextureManager.h"

namespace Hydra
{
	TextureManager* TextureManager::instance = nullptr;
	TextureManager::TextureManager()
	{
        log = Logger::getInstance()->getLog("sysLog");
	}
	TextureManager::~TextureManager()
	{
	}
	TextureManager* TextureManager::getInstance()
	{
		if (instance == nullptr)
			instance = new TextureManager;
		return instance;
	}

	/// \brief Destroys all textures currently stored in the texture manager.
	void TextureManager::freeAll()
	{
        for (auto iter = textures.begin(); iter != textures.end(); iter++)
            SDL_DestroyTexture((*iter).second.texture);
	}

	/// \brief Loads a texture from file.
	/// @param filename The path to the file. Accepts most image formats.
	/// @param name The name this texture will be referred to with from now on.
	void TextureManager::loadTexture(string filename, string name, bool blending)
	{
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            log->log("Error loading image " + name + ": " + IMG_GetError(), error);
            return;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(HydraEngine::getInstance()->getRenderer(), surface);
        if (texture == nullptr)
        {
            log->log("Error creating texture from image " + name + ": " + SDL_GetError(), error);
            return;
        }

        Texture newTexture;
        newTexture.texture = texture;

        SDL_QueryTexture(texture, NULL, NULL, &newTexture.w, &newTexture.h);
        newTexture.scale.w = newTexture.w;
        newTexture.scale.h = newTexture.h;
        newTexture.clip.x = 0;
        newTexture.clip.y = 0;
        newTexture.clip.h = newTexture.h;
        newTexture.clip.w = newTexture.w;
        newTexture.angle.setDegs(0);
        newTexture.center.x = newTexture.w / 2;
        newTexture.center.y = newTexture.h / 2;
        SDL_FreeSurface(surface);

        log->log("Successfully loaded image " + name + " at " + filename, resource);
        textures[name] = newTexture;
	}

    /// \brief Returns a new texture object with default settings.
    Texture TextureManager::getTexture(string name)
    {
        if (textures.count(name) == 0)
        {
            log->log("Could not get texture under name " + name, error);
            Texture badTexture;
            return badTexture; //No textures at this name, sorry.
        }

        return textures[name]; //Hash tables are beautiful.
    }
}
