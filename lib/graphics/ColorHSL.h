#pragma once

#include "../math/hmath.h"
#include "ColorRGB.h"

namespace Hydra
{
    class ColorRGB;

	class ColorHSL
	{
	public:
		ColorHSL();
		ColorRGB getRGB();          //!< Get an RGB conversion. Use sparingly with pepper if needed.

		void setH(Angle newH);      //!< Set the hue value.
		void setH(float degrees);   //!< Set the hue using degrees in place of an angle object.
		void setS(float newS);      //!< Set the saturation value.
		void setL(float newL);      //!< Set the lightness value.

		Angle getH() const;         //!< Get the hue value.
        float getS() const;         //!< Get the saturation value.
		float getL() const;         //!< Get the lightness value.

	protected:
        Angle h; //Angle
        float s; //Percent
        float l; //Percent
	};
}
