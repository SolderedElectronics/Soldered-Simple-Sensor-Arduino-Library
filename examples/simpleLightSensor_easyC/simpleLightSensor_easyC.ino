/**
 **************************************************
 *
 * @file        simpleLightSensor_easyC.ino
 * @brief       Read all the values of the Simple Light Sensor, easyC version.
 *              Also, see how to calibrate it!
 * 
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board via easyC
 *              -Open Serial monitor at 115200 baud!
 *
 *              Simple Light Sensor easyC: solde.red/333041
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert Sorić @ soldered.com
 ***************************************************/

#include "Simple-Light-Sensor-SOLDERED.h" // Include the required library

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
 * 100.00% represents a bright light near the sensor.
 * 
 * You may also use isLightDetected to get a simple digital reading - is light detected or not?
 * The threshold of this reading is adjusted by the setThreshold function.
 * 
 * The LED on the board will turn on if the threshold is reached.
 * If you want to invert this, use invertLED()
*/

// Create the sensor object
simpleLightSensor lightSensor;

void setup()
{
    Serial.begin(115200); // Begin Serial communication so we can see the output

    lightSensor.begin(); // Init the Simple Light Sensor
    
    // If you're starting the sensor on a different address, use this constructor
    //lightSensor.begin(0x32);

    // The default address is 0x30
    // You may change the address via the switches on the front of the board
    // In this table, 'x' represents a switch toggled 'UP'
    // Note that on the physical switches 1 and 3 are swapped
    // Address | 3 | 2 | 1 |
    // 0x30    |   |   |   |
    // 0x31    |   |   | x |
    // 0x32    |   | x |   |
    // 0x33    |   | x | x |
    // 0x34    | x |   |   |
    // 0x35    | x |   | x |
    // 0x36    | x | x |   |
    // 0x37    | x | x | x |

    // Set the threshold for reading is light detected or not
    lightSensor.setThreshold(35.5);

    // Sensor calibration isn't needed but it helps with getting more relevant readings.
    // To calibrate the sensor, first run this sketch with the line of code below commented:
    //lightSensor.calibrate(76.4);

    // Place the sensor so it's as bright as you're ever going to want to measure.
    // This can be under the bright sun or under a small LED light, for example, it's up to you!
    // Note the reading of the light percentage, and then write that value in the calibrate function.
    // What this does is essentially make the range of measurement smaller so the data you get is more relevant.

    // Optionally, Invert the LED on the board
    //lightSensor.invertLED(true);
}

void loop()
{
    // Print the readings to Serial

    // Raw reading is essentially a reading of the analog value on the easyC board
    Serial.print("Raw reading: ");
    Serial.println(lightSensor.getRawReading());
    
    // The resistance is calcualted through a constant
    Serial.print("Resistance: ");
    Serial.print(lightSensor.getResistance());
    Serial.println(" Ohm.");

    // Print percentage of light detection of sensor
    Serial.print("Light detection: ");
    Serial.print(lightSensor.getValue());
    Serial.println("%");

    // Print is a light detected or not
    // Once again, you may adjust this threshold with setThreshold
    Serial.print("Light detected? ");
    if(lightSensor.isLightDetected()) Serial.println("True!");
    else Serial.println("False!");

    Serial.println(); // Print newline

    delay(1000); // Wait a bit until the next reading
}
