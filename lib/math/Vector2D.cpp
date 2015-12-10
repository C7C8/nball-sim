#include "Vector2D.h"

namespace Hydra
{
	Vector2D::Vector2D()
    {
        xComp = 1;
        yComp = 0;
    }
    Vector2D::Vector2D(double newX, double newY)
    {
        xComp = newX;
        yComp = newY;
    }
    void Vector2D::normalize()
    {
        double mag = getMag();
        xComp /= mag;
        yComp /= mag;
    }
    void Vector2D::rotate(double rad)
    {
        double sine = sin(rad);
        double cosine = cos(rad);
        double newX = (xComp * cosine) - (yComp * sine);
        double newY = (xComp * sine) + (yComp * cosine);
        xComp = newX;
        yComp = newY;
    }
    double Vector2D::getADelt(Vector2D vec)
    {
       return acos((*this * vec) / (getMag() * vec.getMag()));
    }
    void Vector2D::setX(double newX)
    {
        xComp = newX;
    }
    void Vector2D::setY(double newY)
    {
        yComp = newY;
    }
    void Vector2D::setMag(double newMag)
    {
        double mRatio = newMag / getMag();
        xComp *= mRatio;
        yComp *= mRatio;
    }
    double Vector2D::getX() const
    {
        return xComp;
    }
    double Vector2D::getY() const
    {
        return yComp;
    }
    double Vector2D::getMag() const
    {
        return sqrt((xComp * xComp) + (yComp * yComp));
    }
    Angle Vector2D::getAngle() const
    {
        Angle angle;
        angle.setRads(atan2(yComp, xComp));
        if (angle.getDegs() < 0)
            angle = angle + H_TAU;
        return angle;
    }
    Vector2D Vector2D::operator+(const Vector2D& vec)
    {
        Vector2D res;
        res.xComp = xComp + vec.xComp;
        res.yComp = yComp + vec.yComp;
        return res;
    }
    Vector2D Vector2D::operator-(const Vector2D& vec)
    {
        Vector2D res;
        res.xComp = xComp - vec.xComp;
        res.yComp = yComp - vec.yComp;
        return res;
    }
    double Vector2D::operator*(const Vector2D& vec)
    {
        //Dot product
        return (xComp * vec.xComp) + (yComp * vec.yComp);
    }
    Vector2D Vector2D::operator *(const double & num)
    {
    	return Vector2D(xComp * num, yComp * num);
    }
}
