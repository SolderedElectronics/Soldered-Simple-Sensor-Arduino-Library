/**
 **************************************************

   @file        ATTINY firmware for all the Simple Sensors

   @brief       This sensor measures an analog value and sends it over easyC.
                It also has an onboard LED which can turn on or off depending on if a set threshold is reached


   @authors     Goran Juric, Karlo Leksic, Robert Soric for Soldered.com
 ***************************************************/

// Include the required libraries
#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS; // 0x30

uint16_t readValue; // Variable for reading the analog value
uint16_t threshold; // Variable for setting the threshold

// Define pins for the sensor and LED
#define LED_PIN    PA4
#define SENSOR_PIN PA5

// LED settings and defines
bool ledInverted = false;
#define LED_ON_WHEN_THRESHOLD     0xFF
#define LED_OFF_WHEN_THRESHOLD    0x00
#define DELAY_BETWEEN_READINGS_MS 50

void setup()
{
    // Set address switches as inputs, and get the I2C address
    initDefault();
    addr = getI2CAddress();

    // Set the LED pin as output and turn it off by default
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Init I2C communication
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
    // Read analog value
    readValue = analogRead(SENSOR_PIN);

    // Turn on the LED if the read value is greater than the threshold value
    // If the led was inverted by the setting, invert it
    if (readValue > threshold)
    {
        digitalWrite(LED_PIN, (ledInverted) ? HIGH : LOW);
    }
    else
    {
        digitalWrite(LED_PIN, (ledInverted) ? LOW : HIGH);
    }

    // Delay between readings
    delay(DELAY_BETWEEN_READINGS_MS);
}

// This function will be executed when Dasduino sends data to this board
void receiveEvent(int howMany)
{
    // The breakout can recieve a threshold value or a 'Invert LED' setting

    // If two bytes are incoming, it's the threshold
    if (howMany == 2)
    {
        // Array for the raw data in bytes
        uint8_t recieved[2];

        // Read 2 bytes which represents the raw threshold value
        Wire.readBytes(recieved, 2);

        // Convert to uint8_t, but first cast to unsigned char
        uint8_t data0 = (unsigned char)recieved[1];
        uint8_t data1 = (unsigned char)recieved[0];

        // Pack into uint16_t and save
        threshold = data0 | data1 << 8;
    }

    // If one byte is coming, it's the invert LED setting
    else if (howMany == 1)
    {
        uint8_t recieved[1];
        Wire.readBytes(recieved, 1);

        // Set the LED according to what was sent
        if (recieved[0] == LED_OFF_WHEN_THRESHOLD)
        {
            ledInverted = true;
        }
        else if (recieved[0] == LED_ON_WHEN_THRESHOLD)
        {
            ledInverted = false;
        }
    }
}

// This function will be executed when Dasduino requests data from the breakout
void requestEvent()
{
    // Convert the raw reading into bytes which can be sent, then send it
    uint8_t *valueToSend = (uint8_t *)&readValue;
    Wire.write(valueToSend, 2);
}