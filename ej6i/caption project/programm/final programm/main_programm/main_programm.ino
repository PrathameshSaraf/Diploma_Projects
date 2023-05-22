#include <RH_ASK.h>
 //Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);







int read_mq7(void);
int read_mq2(void);
int read_ph(void);
int get_temperature(void);


void setup() 
{
  Serial.begin(9600);
rf_driver.init(); // Initialize ASK Object

}

void loop() {
 int PH, Temperature ;
 int MQ7value,MQ2value;

  String transmit;
  String transmit_msg;
  
 PH = read_ph();
 transmit_msg=String(PH);
 transmit = "PH value " + PH;
 const char *msg_ph = transmit.c_str();
 rf_driver.send((uint8_t *)msg_ph, strlen(msg_ph));
 rf_driver.waitPacketSent();

 Temperature = get_temperature();
 transmit_msg=String(Temperature);
 transmit = "PH value " + Temperature;
const char  *msg_temperature = transmit.c_str();
 rf_driver.send((uint8_t *)msg_temperature, strlen(msg_temperature));
 rf_driver.waitPacketSent();

MQ7value = read_mq7();
  transmit_msg=String(MQ7value);
 transmit = "PH value " + MQ7value;
const char  *msg_mq7 = transmit.c_str();
 rf_driver.send((uint8_t *)msg_mq7, strlen(msg_mq7));
 rf_driver.waitPacketSent();



 MQ2value = read_mq2();
  transmit_msg = String(MQ2value);
 transmit = "PH value " + MQ2value;
const char  *msg_mq2 = transmit.c_str();
 rf_driver.send((uint8_t *)msg_mq2, strlen(msg_mq2));
 rf_driver.waitPacketSent();
 
 

 

}



//function decleration



//function difining
int read_ph(void)
{
  const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 

int buf[10],temp;
for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
 }for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 int pHVol=(float)avgValue*5.0/1024/6;
 int phValue = -5.70 * pHVol + 21.34; 
 return phValue;
 delay(20);
}





//function defination
int get_temperature(void)
{
  int Celsius = 0;
  sensors.begin();
   sensors.requestTemperatures();
    Celsius = sensors.getTempCByIndex(0);
    return Celsius;
}


int read_mq7 (void)
{
int pinbuzzer = 11;
int threshold_level=2;
int pinSensor = A2;
int THRESHOLD = 250;
pinMode(pinbuzzer, OUTPUT);

pinMode(pinSensor, INPUT);
pinMode(threshold_level,INPUT);
int analogValue = analogRead(pinSensor);

digitalWrite(pinbuzzer, LOW);
if (analogValue >= THRESHOLD )
  digitalWrite(pinbuzzer,HIGH );
else 
digitalWrite(pinbuzzer,LOW );
return analogValue ;
}



int read_mq2 (void)
{
int pinbuzzer = 11;
int thresholdlevel=1;
int pinSensor = A1;
int THRESHOLD = 250;
pinMode(pinbuzzer, OUTPUT);

pinMode(pinSensor, INPUT);
int analogValue = analogRead(pinSensor);

digitalWrite(pinbuzzer, LOW);
if (analogValue >= THRESHOLD )
  digitalWrite(pinbuzzer,HIGH );
else 
digitalWrite(pinbuzzer,LOW );
return analogValue ;
}
