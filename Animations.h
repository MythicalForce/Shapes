#pragma once

#include <Arduino.h>
#include <FastLED.h>

enum rotdirection { CLOCKWISE, COUNTERCLOCKWISE };
enum movedirection { BNF, UND };
enum wavedirection { FORWARD, BACKWARD };

struct rotation
{
    bool Animate;
    float Angle;
    float AngleAmount;
    rotdirection Direction;
};

struct movement
{
    bool Movement;
    uint8_t MovePosStart;
    uint8_t MovePosEnd;
    uint8_t MovementSpeed;
    uint8_t MovementOffset;
    movedirection MovementDirection;
};

struct wave
{
    bool doWave;
    float Wave;
    float WaveAmount;
    wavedirection WaveDirection;
};

class Animation
{
public:
    rotation Rotation;
    movement Movement;
    wave Wave;
    float pi = 3.1415;

    void Rotate()
    {
        if (Rotation.Animate)
        {
            if (Rotation.Direction == CLOCKWISE)
            {
                Rotation.Angle += Rotation.AngleAmount;
                if (Rotation.Angle == 360.0)
                {
                    Rotation.Angle = 0.0;
                }
            }
            else if (Rotation.Direction == COUNTERCLOCKWISE)
            {
                Rotation.Angle -= Rotation.AngleAmount;
                if (Rotation.Angle == 0.0)
                {
                    Rotation.Angle = 360.0;
                }
            }
        }
        else
        {
            Rotation.Angle = Rotation.AngleAmount;
        }
    }

    void WaveAnim()
    {
        if (Wave.doWave)
        {
            if (Wave.WaveDirection == FORWARD)
            {
                Wave.Wave += Wave.WaveAmount;
                if (Wave.Wave == 360.0)
                {
                    Wave.Wave = 0.0;
                }
            }
            else if (Wave.WaveDirection == BACKWARD)
            {
                Wave.Wave -= Wave.WaveAmount;
                if (Wave.Wave == 0.0)
                {
                    Wave.Wave = 360.0;
                }
            }
        }
    }
};
