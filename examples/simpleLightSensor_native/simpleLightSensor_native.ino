/**
 **************************************************
 *
 * @file        simpleLightSensor_native.ino
 * @brief       Read all the values of the Simple Light Sensor.
 *              Also, see how to calibrate it!
 * 
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board according to the diagrams below
 *              -Open Serial monitor at 115200 baud!
 *
 *              Simple Light Sensor: solde.red/333046
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert Sorić @ soldered.com
 ***************************************************/

#include "Simple-Light-Sensor-SOLDERED.h" // Include the required library

// Define pins to use for A0 and D0
// Make sure to change these so it suits your board
#define SENSOR_A0_PIN A2
#define SENSOR_D0_PIN 7

/**
 * Connecting diagram:
 *
 * Simple Light Sensor          Dasduino Core / Connect / ConnectPlus
 * VCC------------------------->VCC
 * GND------------------------->GND
 * A0-------------------------->SENSOR_A0_PIN, set by user
 * D0-------------------------->SENSOR_D0_PIN, set by user
 * 
 * Make sure the A0 pin supports analogRead!
 */

/**
 * How it works:
 * 
 * This sensor works on the principle that light will lower the resistance
 * of the light-sensitive resistor connected to the Light Sensor board.
 * Through this, a percentage can be calculated which indicates presence of light.
 * 
 * You can use the function getValue() to get that percentage.
 * 
 * 0.00% represents darkness.
 * 100.0% represents a bright light near the sensor.
 * 
 * You may also use isLightDetected to get a simple digital reading - is light detected or not?
 * The threshold of this reading is adjusted by the small potentiometer on the board.
 * 
 * The LED on the board will turn off if the threshold is reached.
*/

// Create the sensor object on the set pins
simpleLightSensor lightSensor(SENSOR_A0_PIN, SENSOR_D0_PIN);

void setup()
{
    Serial.begin(115200); // Begin Serial communication so we can see the output
    
    lightSensor.begin(); // Init the Simple Light Humidity Sensor

    // Sensor calibration isn't needed but it helps with getting more relevant readings.
    // To calibrate the sensor, first run this sketch with the line of code below commented:
    //lightSensor.calibrate(76.4);

    // Place the sensor so it's as bright as you're ever going to want to measure.
    // This can be under the bright sun or under a small LED light, for example, it's up to you!
    // Note the reading of the light percentage, and then write that value in the calibrate function.
    // What this does is essentially make the range of measurement smaller so the data you get is more relevant.
}

void loop()
{
    // Print the readings to Serial

    // Raw reading is essentially a reading of the analog value on SENSOR_A0_PIN
    Serial.print("Raw reading: ");
    Serial.println(lightSensor.getRawReading());
    
    // The resistance is calcualted through a constant
    Serial.print("Resistance: ");
    Serial.print(lightSensor.getResistance());
    Serial.println("Ohm.");

    // Print percentage of light detection of sensor
    Serial.print("Light detection: ");
    Serial.print(lightSensor.getValue());
    Serial.println("%");

    // Print is a light detected or not
    // Once again, you may adjust this threshold with the small potentiometer on the board
    Serial.print("Light detected? ");
    if(lightSensor.isLightDetected()) Serial.println("True!");
    else Serial.println("False!");

    Serial.println(); // Print newline

    delay(1000); // Wait a bit until the next reading
}
