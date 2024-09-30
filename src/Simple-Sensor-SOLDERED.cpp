/**
 **************************************************
 *
 * @file        Simple-Sensor-SOLDERED.CPP
 * @brief       Functions for the Simple Sensors, both native and easyC
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#include "Simple-Sensor-SOLDERED.h"

/**
 * @brief                   Native constructor for the Simple Sensors.
 *
 * @param                   uint8_t _analogPin, the pin connected to A0
 * @param                   uint8_t _digitalPin, the pin connected to D0
 */
simpleSensor::simpleSensor(uint8_t _analogPin, uint8_t _digitalPin)
{
    analogPin = _analogPin;
    digitalPin = _digitalPin;
    native = 1;
}

/**
 * @brief                   easyC constructor for the Simple Sensors.
 *
 */
simpleSensor::simpleSensor()
{
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void simpleSensor::initializeNative()
{
    pinMode(analogPin, INPUT);
    pinMode(digitalPin, INPUT);
}

/**
 * @brief                   Get the raw reading of the sensor.
 *
 * @returns                 uint16_t of the raw analog read
 */
uint16_t simpleSensor::getRawReading()
{
    // If we're using the easyC version
    if (!native)
    {
        // Read 2 bytes of raw  data
        char data[2];
        readData(data, 2);

        // Convert to uint8_t, but first cast to unsigned char
        uint8_t data0 = (unsigned char)data[0];
        uint8_t data1 = (unsigned char)data[1];

        // Pack into uint16_t
        uint16_t rawReadData = data0 | data1 << 8;

        // Return converted value
        return rawReadData;
    }

    // If we're using the native version
    return (uint16_t)analogRead(analogPin);
}

/**
 * @brief                   Calculate resistance which the sensor is measuring.
 *
 * @returns                 float value of the resistance
 */
float simpleSensor::getResistance()
{
    uint16_t temp = getRawReading();
    if (native)
    {
        if (temp != 0)
        {
            return RES * (temp / (float)(ADC_MAX - temp));
        }
    }
    else
    {
        if (temp != 0)
        {
            return RES * (temp / (float)(1024 - temp));
        }
    }
    return 0;
}

/**
 * @brief                   Get the value of the sensor as a percentage.
 *
 * @returns                 float percentage of the sensor reading
 */
float simpleSensor::getValue()
{
    if (!native)
    {
        float measuredValue = (100 - (getRawReading() / float(1024 - 1) * 100));
        float calibratedValue = measuredValue * (100.0F / highPercentage);
        return min(calibratedValue, 100.0F);
    }
    else
    {
        float measuredValue = (100 - (getRawReading() / float(ADC_MAX - 1) * 100));
        float calibratedValue = measuredValue * (100.0F / highPercentage);
        return min(calibratedValue, 100.0F);
    }
}

/**
 * @brief                   Set the raw value of the threshold. Only for easyC.
 *
 * @param                   uint16_t _thresh, threshold to set
 *
 * @returns                 none
 */
void simpleSensor::setRawThreshold(uint16_t _thresh)
{
    if (!native)
    {
        // First, check if it's within the range
        if (_thresh < 0 || _thresh > 1024)
        {
            return;
        }

        rawThreshold = _thresh;

        // Convert raw threshold value into 2 bytes for sending
        uint8_t *thresholdToSend = (uint8_t *)&rawThreshold;

        // Send over easyC
        sendData(thresholdToSend, 2);
    }
}

/**
 * @brief                   Get the raw value of the threshold.
 *
 * @returns                 uint16_t value of the set threshold
 */
uint16_t simpleSensor::getRawThreshold()
{
    return rawThreshold;
}

/**
 * @brief                   Set the threshold as a percentage. Only for easyC.
 *
 * @param                   float _thresh, threshold to set, as a percentage
 *
 * @returns                 none
 */
void simpleSensor::setThreshold(float _thresh)
{
    treshold = _thresh;

    if (!native)
    {
        // First, check if it's within the range
        if (_thresh < 0 || _thresh > 100)
        {
            return;
        }

        // Convert to raw value
        uint16_t newRawThreshold = treshold * 0.01 * 1024 * (highPercentage * 0.01);

        // Set it
        setRawThreshold(newRawThreshold);
    }
}

/**
 * @brief                   Get the percentage value of the threshold, only for easyC.
 *
 * @returns                 float value of the set threshold
 */
float simpleSensor::getThreshold()
{
    if (!native)
    {
        return treshold;
    }
    else
        return 0;
}

/**
 * @brief       Invert the LED on the breakout board
 *
 * @param       bool ledSetting:
 *              -True makes the LED turn off when the threshold is reached
 *              -False will have the LED turn on only when the threshold is reached
 */
void simpleSensor::invertLED(bool _invert)
{
    if (!native)
    {
        if (_invert)
        {
            // Send the inverted setting
            const uint8_t dataToSend[1] = {LED_OFF_WHEN_THRESHOLD};
            sendData(dataToSend, 1);
        }
        else
        {
            // Send the default setting
            const uint8_t dataToSend[1] = {LED_ON_WHEN_THRESHOLD};
            sendData(dataToSend, 1);
        }
    }
}

/**
 * @brief                   Get the location of D0 on the native board.
 *
 * @note                    This is so functions from inherited classes can access the pin.
 *
 * @returns                 uint8_t pin location of the digital pin D0.
 */
uint8_t simpleSensor::getDigitalPin()
{
    return digitalPin;
}

/**
 * @brief                   Calibrate the high percentage value of the reading.
 *
 * @note                    To calibrate, do a test run and read the getValue measurement
 *                          when your sensor should read the highest possible value.
 *
 *                          Then, pass that value to this function.
 *
 * @param                   float _highPercentage: the percentage which we want to represent 100%
 *
 * @returns                 None
 */
void simpleSensor::calibrate(float _highPercentage)
{
    highPercentage = _highPercentage;

    // Also, set the threshold according to this
    setThreshold(treshold);
}