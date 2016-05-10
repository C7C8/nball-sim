#include "ColorRGB.h"

namespace Hydra
{
    ColorRGB::ColorRGB()
    {
        r = 255;
        g = 255;
        b = 255;
    }
    ColorHSL ColorRGB::getHSL() const
    {
        float newR = (float)r / 255.f;
        float newG = (float)g / 255.f;
        float newB = (float)b / 255.f;
        float min = newR < newG ? newR : newG;
        min = min < newB ? min : newB;
        float max = newR > newG ? newR : newG;
        max = max > newB ? max : newB;
        float delta = max - min;
        ColorHSL color;

        //H
        if (delta == 0)
            color.setH(0);
        else if (max == newR)
            color.setH(60.f * fmodf((newG - newB) / delta, 6.f));
        else if (max == newG)
            color.setH(60.f *((((newB - newR) / delta) + 2.f) + 2.f));
        else
            color.setH(60.f *((((newR - newG) / delta) + 4.f) + 4.f));

        //L
        color.setL((max + min) / 2.f);

        //S
        if (delta == 0.f)
            color.setS(0);
        else
            color.setS(delta / (1 - fabsf((2.f * color.getL()) -1)));

        return color;
    }
    void ColorRGB::setB(int newB)
    {
        b = newB;
    }
    void ColorRGB::setG(int newG)
    {
        g = newG;
    }
    void ColorRGB::setR(int newR)
    {
        r = newR;
    }
    int ColorRGB::getB() const
    {
        return b;
    }
    int ColorRGB::getG() const
    {
        return g;
    }
    int ColorRGB::getR() const
    {
        return r;
    }
}
