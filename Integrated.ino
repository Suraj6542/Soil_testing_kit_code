const int sensor_pin = A1;          // Soil moisture sensor O/P pin
const int pH_sensor_pin = A0;       // pH meter Analog output pin
#include <SoftwareSerial.h>
unsigned long int avgValue;         // Store the average value of the pH sensor feedback
float b;
int buf[10],temp;
#define RE 8
#define DE 7

const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];
SoftwareSerial mod(2,3);
void setup()
{
  pinMode(13, OUTPUT);             // Set pin 13 as output for LED
  Serial.begin(9600);              // Define baud rate for serial communication
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}
void loop()
{
  // Soil Moisture Sensor Code
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = (100 - ((sensor_analog/1023.00) * 100));
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");

  // pH Sensor Code
  for(int i=0; i<10; i++)           // Get 10 sample value from the pH sensor for smoothing the value
  { 
    buf[i] = analogRead(pH_sensor_pin);
    delay(10);
  }

  for(int i=0; i<9; i++)            // Sort the analog from small to large
  {
    for(int j=i+1; j<10; j++)
    {
      if(buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0;
  for(int i=2; i<8; i++)            // Take the average value of 6 center samples
    avgValue += buf[i];

  float phValue = (float)avgValue * 5.0 / 1024 / 6; // Convert the analog into millivolt
  phValue = 3.5 * phValue;           // Convert the millivolt into pH value

  Serial.print("pH:");  
  Serial.print(phValue, 2);
  Serial.println(" ");

  digitalWrite(13, HIGH);          // Turn on LED
  delay(800);
  digitalWrite(13, LOW);           // Turn off LED
  delay(200);
 byte val1,val2,val3;
  val1 = nitrogen();
  delay(250);
  val2 = phosphorous();
  delay(250);
  val3 = potassium();
  delay(250);
  
  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  Serial.print("Phosphorous: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  delay(2000);
}

byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

