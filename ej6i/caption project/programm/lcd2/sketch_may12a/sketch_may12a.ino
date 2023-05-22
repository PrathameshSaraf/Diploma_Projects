#include <SPI.h>

#include <LiquidCrystal.h>



// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  // set up the LCD’s number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);

  // Clears the LCD screen
  lcd.clear();
}

void loop() 
{
  // Print a message to the LCD.
  char k [10]="haaaa";
   
  lcd.println(k);
  
 delay(2000);
  lcd.clear();
  

 
  
  Serial.println("LCD Tutorial");
}
