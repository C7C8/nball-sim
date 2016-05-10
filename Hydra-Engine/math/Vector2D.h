#pragma once
#include <math.h>

namespace Hydra
{
	/** \brief Class for 2D vector math. Calculations dones in radians.*/
    class Vector2D
    {
    public:
        Vector2D();
        Vector2D(double newX, double newY);

        void normalize();               			//!< Normalize to unit vector.
        void rotate(double rad);       				//!< Rotate the vector. Uses radians.
        double getADelt(Vector2D vec);          	//!< Returns the angle between the two vectors.

        //Operator overloads
        Vector2D operator+(const Vector2D& vec);    //!< Standard addition.
        Vector2D operator-(const Vector2D& vec);    //!< Standard subtraction.
        double operator*(const Vector2D& vec);      //!< Dot product
        Vector2D operator*(const double& num);

        //All setters
        void setX(double newX);
        void setY(double newY);
        void setMag(double newMag);

        //All getters
        double getX() const;
        double getY() const;
        double getMag() const;
    protected:
        double xComp;
        double yComp;
    };
}
