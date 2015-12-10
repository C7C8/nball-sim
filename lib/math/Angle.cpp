#include "Angle.h"

namespace Hydra
{
	Angle::Angle()
    {
        degrees = 0;
        radians = 0;
    }
    /** \brief Constructor - sets the initial angle.
     * \param angle Accepts either radians or degrees
     * \param rad If true, the constructor sets the angle as radians. Else, degrees.
     */
    Angle::Angle(double angle, bool rad)
    {
        if (!rad)
            setDegs(angle);
        else
            setRads(angle);
    }
    double Angle::toRads(double deg)
    {
        return deg * H_RADCONV;
    }
    double Angle::toDegs(double rad)
    {
        return rad * H_DEGCONV;
    }
    Angle Angle::operator+(const Angle& angle)
    {
        Angle temp;
        temp.degrees = degrees + angle.degrees;
        temp.radians = radians + angle.radians;
        return temp;
    }
    Angle Angle::operator+(const double& rad)
    {
        Angle temp;
        temp.degrees = degrees + toDegs(rad);
        temp.radians = radians + rad;
        return temp;
    }
    Angle Angle::operator-(const Angle& angle)
    {
        Angle temp;
        temp.degrees = degrees - angle.degrees;
        temp.radians = radians - angle.radians;
        return temp;
    }
    Angle Angle::operator-(const double& rad)
    {
        Angle temp;
        temp.degrees = degrees - toDegs(rad);
        temp.radians = radians - rad;
        return temp;
    }
    Angle Angle::operator*(const Angle& angle)
    {
        Angle temp;
        temp.degrees = degrees * angle.degrees;
        temp.radians = radians * angle.radians;
        return temp;
    }
    Angle Angle::operator*(const double& rad)
    {
        Angle temp;
        temp.degrees = degrees * toDegs(rad);
        temp.radians = radians * rad;
        return temp;
    }
    Angle Angle::operator/(const Angle& angle)
    {
        Angle temp;
        temp.degrees = degrees / angle.degrees;
        temp.radians = radians / angle.radians;
        return temp;
    }
    Angle Angle::operator/(const double& rad)
    {
        Angle temp;
        temp.degrees = degrees / toDegs(rad);
        temp.radians = radians / rad;
        return temp;
    }
    void Angle::setDegs(double deg)
    {
        degrees = deg;
        radians = toRads(deg);
    }
    void Angle::setRads(double rad)
    {
        radians = rad;
        degrees = toDegs(rad);
    }
    double Angle::getDegs() const
    {
        return degrees;
    }
    double Angle::getRads() const
    {
        return radians;
    }
}
