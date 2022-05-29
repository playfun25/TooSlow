
#pragma once

#include "mbed.h"

#include "Servo.hpp"

class ServoEF92A : public Servo
{

public:
    /** Create a servo object connected to the specified PwmOut pin
     *
     * @param pin PwmOut pin to connect to 
     */
    ServoEF92A(PinName pin);
    
    /** Set the servo position, normalised to it's full range
     *
     * @param percent A normalised number 0.0-1.0 to represent the full range.
     */
    void write(float percent);
    
    /**  Read the servo motors current position
     *
     * @param returns A normalised number 0.0-1.0  representing the full range.
     */
    float read();
    
    /** Set the servo position
     *
     * @param degrees Servo position in degrees
     */
    void position(float degrees);
    
    /**  Allows calibration of the range and angles for a particular servo
     *
     * @param range Pulsewidth range from center (1.5ms) to maximum/minimum position in seconds
     * @param degrees Angle from centre to maximum/minimum position in degrees
     */
    void calibrate(float range = 0.0005, float degrees = 45.0); 
};