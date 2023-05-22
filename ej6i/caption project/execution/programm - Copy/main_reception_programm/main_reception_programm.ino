#include <RH_ASK.h>// Include dependant SPI Library 
#include <SPI.h> // Create Amplitude Shift Keying Object
RH_ASK rf_driver;
#include <LiquidCrystal.h>//include the liquid crystal diaply library
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

String str_out;//string to store the recived data
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // set up the LCD’s number of columns and rows:
    lcd.begin(20, 4);
    // Clears the LCD screen
    lcd.clear();
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[11];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      str_out = String((char*)buf);
      // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
      lcd.setCursor(0, 1);
       lcd.print(str_out );
       delay(3000);
       }
       else {
         lcd.print("data not received" );
        }
}
