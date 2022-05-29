/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


#include <chrono>
#include "mbed.h"

#include "Servo.h"
#include "GroveColourSensor.hpp"


constexpr uint8_t refreshSpeed = 100;
constexpr uint8_t reactSpeed = 100;

bool buttonIsPressed;

// fonction appelé lors de l'appui sur le bouton robot
void button_pressed() 
{
    buttonIsPressed = true;
}

int main()
{
    printf("************************************************** \n");
    printf("*****             To Slow                    ***** \n");
    printf("************************************************** \n");

    int gameLevel = 5;
    bool gamgeLevel_changed = true;
    buttonIsPressed = false;
    bool isGreen = false;

    I2C *i2c = new I2C(p28, p27);
    printf("I2C ok \n");

    Servo myservo(p21);     // Declaration du servomoteur
    printf("servo ok \n");

    ColorSensor *colorSensor = new GroveColourSensor(i2c);
    printf("color ok \n");

    InterruptIn button(p26);
    printf("button ok \n");

    colorSensor->powerUp();
    myservo.position(0);

    button.rise(&button_pressed);

    while (true) 
    {
        if(buttonIsPressed == true)
        {
            if(gameLevel > 0)
            {
                gameLevel--;
            }
            else 
            {
                gameLevel = 5;
            }
            buttonIsPressed = false;
            gamgeLevel_changed = true;
        }

        if(gamgeLevel_changed)
        {
            switch (gameLevel) 
            {
            case  0 : 
                printf("Difficultée ToSlow\n");
                break;
            case 1 :
                printf("Difficultée Dieu\n");
                break;
            case 2 :
                printf("Difficultée hardcore\n");
                break;
            case 3 :
                printf("Difficultée difficile\n");
                break;
            case 4 :
                printf("Difficultée moyen\n");
                break;
            case 5 :
                printf("Difficultée facile\n");
                break;
            default:
                printf("Quel est se satanisme ?\n");
            }

            gamgeLevel_changed = false;
        }

        uint16_t red = colorSensor->readColor(GroveColourSensor::Color::RED);
        uint16_t green = colorSensor->readColor(GroveColourSensor::Color::GREEN);
        uint16_t blue = colorSensor->readColor(GroveColourSensor::Color::BLUE);
        //printf("RGB : %d, %d, %d\n", red, green, blue);


        if((blue > red) && (blue > green))
        {
            //printf("c'est bleu\n");
            isGreen = false;
        }
        else if((green > red) && (green > blue))
        {
            //printf("c'est vert\n");
            isGreen = false;
        }
        else 
        {
            //printf("c'est rouge\n");
            isGreen = true;
        }

        // Si la led est verte, on appui sur le bouton poussoir 
        if(isGreen)
        {
            ThisThread::sleep_for(std::chrono::milliseconds(reactSpeed*gameLevel));
            myservo.position(90);
        }
        else 
        {
            myservo.position(0);
        }
        
        ThisThread::sleep_for(std::chrono::milliseconds(refreshSpeed));
    }
}
