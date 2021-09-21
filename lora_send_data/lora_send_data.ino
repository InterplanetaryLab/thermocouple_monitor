#include <SPI.h>
#include <LoRa.h>

// LoRa config vars
#define SS 8
#define RST 4
#define DIO0 7
#define SPREAD_FACTOR 10
#define CENTER_FREQ 437E6
#define BANDWIDTH 62.5E3
#define TX_POWER 4

//function predefinitions
void lora_init();
void lora_transmit();

void lora_init()
{
	LoRa.setPins(SS, RST, DIO0);

	if (!LoRa.begin(CENTER_FREQ)) { // loop until lora initializes properly
		Serial.println("Starting LoRa failed!");
		while (1);
	}
}
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

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  Serial.println("t-vac lora logger");

  pinMode(LED_BUILTIN, OUTPUT);
}



void loop() {
 
}
