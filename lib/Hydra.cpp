#include "Hydra.h"

namespace Hydra
{
	HydraEngine* HydraEngine::instance = NULL;
	HydraEngine* HydraEngine::getInstance()
	{
		if (instance == NULL)
			instance = new HydraEngine;
		return instance;
	}
	HydraEngine::HydraEngine()
	{
	    systemLog = Logger::getInstance();
        systemLog->newLog("sysLog", "sysLog");

		wXSize = 800;
		wYSize = 600;
		window = NULL;
		renderer = NULL;
		wTitle = "Hydra 2D Game Engine V3";
		fullscreen = false;
	}
	bool HydraEngine::init()
	{
	    systemLog->log("Initializing Hydra Engine " + getVNumber() + " (prepare for a wild ride!)");
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_PNG);
		systemLog->log("Successfully initialized SDL");

		window = SDL_CreateWindow(wTitle.c_str(),  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		wXSize, wYSize, SDL_WINDOW_SHOWN);
		if (window == NULL)
        {
            systemLog->log("Error: Failed to create SDL window!", error);
            return false;
        }

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
        {
            systemLog->log("Error: Failed to create renderer!", error);
            return false;
        }
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);	//Black

		srand((int)time(0));
		setWTitle("Hydra Engine " + getVNumber());
		systemLog->log("Successfully started the Hydra Engine!");
		return true;
	}
    void HydraEngine::queueTexture(Texture texture)
    {
        renderList.push(texture);
    }
    void HydraEngine::renderAll()
    {
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
                             texture.angle.getDegs(),
                             &texture.center,
                             SDL_FLIP_NONE);
        }
        SDL_RenderPresent(renderer);
    }

	void HydraEngine::shutdown()
	{
	    systemLog->log("Shutting down Hydra Engine...");
	    TextureManager::getInstance()->freeAll();
		IMG_Quit();
		//TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		window = NULL;
		renderer = NULL;
		systemLog->log("Successfully shut down Hydra Engine");
		systemLog->flushLogBuffers();
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
		systemLog->log("Set window title to " + wTitle);
	}
	string HydraEngine::getWTitle() const
	{
		return wTitle;
	}
    string HydraEngine::getVNumber() const
    {
        stringstream version;
        version << AutoVersion::STATUS_SHORT << AutoVersion::MAJOR << "." << AutoVersion::MINOR << "." << AutoVersion::REVISION << "b" << AutoVersion::BUILD;
        return version.str();
    }
	SDL_Renderer* HydraEngine::getRenderer() const
	{
		return renderer;
	}
};
