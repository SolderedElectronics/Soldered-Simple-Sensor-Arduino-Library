/**
 **************************************************
 *
 * @file        simpleFireSensor_native.ino
 * @brief       Read all the values of the Simple Fire Sensor.
 *              Also, see how to calibrate it!
 * 
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board according to the diagrams below
 *              -Open Serial monitor at 115200 baud!
 *
 *              Simple Soil Sensor: solde.red/333045
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert Sorić @ soldered.com
 ***************************************************/

#include "Simple-Fire-Sensor-SOLDERED.h" // Include the required library

// Define pins to use for A0 and D0
// Make sure to change these so it suits your board
#define SENSOR_A0_PIN A2
#define SENSOR_D0_PIN 7

/**
 * Connecting diagram:
 *
 * Simple Fire Sensor           Dasduino Core / Connect / ConnectPlus
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
 * This sensor works on the principle that humidity will short electrical
 * contacts on the board of the Fire sensor, thus, lowering the resistance.
 * Through this, a percentage can be calculated which indicates moistness of the soil.
 * 
 * You can use the function getValue() to get that percentage.
 * 
 * 0.00% represents no shorted contacts, so, no rain at all.
 * 100.0% represents fully shorted contacts - the board is fully wet, so, rain is detected.
 * 
 * You may also use isRaining to get a simple digital reading - is it raining or not?
 * The threshold of this reading is adjusted by the small potentiometer on the board.
 * 
 * The LED on the board will turn off if the threshold is reached.
*/

// Create the sensor object on the set pins
simpleFireSensor fireSensor(SENSOR_A0_PIN, SENSOR_D0_PIN);

void setup()
{
    Serial.begin(115200); // Begin Serial communication so we can see the output
    
    fireSensor.begin(); // Init the Simple Fire Sensor

    // Sensor calibration isn't needed but it helps with getting more relevant readings.
    // To calibrate the sensor, first run this sketch with the line of code below commented:
    //fireSensor.calibrate(65.5);

    // Place the sensor in front of a fire.
    // Note the reading of the Fire detection percentage, and then write that value in the calibrate function.
    // What this does is essentially make the range of measurement smaller so the data you get is more relevant.
}

void loop()
{
    // Print the readings to Serial

    // Raw reading is essentially a reading of the analog value on SENSOR_A0_PIN
    Serial.print("Raw reading: ");
    Serial.println(fireSensor.getRawReading());
    
    // The resistance is calcualted through a constant
    Serial.print("Resistance: ");
    Serial.print(fireSensor.getResistance());
    Serial.println("Ohm.");

    // Print percentage of the fire detection of sensor
    Serial.print("Fire detection: ");
    Serial.print(fireSensor.getValue());
    Serial.println("%");

    // Print is a fire detected or not
    // Once again, you may adjust this threshold with the small potentiometer on the board
    Serial.print("Is the soil moist? ");
    if(fireSensor.isFireDetected()) Serial.println("True!");
    else Serial.println("False!");

    Serial.println(); // Print newline

    delay(1000); // Wait a bit until the next reading
}
