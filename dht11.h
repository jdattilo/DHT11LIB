/*####################################################################
 FILE: dht11.cpp
 VERSION: 0.4.5
 PURPOSE: DHT11 Temperature & Humidity Sensor library for Arduino
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

#ifndef dht11_h
#define dht11_h

// make compatible for arduino > 1.0
// http://nootropicdesign.com/forum/viewtopic.php?t=2434
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define DHT11LIB_VERSION "0.4.5"

class dht11
{
private:
	int sensorPin;//defaults to pin 2
public:
    void attach(int pin);//Attaches dht11 object to a particular sensorPin
	int read();//defaults to the attached pin
    int read(int pin);
	int humidity;
	int temperature;
	int celcius();
	double fahrenheit();
	double fahrenheit(double dCelcius);
	double kelvin();
	double kelvin(double dCelcius);
	double dewPoint();
	double dewPointFast();
};
#endif
