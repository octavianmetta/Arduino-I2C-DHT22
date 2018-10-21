#include "DHT.h"
#include <Wire.h>
unsigned char I2Cdata[2];

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

void setup() {
        Wire.begin(8);          // join i2c bus with address #8
        Wire.onRequest(RequestData);
        Serial.begin(9600);
        Serial.println("DHTxx test!");

        dht.begin();
}

void loop() {
        delay(1000);

        float h = dht.readHumidity();
        float t = dht.readTemperature();
        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
        }
        I2Cdata[0] = t;
        I2Cdata[1] = h;
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.println(" *C ");
}

void RequestData()
{
        Wire.write(I2Cdata,2);
}
