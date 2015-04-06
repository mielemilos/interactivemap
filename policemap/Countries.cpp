#include "Countries.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const char _city_00[] PROGMEM = "Tokio";       	//00
const char _city_01[] PROGMEM = "Ulan Bator";  	//01
const char _city_02[] PROGMEM = "Bangkok";     	//02
const char _city_03[] PROGMEM = "Quezon City"; 	//03
const char _city_04[] PROGMEM = "Jakarta";     	//04
const char _city_05[] PROGMEM = "Tennan Creek";	//05
const char _city_06[] PROGMEM = "Sydney";      	//06
const char _city_07[] PROGMEM = "Antarctica";  	//07
const char _city_08[] PROGMEM = "Xining";      	//08
const char _city_09[] PROGMEM = "Delhi";       	//09

const char _city_10[] PROGMEM = "Antananarivo";	//10
const char _city_11[] PROGMEM = "Johannesburg";	//11
const char _city_12[] PROGMEM = "Woestijn";    	//12
const char _city_13[] PROGMEM = "Cairo";       	//13
const char _city_14[] PROGMEM = "Tel-Aviv";    	//14
const char _city_15[] PROGMEM = "Ankara";      	//15
const char _city_16[] PROGMEM = "Moscow";      	//16
const char _city_17[] PROGMEM = "Rome";        	//17
const char _city_18[] PROGMEM = "Berlijn";     	//18
const char _city_19[] PROGMEM = "Winsum";  	   	//19

const char _city_20[] PROGMEM = "Parijs";      	//20
const char _city_21[] PROGMEM = "Londen";      	//21
const char _city_22[] PROGMEM = "Dublin";      	//22
const char _city_23[] PROGMEM = "Arhus";       	//23
const char _city_24[] PROGMEM = "Madrid";      	//24
const char _city_25[] PROGMEM = "Casablanca";  	//25
const char _city_26[] PROGMEM = "Buenos Aires";	//26
const char _city_27[] PROGMEM = "Lima";     	//27
const char _city_28[] PROGMEM = "Thunderbirds"; //28
const char _city_29[] PROGMEM = "Manaus";    	//29

const char _city_30[] PROGMEM = "Noordpool";   	//30
const char _city_31[] PROGMEM = "Santiago";   	//31
const char _city_32[] PROGMEM = "New York";  	//32
const char _city_33[] PROGMEM = "Toronto";   	//33
const char _city_34[] PROGMEM = "Franin City";  //34
const char _city_35[] PROGMEM = "Fairbanks"; 	//35 
const char _city_36[] PROGMEM = "Havana";    	//36
const char _city_37[] PROGMEM = "Panama City";  //37
const char _city_38[] PROGMEM = "Los Angeles";  //38
const char _city_39[] PROGMEM = "Mexico City";  //39
const char _city_40[] PROGMEM = "Ostersund";	//40

const char* _cities[] PROGMEM = {_city_00, _city_01, _city_02,
				_city_03, _city_04, _city_05, _city_06, _city_07, 
				_city_08, _city_09, _city_10, _city_11, _city_12,
				_city_13, _city_14, _city_15, _city_16, _city_17,
				_city_18, _city_19, _city_20, _city_21, _city_22,
				_city_23, _city_24, _city_25, _city_26, _city_27,
				_city_28, _city_29, _city_30, _city_31, _city_32,
				_city_33, _city_34, _city_35, _city_36, _city_37,
				_city_38, _city_39, _city_40
			};


/*
	const char* _countries[35] = { 
*/
const char _country_00[] PROGMEM = "Japan";		//00
const char _country_01[] PROGMEM = "Mongolie";	//01
const char _country_02[] PROGMEM = "Thailand";	//02
const char _country_03[] PROGMEM = "Filipijnen";//03
const char _country_04[] PROGMEM = "Indonesie";	//04
const char _country_05[] PROGMEM = "Australie";	//05
// 06 == 05
const char _country_07[] PROGMEM = "Antarctica";//07
const char _country_08[] PROGMEM = "China";		//08
const char _country_09[] PROGMEM = "India";		//09

const char _country_11[] PROGMEM = "Canada"; 	//00
const char _country_12[] PROGMEM = "Amerika";	//01
const char _country_13[] PROGMEM = "Mexico";	//02
const char _country_14[] PROGMEM = "Cuba";		//03
const char _country_15[] PROGMEM = "Panama"; 	//04
const char _country_16[] PROGMEM = "Ecudor";	//05
const char _country_17[] PROGMEM = "Brazilie"; 	//06
const char _country_18[] PROGMEM = "Peru";		//07
const char _country_19[] PROGMEM = "Chili";		//08
const char _country_10[] PROGMEM = "Argentinie";//09
const char _country_21[] PROGMEM = "Zuid Africa";//10
const char _country_22[] PROGMEM = "Madagascar";//11
const char _country_23[] PROGMEM = "Marocco"; 	//12
const char _country_24[] PROGMEM = "Libie";		//13
const char _country_25[] PROGMEM = "Egypte";	//14
const char _country_26[] PROGMEM = 	"Israel"; 	//15
const char _country_27[] PROGMEM = "Turkije";	//16
const char _country_28[] PROGMEM = "Italie"; 	//17
const char _country_29[] PROGMEM = "Spanje"; 	//18
const char _country_30[] PROGMEM = 	"Frankrijk";//19
const char _country_31[] PROGMEM = "Engeland"; 	//20
const char _country_32[] PROGMEM = "Ierland";	//21
const char _country_33[] PROGMEM = "Nederland";	//22
const char _country_34[] PROGMEM = "Duitsland";	//23
const char _country_35[] PROGMEM = "Denemarken";//24
const char _country_36[] PROGMEM = "Zweden";	//25
const char _country_37[] PROGMEM = "Rusland";	//26



/*
const char* _continents[7] = { 
 	"Africa",
    "Europe",
    "Asia",
    "North America",
    "South America",
    "Antarctica",
    "Australia"
};
*/


Countries::Countries() {
}

const char* Countries::getCityById(int id) {
	if (id > 40) id = 40;
	if (id < 0) id = 0;

	strcpy_P(_city_buffer, (char*)pgm_read_word(&(_cities[id]))); // Necessary casts and dereferencing, just copy. 

	return _city_buffer;
}

const char* Countries::getCountryById(int id) {
	if (id > 40) id = 40;
	if (id < 0) id = 0;

	strcpy_P(_city_buffer, (char*)pgm_read_word(&(_cities[id]))); // Necessary casts and dereferencing, just copy. 

	return _city_buffer;
}
