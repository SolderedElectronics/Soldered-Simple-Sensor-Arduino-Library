/**
 **************************************************
 *
 * @file        Simple-Rain-Sensor-SOLDERED.cpp
 * @brief       Function definitions for the Simple Rain Sensor
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#include "Simple-Rain-Sensor-SOLDERED.h"

/**
 * @brief                   Get the reading of the sensor if it's raining or not according to the set threshold
 *
 * @returns                 bool, True if it's raining, False if it's not
 */
bool simpleRainSensor::isRaining()
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
