#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <queue>

#include "graphics/TextureManager.h"
#include "graphics/Texture.h"
#include "utility/Logger.h"
#include "Timer.h"
#include "math/hmath.h"
#include "../version.h"

using std::string;
using std::stringstream;
using std::queue;
using std::pair;

namespace Hydra
{
	class HydraEngine
	{
	public:
		static HydraEngine* getInstance();                              //!< Returns pointer to instance of HydraEngine
		void shutdown();                                                //!< Automatically shuts down all Engine and SDL2 components
		void update();                                                  //!< Has no current function.
		bool init();                                                    //!< Automatically initializes all Engine and SDL2 components.

		//Graphics stuff
		void queueTexture(Texture texture);                             //!< Accepts a texture object and adds it into the queue. First in, first rendered.
		void renderAll();                                               //!< Renders all textures stored in the render queue.

		//Getters and setters
		void setWSize(int newXSize = 800, int newYSize = 600);          //!< Sets the window size to the designated size
		void setWTitle(string newTitle);                                //!< Sets the window title to the designated title

		int getWXSize() const;                                          //!< Returns the width of the window.
		int getWYSize() const;                                          //!< Returns the height of the window.
		void setFullscreen(bool newFull);                               //!< Set whether the window is fullscreen or not.
		bool getFullscreen();                                           //!< Get whether the window is fullscreen or not.
		pair<int, int> getNativeWSize();                                //!< Returns the native window size in X, Y form.

		string getWTitle() const;                                       //!< Returns a string containing the title of the window.
		string getVNumber() const;                                      //!< Returns a string containing the version number information
		SDL_Renderer* getRenderer() const;
	private:
	    //Core engine members
	    Logger* systemLog;

		//Singleton stuff
		static HydraEngine* instance;
		HydraEngine();
		~HydraEngine();

		//Window & core graphics stuff
		bool fullscreen;
		int wYSize;
		int wXSize;
		SDL_Window* window;
		SDL_Renderer* renderer;
		string wTitle;
		queue<Texture> renderList;
	};
}
