#pragma once

#include <stdint.h>
#include "../math/hmath.h"
#include "ColorHSL.h"

namespace Hydra
{
    class ColorHSL;

	class ColorRGB
	{
	public:
		ColorRGB();

		int getR() const;
		int getG() const;
		int getB() const;

		void setR(int newR);
		void setG(int newG);
		void setB(int newB);

		ColorHSL getHSL() const;          //!< Gets an HSL conversion. Use sparingly. Add a dash of salt if needed.
	protected:
        int r;
        int g;
        int b;
	};
}
