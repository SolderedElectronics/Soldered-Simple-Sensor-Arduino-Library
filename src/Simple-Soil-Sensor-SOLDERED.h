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

#ifndef __SIMPLE_SOIL_SENSOR_SOLDERED_H__
#define __SIMPLE_SOIL_SENSOR_SOLDERED_H__

#include "Simple-Sensor-SOLDERED.h"

/**
 * This class inherits the main simpleSensor class
 */

class simpleSoilSensor : public simpleSensor
{
  public:
    // Constructors
    simpleSoilSensor() : simpleSensor(){};                                                               // easyC
    simpleSoilSensor(uint8_t _analogPin, uint8_t _digitalPin) : simpleSensor(_analogPin, _digitalPin){}; // Native

    bool isMoist();
};

#endif
