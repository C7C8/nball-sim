#pragma once

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Hydra.h" //Needed to get the renderer.
#include "../utility/Logger.h"
#include "Texture.h"

using std::string;
using std::unordered_map;

namespace Hydra
{
    /**
    * \brief Singleton class for handeling all texture operations.
    */
	class TextureManager
	{
	public:
		static TextureManager* getInstance();

		void freeAll();
		void loadTexture(string filename, string name, bool blending = false);
		Texture getTexture(string name);
	protected:
		static TextureManager* instance;
		TextureManager();
		~TextureManager();

		unordered_map<string, Texture> textures;
		Log* log;
	};
}
