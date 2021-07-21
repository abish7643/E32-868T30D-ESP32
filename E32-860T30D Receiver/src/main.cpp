/*
 * LoRa E32-TTL-100
 * Receive fixed transmission message as a specified point.
 * https://www.mischianti.org/2019/11/10/lora-e32-device-for-arduino-esp32-or-esp8266-fixed-transmission-part-4/
 *
 * E32-TTL-100----- ESP32 Pico Kit
 * M0         ----- 25
 * M1         ----- 26
 * TX         ----- 10
 * RX         ----- 9
 * AUX        ----- 23 / Connect to Negative of LED Pin
 * VCC        ----- 3.3v / 5v (5v for best performance, Refer Docs)
 * GND        ----- GND
 *
 */
#include <Arduino.h>
#include <LoRa_E32.h>
#include <HardwareSerial.h>

#define RX1 9
#define TX1 10

LoRa_E32 e32ttl(&Serial1, 23, 25, 26);

void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
	while (!Serial) {
	    ; // wait for serial port to connect. Needed for native USB
    }
	delay(100);

	e32ttl.begin();

	Serial.println();
	Serial.println("Start listening!");
}

// The loop function is called in an endless loop
void loop()
{
	if (e32ttl.available()  > 1){
		ResponseContainer rs = e32ttl.receiveMessage();
        // First of all get the data
		String message = rs.data;

		Serial.println(rs.status.getResponseDescription());
		Serial.println(message);
	}
}

void printParameters(struct Configuration configuration) {
	Serial.println("----------------------------------------");

	Serial.print(F("HEAD : "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
	Serial.println(F(" "));
	Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, DEC);
	Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, DEC);
	Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
	Serial.println(F(" "));
	Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
	Serial.print(F("SpeedUARTDatte  : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
	Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());

	Serial.print(F("OptionTrans        : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
	Serial.print(F("OptionPullup       : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
	Serial.print(F("OptionWakeup       : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
	Serial.print(F("OptionFEC          : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
	Serial.print(F("OptionPower        : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());

	Serial.println("----------------------------------------");

}
void printModuleInformation(struct ModuleInformation moduleInformation) {
	Serial.println("----------------------------------------");
	Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);

	Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
	Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	Serial.println("----------------------------------------");

}
