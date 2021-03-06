#include "thermistor-library.h"

Thermistor::Thermistor(int pin, int resistor) {
	_pin = pin;
	_resistor = resistor;
}


void Thermistor::begin(void) {
	pinMode(_pin, INPUT);
}


int Thermistor::getTempRaw(bool smooth) {
	delay(1);
	
	if(smooth==true) {
		int total = 0;
		
		for(int i=0; i<100; i++) {
			total += analogRead(_pin);
			delay(1);
		}
		
		_temp_raw = total/100;
	} else
		_temp_raw = analogRead(_pin);
		
	Serial.print("Temp Raw: ");
	Serial.println(_temp_raw);

	return _temp_raw;
}


float Thermistor::getTempK(bool smooth) {
	_temp_raw = getTempRaw(smooth);

	_temp_k = log(((40960000/_temp_raw) - _resistor));
	_temp_k = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * _temp_k * _temp_k ))* _temp_k);
	
	Serial.print("Temp K: ");
	Serial.println(_temp_k);
	
	return _temp_k;
}


float Thermistor::getTempC(bool smooth) {
	_temp_k = getTempK(smooth);
	
	_temp_c = _temp_k - 273.15;

	Serial.print("Temp C: ");
	Serial.println(_temp_c);
	
	return _temp_c;
}


float Thermistor::getTempF(bool smooth) {
	_temp_c = getTempC(smooth);
	
	_temp_f = (_temp_c * 9.0)/ 5.0 + 32.0;

	Serial.print("Temp F: ");
	Serial.println(_temp_f);
	
	return _temp_f;
}


float Thermistor::getTemp(bool smooth) {
	return getTempC(smooth);
}
