/**
 **************************************************
 *
 * @file        Simple-Rain-Sensor-SOLDERED.h
 * @brief       Header file for the Simple Rain Sensor
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#ifndef __SIMPLE_RAIN_SENSOR_SOLDERED_H__
#define __SIMPLE_RAIN_SENSOR_SOLDERED_H__

#include "Simple-Sensor-SOLDERED.h"

/**
 * This class inherits the main simpleSensor class
 */

class simpleRainSensor : public simpleSensor
{
  public:
    // Constructors
    simpleRainSensor() : simpleSensor(){};                                                               // easyC
    simpleRainSensor(uint8_t _analogPin, uint8_t _digitalPin) : simpleSensor(_analogPin, _digitalPin){}; // Native

    bool isRaining();
};

#endif
