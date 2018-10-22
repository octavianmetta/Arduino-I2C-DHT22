#include "DHT.h"
#include <Wire.h>
#define PACKET_SIZE 8
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
const byte addrSlaveI2C =  8;  // I2C Slave address of this device
float temp = 0;
float humid = 0;

byte I2C_Packet[PACKET_SIZE];            // Array to hold data sent over I2C to main Arduino
DHT dht(DHTPIN, DHTTYPE);

// convert float to byte array  source: http://mbed.org/forum/helloworld/topic/2053/
typedef union float2bytes_t   // union consists of one variable represented in a number of different ways 
{ 
  float f; 
  byte b[sizeof(float)]; 
}; 

void setup() {
        Wire.begin(addrSlaveI2C);    // Initiate the Wire library and join the I2C bus         
        Wire.onRequest(RequestData);
        Serial.begin(9600);
        Serial.println("DHTxx test!");

        dht.begin();
}

void loop() {
        delay(1000);

        humid = dht.readHumidity();
        temp = dht.readTemperature();
        // Check if any reads failed and exit early (to try again).
        if (isnan(humid) || isnan(temp)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
        }
        float2bytes_t t2b,h2b; 
        t2b.f = temp;
        I2C_Packet[0] = t2b.b[0];
        I2C_Packet[1] = t2b.b[1];
        I2C_Packet[2] = t2b.b[2];
        I2C_Packet[3] = t2b.b[3];
        h2b.f = humid;
        I2C_Packet[4] = h2b.b[0];
        I2C_Packet[5] = h2b.b[1];
        I2C_Packet[6] = h2b.b[2];
        I2C_Packet[7] = h2b.b[3];
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.println(" *C ");
}

void RequestData()
{
	Wire.write(I2C_Packet,PACKET_SIZE);
}
