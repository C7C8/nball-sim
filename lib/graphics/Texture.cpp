#include "Texture.h"

namespace Hydra
{
    Texture::Texture()
    {
        texture = NULL;
        h = 0;
        w = 0;
        scale.h = 0;
        scale.y = 0;
        scale.x = 0;
        scale.y = 0;
        alpha = 255;

        setColor(255, 255, 255);
    }
    void Texture::setColor(int newR, int newG, int newB)
    {
        rgb.setR(newR);
        rgb.setG(newG);
        rgb.setB(newB);
        hsl = rgb.getHSL();
    }
    void Texture::setR(int newR)
    {
        rgb.setR(newR);
        hsl = rgb.getHSL();
    }
    void Texture::setG(int newG)
    {
        rgb.setG(newG);
        hsl = rgb.getHSL();
    }
    void Texture::setB(int newB)
    {
        rgb.setB(newB);
        hsl = rgb.getHSL();
    }
    int Texture::getR() const
    {
        return rgb.getR();
    }
    int Texture::getG() const
    {
        return rgb.getG();
    }
    int Texture::getB() const
    {
        return rgb.getB();
    }
    int Texture::getH() const
    {
        return h;
    }
    int Texture::getW() const
    {
        return w;
    }
    void Texture::setClipX(int newX)
    {
        clip.x = newX;
    }
    void Texture::setClipY(int newY)
    {
        clip.y = newY;
    }
    void Texture::setClipH(int newH)
    {
        clip.h = newH;
    }
    void Texture::setClipW(int newW)
    {
        clip.w = newW;
    }
    void Texture::setClip(SDL_Rect newClip)
    {
        clip = newClip;
    }
    int Texture::getClipX() const
    {
        return clip.x;
    }
    int Texture::getClipY() const
    {
        return clip.y;
    }
    int Texture::getClipW() const
    {
        return clip.w;
    }
    int Texture::getClipH() const
    {
        return clip.h;
    }
    int Texture::getScaleW() const
    {
        return scale.w;
    }
    int Texture::getScaleH() const
    {
        return scale.h;
    }
    SDL_Rect Texture::getScale() const
    {
        return scale;
    }
    void Texture::setScaleW(int newW)
    {
        scale.w = newW;
        center.x = scale.w / 2.0f;
    }
    void Texture::setScaleH(int newH)
    {
        scale.h = newH;
        center.y = scale.h / 2.0f;
    }
    void Texture::setBlending(bool blend)
    {
        blending = blend;
    }
    void Texture::setAlpha(int newAlpha)
    {
        alpha = newAlpha;
    }
    int Texture::getAlpha() const
    {
        return alpha;
    }
    void Texture::setCenterX(int newX)
    {
        center.x = newX;
    }
    void Texture::setCenterY(int newY)
    {
        center.y = newY;
    }
    void Texture::setCenter(SDL_Point newPoint)
    {
        center = newPoint;
    }
    void Texture::setAngle(double newAngle)
    {
        angle.setDegs(newAngle);
    }
    void Texture::setAngle(Angle newAngle)
    {
        angle = newAngle;
    }
    SDL_Point Texture::getCenter() const
    {
        return center;
    }
    Angle Texture::getAngle() const
    {
        return angle;
    }
    void Texture::setTexture(SDL_Texture* newTexture)
    {
        texture = newTexture;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        scale.w = w;
        scale.h = h;
        clip.x = 0;
        clip.y = 0;
        clip.h = h;
        clip.w = w;
        angle.setDegs(0);
        center.x = w / 2;
    }
    void Texture::free()
    {
        SDL_DestroyTexture(texture);
    }
    void Texture::setX(float newX)
    {
        scale.x = newX;
    }
    void Texture::setY(float newY)
    {
        scale.y = newY;
    }
    float Texture::getX() const
    {
        return scale.x;
    }
    float Texture::getY() const
    {
        return scale.y;
    }
    void Texture::setHue(Angle hue)
    {
        hsl.setH(hue);
        rgb = hsl.getRGB();
    }
    void Texture::setHue(double hue)
    {
        hsl.setH(hue);
        rgb = hsl.getRGB();
    }
    void Texture::setS(double newS)
    {
        hsl.setS(newS);
        rgb = hsl.getRGB();
    }
    void Texture::setL(double newL)
    {
        hsl.setL(newL);
        rgb = hsl.getRGB();
    }
    Angle Texture::getHue() const
    {
        return hsl.getH();
    }
    float Texture::getS() const
    {
        return hsl.getS();
    }
    float Texture::getL() const
    {
        return hsl.getL();
    }
}
