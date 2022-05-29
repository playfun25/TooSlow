/* mbed R/C Servo Library
 * Copyright (c) 2007-2010 sford, cstyles
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
  
#pragma once

#include "mbed.h"


class Servo 
{

protected:
    PwmOut m_pwm;
    float m_range;
    float m_degrees;
    float m_p;

public:
  
    /** Set the servo position, normalised to it's full range
     *
     * @param percent A normalised number 0.0-1.0 to represent the full range.
     */
    virtual void write(float percent) = 0;
    
    /**  Read the servo motors current position
     *
     * @param returns A normalised number 0.0-1.0  representing the full range.
     */
    virtual float read() = 0;
    
    /** Set the servo position
     *
     * @param degrees Servo position in degrees
     */
    virtual void position(float degrees) = 0;
    
    /**  Allows calibration of the range and angles for a particular servo
     *
     * @param range Pulsewidth range from center (1.5ms) to maximum/minimum position in seconds
     * @param degrees Angle from centre to maximum/minimum position in degrees
     */
    virtual void calibrate(float range = 0.0005, float degrees = 45.0) = 0; 
};