#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "config.h"


void i2c_scan(){
Serial.println(F("I2C scan:"));
Wire.begin();
for (uint8_t addr=1; addr<127; ++addr){
Wire.beginTransmission(addr);
uint8_t err = Wire.endTransmission();
if(err==0){ Serial.print(F(" - 0x")); Serial.println(addr, HEX); }
}
}


bool sd_init(){
Serial.print(F("SD init CS=")); Serial.println(PIN_SD_CS);
if(SD.begin(PIN_SD_CS)){
Serial.println(F("SD: OK"));
File root = SD.open("/");
while(true){
File f = root.openNextFile();
if(!f) break;
Serial.print(F(" ")); Serial.print(f.name());
if(f.isDirectory()) Serial.println(F("/")); else Serial.println();
f.close();
}
root.close();
return true;
}
Serial.println(F("SD: FAIL"));
return false;
}


void run_boot_checks(){ i2c_scan(); sd_init(); }