/**
 **************************************************
 *
 * @file        Simple-Sensor-SOLDERED.h
 * @brief       Header file for all the Simple Sensors, native and easyC.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#ifndef __SIMPLE_SENSOR_SOLDERED_H__
#define __SIMPLE_SENSOR_SOLDERED_H__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

/**
 * Different boards use different ADC's with a different range and resolution.
 * This is used to auto-set the ADC's width in bits so correct measurements can be made.
 */
#ifdef ESP32 // Dasduino ConnectPlus
#define ADC_MAX 4096
#elif ESP8266 // Dasduino Connect
#define ADC_MAX 1024
#else // Dasduino Core and other boards
#define ADC_MAX 1024
#endif

/**
 * Resistance constant
 */
#define R 10000

/**
 * Settings for the LED, to be sent via easyC
 */
#define DEFAULT_TRESHOLD       50.0F
#define LED_ON_WHEN_THRESHOLD  0xFF
#define LED_OFF_WHEN_THRESHOLD 0x00

class simpleSensor : public EasyC
{
  public:
    // Constructors
    simpleSensor();                                        // easyC
    simpleSensor(uint8_t _analogPin, uint8_t _digitalPin); // Native

    // Reading the values from the sensor
    uint16_t getRawReading();
    float getResistance();
    float getValue();

    // Threshold
    void setRawThreshold(uint16_t _thresh);
    uint16_t getRawThreshold();
    void setThreshold(float _thresh);
    float getThreshold();

    // Settings
    void invertLED(bool _invert); // Only for easyC
    void calibrate(float _highPercentage);
    uint8_t getDigitalPin();

  protected:
    void initializeNative();

  private:
    uint8_t analogPin, digitalPin;
    uint8_t rawReadData;
    uint16_t rawThreshold; // Default threshold is 50%
    float treshold;
    uint8_t adcWidthInBits;
    float adcMaxVoltage;
    float highPercentage = 100.0; // Used for calibration
};

#endif
