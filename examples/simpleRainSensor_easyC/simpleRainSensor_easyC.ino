/**
 **************************************************
 *
 * @file        simpleRainSensor_easyC.ino
 * @brief       Read all the values of the Simple Rain Sensor, easyC version.
 *              Also, see how to calibrate it!
 * 
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board via easyC
 *              -Open Serial monitor at 115200 baud!
 *
 *              Simple Rain Sensor easyC: solde.red/333043
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert Sorić @ soldered.com
 ***************************************************/

#include "Simple-Rain-Sensor-SOLDERED.h" // Include the required library

/**
 * How it works:
 * 
 * This sensor works on the principle that humidity will short electrical
 * contacts on the board of the Rain sensor, thus, lowering the resistance.
 * Through this, a percentage can be calculated which indicates presence of rain.
 * 
 * You can use the function getValue() to get that percentage.
 * 
 * 0.00% represents no shorted contacts, so, no rain at all.
 * 100.00% represents fully shorted contacts - the sensor is fully wet, so, rain is detected.
 * 
 * You may also use isRaining to get a simple digital reading - is it raining or not?
 * The threshold of this reading is adjusted by the setThreshold function.
 * 
 * The LED on the board will turn on if the threshold is reached.
 * If you want to invert this, use invertLED()
*/

// Create the sensor object
simpleRainSensor rainSensor;

void setup()
{
    Serial.begin(115200); // Begin Serial communication so we can see the output

    rainSensor.begin(); // Init the Simple Rain Sensor

    // If you're starting the sensor on a different address, use this constructor
    //rainSensor.begin(0x32);

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

    // Set the threshold for reading is it raining or not
    rainSensor.setThreshold(35.5);

    // Sensor calibration isn't needed but it helps with getting more relevant readings.
    // To calibrate the sensor, first run this sketch with the line of code below commented:
    //rainSensor.calibrate(76.4);

    // Place the sensor in water - so it's as wet as you're ever going to want to measure.
    // Note the reading of the Rain percentage, and then write that value in the calibrate function.
    // What this does is essentially make the range of measurement smaller so the data you get is more relevant.

    // Optionally, Invert the LED on the board
    //rainSensor.invertLED(true);
}

void loop()
{
    // Print the readings to Serial

    // Raw reading is essentially a reading of the analog value on the easyC board
    Serial.print("Raw reading: ");
    Serial.println(rainSensor.getRawReading());
    
    // The resistance is calcualted through a constant
    Serial.print("Resistance: ");
    Serial.print(rainSensor.getResistance());
    Serial.println(" Ohm.");

    // Print percentage of rain detected on sensor
    Serial.print("Rain percentage: ");
    Serial.print(rainSensor.getValue());
    Serial.println("%");
    
    // Print is it raining or not
    // Once again, you may adjust this threshold with setThreshold
    Serial.print("Is it raining? ");
    if(rainSensor.isRaining()) Serial.println("True!");
    else Serial.println("False!");

    Serial.println(); // Print newline

    delay(1000); // Wait a bit until the next reading
}
