/*
  Countries.h - Library for mapping countries to leds
  Created by Michiel Bodewes, oktober 15, 2013
  Released into the public domain.
*/

#ifndef Arduino_h
#include "Arduino.h"
#endif


#ifndef Countries_h
#define Countries_h


class Countries
{
  public:
  	Countries();
	const char* getCityById(int id);
	const char* getCountryById(int id);

	//find index by name
	//find name by index
	//find countries by continent
	//find continent by country

  private:
	char _city_buffer[50];

};

#endif
