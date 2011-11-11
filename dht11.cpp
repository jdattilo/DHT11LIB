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

#include "dht11.h"

// returnvalues:
//  0 : OK
// -1 : checksum error
// -2 : timeout

void dht11::attach(int pin)
{
	sensorPin = pin; //and there was much rejoicing! Pin attached.
}

int dht11::read()
{
	if(sensorPin<0){attach(2);}//not a pin change to default pin 2
	return read(sensorPin);//reads from attached sensorPin (attach command must be run first or this will use the default pin 2)
}

int dht11::read(int pin)
{
	// BUFFER TO RECEIVE
	uint8_t bits[5];
	uint8_t cnt = 7;
	uint8_t idx = 0;

	// EMPTY BUFFER
	for (int i=0; i< 5; i++) bits[i] = 0;

	// REQUEST SAMPLE
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(18);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);

	// ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	while(digitalRead(pin) == LOW)
		if (loopCnt-- == 0) return -2;

	loopCnt = 10000;
	while(digitalRead(pin) == HIGH)
		if (loopCnt-- == 0) return -2;

	// READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
	for (int i=0; i<40; i++)
	{
		loopCnt = 10000;
		while(digitalRead(pin) == LOW)
			if (loopCnt-- == 0) return -2;

		unsigned long t = micros();

		loopCnt = 10000;
		while(digitalRead(pin) == HIGH)
			if (loopCnt-- == 0) return -2;

		if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		if (cnt == 0)   // next byte?
		{
			cnt = 7;    // restart at MSB
			idx++;      // next byte!
		}
		else cnt--;
	}

	// WRITE TO RIGHT VARS
    // as bits[1] and bits[3] are allways zero they are omitted in formulas.
	humidity    = bits[0]; 
	temperature = bits[2]; 

	uint8_t sum = bits[0] + bits[2];  

	if (bits[4] != sum) return -1;
	return 0;
}

int dht11::celcius()
{
	read();//make sure the temp has been read

	return temperature;
}


//Celsius to Fahrenheit conversion
double dht11::fahrenheit(double dCelsius)
{
	return 1.8 * dCelsius + 32;
}

double dht11::fahrenheit()
{
	read();//make sure the temp has been read

	return fahrenheit(temperature);
}

//Celsius to Kelvin conversion
double dht11::kelvin(double dCelsius)
{
	return dCelsius + 273.15;
}

double dht11::kelvin()
{
	read();
	return kelvin(temperature);
}


// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm 
double dht11::dewPoint()
{
	read();//make sure the temp has been read

	double A0= 373.15/(273.15 + temperature);
	double SUM = -7.90298 * (A0-1);
	SUM += 5.02808 * log10(A0);
	SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
	SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
	SUM += log10(1013.246);
	double VP = pow(10, SUM-3) * humidity;
	double T = log(VP/0.61078);   // temp var
	return (241.88 * T) / (17.558-T);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dht11::dewPointFast()
{
	read();//make sure the temp has been read

	double a = 17.271;
	double b = 237.7;
	double temp = (a * temperature) / (b + temperature) + log((double) humidity/100);
	double Td = (b * temp) / (a - temp);
	return Td;
}
