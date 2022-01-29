//Sensors' Library
#include "DHT.h"
#include "String.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup()
{
  Serial.begin(9600);     //Test printing baud rate
  Serial1.begin(57600);   //Sever's baud rate

  dht.begin();

  pinMode(8, INPUT);
  starttime = millis();//get the current time;
}

void loop()
{
  // Reading temperature & humidity //
  float t = 29.23;
  float h = 72.56;
  dht.readHT(&t, &h);
  delay(20);


  // Reading UV //
  int sensorValue;
  long  sum = 0;
  int uv_index = 0;
  for (int i = 0; i < 32; i++)
  {
    sensorValue = analogRead(A0);
    sum = sensorValue + sum;
    delay(1);
  }
  sum = sum >> 5;
  sum = sum * 4980.0 / 1023.0;
  delay(20);

  if(sum < 50)
    uv_index = 0;
  else if(sum > 50 && sum < 227)
    uv_index = 1;
  else if(sum > 227 && sum < 318)
    uv_index = 2;
  else if(sum > 318 && sum < 408)
    uv_index = 3;
  else if(sum > 408 && sum < 503)
    uv_index = 4;
  else if(sum > 503 && sum < 606)
    uv_index = 5;
  else if(sum > 606 && sum < 696)
    uv_index = 6;
  else if(sum > 696 && sum < 795)
    uv_index = 7;
  else if(sum > 795 && sum < 881)
    uv_index = 8;
  else if(sum > 881)
    uv_index = 9;
 // else if(sum > 976 && sum < 1079)
 //   uv_index = 10;
 //else if(sum > 1079)
 //   uv_index = 11;
    


  //Reading Dust //
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;
  if ((millis() - starttime) > sampletime_ms) //if the sampel time == 30s
  {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0); // Integer percentage 0=>100
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
    lowpulseoccupancy = 0;
    starttime = millis();
  }

//Test printing
  Serial.println("------------------------------");
  Serial.print("temperature = ");
  Serial.println(t);
  Serial.print("humidity = ");
  Serial.println(h);
  Serial.print("UV index = ");
  Serial.print(uv_index);
  Serial.println("mV");
  Serial.print("Dust concentration = ");
  Serial.print(concentration);
  Serial.println(" pcs/0.01cf");


//Convert snesors' datas to specific string format
  String mystring = String(int(100 * t));
  mystring += String(int(100 * h));
  mystring += String(int(uv_index));
  char abc[10]; 
  mystring.toCharArray(abc, 10);

  //Test printing
  Serial.println(abc);

  //Print data string to server
  Serial1.write(abc);

}
