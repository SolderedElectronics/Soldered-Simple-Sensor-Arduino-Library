/**
 **************************************************
 *
 * @file        Simple-Soil-Sensor-SOLDERED.cpp
 * @brief       Function definitions for the Simple Soil Sensor
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#include "Simple-Soil-Sensor-SOLDERED.h"

/**
 * @brief                   Get the reading of the sensor if the soil is moist or not according to the set threshold
 *
 * @returns                 bool, True if it's moist, False if not
 */
bool simpleSoilSensor::isMoist()
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
