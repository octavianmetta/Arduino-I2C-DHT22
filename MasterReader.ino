#include <Arduino.h>
#include <Wire.h>
#define dataSize 8              //Ukuran data dari 2 float yang diterima         
#define startingAddress 8       //Alamat mulai slave
#define numberOfDevices 3       //Jumlah slave
typedef union float2bytes_t     //Union untuk konversi float menjadi bytes. 
                                //Union berisi satu variabel yang direpresentasikan dalam berbagai tipe data 
{ 
  float f; 
  char b[sizeof(float)]; 
}; 

byte I2C_data[dataSize]={0};    // Array untuk menerima data
float temp[3]={0};              //Array untuk menyimpan data dari sender
float humid[3]={0};             //Array untuk menyimpan data dari sender

float meanFunc(float value[], int size);        //Fungsi mean
float medianFunc(float value[]);                //Fungsi median
float modusFunc(float value[]);                 //Fungsi modus

void setup() {
        Wire.begin();     // join i2c bus (address optional for master)
        Serial.begin(9600); // start serial for output
}

void loop() {
        float2bytes_t t2f, h2f;         //Deklarasi untuk konversi menjadi float
        for(int i=startingAddress; i<(startingAddress+numberOfDevices); i++){      //Loop untuk akuisisi data dari sender
                Wire.requestFrom(i, dataSize); //Alamat sender dimulai dari 8-10
                int j=0;
                while(Wire.available()){
                        I2C_data[j]=Wire.read();        //Terima data byte berurutan
                        j++;
                }

        t2f.b[0] = I2C_data[0];
        t2f.b[1] = I2C_data[1];
        t2f.b[2] = I2C_data[2];
        t2f.b[3] = I2C_data[3];
        temp[i-startingAddress]=t2f.f;
    
        h2f.b[0] = I2C_data[4];
        h2f.b[1] = I2C_data[5];
        h2f.b[2] = I2C_data[6];
        h2f.b[3] = I2C_data[7];
        humid[i-startingAddress]=h2f.f;
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

float medianFunc(float value[3]){

        bool A,B,C = false; //Boolean untuk pembanding
        float median = 0; //Untuk menyimpan nilai median


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

float meanFunc(float value[], int size){
        int i, sum = 0;
        double mean;

        for (i = 0; i < size; ++i) {
                sum += value[i];
        }
        mean = double(sum) / size;

        return(mean);
}

float modusFunc(float value[]){
        float modus = 0; //Untuk menyimpan nilai modus

        for(int i=0; i<3; i++) {
                for(int j=i+1; j<3; j++) {
                        if(value[i]==value[j]) modus = value[j];
                }
        }
        return(modus);
}
