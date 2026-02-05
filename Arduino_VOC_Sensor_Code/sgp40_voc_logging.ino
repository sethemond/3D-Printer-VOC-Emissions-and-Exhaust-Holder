#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"

Adafruit_SGP40 sgp;
Adafruit_SHT31 sht31;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); } // Wait for serial console to open!

  Serial.println("SGP40 test with SHT31 compensation");

  if (! sgp.begin()){
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }

  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1);
  }

  Serial.print("Found SHT3x + SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
  Serial.println("Headers");
  Serial.println("Time\tTemperature(*C)\tHumidity(%)\tVocRaw\tVocIndex");
}

int counter = 0;
void loop() {
  uint16_t sraw;
  int32_t voc_index;
  char output[100];
  int32_t ttime = millis();
  Serial.print(ttime);
  Serial.print(",\t");
  float t = sht31.readTemperature();
  //Serial.print("Temp *C = "); 
  Serial.print(t); Serial.print(",\t");
  float h = sht31.readHumidity();
  //Serial.print("Hum. % = "); 
  Serial.print(h);
  Serial.print(",\t");

  sraw = sgp.measureRaw(t, h);
  //Serial.print("Raw measurement: ");
  Serial.print(sraw);
  Serial.print(",\t");

  voc_index = sgp.measureVocIndex(t, h);
  //Serial.print("Voc Index: ");
  Serial.print(voc_index);
  Serial.print("\t");
  Serial.print("\n\r");

  //sprintf(output, "%i\t%d\t%d\t%i\t%i", millis(),t,h,sraw,voc_index);
  //Serial.println(ttime + "\t" + t +"\t" + h +"\t" + sraw +"\t" + voc_index);
  delay(1000);
}
