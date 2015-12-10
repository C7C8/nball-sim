#include "ColorHSL.h"

namespace Hydra
{
    ColorHSL::ColorHSL()
    {
        //Angle constructor handels h setting - automatically sets it to 0
        s = 1.f;
        l = 1.f;
    }
    ColorRGB ColorHSL::getRGB()
    {
        //Fix angle being too large or too small - that'll mess up the conversion
        while (h.getDegs() >= 360.f)
            h.setDegs(h.getDegs() - 360.f);
        while (h.getDegs() < 0.f)
            h.setDegs(h.getDegs() + 360.f);

        float c = (1.f - fabs((2.f * l) - 1.f)) * s;
        float newH = h.getDegs() / 60.f;
        float x = c * (1.f - fabs(fmodf(newH, 2.f) - 1.f));

        float m = l - (c / 2.f);

        float rgb[3] = {0, 0, 0};

        if (0.f <= h.getDegs() && h.getDegs() < 60.f)
        {
            rgb[0] = c; rgb[1] = x;
        }
        if (60.f <= h.getDegs()  && h.getDegs() < 120.f)
        {
            rgb[0] = x; rgb[1] = c;
        }
        if (120.f <= h.getDegs() && h.getDegs() < 180.f)
        {
            rgb[1] = c; rgb[2] = x;
        }
        if (180.f <= h.getDegs() && h.getDegs() < 240.f)
        {
            rgb[1] = x; rgb[2] = c;
        }
        if (240.f <= h.getDegs() && h.getDegs() < 300.f)
        {
            rgb[0] = x; rgb[2] = c;
        }
        if (300.f <= h.getDegs() && h.getDegs() < 360.f)
        {
            rgb[0] = c; rgb[2] = x;
        }

        rgb[0] = (rgb[0] + m) * 255.f;
        rgb[1] = (rgb[1] + m) * 255.f;
        rgb[2] = (rgb[2] + m) * 255.f;

        ColorRGB color;
        color.setR((int)rgb[0]);
        color.setG((int)rgb[1]);
        color.setB((int)rgb[2]);
        return color;
    }
    void ColorHSL::setH(Angle newH)
    {
        h = newH;
    }
    void ColorHSL::setH(float degrees)
    {
        h.setDegs(degrees);
    }
    void ColorHSL::setS(float newS)
    {
        s = newS;
        if (s > 1.f)
            s = 1.f;
        if (s < 0.f)
            s = 0.f;
    }
    void ColorHSL::setL(float newL)
    {
        l = newL;
        if (l > 1.f)
            l = 1.f;
        if (l < 0.f)
            l = 0.f;
    }
    Angle ColorHSL::getH() const
    {
        return h;
    }
    float ColorHSL::getS() const
    {
        return s;
    }
    float ColorHSL::getL() const
    {
        return l;
    }
}
