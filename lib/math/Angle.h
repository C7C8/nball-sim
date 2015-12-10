#pragma once

#include <math.h>
#include "mathdefs.h"

namespace Hydra
{
	 /** \brief A generic angle class that handles both angles and degrees. All calculations are done in radians.*/
    class Angle
    {
    public:
        //Misc
        Angle();
        Angle(double angle, bool rad = true);
        static double toRads(double deg); //!< Converts a degree value to radians.
        static double toDegs(double rad); //!< Converts a radian calue to degrees.

        //Operator overloads for angles
        Angle operator+(const Angle& angle);
        Angle operator-(const Angle& angle);
        Angle operator*(const Angle& angle);
        Angle operator/(const Angle& angle);

        //Operator overloads for scalars - only radians are accepted
        Angle operator+(const double& rad);
        Angle operator-(const double& rad);
        Angle operator*(const double& rad);
        Angle operator/(const double& rad);

        //All setters
        void setDegs(double deg);
        void setRads(double rad);

        //All getters
        double getDegs() const;
        double getRads () const;
    protected:
        double degrees;
        double radians;
    };
}
