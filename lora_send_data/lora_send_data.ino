#include <SPI.h>
#include <LoRa.h>

// LoRa config vars
#define SS 8
#define RST 4
#define DIO0 7
#define SPREAD_FACTOR 10
#define CENTER_FREQ 437.5E6
#define BANDWIDTH 62.5E3
#define TX_POWER 4

//MAX31855 config vars
#define SS_1 12
#define SS_2 11

//function predefinitions
void lora_init();
void lora_transmit();

void setup() {
	Serial.begin(9600);
	//while (!Serial);

	Serial.println("t-vac lora logger");
	lora_init();

	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	lora_transmit(); 
	delay(500);
}

// lora_section inits using the given config pins does a test begin to make sure the lora radio is works properly
void lora_init()
{
	LoRa.setPins(SS, RST, DIO0);

	if (!LoRa.begin(CENTER_FREQ)) { // loop until lora initializes properly
		Serial.println("Starting LoRa failed!");
		while (1);
	}
} 
//for now just transmitting the string literal "test"
void lora_transmit()
{
	LoRa.begin(CENTER_FREQ);
	LoRa.setSpreadingFactor(SPREAD_FACTOR);
	LoRa.setSignalBandwidth(BANDWIDTH);
	LoRa.enableCrc();
	LoRa.setTxPower(TX_POWER);
	Serial.print("Sending packet: ");
	LoRa.beginPacket();
	LoRa.print("test");
	LoRa.endPacket();
}
