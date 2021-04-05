#pragma once

#include <Arduino.h>
#include "Config.h"
#include "Animation.h"

uint16_t RED = dma_display->color565(255,0,0);
uint16_t GREEN = dma_display->color565(0,255,0);
uint16_t BLUE = dma_display->color565(0,0,255);
uint16_t YELLOW = dma_display->color565(255,255,0);
uint16_t PURPLE = dma_display->color565(255,0,255);
uint16_t AQUA = dma_display->color565(0,255,255);

/**************************************************************************/
/*!
    @brief       Draw a rectangle and rotate it inplace
    @param l     Height
    @param w     Width
    @param x     Horizontal Placement (Left - Right)
    @param y     Vertical Placement (Up - Down)
    @param color 16-bit 5-6-5 Color to draw with
    @param raa   Rotation Angle Amount to rotate
    @param ra    Should the object rotate (True, False)
    @param rd    Rotation direction (Enum CLOCKWISE, COUNTERCLOCKWISE)
*/
/**************************************************************************/
class Rectangle : public Animation
{
public:
    float _Height;
    float _Width;
    float _x;
    float _y;
    uint16_t _color;

    Rectangle(float l, float w, float x, float y, uint16_t color, float raa, bool ra, rotdirection rd)
    : _Height(l), _Width(w), _x(x), _y(y), _color(color)
    {
        Animation::Rotation.AngleAmount = raa;
        Animation::Rotation.Animate = ra;
        Animation::Rotation.Direction = rd;
    }

    void draw()
    {
        float x1, y1, x2, y2, x3, y3, x4, y4;

        x1 = cos(Rotation.Angle)*_Height/2 - sin(Rotation.Angle)*_Width/2 + _x;
        y1 = sin(Rotation.Angle)*_Height/2 + cos(Rotation.Angle)*_Width/2 + _y;

        x2 = -cos(Rotation.Angle)*_Height/2 - sin(Rotation.Angle)*_Width/2 + _x;
        y2 = -sin(Rotation.Angle)*_Height/2 + cos(Rotation.Angle)*_Width/2 + _y;

        x3 = -cos(Rotation.Angle)*_Height/2 + sin(Rotation.Angle)*_Width/2 + _x;
        y3 = -sin(Rotation.Angle)*_Height/2 - cos(Rotation.Angle)*_Width/2 + _y;

        x4 = cos(Rotation.Angle)*_Height/2 + sin(Rotation.Angle)*_Width/2 + _x;
        y4 = sin(Rotation.Angle)*_Height/2 - cos(Rotation.Angle)*_Width/2 + _y;

        dma_display->writeLine(x1, y1, x2, y2, _color);
        dma_display->writeLine(x2, y2, x3, y3, _color);
        dma_display->writeLine(x3, y3, x4, y4, _color);
        dma_display->writeLine(x4, y4, x1, y1, _color);

        Animation::Rotate();
    }
};

/**************************************************************************/
/*!
    @brief       Draw a triangle and rotate it inplace
    @param l     Length of triangle sides
    @param x     Horizontal Placement (Left - Right)
    @param y     Vertical Placement (Up - Down)
    @param color 16-bit 5-6-5 Color to draw with
    @param raa   Rotation Angle Amount to rotate
    @param ra    Should the object rotate (True, False)
    @param rd    Rotation direction (Enum CLOCKWISE, COUNTERCLOCKWISE)
*/
/**************************************************************************/
class Triangle : public Animation
{
public:
    float _Length;
    float _x;
    float _y;
    uint16_t _color;

    Triangle(float l, float x, float y, uint16_t color, float raa, bool ra, rotdirection rd)
    : _Length(l), _x(x), _y(y), _color(color)
    {
        Animation::Rotation.AngleAmount = raa;
        Animation::Rotation.Animate = ra;
        Animation::Rotation.Direction = rd;
    }

    void draw()
    {
        float x1, y1, x2, y2, x3, y3;

        x1 = -sin(Rotation.Angle)*_Length*sqrt(3)/3 + _x;
        y1 = cos(Rotation.Angle)*_Length*sqrt(3)/3 + _y;

        x2 = -cos(Rotation.Angle)*_Length/2 + sin(Rotation.Angle)*_Length*sqrt(3)/6 + _x;
        y2 = -sin(Rotation.Angle)*_Length/2 - cos(Rotation.Angle)*_Length*sqrt(3)/6 + _y;

        x3 = cos(Rotation.Angle)*_Length/2 + sin(Rotation.Angle)*_Length*sqrt(3)/6 + _x;
        y3 = sin(Rotation.Angle)*_Length/2 - cos(Rotation.Angle)*_Length*sqrt(3)/6 + _y;

        dma_display->writeLine(x1, y1, x2, y2, _color);
        dma_display->writeLine(x2, y2, x3, y3, _color);
        dma_display->writeLine(x3, y3, x1, y1, _color);

        Animation::Rotate();
    }

};
/**************************************************************************/
/*!
    @brief       Draw a sine wave
    @param a     Amplitude, how tall the sine wave is
    @param p     Period, how long should each segment be
    @param x1    Start Point
    @param y1    End Point
    @param x     How much to shift the wave by
    @param y     How much to move the wave up or down
    @param color 16-bit 5-6-5 Color to draw with
    @param dw    Animate Wave (True, False)
    @param wd    Wave Direction (enum FORWARD, BACKWARD)
    @param wa    Wave Amount
*/
/**************************************************************************/
class SinWave : public Animation
{
public:
    int _Amplitude;
    int _Period;
    float _x1;
    float _x2;
    float _x;
    float _y;
    uint16_t _color;

    SinWave(int a, int p, float x1, float x2, float x, float y, uint16_t color, bool dw, wavedirection wd, float wa)
    : _Amplitude(a), _Period(p), _x1(x1), _x2(x2), _x(x), _y(y), _color(color)
    {
        Animation::Wave.doWave = dw;
        Animation::Wave.WaveDirection = wd;
        Animation::Wave.WaveAmount = wa;
    }

    void draw()
    {       
        for (int i = _x1; i <= _x2; i++)
        {
            dma_display->drawPixel(i, _Amplitude*sin(i*pi/_Period-pi*Wave.Wave)+_y, _color);

            WaveAnim();
        }
    }
};
