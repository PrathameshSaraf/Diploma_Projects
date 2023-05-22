#include <RH_ASK.h> //include a radiohead library for Rf module interface

#include <SPI.h> //Include dependant SPI Library for communicating with transmitter
#include <OneWire.h>//include a oneWire library for temperature sensor
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS 0// Data wire is plugged into digital pin 0 on the Arduino

OneWire oneWire(ONE_WIRE_BUS);// Setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire);// Pass oneWire reference to DallasTemperature 
RH_ASK rf_driver;// Create Amplitude Shift Keying Object

//*******FUNCTION INITIALIZATION********
float read_mq7(void);//initialize function to read carbon monoxide value 
float read_mq2(void);//initialize function to read smoke gas value 
float read_ph(void);//initialize function to read PH value of solution
float get_temperature(void);//initialize function to read temperature value of solution 


void setup() 
{
Serial.begin(9600);
rf_driver.init(); // Initialize ASK Object


}

void loop() {
 
  float PH, Temperature, MQ7value,MQ2value; ; // initialize the variables to store the input value of the sensors 
  String transmit ,transmit_msg;// Define output strings

 PH = read_ph();//call the function to measure the get the PH data
 transmit_msg=String(PH);//converte the data into string for transmitting through the rf module
 transmit = "PH value " + transmit_msg;//concinate the msg string and converted data to transmit 
 const char *msg_ph = transmit.c_str();  // Compose output character
 rf_driver.send((uint8_t *)msg_ph, strlen(msg_ph));//transmit the data using the inbuild function of RH library
 rf_driver.waitPacketSent();//wait for the data to be send 
 delay(200);

//same procedure for the temperature value
 Temperature = get_temperature();
 transmit_msg=String(Temperature);
 transmit = "PH value " + transmit_msg;
const char  *msg_temperature = transmit.c_str();
 rf_driver.send((uint8_t *)msg_temperature, strlen(msg_temperature));
 rf_driver.waitPacketSent();
 delay(200);
 
//same procedure for the carbon monoxide  value
 MQ7value = read_mq7();
 transmit_msg=String(MQ7value);
 transmit = "PH value " + transmit_msg;
const char  *msg_mq7 = transmit.c_str();
rf_driver.send((uint8_t *)msg_mq7, strlen(msg_mq7));
rf_driver.waitPacketSent();
delay(200);

//same procedure for the smoke gas value
 MQ2value = read_mq2();
  transmit_msg = String(MQ2value);
 transmit = "PH value " + transmit_msg;
const char  *msg_mq2 = transmit.c_str();
 rf_driver.send((uint8_t *)msg_mq2, strlen(msg_mq2));
 rf_driver.waitPacketSent();
 delay(200);
 
}



//*******DEFINING THE FUNCTION********
//defining the function to read the ph value
float read_ph(void)
{
 const int analogInPin = A0;//variable to store the data read by analog pin 0 
unsigned long int avgValue;// variable to store the avarage of sensor value taken

int buf[10],temp;// variable to store the 10 samples of ph measured and a ''temp'' to store temperary value
for(int i=0;i<10;i++) //lope to take a 10 samples of the the ph value
 { 
  buf[i]=analogRead(analogInPin);//read the ph value 
  delay(10);
 }for(int i=0;i<9;i++)//sort the analog values  from small to large
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
 for(int i=2;i<8;i++) //take the average value of 6 center sample
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;//convert the values in  into volt
 float phValue = -5.70 * pHVol + 21.34; //convert the volt into pH value
 return phValue;// return the PH value to function call.
 delay(20);
}




//defining the function to read the temperature value
float get_temperature(void)
{
  float Celsius = 0;//define the variable to store the temperature value
  sensors.begin();// begin the sensors library
   sensors.requestTemperatures();//read the temperature 
    Celsius = sensors.getTempCByIndex(0);//store the  temperatur value in the variable
    return Celsius;//return the temperature value to function call
}

//defining the function to read the carbon monoxide value
float read_mq7 (void)
{
int pinbuzzer = 11;//assign the buzzer  pin to digital 11 pin of arduino
int threshold_level=2;//assign the threshold pin of sensor to digital pin 2 of arduino
float pinSensor = A2;//variable to store the analog value of sensor from analog pin2 of arduino
int THRESHOLD = 300;//set the threshold level according to the requirement 
pinMode(pinbuzzer, OUTPUT);//assing pin as output

pinMode(pinSensor, INPUT);//assign pin as input
pinMode(threshold_level,INPUT);//assign pin as input

int analogValue = analogRead(pinSensor);//read the analog value of carbon monoxide
return analogValue ;//return the measured value 
digitalWrite(pinbuzzer, LOW);//low the buxzzer 
if (analogValue >= THRESHOLD )//if the read value is above the thereshold 
  digitalWrite(pinbuzzer,HIGH );//then sound the buzzer 
else 
digitalWrite(pinbuzzer,LOW );//if not then dont sound 

}


//defining the function to read the smoke gas  value
float read_mq2 (void)
{
int pinbuzzer = 11; //assign the buzzer  pin to digital 11 pin of arduino
int threshold_level=1;//assign the threshold pin of sensor to digital pin 1 of arduino
float pinSensor = A1;//variable to store the analog value of sensor from analog pin2 of arduino
int THRESHOLD = 450;//set the threshold level according to the requirement 
pinMode(pinbuzzer, OUTPUT);//assing pin as output
pinMode(pinSensor, INPUT);//assign pin as input
pinMode(threshold_level,INPUT);//assign pin as input

int analogValue = analogRead(pinSensor);//read the analog value of smoke gas
return analogValue ;//return the measured value to function call
digitalWrite(pinbuzzer, LOW);//low the buxzzer 
if (analogValue >= THRESHOLD )//if the read value is above the thereshold 
digitalWrite(pinbuzzer,HIGH );// then sound the buzzer 
else 
digitalWrite(pinbuzzer,LOW );//if not then dont sound 

}
