/*####################################################################
 FILE: dht11_functions.pde
 VERSION: 0.4.5
 PURPOSE: Test DHT11 Temperature & Humidity Sensor library functions
 LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)

 DATASHEET: http://feed.virtuabotix.com/wp-content/uploads/2011/11/DHT11.pdf
 GET UPDATES: http://feed.virtuabotix.com/?239
 
     --##--##--##--##--##--##--##--##--##--##--  
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     | ##  ##  ##  ##  ##  ##  ##  ##  ##  ## |
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     | ##  ##  ##  ##  ##  ##  ##  ##  ##  ## |
     ##  ##  ##  ## DHT11 SENSOR ##  ##  ##  ##
     ##  ##  ##  ##  ##FRONT ##  ##  ##  ##  ##
     | ##  ##  ##  ##  ##  ##  ##  ##  ##  ## |
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     | ##  ##  ##  ##  ##  ##  ##  ##  ##  ## |
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     ##  ##  ##  ##  ##  ##  ##  ##  ##  ##  ##
     --##--##--##--##--##--##--##--##--##--##--
         ||       ||          || (Not    || 
         ||       ||          || Used)   || 
       VDD(5V)   Readout(I/O)          Ground
                 
 HISTORY:
 Mod by Joseph Dattilo (Virtuabotix LLC) - Version 0.4.5 (11/11/11)
 Mod by Joseph Dattilo (Virtuabotix LLC) - Version 0.4.0 (06/11/11)
 Mod by Rob Tillaart - Version 0.3 (28/03/2011)
 Mod by SimKard - Version 0.2 (24/11/2010)
 George Hadjikyriacou - Original version (??)
#######################################################################*/

#include <dht11.h>

dht11 DHT11;

void setup()
{
  DHT11.attach(2);
  Serial.begin(9600);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
}

void loop()
{
  Serial.println("\n");

  int chk = DHT11.read();

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, DEC);

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, DEC);

  Serial.print("Temperature (°F): ");
  Serial.println(DHT11.fahrenheit(), DEC);

  Serial.print("Temperature (°K): ");
  Serial.println(DHT11.kelvin(), DEC);

  Serial.print("Dew Point (°C): ");
  Serial.println(DHT11.dewPoint(), DEC);

  Serial.print("Dew PointFast (°C): ");
  Serial.println(DHT11.dewPointFast(), DEC);

  delay(2000);
}
