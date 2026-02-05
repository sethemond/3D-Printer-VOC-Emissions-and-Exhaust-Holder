/**
* The MySensors Arduino library handles the wireless radio link and protocol
* between your home built sensors/actuators and HA controller of choice.
* The sensors forms a self healing radio network with optional repeaters. Each
* repeater and gateway builds a routing tables in EEPROM which keeps track of the
* network topology allowing messages to be routed to nodes.
*
* Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
* Copyright (C) 2013-2019 Sensnology AB
* Full contributor list: https://github.com/mysensors/MySensors/graphs/contributors
*
* Documentation: http://www.mysensors.org
* Support Forum: http://forum.mysensors.org
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation.
*
*******************************
*
* DESCRIPTION
* The ArduinoGateway prints data received from sensors on the serial link.
* The gateway accepts input on serial which will be sent out on radio network.
*
* The GW code is designed for Arduino Nano 328p / 16MHz
*
* Wire connections (OPTIONAL):
* - Inclusion button should be connected between digital pin 3 and GND
* - RX/TX/ERR leds need to be connected between +5V (anode) and digital pin 6/5/4 with resistor 270-330R in a series
*
* LEDs (OPTIONAL):
* - To use the feature, uncomment any of the MY_DEFAULT_xx_LED_PINs
* - RX (green) - blink fast on radio message received. In inclusion mode will blink fast only on presentation received
* - TX (yellow) - blink fast on radio message transmitted. In inclusion mode will blink slowly
* - ERR (red) - fast blink on error during transmission error or receive crc error
*
*/

// Enable debug prints to serial monitor
#define MY_DEBUG


// Enable and select radio type attached
#define MY_RADIO_RF24
//#define MY_RADIO_NRF5_ESB
//#define MY_RADIO_RFM69
//#define MY_RADIO_RFM95

// Set LOW transmit power level as default, if you have an amplified NRF-module and
// power your radio separately with a good regulator you can turn up PA level.
#define MY_RF24_PA_LEVEL RF24_PA_LOW

//// Enable serial gateway
//#define MY_GATEWAY_SERIAL
//
//// Define a lower baud rate for Arduinos running on 8 MHz (Arduino Pro Mini 3.3V & SenseBender)
//#if F_CPU == 8000000L
//#define MY_BAUD_RATE 38400
//#endif
//
//// Enable inclusion mode
//#define MY_INCLUSION_MODE_FEATURE
//// Enable Inclusion mode button on gateway
////#define MY_INCLUSION_BUTTON_FEATURE
//
//// Inverses behavior of inclusion button (if using external pullup)
////#define MY_INCLUSION_BUTTON_EXTERNAL_PULLUP
//
//// Set inclusion mode duration (in seconds)
//#define MY_INCLUSION_MODE_DURATION 60
//// Digital pin used for inclusion mode button
////#define MY_INCLUSION_MODE_BUTTON_PIN  3
//
//// Set blinking period
//#define MY_DEFAULT_LED_BLINK_PERIOD 300

// Inverses the behavior of leds
//#define MY_WITH_LEDS_BLINKING_INVERSE

// Flash leds on rx/tx/err
// Uncomment to override default HW configurations
//#define MY_DEFAULT_ERR_LED_PIN 4  // Error led pin
//#define MY_DEFAULT_RX_LED_PIN  6  // Receive led pin
//#define MY_DEFAULT_TX_LED_PIN  5  // the PCB, on board LED

#include <MySensors.h>
#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"

Adafruit_SGP40 sgp;
Adafruit_SHT31 sht31;

#define TEMP_CHILD_ID 0
#define HUM_CHILD_ID 1
#define VOCRAW_CHILD_ID 2
#define VOC_CHILD_ID 3

// MY SENSOR COMMUNICATION VARIABLES
MyMessage tempMsg(TEMP_CHILD_ID, V_TEMP);
MyMessage humMsg(HUM_CHILD_ID, V_HUM);
MyMessage rawMsg(VOCRAW_CHILD_ID, V_VAR1);
MyMessage vocMsg(VOC_CHILD_ID, V_LEVEL);

//SET TIMING CONSTANTS
const unsigned long tUpdate=1000; //undate interval (every 1s)
unsigned long t0; // time of last update


void setup()
{
	// Setup locally attached sensors
 Wire.begin(); //theoretically start wire communication protocol
 //Serial.begin(115200); /// for serail debugging over USB (will this interfer with gateway??)

   if (! sgp.begin()){
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }

  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1);
  }
  //update time
  t0 = millis();
  
}

void presentation()
{
	// Present locally attached sensors
 sendSketchInfo("Node 2-VOC Sensor", "0.1.0");

 //Tell Gateway what kind of sensor are locally attached
 present(TEMP_CHILD_ID, S_TEMP);
 present(HUM_CHILD_ID, S_HUM);
 present(VOCRAW_CHILD_ID, S_CUSTOM);
 present(VOC_CHILD_ID, S_AIR_QUALITY);
}

void loop()
{
	// Send locally attached sensor data here
 if ((millis()-t0) > tUpdate) ServerUpdate();
}

void ServerUpdate(){
  
  uint16_t VOCraw;
  int32_t voc_index;
  float hum;
  float temp;

  temp = sht31.readTemperature();
  hum = sht31.readHumidity();
  VOCraw = sgp.measureRaw(temp, hum);
  voc_index = sgp.measureVocIndex(temp, hum);


  //send variable data. 
  //msg.set(float, <int>decimal places)  https://mysensors.readthedocs.io/en/latest/api.html
  send(tempMsg.set(temp*9/5+32, 3)); //convert to F
  send(humMsg.set(hum, 3));
  send(rawMsg.set(VOCraw));
  send(vocMsg.set(voc_index));

  }
