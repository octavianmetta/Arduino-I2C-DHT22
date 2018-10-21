#include <Arduino.h>
#include <Wire.h>
#define dataSize 2
#define startingAddress 8

int8_t I2C_data[2]={0}; // Array untuk menerima data
int8_t temp[3]={0};   //Array untuk menyimpan data dari sender
int8_t humid[3]={0};  //Array untuk menyimpan data dari sender

float meanFunc(int8_t value[], int size);
int8_t medianFunc(int8_t value[]);
int8_t modusFunc(int8_t value[]);

void setup() {
        Wire.begin();     // join i2c bus (address optional for master)
        Serial.begin(9600); // start serial for output
}

void loop() {
        for(int i=startingAddress; i<(startingAddress+3); i++) { //Loop untuk akuisisi data dari sender
                Wire.requestFrom(i, dataSize); //Alamat sender dimulai dari 2-4
                I2C_data[0]=Wire.read();
                I2C_data[1]=Wire.read();

                temp[i-startingAddress]=I2C_data[0];
                humid[i-startingAddress]=I2C_data[1];
        }
        Serial.println("");

        //TEMPERATURE
        //MEDIAN
        Serial.print("Temp Median  = "); Serial.print(medianFunc(temp));

        //MEAN
        Serial.print("  Temp Mean  = "); Serial.print(meanFunc(temp, 3));

        //MODUS
        Serial.print("  Temp Modus  = "); Serial.println(modusFunc(temp));

        //HUMIDITY
        //MEDIAN
        Serial.print("Humid Median  = "); Serial.print(medianFunc(humid));

        //MEAN
        Serial.print("  Humid Mean  = "); Serial.print(meanFunc(humid, 3));

        //MODUS
        Serial.print("  Humid Modus  = "); Serial.println(modusFunc(humid));

        Serial.println("");

        delay(1000);
}

int8_t medianFunc(int8_t value[3]){

        bool A,B,C = false; //Boolean untuk pembanding
        int8_t median = 0; //Untuk menyimpan nilai median


        if(value[0]<=value[1]) A=false;
        else A=true;
        if(value[1]<=value[2]) B=false;
        else B=true;
        if(value[0]<=value[2]) C=false;
        else C=true;

        //Untuk memilih keluaran data dengan metode median
        //Data yang termasuk median yang dipakai
        if((!A&&C)||(A&&!C)) median = value[0]; //Persamaan didapatkan dari kmap di sisdig
        if((!A&&!B)||(A&&B)) median = value[1]; //Tabel kebenaran multiplexer
        if((!B&&C)||(B&&!C)) median = value[2];
        return(median);
}

float meanFunc(int8_t value[], int size){
        int i, sum = 0;
        double mean;

        for (i = 0; i < size; ++i) {
                sum += value[i];
        }
        mean = double(sum) / size;

        return(mean);
}

int8_t modusFunc(int8_t value[]){
        int8_t modus = 0; //Untuk menyimpan nilai modus

        for(int i=0; i<3; i++) {
                for(int j=i+1; j<3; j++) {
                        if(value[i]==value[j]) modus = value[j];
                }
        }
        return(modus);
}
