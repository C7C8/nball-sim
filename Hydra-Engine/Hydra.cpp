#include "Hydra.h"

namespace Hydra
{
	HydraEngine* HydraEngine::instance = NULL;

	/**
	 * @brief Returns pointer to the instance of Hydra engine.
	 * @return
	 */
	HydraEngine* HydraEngine::getInstance()
	{
		if (instance == NULL)
			instance = new HydraEngine;
		return instance;
	}

	/**
	 * @brief Constructor
	 */
	HydraEngine::HydraEngine()
	{
		wXSize = 800;
		wYSize = 600;
		window = NULL;
		renderer = NULL;
		wTitle = "Hydra 2D Game Engine V3";
		fullscreen = false;
	}

	/**
	 * @brief Intializes EVERYTHING - window, renderer, random number generator, etc.
	 * @return Success status of initialization
	 */
	bool HydraEngine::init()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_PNG);

		window = SDL_CreateWindow(wTitle.c_str(),  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		wXSize, wYSize, SDL_WINDOW_SHOWN);
		if (window == NULL)
            return false;

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
            return false;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);	//Black

		srand((int)time(0));
		setWTitle("Hydra Engine");
		return true;
	}

	/**
	 * @brief Queue a texture to be rendered. Order matters -- first in, first out.
	 * @param texture A texture object to be rendered.
	 */
	void HydraEngine::queueTexture(Texture texture)
    {
        renderList.push(texture);
    }

	/**
	 * @brief Renders all textures on the render queue.
	 */
	void HydraEngine::renderAll()
    {
		//Commented out because... just because.
		//Okay, fine, it's in the name of the Holy Low Bar.
        //SDL_RenderClear(renderer);

        while (renderList.size() > 0)
        {
            Texture texture = renderList.front(); //Get and remove the first element. First in, first out.
            renderList.pop();

            if (texture.blending)
                SDL_SetTextureBlendMode(texture.texture, SDL_BLENDMODE_BLEND);
            else
                SDL_SetTextureBlendMode(texture.texture, SDL_BLENDMODE_NONE);

            SDL_SetTextureColorMod(texture.texture, texture.rgb.getR(), texture.rgb.getG(), texture.rgb.getB());
            SDL_SetTextureAlphaMod(texture.texture, texture.alpha);
            SDL_RenderCopyEx(renderer,
                             texture.texture,
                             &texture.clip,
                             &texture.scale,
                             texture.angle,
                             &texture.center,
                             SDL_FLIP_NONE);
        }
        SDL_RenderPresent(renderer);
    }

	/**
	 * @brief Shuts down the Hydra engine, destroying the windows and renderer.
	 */
	void HydraEngine::shutdown()
	{
	    TextureManager::getInstance()->freeAll();
		IMG_Quit();
		//TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		window = NULL;
		renderer = NULL;
	}

	//Getters and setters
	void  HydraEngine::setWSize(int newXSize, int newYSize)
	{
		wXSize = newXSize;
		wYSize = newYSize;
		SDL_SetWindowSize(window, wXSize, wYSize);
	}
	int HydraEngine::getWXSize() const
	{
		return wXSize;
	}
	int HydraEngine::getWYSize() const
	{
		return wYSize;
	}
	pair<int, int> HydraEngine::getNativeWSize()
	{
        SDL_DisplayMode vmode;
        SDL_GetCurrentDisplayMode(0, &vmode);
        pair<int, int> size(vmode.w, vmode.h);
        return size;
	}
	void HydraEngine::setFullscreen(bool newFull)
	{
	    //Only call window changing functions if the new status is different than the old one.
        if (newFull != fullscreen)
        {
            if (newFull)
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            else
                SDL_SetWindowFullscreen(window, 0);
        }
        fullscreen = newFull;
	}
	bool HydraEngine::getFullscreen()
	{
	    return fullscreen;
	}
	void HydraEngine::setWTitle(string newTitle)
	{
		wTitle = newTitle;
		SDL_SetWindowTitle(window, wTitle.c_str());
	}
	string HydraEngine::getWTitle() const
	{
		return wTitle;
	}
	SDL_Renderer* HydraEngine::getRenderer() const
	{
		return renderer;
	}
};
