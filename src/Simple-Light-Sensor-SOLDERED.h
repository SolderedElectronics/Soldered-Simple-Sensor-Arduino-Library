/**
 **************************************************
 *
 * @file        Simple-Soil-Sensor-SOLDERED.h
 * @brief       Header file for the Simple Soil Sensor
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#ifndef __SIMPLE_LIGHT_SENSOR_SOLDERED_H__
#define __SIMPLE_LIGHT_SENSOR_SOLDERED_H__

#include "Simple-Sensor-SOLDERED.h"

/**
 * This class inherits the main simpleSensor class
 */

class simpleLightSensor : public simpleSensor
{
  public:
    // Constructors
    simpleLightSensor() : simpleSensor(){};                                                               // easyC
    simpleLightSensor(uint8_t _analogPin, uint8_t _digitalPin) : simpleSensor(_analogPin, _digitalPin){}; // Native

    bool isLightDetected();
};

#endif
