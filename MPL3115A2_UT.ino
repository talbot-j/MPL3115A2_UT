//------------------------------------------------------------------------------
/// @addtogroup MPL3115A2 Unit Test
///
/// @file MPL3115A2_UT.ino
///
/// @author     Joshua R. Talbot
///
/// @date       02-FEB-18
///
/// @version    1.0 - initial release
///
/// @license
/// MIT License
/// 
/// Copyright (c) 2018 J. Talbot
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
///
/// @brief      This is the non-exhaustive test for the HTU21D driver.  More
///             tests to come...
///

#include <Wire.h>

#include "MPL3115A2.h"

MPL3115A2 baro = MPL3115A2();

void setup() {
	
	Serial.begin(9600);

	Serial.println("MPL3115A2.c test!");
    if ( baro.init( true ) ){
        Serial.println("MPL3115A2 init'd!");
        baro.setPressure_Mode();
    }
    else {
    	Serial.println("\n\nERR: MPL3115A2 Sensor FAILED Init!");
        while(1);
    }
}

void loop() {
	uint32_t pressure;
    float temp_c, temp_f;
	
	Serial.println("--------  MPL3115A2  -----------");
    if ( baro.getPressure( &pressure ) ) {
        Serial.println("Raw Pressure: ");
        Serial.println(pressure);
        float f_press = pressure;
        f_press /= 4.0;
        Serial.println("Float Pressure (take 1): ");
        Serial.print(f_press);Serial.println(" pascals.");
        Serial.print(f_press/3386.38); Serial.println(" Inches (Hg)");
    }

    Serial.println("Float Pressure (take 2): ");
    Serial.print(baro.getPressure_Pa());Serial.println(" pascals.");
    Serial.print(baro.getPressure_InHg()); Serial.println(" Inches (Hg)");

    float tempC = baro.getTemperature();
    Serial.print(tempC); Serial.println("*C");

    float tempF = tempC * 9/5 + 32;
    Serial.print(tempF); Serial.println("*F");

    delay(1000);
}