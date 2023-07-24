/**
 **************************************************
 *
 * @file        Simple-Fire-Sensor-SOLDERED.h
 * @brief       Header file for the Simple Fire Sensor
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#ifndef __SIMPLE_FIRE_SENSOR_SOLDERED_H__
#define __SIMPLE_FIRE_SENSOR_SOLDERED_H__

#include "Simple-Sensor-SOLDERED.h"

/**
 * This class inherits the main simpleSensor class
 */

class simpleFireSensor : public simpleSensor
{
  public:
    // Constructors
    simpleFireSensor() : simpleSensor(){};                                                               // easyC
    simpleFireSensor(uint8_t _analogPin, uint8_t _digitalPin) : simpleSensor(_analogPin, _digitalPin){}; // Native

    bool isFireDetected();
};

#endif
