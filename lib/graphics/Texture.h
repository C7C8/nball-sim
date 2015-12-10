#pragma once

#include <SDL.h>
#include "../math/Angle.h"
#include "ColorHSL.h"
#include "ColorRGB.h"

namespace Hydra
{
    class Texture
	{
	public:
		Texture();
		void free();                                        //!< Manually free this texture. Done automatically if you use TextureManager::getTexture().
		void setColor (int newR, int newG, int newB);       //!< Sets all three color values at once.

		//RGB color - direct set
		void setR(int newR);                                //!< Sets the red value.
		void setG(int newG);                                //!< Sets the green value.
		void setB(int newB);                                //!< Sets the blue value.

		//HSL color - indirect set
		void setHue(double hue);                              //!< Sets the hue value. Accepts an angle in degrees.
		void setHue(Angle hue);                               //!< Sets the hue value. Accepts an angle object.
		void setS(double sat);                              //!< Sets the saturation value.
		void setL(double lih);                              //!< Sets the lightness value.

		void setClipX(int newX);                            //!< Sets the X coordinate of the area to take a clip from.
		void setClipY(int newY);                            //!< Sets the Y coordinate of the area to take a clip from.
		void setClipH(int newH);                            //!< Sets the height of the area to take a clip from.
		void setClipW(int newW);                            //!< Sets the width of the area to take a clip from.
		void setClip(SDL_Rect newCLip);                     //!< Allows you to set the clip settings all at once using an SDL_Rect
		void setScaleW(int newW);                           //!< Set the scaling width.
		void setScaleH(int newH);                           //!< Set the scaling height.
		void setBlending(bool blend);                       //!< Set whether blending is enabled or not.
		void setAlpha(int newAlpha);                        //!< Sets the alpha setting (0-100?)
		void setCenterX(int newX);                          //!< Sets the center X coordinate of this texture - used for rotations.
		void setCenterY(int newY);                          //!< Sets the cetner Y coordinate of this texture - used for rotations.
		void setCenter(SDL_Point newPoint);                 //!< Sets the center coordinates all at once using an SDL_Point.
		void setAngle(double degrees);                      //!< Sets the angle by accepting number in the form of degrees.
		void setAngle(Angle newAngle);                      //!< Sets the angle by passing an angle object.
		void setTexture(SDL_Texture* newTexture);           //!< Sets the texture and resets current settings to match this new texture's data.
        void setX(float newX);                              //!< Sets the X coordinate.
        void setY(float newY);                              //!< Sets the Y coordinate.

        //RGB color - direct get
        int getR() const;                                   //!< Gets the red value of this texture.
		int getG() const;                                   //!< Gets the green value of this texture.
		int getB() const;                                   //!< Gets the blue value of this texture.

		//HSL color
        Angle getHue() const;                               //!< Gets the hue value in the form of an angle object.
        float getS() const;                                 //!< Gets the saturation value.
        float getL() const;                                 //!< Gets the lightness value.

		int getW() const;                                   //!< Gets the unscaled width of this texture.
		int getH() const;                                   //!< Gets the unscaled height of this texture.
		int getClipX() const;                               //!< Gets the clip X coordinate.
		int getClipY() const;                               //!< Gets the clip Y coordinate.
		int getClipW() const;                               //!< Gets the clip width.
		int getClipH() const;                               //!< Gets the clip height.
		int getScaleW() const;                              //!< Gets the scaled width.
		int getScaleH() const;                              //!< Gets the scaled height.
		int getAlpha() const;                               //!< Gets the alpha setting.
		float getX() const;                                 //!< Gets the X coordinate.
        float getY() const;                                 //!< Gets the Y coordinate.
		SDL_Rect getScale() const;                          //!< Gets an SDL_Rect containing all scaling values.
		SDL_Point getCenter() const;                        //!< Gets the center coordinate.
		Angle getAngle() const;                             //!< Gets the angle in the form of an angle object.
	protected:

        ColorHSL hsl;
        ColorRGB rgb;

		int alpha;
		bool blending;

		//Positional & dimensional stuff
		Angle angle; //SDL uses degrees.
		int h;
		int w;
		SDL_Point center;
		SDL_Rect scale;
		SDL_Rect clip;
		SDL_Texture* texture;

		friend class TextureManager;
		friend class HydraEngine;
	};
};
