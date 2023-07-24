/**
 **************************************************
 *
 * @file        Simple-Light-Sensor-SOLDERED.cpp
 * @brief       Function definitions for the Simple Light Sensor
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#include "Simple-Light-Sensor-SOLDERED.h"

/**
 * @brief                   Get the reading of the sensor if light is detected or not according to the set threshold
 *
 * @returns                 bool, True if it's detected, False if not
 */
bool simpleLightSensor::isLightDetected()
{
    if (native)
    {
        return !digitalRead(getDigitalPin());
    }
    else
    {
        if (getValue() > getThreshold())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
