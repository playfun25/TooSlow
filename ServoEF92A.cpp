/* mbed R/C Servo Library
 *  
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
 
#include "mbed.h"

#include "ServoEF92A.hpp"

static float clamp(float value, float min, float max) {
    if(value < min) {
        return min;
    } else if(value > max) {
        return max;
    } else {
        return value;
    }
}

ServoEF92A::ServoEF92A(PinName pin) : m_pwm(pin) {
    calibrate();
    write(0.5);
}

void ServoEF92A::write(float percent) {
    float offset = m_range * 2.0 * (percent - 0.5);
    m_pwm.pulsewidth(0.0015 + clamp(offset, -m_range, m_range));
    m_p = clamp(percent, 0.0, 1.0);
}

void ServoEF92A::position(float degrees) {
    float offset = m_range * (degrees / m_degrees);
    m_pwm.pulsewidth(0.0015 + clamp(offset, -m_range, m_range));
}

void ServoEF92A::calibrate(float range, float degrees) {
    m_range = range;
    m_degrees = degrees;
}

float ServoEF92A::read() {
    return m_p;
}
