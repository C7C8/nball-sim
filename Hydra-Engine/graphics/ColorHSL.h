#pragma once
#include <math.h>
#include "ColorRGB.h"

namespace Hydra
{
    class ColorRGB;

	class ColorHSL
	{
	public:
		ColorHSL();
		ColorRGB getRGB();          //!< Get an RGB conversion. Use sparingly with pepper if needed.

		void setH(double newH);     //!< Set the hue value in degrees
		void setS(float newS);      //!< Set the saturation value.
		void setL(float newL);      //!< Set the lightness value.

		double getH() const;        //!< Get the hue value.
        float getS() const;         //!< Get the saturation value.
		float getL() const;         //!< Get the lightness value.

	protected:
        double h; //Angle, in degrees
        float s; //Percent
        float l; //Percent
	};
}
