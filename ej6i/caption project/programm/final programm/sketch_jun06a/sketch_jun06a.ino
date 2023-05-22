#include <LiquidCrystal.h>



// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#include <OneWire.h>//include a oneWire library for temperature sensor
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS 8// Data wire is plugged into digital pin 8 on the Arduino

OneWire oneWire(ONE_WIRE_BUS);// Setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire);// Pass oneWire reference to DallasTemperature 


//*******FUNCTION INITIALIZATION********
float read_mq7(void);//initialize function to read carbon monoxide value 
float read_mq2(void);//initialize function to read smoke gas value 
float read_ph(void);//initialize function to read PH value of solution
float get_temperature(void);//initialize function to read temperature value of solution 


void setup() 
{
  
lcd.begin(20, 4);
Serial.begin(9600);
lcd.clear();
}




void loop() {
 
 float PH, Temperature, MQ7value,MQ2value; ; // initialize the variables to store the input value of the sensors 
  

 PH = read_ph();//call the function to measure the get the PH data
 lcd.setCursor(0, 0);
 lcd.print("PH Value      ");
 lcd.print(PH);
 delay(20);
 
 


//same procedure for the temperature value
 Temperature = get_temperature();
 lcd.setCursor(0, 1);
 lcd.print("Temperature  ");
 lcd.print(Temperature);
 lcd.print(" c");
  delay(20);

 
//same procedure for the carbon monoxide  value
 MQ7value = read_mq7();
 lcd.setCursor(0, 2);
 lcd.print("CO(MQ7)      ");
 lcd.print(MQ7value);
  delay(20);

//same procedure for the smoke gas value
 MQ2value = read_mq2();
  lcd.setCursor(0, 3);
 lcd.print("Smoke Gas    ");
 lcd.print(MQ2value);
 

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
 delay(10);
}




//defining the function to read the temperature value
float get_temperature(void)
{
  float Celsius = 0;//define the variable to store the temperature value
  sensors.begin();// begin the sensors library
   sensors.requestTemperatures();//read the temperature 
    Celsius = sensors.getTempCByIndex(0);//store the  temperatur value in the variable
    return Celsius;//return the temperature value to function call
    delay(10);
}

//defining the function to read the carbon monoxide value
float read_mq7 (void)
{

float pinSensor = A2;//variable to store the analog value of sensor from analog pin2 of arduino
pinMode(pinSensor, INPUT);//assign pin as input
int analogValue = analogRead(pinSensor);//read the analog value of carbon monoxide
return analogValue ;//return the measured value 
delay(10);
}


//defining the function to read the smoke gas  value
float read_mq2 (void)
{


float pinSensor = A1;//variable to store the analog value of sensor from analog pin2 of arduino
pinMode(pinSensor, INPUT);//assign pin as input
int analogValue = analogRead(pinSensor);//read the analog value of smoke gas
return analogValue ;//return the measured value to function call
delay(10);

}
