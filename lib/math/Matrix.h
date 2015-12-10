#pragma once

#include <math.h>
#include <vector>
#include <iostream>
#include "mathdefs.h"
using namespace std; //Ugh

namespace Hydra
{
    /** \brief A generic class for matrix math. All matrix slots are zero-ordered. Note that the y axis is inverted.*/
    class Matrix
    {
    public:
        Matrix(usint x = 2, usint y = 2);

        Matrix operator+(const Matrix &matr);   //!< Standard addition.
        Matrix operator-(const Matrix &matr);   //!< Standard subtraction.
        Matrix operator*(const Matrix &matr);   //!< Standard multiplication.
        Matrix operator*(const double num);     //!< Scalar multiplication.

        void setValue(double value, usint x = 0, usint y = 0);
        void setSize(usint newXSize = 2, usint newYSize = 2); //!< Sets the matrix to the designated size, completely wiping it in the process.

        double getValue(usint x = 0, usint y = 0) const;
        usint getXSize() const;
        usint getYSize() const;
    protected:
        usint xSize;
        usint ySize;
        vector<vector<double>> mat;
    };

    ostream& operator<<(ostream& output, Matrix& matr);
}
