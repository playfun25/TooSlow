/*
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once
 
#include "mbed.h"

#include "ColorSensor.hpp"
 
 
class GroveColourSensor : public ColorSensor
{

    private :
        static const uint8_t SEVEN_BIT_ADDRESS = 0x39;
        I2C* m_i2c;

    public :
        GroveColourSensor(I2C *i2c) : m_i2c{i2c} 
        {

        }
 
        void powerUp()
        {
            static const char powerUpCommand[] = {0x80, 0x03};
            /* turn on the color sensor */
            if (m_i2c->write((SEVEN_BIT_ADDRESS << 1), powerUpCommand, sizeof(powerUpCommand)) != 0) 
            {
                error("failed to power up the sensor");
            }
        }
 
        void powerDown() 
        {
            static const char powerDownCommand[] = {0x80, 0x00};
            /* turn on the color sensor */
            if (m_i2c->write((SEVEN_BIT_ADDRESS << 1), powerDownCommand, sizeof(powerDownCommand)) != 0) 
            {
                error("failed to power down the sensor");
            }
        }
    
        uint16_t readColor(const Color color) 
        {
            char readColorRegistersCommand = 0xb0 + (2 * static_cast<unsigned>(color));
            m_i2c->write((SEVEN_BIT_ADDRESS << 1), &readColorRegistersCommand, 1 /* size */);
    
            uint16_t colourValue;
            m_i2c->read((SEVEN_BIT_ADDRESS << 1), reinterpret_cast<char *>(&colourValue), sizeof(uint16_t));
            return colourValue;
        }
};